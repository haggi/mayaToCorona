#include "CoronaSurfaceMaterial.h"

#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnLightDataAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFloatVector.h>
#include <maya/MGlobal.h>
#include <maya/MDrawRegistry.h>
#include <maya/MDGModifier.h>
#include <maya/MFnDependencyNode.h>

// IFF type ID
// Each node requires a unique identifier which is used by
// MFnDependencyNode::create() to identify which node to create, and by
// the Maya file format.
//
// For local testing of nodes you can use any identifier between
// 0x00000000 and 0x0007ffff, but for any node that you plan to use for
// more permanent purposes, you should get a universally unique id from
// Autodesk Support. You will be assigned a unique range that you
// can manage on your own.
//
MTypeId	CoronaSurface::id( 0x0011CF57 );


// the postConstructor() function is called immediately after the objects
// constructor. It is not safe to call MPxNode member functions from the
// constructor, instead they should be called here.
//
void CoronaSurface::postConstructor( )
{
    // setMPSafe indicates that this shader can be used for multiprocessor
    // rendering. For a shading node to be MP safe, it cannot access any
    // shared global data and should only use attributes in the datablock
    // to get input data and store output data.
    //
	MStatus stat;
	setMPSafe( true );
	this->setExistWithoutInConnections(true);

	//MFnDependencyNode depFn(this->thisMObject());
	//if (depFn.findAlias("diffuse", diffuse))
	//{
	//	MGlobal::displayInfo("Found alias.");
	//}
	//else{
	//	depFn.setAlias("diffuse", "color", MPlug(depFn.findPlug("color")));
	//	MGlobal::displayInfo("Set alias.");
	//}
}


// DESCRIPTION: attribute information
//
MObject  CoronaSurface::aTranslucenceCoeff;
MObject  CoronaSurface::aDiffuseReflectivity;
MObject  CoronaSurface::aInTransparency;
MObject  CoronaSurface::aOutColor;
MObject  CoronaSurface::aOutTransparency;
MObject  CoronaSurface::aNormalCamera;
MObject  CoronaSurface::aNormalCameraX;
MObject  CoronaSurface::aNormalCameraY;
MObject  CoronaSurface::aNormalCameraZ;
MObject  CoronaSurface::aLightData;
MObject  CoronaSurface::aLightDirection;
MObject  CoronaSurface::aLightDirectionX;
MObject  CoronaSurface::aLightDirectionY;
MObject  CoronaSurface::aLightDirectionZ;
MObject  CoronaSurface::aLightIntensity;
MObject  CoronaSurface::aLightIntensityR;
MObject  CoronaSurface::aLightIntensityG;
MObject  CoronaSurface::aLightIntensityB;
MObject  CoronaSurface::aLightAmbient;
MObject  CoronaSurface::aLightDiffuse;
MObject  CoronaSurface::aLightSpecular;
MObject  CoronaSurface::aLightShadowFraction;
MObject  CoronaSurface::aPreShadowIntensity;
MObject  CoronaSurface::aLightBlindData;

MObject CoronaSurface::opacity;
MObject CoronaSurface::opacityMultiplier;
MObject CoronaSurface::emissionMultiplier;
MObject CoronaSurface::volumeScatteringAlbedo;
MObject CoronaSurface::fresnelIor;
MObject CoronaSurface::fresnelIorMap;
MObject CoronaSurface::roundCornersSamples;
MObject CoronaSurface::emissionSharpnessFakePoint;
MObject CoronaSurface::glassMode;
MObject CoronaSurface::attenuationColor;
MObject CoronaSurface::emissionSharpnessFake;
MObject CoronaSurface::reflectivity;
MObject CoronaSurface::reflectivityMultiplier;
MObject CoronaSurface::castsShadows;
MObject CoronaSurface::translucency;
MObject CoronaSurface::translucencyFraction;
MObject CoronaSurface::volumeEmissionColor;
MObject CoronaSurface::anisotropyRotation;
MObject CoronaSurface::reflectionGlossiness;
MObject CoronaSurface::volumeEmissionDist;
MObject CoronaSurface::roundCornersRadius;
MObject CoronaSurface::roundCornersMultiplier;
MObject CoronaSurface::bgOverride;
MObject CoronaSurface::refractionGlossiness;
MObject CoronaSurface::refractionIndex;
MObject CoronaSurface::refractionIndexMap;
MObject CoronaSurface::diffuse;
MObject CoronaSurface::diffuseMultiplier;
MObject CoronaSurface::refractivity;
MObject CoronaSurface::refractivityMultiplier;
MObject CoronaSurface::emissionColor;
MObject CoronaSurface::shadowCatcherMode;
MObject CoronaSurface::anisotropy;
MObject CoronaSurface::volumeMeanCosine;
MObject CoronaSurface::emissionDisableSampling;
MObject CoronaSurface::alphaMode;
MObject CoronaSurface::attenuationDist;
MObject CoronaSurface::volumeSSSMode;
MObject CoronaSurface::glassType;
MObject CoronaSurface::iesProfile;
MObject CoronaSurface::singleScatteringOnly;
MObject CoronaSurface::roundCornersMap;


// This node does not need to perform any special actions on creation or
// destruction
//

CoronaSurface::CoronaSurface() { }
CoronaSurface::~CoronaSurface() { }


// The creator() method allows Maya to instantiate instances of this node.
// It is called every time a new instance of the node is requested by
// either the createNode command or the MFnDependencyNode::create()
// method.
//
// In this case creator simply returns a new CoronaSurface object.
//

void* CoronaSurface::creator()
{
    return new CoronaSurface();
}

MStatus CoronaSurface::initialize()
{
	MFnNumericAttribute nAttr;
	MFnLightDataAttribute lAttr;
	MFnTypedAttribute tAttr;
	MFnGenericAttribute gAttr;
	MFnEnumAttribute eAttr;
	MFnMessageAttribute mAttr;

    MStatus status; 

	diffuse = nAttr.createColor("diffuse", "diffuse");
	nAttr.setKeyable(true);
	nAttr.setDefault(0.5, 0.5, 0.5);
	CHECK_MSTATUS(addAttribute(diffuse));

	diffuseMultiplier = nAttr.create("diffuseMultiplier", "diffuseMultiplier", MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(diffuseMultiplier));

	translucencyFraction = nAttr.create("translucencyFraction", "translucencyFraction", MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	CHECK_MSTATUS(addAttribute(translucencyFraction));

	opacity = nAttr.createColor("opacity", "opacity");
	nAttr.setDefault(1.0,1.0,1.0);
	nAttr.setKeyable(true);
	CHECK_MSTATUS(addAttribute( opacity ));

	opacityMultiplier = nAttr.create("opacityMultiplier", "opacityMultiplier", MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	//nAttr.setKeyable(true);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(opacityMultiplier));

	emissionMultiplier = nAttr.create("emissionColorMultiplier", "emissionColorMultiplier", MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(emissionMultiplier));

	reflectivityMultiplier = nAttr.create("reflectivityMultiplier", "reflectivityMultiplier", MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(reflectivityMultiplier));

	refractivityMultiplier = nAttr.create("refractivityMultiplier", "refractivityMultiplier", MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(refractivityMultiplier));

	volumeScatteringAlbedo = nAttr.createColor("volumeScatteringAlbedo", "volumeScatteringAlbedo");
	nAttr.setDefault(0.5,0.5,0.5);
	CHECK_MSTATUS(addAttribute( volumeScatteringAlbedo ));

	fresnelIor = nAttr.create("fresnelIorMultiplier", "fresnelIorMultiplier",  MFnNumericData::kFloat, 1.52);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(2.0);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(fresnelIor));

	fresnelIorMap = nAttr.createColor("fresnelIor", "fresnelIor");
	nAttr.setDefault(1.0, 1.0, 1.0);
	CHECK_MSTATUS(addAttribute(fresnelIorMap));

	roundCornersSamples = nAttr.create("roundCornersSamples", "roundCornersSamples",  MFnNumericData::kInt, 10);
	nAttr.setMin(1);
	nAttr.setSoftMax(20);
	CHECK_MSTATUS(addAttribute( roundCornersSamples ));

	glassMode = eAttr.create("glassMode", "glassMode", 0, &status);
	status = eAttr.addField( "OneSided", 0 );
	status = eAttr.addField( "TwoSided", 1 );
	status = eAttr.addField( "Hybrid", 2 );
	CHECK_MSTATUS(addAttribute( glassMode ));

	glassType = eAttr.create("glassType", "glassType", 0, &status);
	status = eAttr.addField("Transparent Shadows (fast)", 0);
	status = eAttr.addField("Caustic (slow)", 1);
	status = eAttr.addField("ThinFilm (fast)", 2);
	CHECK_MSTATUS(addAttribute(glassType));	

	attenuationColor = nAttr.createColor("attenuationColor", "attenuationColor");
	nAttr.setDefault(0,0,0);
	CHECK_MSTATUS(addAttribute( attenuationColor ));

	emissionSharpnessFake = nAttr.create("emissionSharpnessFake", "emissionSharpnessFake",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( emissionSharpnessFake ));

	reflectivity = nAttr.createColor("reflectivity", "reflectivity");
	nAttr.setKeyable(true);
	nAttr.setDefault(1.0, 1.0, 1.0);
	CHECK_MSTATUS(addAttribute( reflectivity ));

	castsShadows = nAttr.create("castsShadows", "castsShadows",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( castsShadows ));

	translucency = nAttr.createColor("translucency", "translucency");
	nAttr.setKeyable(true);
	nAttr.setDefault(1.0, 1.0, 1.0);
	CHECK_MSTATUS(addAttribute( translucency ));

	volumeEmissionColor = nAttr.createColor("volumeEmissionColor", "volumeEmissionColor");
	nAttr.setDefault(0,0,0);
	CHECK_MSTATUS(addAttribute( volumeEmissionColor ));

	anisotropyRotation = nAttr.create("anisotropicRotation", "anisotropicRotation",  MFnNumericData::kFloat, 0.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	CHECK_MSTATUS(addAttribute(anisotropyRotation));

	reflectionGlossiness = nAttr.create("reflectionGlossiness", "reflectionGlossiness",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute(reflectionGlossiness));

	volumeEmissionDist = nAttr.create("volumeEmissionDist", "volumeEmissionDist",  MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(10.0);
	CHECK_MSTATUS(addAttribute( volumeEmissionDist ));

	roundCornersRadius = nAttr.create("roundCornersRadius", "roundCornersRadius",  MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(5.0);
	CHECK_MSTATUS(addAttribute(roundCornersRadius));

	roundCornersMultiplier = nAttr.create("roundCornersRadiusMultiplier", "roundCornersRadiusMultiplier", MFnNumericData::kFloat, 0.001);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(1.0);
	CHECK_MSTATUS(addAttribute(roundCornersMultiplier));
	

	bgOverride = nAttr.createColor("bgOverride", "bgOverride");
	nAttr.setDefault(0,0,0);
	CHECK_MSTATUS(addAttribute( bgOverride ));

	refractionGlossiness = nAttr.create("refractionGlossiness", "refractionGlossiness",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute(refractionGlossiness));

	refractivity = nAttr.createColor("refractivity", "refractivity");
	nAttr.setKeyable(true);
	nAttr.setDefault(1.0, 1.0, 1.0);
	CHECK_MSTATUS(addAttribute( refractivity ));

	//brdfType = eAttr.create("brdfType", "brdfType", 0, &status);
	//status = eAttr.addField( "Ashikmin", 0 );
	//status = eAttr.addField( "Phong", 1 );
	//CHECK_MSTATUS(addAttribute( brdfType ));

	emissionColor = nAttr.createColor("emissionColor", "emissionColor");
	nAttr.setKeyable(true);
	nAttr.setDefault(1.0, 1.0, 1.0);
	CHECK_MSTATUS(addAttribute( emissionColor ));

	shadowCatcherMode = eAttr.create("shadowCatcherMode", "shadowCatcherMode", 0, &status);
	status = eAttr.addField( "Off", 0 );
	status = eAttr.addField( "Final", 1 );
	status = eAttr.addField( "Composite", 2 );
	CHECK_MSTATUS(addAttribute( shadowCatcherMode ));

	anisotropy = nAttr.create("anisotropy", "anisotropy",  MFnNumericData::kFloat, 0.5);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute(anisotropy));

	volumeMeanCosine = nAttr.create("volumeMeanCosine", "volumeMeanCosine",  MFnNumericData::kFloat, 0.0);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(1.0);
	CHECK_MSTATUS(addAttribute(volumeMeanCosine));

	refractionIndex = nAttr.create("refractionIndexMultiplier", "refractionIndexMultiplier",  MFnNumericData::kFloat, 1.52);
	nAttr.setSoftMin(0.0);
	nAttr.setSoftMax(2.0);
	nAttr.setConnectable(false);
	CHECK_MSTATUS(addAttribute(refractionIndex));

	refractionIndexMap = nAttr.createColor("refractionIndex", "refractionIndex");
	nAttr.setDefault(1.0, 1.0, 1.0);
	CHECK_MSTATUS(addAttribute(refractionIndexMap));

	emissionDisableSampling = nAttr.create("emissionDisableSampling", "emissionDisableSampling",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( emissionDisableSampling ));

	alphaMode = eAttr.create("alphaMode", "alphaMode", 0, &status);
	status = eAttr.addField( "Default", 0 );
	status = eAttr.addField( "Solid", 1 );
	status = eAttr.addField( "Transparent", 2 );
	CHECK_MSTATUS(addAttribute( alphaMode ));

	attenuationDist = nAttr.create("attenuationDist", "attenuationDist",  MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setSoftMax(10.0);
	CHECK_MSTATUS(addAttribute(attenuationDist));

	volumeSSSMode = nAttr.create("volumeSSSMode", "volumeSSSMode", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(volumeSSSMode));

	singleScatteringOnly = nAttr.create("singleScatteringOnly", "singleScatteringOnly", MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute(singleScatteringOnly));

	//MObject roundCornersMapX = nAttr.create("roundCornersMapX", "roundCornersMapX", MFnNumericData::kFloat);
	//CHECK_MSTATUS(addAttribute(roundCornersMapX));
	//MObject roundCornersMapY = nAttr.create("roundCornersMapY", "roundCornersMapY", MFnNumericData::kFloat);
	//CHECK_MSTATUS(addAttribute(roundCornersMapY));
	//MObject roundCornersMapZ = nAttr.create("roundCornersMapZ", "roundCornersMapZ", MFnNumericData::kFloat);
	//CHECK_MSTATUS(addAttribute(roundCornersMapZ));

	roundCornersMap = nAttr.createPoint("roundCornersMap", "roundCornersMap");
	CHECK_MSTATUS(addAttribute(roundCornersMap));

	//---------------------------- automatically created attributes end ------------------------------------

	iesProfile = tAttr.create("iesProfile", "iesProfile", MFnNumericData::kString);
	tAttr.setUsedAsFilename(true);
	CHECK_MSTATUS(addAttribute(iesProfile));

    // Input Attributes
    //
    aTranslucenceCoeff = nAttr.create( "translucenceCoeff", "tc",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.0f ) );

    aDiffuseReflectivity = nAttr.create( "diffuseReflectivity", "drfl",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.8f ) );

 //   aColor = nAttr.createColor( "color", "c", &status );
 //   CHECK_MSTATUS( status );
	//CHECK_MSTATUS( nAttr.setHidden( true ) );
 //   CHECK_MSTATUS( nAttr.setKeyable( true ) );
 //   CHECK_MSTATUS( nAttr.setStorable( true ) );
 //   CHECK_MSTATUS( nAttr.setDefault( 0.0f, 0.58824f, 0.644f ) );

 //   aIncandescence = nAttr.createColor( "incandescence", "ic", &status );
 //   CHECK_MSTATUS( status );
	//CHECK_MSTATUS( nAttr.setHidden( true ) );
 //   CHECK_MSTATUS( nAttr.setKeyable( true ) );
 //   CHECK_MSTATUS( nAttr.setStorable( true ) );
 //   CHECK_MSTATUS( nAttr.setDefault( 0.0f, 0.0f, 0.0f ) );

    aInTransparency = nAttr.createColor( "transparency", "it", &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.0f, 0.0f, 0.0f ) );

    // Color Output
    
    aOutColor = nAttr.createColor( "outColor", "oc", &status );
    CHECK_MSTATUS( status );

    CHECK_MSTATUS( nAttr.setHidden( false ) );
    CHECK_MSTATUS( nAttr.setReadable( true ) );
    CHECK_MSTATUS( nAttr.setWritable( false ) );

    aOutTransparency = nAttr.createColor( "outTransparency", "ot", &status );
    CHECK_MSTATUS( status );

    CHECK_MSTATUS( nAttr.setHidden( false ) );
    CHECK_MSTATUS( nAttr.setReadable( true ) );
    CHECK_MSTATUS( nAttr.setWritable( false ) );

    // Camera Normals
    //
    aNormalCameraX = nAttr.create( "normalCameraX", "nx",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aNormalCameraY = nAttr.create( "normalCameraY", "ny",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aNormalCameraZ = nAttr.create( "normalCameraZ", "nz",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aNormalCamera = nAttr.create( "normalCamera","n", aNormalCameraX,
            aNormalCameraY, aNormalCameraZ, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f, 1.0f, 1.0f ) );
    CHECK_MSTATUS( nAttr.setHidden( true ) );


    // Light Direction
    //
    aLightDirectionX = nAttr.create( "lightDirectionX", "ldx",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightDirectionY = nAttr.create( "lightDirectionY", "ldy",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightDirectionZ = nAttr.create( "lightDirectionZ", "ldz",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightDirection = nAttr.create( "lightDirection", "ld",
            aLightDirectionX, aLightDirectionY, aLightDirectionZ,
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f, 1.0f, 1.0f ) );


    // Light Intensity
    //
    aLightIntensityR = nAttr.create( "lightIntensityR", "lir",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightIntensityG = nAttr.create( "lightIntensityG", "lig",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightIntensityB = nAttr.create( "lightIntensityB", "lib",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightIntensity = nAttr.create( "lightIntensity", "li",
            aLightIntensityR, aLightIntensityG, aLightIntensityB,
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f, 1.0f, 1.0f ) );


    // Light
    //
    aLightAmbient = nAttr.create( "lightAmbient", "la",
            MFnNumericData::kBoolean, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( true ) );

    aLightDiffuse = nAttr.create( "lightDiffuse", "ldf",
            MFnNumericData::kBoolean, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( true ) );

    aLightSpecular = nAttr.create( "lightSpecular", "ls",
            MFnNumericData::kBoolean, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( false ) );

    aLightShadowFraction = nAttr.create( "lightShadowFraction", "lsf",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aPreShadowIntensity = nAttr.create( "preShadowIntensity", "psi",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightBlindData = nAttr.createAddr( "lightBlindData", "lbld",
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aLightData = lAttr.create( "lightDataArray", "ltd", aLightDirection,
            aLightIntensity, aLightAmbient, aLightDiffuse, aLightSpecular,
            aLightShadowFraction, aPreShadowIntensity, aLightBlindData,
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( lAttr.setArray( true ) );
    CHECK_MSTATUS( lAttr.setStorable( false ) );
    CHECK_MSTATUS( lAttr.setHidden( true ) );
    CHECK_MSTATUS( lAttr.setDefault( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            true, true, false, 1.0f, 1.0f, nullptr ) );


    // Next we will add the attributes we have defined to the node
    //
    CHECK_MSTATUS( addAttribute( aTranslucenceCoeff ) );
    CHECK_MSTATUS( addAttribute( aDiffuseReflectivity ) );
    //CHECK_MSTATUS( addAttribute( aColor ) );
    //CHECK_MSTATUS( addAttribute( aIncandescence ) );
    CHECK_MSTATUS( addAttribute( aInTransparency ) );
    CHECK_MSTATUS( addAttribute( aOutColor ) );
    CHECK_MSTATUS( addAttribute( aOutTransparency ) );
    CHECK_MSTATUS( addAttribute( aNormalCamera ) );

    // Only add the parent of the compound
    CHECK_MSTATUS( addAttribute( aLightData ) );

    // The attributeAffects() method is used to indicate when the input
    // attribute affects the output attribute. This knowledge allows Maya
    // to optimize dependencies in the graph in more complex nodes where
    // there may be several inputs and outputs, but not all the inputs
    // affect all the outputs.
    //
	CHECK_MSTATUS(attributeAffects(iesProfile, aOutColor));
	CHECK_MSTATUS(attributeAffects(aTranslucenceCoeff, aOutColor));
	CHECK_MSTATUS(attributeAffects(aDiffuseReflectivity, aOutColor));
    CHECK_MSTATUS( attributeAffects( diffuse, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( emissionColor, aOutColor ) );
    //CHECK_MSTATUS( attributeAffects( aColor, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aInTransparency, aOutTransparency ) );
    CHECK_MSTATUS( attributeAffects( aInTransparency, aOutColor ) );
    //CHECK_MSTATUS( attributeAffects( aIncandescence, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensityR, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensityB, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensityG, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensity, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCameraX, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCameraY, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCameraZ, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCamera, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirectionX, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirectionY, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirectionZ, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirection, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightAmbient, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightSpecular, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDiffuse, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightShadowFraction, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aPreShadowIntensity, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightBlindData, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightData, aOutColor ) );

    return( MS::kSuccess );
}


// Compute takes two parameters: plug and data.
// - Plug is the the data value that needs to be recomputed
// - Data provides handles to all of the nodes attributes, only these
//   handles should be used when performing computations.
//
MStatus CoronaSurface::compute( const MPlug& plug, MDataBlock& block )
{
    // The plug parameter will allow us to determine which output attribute
    // needs to be calculated.
    //
	if( plug == aOutColor || plug == aOutTransparency || plug.parent() == aOutColor || plug.parent() == aOutTransparency  )
    {
        MStatus status;
        MFloatVector resultColor( 0.0, 0.0, 0.0 );

        // Get surface shading parameters from input block
        //
        MFloatVector& surfaceNormal = block.inputValue( aNormalCamera, &status ).asFloatVector();
        CHECK_MSTATUS( status );

        //MFloatVector& emissionColor = block.inputValue( emissionColor, &status ).asFloatVector();
        //CHECK_MSTATUS( status );

        MFloatVector& diffuseColor = block.inputValue( diffuse, &status ).asFloatVector();
        CHECK_MSTATUS( status );

		//MPlug cplug(this->thisMObject(), aColor);
		//cplug.child(0).setDouble(surfaceColor.x);
		//cplug.child(1).setDouble(surfaceColor.y);
		//cplug.child(2).setDouble(surfaceColor.z);

        //MFloatVector& incandescence = block.inputValue( aIncandescence,  &status ).asFloatVector();
        //CHECK_MSTATUS( status );

        float diffuseReflectivity = block.inputValue( aDiffuseReflectivity, &status ).asFloat();
        CHECK_MSTATUS( status );

		MFloatVector& incandescence = block.inputValue(emissionColor, &status).asFloatVector();
        CHECK_MSTATUS( status );

        // Get light list
        //
        MArrayDataHandle lightData = block.inputArrayValue( aLightData, &status );
        CHECK_MSTATUS( status );

        int numLights = lightData.elementCount( &status );
        CHECK_MSTATUS( status );


        // Calculate the effect of the lights in the scene on the color
        //

        // Iterate through light list and get ambient/diffuse values
        //
        for( int count=1; count <= numLights; count++ )
        {
            // Get the current light out of the array
            //
            MDataHandle currentLight = lightData.inputValue( &status );
            CHECK_MSTATUS( status );


            // Get the intensity of that light
            //
            MFloatVector& lightIntensity = currentLight.child( aLightIntensity ).asFloatVector();


            // Find ambient component
            //
            if ( currentLight.child( aLightAmbient ).asBool() )
            {
                resultColor += lightIntensity;
            }


            // Find diffuse component
            //
            if ( currentLight.child( aLightDiffuse ).asBool() )
            {
                MFloatVector& lightDirection = currentLight.child( aLightDirection ).asFloatVector();
                float cosln = lightDirection * surfaceNormal;

               if ( cosln > 0.0f ) 
			   {
                    resultColor += lightIntensity * ( cosln * diffuseReflectivity );
               }
            }


            // Advance to the next light.
            //
            if ( count < numLights ) {
                status = lightData.next();
                CHECK_MSTATUS( status );
            }
        }


        // Factor incident light with surface color and add incandescence
        //
		resultColor[0] = resultColor[0] * diffuseColor[0] + incandescence[0];
		resultColor[1] = resultColor[1] * diffuseColor[1] + incandescence[1];
		resultColor[2] = resultColor[2] * diffuseColor[2] + incandescence[2];


        // Set ouput color attribute
        //
		if ( plug == aOutColor || plug.parent() == aOutColor )
        {
            // Get the handle to the attribute
            //
            MDataHandle outColorHandle = block.outputValue( aOutColor, &status );
            CHECK_MSTATUS( status );
            MFloatVector& outColor = outColorHandle.asFloatVector();

            outColor = resultColor;     // Set the output value
            outColorHandle.setClean(); // Mark the output value as clean
        }


        // Set ouput transparency
        //
		if ( plug == aOutTransparency || plug.parent() == aOutTransparency )
        {
            MFloatVector& transparency = block.inputValue( aInTransparency, &status ).asFloatVector();
            CHECK_MSTATUS( status );


            // Get the handle to the attribute
            //
            MDataHandle outTransHandle = block.outputValue( aOutTransparency, &status );
            CHECK_MSTATUS( status );
            MFloatVector& outTrans = outTransHandle.asFloatVector();

            outTrans = transparency;   // Set the output value
            outTransHandle.setClean(); // Mark the output value as clean
        }
    }
    else
    {
        return( MS::kUnknownParameter ); // We got an unexpected plug
    }

    return( MS::kSuccess );
}


