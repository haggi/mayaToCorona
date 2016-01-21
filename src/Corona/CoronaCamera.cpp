#include "Corona.h"
#include "CoronaCamera.h"
#include <maya/MPoint.h>
#include <maya/MFnCamera.h>
#include "renderGlobals.h"
#include "utilities/logging.h"
#include "../mtco_common/mtco_mayaObject.h"
#include "mayaScene.h"
#include "utilities/tools.h"
#include "utilities/attrTools.h"
#include "world.h"

static Logging logger;

void updateCamera(Corona::CameraData& cameraData, MObject& cameraObject, const MMatrix& matrix, float deviceAspect)
{
	//MVector cameraUpVector(0.0, 1.0, 0.0);
	MVector cameraUpVector(0.0, -1.0, 0.0);
	MFnCamera camFn(cameraObject);
	MPoint pos, rot, scale;
	MMatrix camMatrix = matrix * MayaTo::getWorldPtr()->globalConversionMatrix;
	cameraUpVector *= camMatrix;
	cameraUpVector.normalize();
	Corona::Dir upVector(cameraUpVector.x, cameraUpVector.y, cameraUpVector.z);
	getMatrixComponents(camMatrix, pos, rot, scale);
	Corona::Pos cpos(pos.x, pos.y, pos.z);

	float horizontalFilmAperture = getFloatAttr("horizontalFilmAperture", camFn, 1.0f);
	float verticalFilmAperture = getFloatAttr("verticalFilmAperture", camFn, 35.0f);
	float focalLength = getFloatAttr("focalLength", camFn, 55.0f);
	bool dof = getBoolAttr("depthOfField", camFn, false);
	float focusDistance = getFloatAttr("focusDistance", camFn, 100.f);
	float fStop = getFloatAttr("fStop", camFn, 5.6f);
	float coi = getFloatAttr("centerOfInterest", camFn, 100.0f);
	focusDistance *= MayaTo::getWorldPtr()->scaleFactor;
	MPoint coiBase(0, 0, -coi);
	MPoint coiTransform = coiBase * camMatrix;
	Corona::Pos center(coiTransform.x, coiTransform.y, coiTransform.z);
	float factor = horizontalFilmAperture;
	float fov = 2.0 * atan((factor * 0.5f) / (focalLength * 0.03937)); // make horizontal film fit the default
	MFnCamera::FilmFit filmFit = camFn.filmFit();
	float dAspect = deviceAspect;
	double fAspect = horizontalFilmAperture / verticalFilmAperture;

	switch (filmFit)
	{
		case  MFnCamera::kHorizontalFilmFit:
		{
			fov = 2.0 * atan((factor * 0.5f) / (focalLength * 0.03937));
		}
		break;

		case  MFnCamera::kVerticalFilmFit:
		{
			factor = verticalFilmAperture * dAspect;
			fov = 2.0 * atan((factor * 0.5f) / (focalLength * 0.03937));
		}
		break;

		case  MFnCamera::kFillFilmFit:
		{}
		break;

		case  MFnCamera::kOverscanFilmFit:
		{}
		break;

		default:
			break;
	}

	float fovDeg = fov * 57.29578;
	Corona::AnimatedFloat fieldOfView(fov);
	bool orthographic = getBoolAttr("orthographic", camFn, false);

	if (orthographic)
	{
		Corona::AnimatedAffineTm tm;
		tm.setSegments(0);
		tm[0] = Corona::AffineTm::IDENTITY;
		cameraData.createOrtho(tm, 10.0f);
	}
	else{
		cameraData.createPerspective(Corona::AnimatedPos(cpos), Corona::AnimatedPos(center), Corona::AnimatedDir(upVector), fieldOfView);
	}
	cameraData.spherical.roll = Corona::AnimatedDir(upVector);
	cameraData.cylindrical.roll = Corona::AnimatedDir(upVector);
	cameraData.cylindrical.height = 1.0f;
	int projType = getEnumInt("mtco_cameraType", camFn);
	//CameraProjectionType
	cameraData.type = Corona::PROJECTION_PERSPECTIVE;
	if (projType == 1)
		cameraData.type = Corona::PROJECTION_CYLINDRICAL;
	if (projType == 2)
		cameraData.type = Corona::PROJECTION_SPHERICAL;

	Corona::AnimatedFloat focalDist(focusDistance);
	cameraData.perspective.focalDist = focalDist;
	cameraData.perspective.fStop = fStop;
	cameraData.perspective.filmWidth = MayaTo::getWorldPtr()->toMillimeters(horizontalFilmAperture * 2.54f * 10.0f); //film width in mm 

	if (!getBoolAttr("bestFitClippingPlanes", camFn, false))
	{
		cameraData.distances.minimal = getFloatAttr("nearClipPlane", camFn, 0.001f) * MayaTo::getWorldPtr()->scaleFactor;
		cameraData.distances.maximal = getFloatAttr("farClipPlane", camFn, 100000.0f) * MayaTo::getWorldPtr()->scaleFactor;
	}

	if (getBoolAttr("mtco_useBokeh", camFn, false))
	{
		cameraData.perspective.bokeh.use = true;
		cameraData.perspective.bokeh.blades = getIntAttr("mtco_blades", camFn, 6);
		cameraData.perspective.bokeh.bladesRotation = getIntAttr("mtco_bladeRotation", camFn, 0.0);
		MPlug bokehBitMapPlug = camFn.findPlug("mtco_bokehBitmap");
		if (!bokehBitMapPlug.isNull())
		{
			if (bokehBitMapPlug.isConnected())
			{
				MObject bitmapNode = getConnectedInNode(bokehBitMapPlug);
				if (bitmapNode.hasFn(MFn::kFileTexture))
				{
					MFnDependencyNode bitMapFn(bitmapNode);
					MPlug texNamePlug = bitMapFn.findPlug("fileTextureName");
					if (!texNamePlug.isNull())
					{
						MString fileName = texNamePlug.asString();
						Logging::debug(MString("Found bokeh bitmap file: ") + fileName);
						Corona::Bitmap<Corona::Rgb> bokehBitmap;
						Corona::loadImage(fileName.asChar(), bokehBitmap);
						cameraData.perspective.bokeh.customShape = bokehBitmap;
					}
				}
			}
		}
	}
}


void CoronaRenderer::updateCamera(std::shared_ptr<MayaObject> cam)
{
	std::shared_ptr<MayaScene> mayaScene = MayaTo::getWorldPtr()->worldScenePtr;
	std::shared_ptr<RenderGlobals> renderGlobals = MayaTo::getWorldPtr()->worldRenderGlobalsPtr;
	MFnDependencyNode rgFn(getRenderGlobalsNode());

	Logging::debug(MString("using camera ") + cam->shortName);
	MVector cameraUpVector(0.0, 1.0, 0.0);
	MFnCamera camera(cam->mobject);
	MPoint pos, rot, scale;
	
	MMatrix camMatrix = cam->transformMatrices[0] * renderGlobals->globalConversionMatrix;
	if (MayaTo::getWorldPtr()->getRenderType() == MayaTo::MayaToWorld::WorldRenderType::IPRRENDER)
		camMatrix = cam->dagPath.inclusiveMatrix()  * renderGlobals->globalConversionMatrix;
	cameraUpVector *= camMatrix;
	cameraUpVector.normalize();
	Corona::Dir upVector(cameraUpVector.x, cameraUpVector.y, cameraUpVector.z);
	getMatrixComponents(camMatrix, pos, rot, scale);
	Corona::Pos cpos(pos.x, pos.y, pos.z);

	float focusDistance = 0.0;
	float fStop = 0.0;

	float focalLength = 35.0f;
	bool dof;
	float horizontalFilmAperture, verticalFilmAperture;
	float coi = 100.0f;
	getFloat(MString("horizontalFilmAperture"), camera, horizontalFilmAperture);
	getFloat(MString("verticalFilmAperture"), camera, verticalFilmAperture);
	getFloat(MString("focalLength"), camera, focalLength);
	getBool(MString("depthOfField"), camera, dof);
	getFloat(MString("focusDistance"), camera, focusDistance);
	getFloat(MString("fStop"), camera, fStop);
	getFloat(MString("centerOfInterest"), camera, coi);

	focusDistance *= renderGlobals->scaleFactor;

	MPoint coiBase(0, 0, -coi);
	MPoint coiTransform = coiBase * camMatrix;
	//Logging::debug(MString("Center of interest: ") + coi + " transformed " + coiTransform.x + " "  + coiTransform.y + " "  + coiTransform.z);
	Corona::Pos center(coiTransform.x, coiTransform.y, coiTransform.z);
	float factor = horizontalFilmAperture;
	float fov = 2.0 * atan((factor * 0.5f) / (focalLength * 0.03937)); // make horizontal film fit the default
	MFnCamera::FilmFit filmFit = camera.filmFit();
	float dAspect = (float)renderGlobals->getWidth() / (float)renderGlobals->getHeight();
	double fAspect = horizontalFilmAperture / verticalFilmAperture;

	switch (filmFit)
	{
	case  MFnCamera::kHorizontalFilmFit:
	{
		fov = 2.0 * atan((factor * 0.5f) / (focalLength * 0.03937));
	}
	break;

	case  MFnCamera::kVerticalFilmFit:
	{
		factor = verticalFilmAperture * dAspect;
		fov = 2.0 * atan((factor * 0.5f) / (focalLength * 0.03937));
	}
	break;

	case  MFnCamera::kFillFilmFit:
	{}
	break;

	case  MFnCamera::kOverscanFilmFit:
	{}
	break;

	default:
		break;
	}

	float fovDeg = fov * 57.29578;
	Corona::AnimatedFloat fieldOfView(fov);
	Corona::CameraData cameraData;
	bool orthographic = getBoolAttr("orthographic", camera, false);

	if (orthographic)
	{
		cameraData.createOrtho(Corona::AnimatedAffineTm(), 10.0f);
	}
	else{
		cameraData.createPerspective(Corona::AnimatedPos(cpos), Corona::AnimatedPos(center), Corona::AnimatedDir(upVector), fieldOfView);
	}
	cameraData.spherical.roll = Corona::AnimatedDir(upVector);
	cameraData.cylindrical.roll = Corona::AnimatedDir(upVector);
	cameraData.cylindrical.height = 1.0f;
	int projType = getEnumInt("mtco_cameraType", camera);
	//CameraProjectionType
	cameraData.type = Corona::PROJECTION_PERSPECTIVE;
	if (projType == 1)
		cameraData.type = Corona::PROJECTION_CYLINDRICAL;
	if (projType == 2)
		cameraData.type = Corona::PROJECTION_SPHERICAL;

	Corona::AnimatedFloat focalDist(focusDistance);
	cameraData.perspective.focalDist = focalDist;
	cameraData.perspective.fStop = fStop;
	cameraData.perspective.filmWidth = renderGlobals->toMillimeters(horizontalFilmAperture * 2.54f * 10.0f); //film width in mm 
	if (dof && getBoolAttr("doDof", rgFn, false))
		cameraData.perspective.useDof = true;

	if (!getBoolAttr("bestFitClippingPlanes", camera, false))
	{
		cameraData.distances.minimal = getFloatAttr("nearClipPlane", camera, 0.001f) * renderGlobals->scaleFactor;
		cameraData.distances.maximal = getFloatAttr("farClipPlane", camera, 100000.0f) * renderGlobals->scaleFactor;
	}

	if (getBoolAttr("mtco_useBokeh", camera, false))
	{
		cameraData.perspective.bokeh.use = true;
		cameraData.perspective.bokeh.blades = getIntAttr("mtco_blades", camera, 6);
		cameraData.perspective.bokeh.bladesRotation = getIntAttr("mtco_bladeRotation", camera, 0.0);
		MPlug bokehBitMapPlug = camera.findPlug("mtco_bokehBitmap");
		if (!bokehBitMapPlug.isNull())
		{
			if (bokehBitMapPlug.isConnected())
			{
				MObject bitmapNode = getConnectedInNode(bokehBitMapPlug);
				if (bitmapNode.hasFn(MFn::kFileTexture))
				{
					MFnDependencyNode bitMapFn(bitmapNode);
					MPlug texNamePlug = bitMapFn.findPlug("fileTextureName");
					if (!texNamePlug.isNull())
					{
						MString fileName = texNamePlug.asString();
						Logging::debug(MString("Found bokeh bitmap file: ") + fileName);
						Corona::Bitmap<Corona::Rgb> bokehBitmap;
						Corona::loadImage(fileName.asChar(), bokehBitmap);
						cameraData.perspective.bokeh.customShape = bokehBitmap;
					}
				}
			}
		}
	}

	this->context.scene->getCamera() = cameraData;
	this->renderCam = cam->mobject;
	updateCameraFbCallback(cam->mobject);
}


void CoronaRenderer::defineCamera()
{
	MPoint rot, pos, scale;
	std::shared_ptr<MayaScene> mayaScene = MayaTo::getWorldPtr()->worldScenePtr;
	std::shared_ptr<RenderGlobals> renderGlobals = MayaTo::getWorldPtr()->worldRenderGlobalsPtr;

	for (auto cam : mayaScene->camList)
	{
		if (!isCameraRenderable(cam->mobject) && (!(cam->dagPath == mayaScene->uiCamera)))
		{	
			continue;
		}

		updateCamera(cam);
	}

}
