#include <maya/MFnNumericAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMessageAttribute.h>

#include "mtco_renderGlobalsNode.h"

MTypeId	MayaToCoronaGlobals::id(0x0011CF56);

MObject MayaToCoronaGlobals::exportOnly;
MObject MayaToCoronaGlobals::gi_saveSecondary;
MObject MayaToCoronaGlobals::gi_loadSecondary;
MObject MayaToCoronaGlobals::lowThreadPriority;
MObject MayaToCoronaGlobals::vfb_showBucketOrder;
MObject MayaToCoronaGlobals::doShading;
MObject MayaToCoronaGlobals::doAa;
MObject MayaToCoronaGlobals::renderer;
MObject MayaToCoronaGlobals::accelerationStructure;
MObject MayaToCoronaGlobals::gi_primarySolver;
MObject MayaToCoronaGlobals::gi_secondarySolver;
MObject MayaToCoronaGlobals::lights_solver;
MObject MayaToCoronaGlobals::enviroSolver;
MObject MayaToCoronaGlobals::embree_triangles;
MObject MayaToCoronaGlobals::random_sampler;
MObject MayaToCoronaGlobals::progressive_maxPasses;
MObject MayaToCoronaGlobals::progressive_timeLimit;
MObject MayaToCoronaGlobals::lights_areaSamplesMult;
MObject MayaToCoronaGlobals::lights_env_resolution;
MObject MayaToCoronaGlobals::pathtracingSamples;
MObject MayaToCoronaGlobals::lights_areaMethod;
MObject MayaToCoronaGlobals::raycaster_maxDepth;
MObject MayaToCoronaGlobals::raycaster_minDepth;
MObject MayaToCoronaGlobals::buffer_updateInterval;
MObject MayaToCoronaGlobals::gi_primaryFile;
MObject MayaToCoronaGlobals::gi_secondaryFile;
MObject MayaToCoronaGlobals::image_bucketSize;
MObject MayaToCoronaGlobals::color_exit;
MObject MayaToCoronaGlobals::fb_internalResolutionMult;
MObject MayaToCoronaGlobals::imagefilter_width;
MObject MayaToCoronaGlobals::imagefilter_blurring;
MObject MayaToCoronaGlobals::system_maxNormalDev;
MObject MayaToCoronaGlobals::progressive_recalculateEvery;
MObject MayaToCoronaGlobals::progressive_adaptivity;
MObject MayaToCoronaGlobals::maxPtSampleIntensity;
MObject MayaToCoronaGlobals::subdivEnviroThreshold;
MObject MayaToCoronaGlobals::lights_texturedResolution;
MObject MayaToCoronaGlobals::random_seed;
MObject MayaToCoronaGlobals::lightSolver_localFrac;
MObject MayaToCoronaGlobals::lightSolver_globalFrac;
MObject MayaToCoronaGlobals::portals_sampleAmount;
MObject MayaToCoronaGlobals::shadowBias;
MObject MayaToCoronaGlobals::resumeRendering;
MObject MayaToCoronaGlobals::instance_minSize;
MObject MayaToCoronaGlobals::gi_ic_incrementalBuild;
MObject MayaToCoronaGlobals::gi_ic_incrementalFilename;
MObject MayaToCoronaGlobals::gi_ic_hemisphereSubdiv;
MObject MayaToCoronaGlobals::gi_ic_precompAmount;
MObject MayaToCoronaGlobals::gi_ic_pathtracingCorners;
MObject MayaToCoronaGlobals::gi_ic_maxGeomError;
MObject MayaToCoronaGlobals::gi_ic_smoothing;
MObject MayaToCoronaGlobals::gi_ic_colorThreshold;
MObject MayaToCoronaGlobals::gi_ic_recordSpacingMin;
MObject MayaToCoronaGlobals::gi_ic_recordSpacingMax;
MObject MayaToCoronaGlobals::gi_ic_useRotationGradient;
MObject MayaToCoronaGlobals::gi_ic_useTranslationGradient;
MObject MayaToCoronaGlobals::gi_ic_interpolationSchema;
MObject MayaToCoronaGlobals::gi_ic_searchStructure;
MObject MayaToCoronaGlobals::gi_ic_relaxedInterpolation;
MObject MayaToCoronaGlobals::gi_ic_vizualization;
MObject MayaToCoronaGlobals::gi_ic_minInterpSamples;
MObject MayaToCoronaGlobals::gi_hdCache_precalcMode;
MObject MayaToCoronaGlobals::gi_hdCache_precompMult;
MObject MayaToCoronaGlobals::gi_hdCache_interpolationCount;
MObject MayaToCoronaGlobals::gi_hdCache_dirSensitivity;
MObject MayaToCoronaGlobals::gi_hdCache_posSensitivity;
MObject MayaToCoronaGlobals::gi_hdCache_normalSensitivity;
MObject MayaToCoronaGlobals::gi_hdCache_ptSamples;
MObject MayaToCoronaGlobals::gi_hdCache_smoothing;
MObject MayaToCoronaGlobals::gi_hdCache_glossyThreshold;
MObject MayaToCoronaGlobals::gi_hdCache_maxRecords;
MObject MayaToCoronaGlobals::gi_hdCache_writePasses;
MObject MayaToCoronaGlobals::gi_photons_emitted;
MObject MayaToCoronaGlobals::gi_photons_storeDirect;
MObject MayaToCoronaGlobals::gi_photons_depth;
MObject MayaToCoronaGlobals::gi_photons_lookupCount;
MObject MayaToCoronaGlobals::gi_photons_filter;
MObject MayaToCoronaGlobals::gi_vpl_emittedCount;
MObject MayaToCoronaGlobals::gi_vpl_usedCount;
MObject MayaToCoronaGlobals::gi_vpl_progressiveBatch;
MObject MayaToCoronaGlobals::gi_vpl_clamping;
MObject MayaToCoronaGlobals::gi_pathtracing_directMode;
MObject MayaToCoronaGlobals::buckets_initialSamples;
MObject MayaToCoronaGlobals::buckets_adaptiveSteps;
MObject MayaToCoronaGlobals::buckets_adaptiveThreshold;
MObject MayaToCoronaGlobals::bvh_cost_iteration;
MObject MayaToCoronaGlobals::bvh_cost_triangle;
MObject MayaToCoronaGlobals::bvh_leafSizeMin;
MObject MayaToCoronaGlobals::bvh_leafSizeMax;
MObject MayaToCoronaGlobals::exposure_type;
MObject MayaToCoronaGlobals::colorMapping_gamma;
MObject MayaToCoronaGlobals::colorMapping_colorTemperature;
MObject MayaToCoronaGlobals::colorMapping_useSimpleExposure;
MObject MayaToCoronaGlobals::colorMapping_simpleExposure;
MObject MayaToCoronaGlobals::colorMapping_tint;
MObject MayaToCoronaGlobals::colorMapping_useContrast;
MObject MayaToCoronaGlobals::colorMapping_contrast;
MObject MayaToCoronaGlobals::colorMapping_highlightCompression;
MObject MayaToCoronaGlobals::colorMapping_fStop;
MObject MayaToCoronaGlobals::colorMapping_iso;
MObject MayaToCoronaGlobals::colorMapping_shutterSpeed;
MObject MayaToCoronaGlobals::ppm_samplesPerIter;
MObject MayaToCoronaGlobals::ppm_photonsPerIter;
MObject MayaToCoronaGlobals::ppm_alpha;
MObject MayaToCoronaGlobals::ppm_initialRadius;
MObject MayaToCoronaGlobals::bidir_doMis;
MObject MayaToCoronaGlobals::vcm_mode;
MObject MayaToCoronaGlobals::displace_useProjectionSize;
MObject MayaToCoronaGlobals::displace_maxProjectSize;
MObject MayaToCoronaGlobals::displace_maxWorldSize;
MObject MayaToCoronaGlobals::displace_maxSubdiv;
MObject MayaToCoronaGlobals::renderstamp_use;
MObject MayaToCoronaGlobals::renderstamp_inFile;
MObject MayaToCoronaGlobals::renderStamp;
MObject MayaToCoronaGlobals::bgColor;
MObject MayaToCoronaGlobals::bgType;
MObject MayaToCoronaGlobals::pSkyModel;
MObject MayaToCoronaGlobals::pSkyMultiplier;
MObject MayaToCoronaGlobals::pSkyHorizBlur;
MObject MayaToCoronaGlobals::pSkyGroundColor;
MObject MayaToCoronaGlobals::pSkyAffectGround;
MObject MayaToCoronaGlobals::pSkyPreethamTurb;
MObject MayaToCoronaGlobals::pSkySunFalloff;
MObject MayaToCoronaGlobals::pSkyZenith;
MObject MayaToCoronaGlobals::pSkyHorizon;
MObject MayaToCoronaGlobals::pSkySunGlow;
MObject MayaToCoronaGlobals::pSkySunSideGlow;
MObject MayaToCoronaGlobals::pSkySunBleed;
MObject MayaToCoronaGlobals::sunSizeMulti;
MObject MayaToCoronaGlobals::dumpAndResume;
MObject MayaToCoronaGlobals::dumpExrFile;
MObject MayaToCoronaGlobals::uhdCacheType;
MObject MayaToCoronaGlobals::uhdPrecision;
MObject MayaToCoronaGlobals::globalVolume;
MObject MayaToCoronaGlobals::useGlobalMaterialOverride;
MObject MayaToCoronaGlobals::globalMaterialOverride;
MObject MayaToCoronaGlobals::useCoronaVFB;
MObject MayaToCoronaGlobals::globalDirectOverride;
MObject MayaToCoronaGlobals::globalReflectionOverride;
MObject MayaToCoronaGlobals::globalRefractionOverride;
MObject MayaToCoronaGlobals::useGlobalDirectOverride;
MObject MayaToCoronaGlobals::useGlobalReflectionOverride;
MObject MayaToCoronaGlobals::useGlobalRefractionOverride;
MObject MayaToCoronaGlobals::lockSamplingPattern;



MayaToCoronaGlobals::MayaToCoronaGlobals()
{
	imageFormatList.append("Bmp");
	imageFormatList.append("Exr");
	imageFormatList.append("Jpg");
	imageFormatList.append("Png");

	filterTypeList.append("None");
	filterTypeList.append("Box");
	filterTypeList.append("Gauss");
	filterTypeList.append("Tent");

	this->defaultEnumFilterType = 2;
}

MayaToCoronaGlobals::~MayaToCoronaGlobals()
{}


void *MayaToCoronaGlobals::creator()
{
	return new MayaToCoronaGlobals();
}

MStatus	MayaToCoronaGlobals::initialize()
{
	MayaRenderGlobalsNode::initialize();

	MFnNumericAttribute nAttr;
	MFnTypedAttribute tAttr;
	MFnGenericAttribute gAttr;
	MFnEnumAttribute eAttr;
	MFnMessageAttribute mAttr;

	MStatus stat = MStatus::kSuccess;

	useCoronaVFB = nAttr.create("useCoronaVFB", "useCoronaVFB", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(useCoronaVFB));

	exportOnly = nAttr.create("exportOnly", "exportOnly", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( exportOnly ));

	gi_saveSecondary = nAttr.create("gi_saveSecondary", "gi_saveSecondary",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( gi_saveSecondary ));

	gi_loadSecondary = nAttr.create("gi_loadSecondary", "gi_loadSecondary",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( gi_loadSecondary ));

	lowThreadPriority = nAttr.create("lowThreadPriority", "lowThreadPriority",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( lowThreadPriority ));

	vfb_showBucketOrder = nAttr.create("vfb_showBucketOrder", "vfb_showBucketOrder",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( vfb_showBucketOrder ));

	doShading = nAttr.create("doShading", "doShading",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( doShading ));

	doAa = nAttr.create("doAa", "doAa",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( doAa ));

	gi_hdCache_precalcMode = eAttr.create("gi_hdCache_precalcMode", "gi_hdCache_precalcMode", 0, &stat);
	stat = eAttr.addField("Rebuild", 0);
	stat = eAttr.addField("Load", 1);
	stat = eAttr.addField("Append", 2);
	CHECK_MSTATUS(addAttribute(gi_hdCache_precalcMode));

	renderer = eAttr.create("renderer", "renderer", 0, &stat);
	stat = eAttr.addField( "Progressive", 0 );
	stat = eAttr.addField( "Bucket", 1 );
	stat = eAttr.addField( "BiDir/VCM", 2 );
	CHECK_MSTATUS(addAttribute( renderer ));

	accelerationStructure = eAttr.create("accelerationStructure", "accelerationStructure", 0, &stat);
	stat = eAttr.addField( "Embree_bvh4_spatial", 0 );
	stat = eAttr.addField( "Embree_bvh4", 1 );
	stat = eAttr.addField( "BVH full SAH", 2 );
	CHECK_MSTATUS(addAttribute( accelerationStructure ));

	gi_primarySolver = eAttr.create("gi_primarySolver", "gi_primarySolver", 1, &stat);
	stat = eAttr.addField( "None", 0 );
	stat = eAttr.addField( "Pathtracing", 1 );
	CHECK_MSTATUS(addAttribute( gi_primarySolver ));

	gi_secondarySolver = eAttr.create("gi_secondarySolver", "gi_secondarySolver", 3, &stat);
	stat = eAttr.addField( "None", 0 );
	stat = eAttr.addField( "Pathtracing", 1 );
	stat = eAttr.addField("HD Cache", 2);
	stat = eAttr.addField("UHD Cache", 3);
	CHECK_MSTATUS(addAttribute( gi_secondarySolver ));

	lights_solver = eAttr.create("lights_solver", "lights_solver", 0, &stat);
	stat = eAttr.addField( "Combined", 0 );
	stat = eAttr.addField( "Photon", 1 );
	CHECK_MSTATUS(addAttribute( lights_solver ));

	enviroSolver = eAttr.create("enviroSolver", "enviroSolver", 0, &stat);
	stat = eAttr.addField( "Fast", 0 );
	stat = eAttr.addField( "Fast_compensate", 1 );
	CHECK_MSTATUS(addAttribute( enviroSolver ));

	embree_triangles = eAttr.create("embree_triangles", "embree_triangles", 0, &stat);
	stat = eAttr.addField( "Fast", 0 );
	stat = eAttr.addField( "Avx", 1 );
	CHECK_MSTATUS(addAttribute( embree_triangles ));

	random_sampler = eAttr.create("random_sampler", "random_sampler", 0, &stat);
	stat = eAttr.addField( "5d_highd", 0 );
	stat = eAttr.addField( "Shared", 1 );
	stat = eAttr.addField( "Maximal_value", 2 );
	CHECK_MSTATUS(addAttribute( random_sampler ));

	progressive_maxPasses = nAttr.create("progressive_maxPasses", "progressive_maxPasses",  MFnNumericData::kInt, 0);
	CHECK_MSTATUS(addAttribute( progressive_maxPasses ));

	progressive_timeLimit = nAttr.create("progressive_timeLimit", "progressive_timeLimit",  MFnNumericData::kInt, 0);
	CHECK_MSTATUS(addAttribute( progressive_timeLimit ));

	lights_areaSamplesMult = nAttr.create("lights_areaSamplesMult", "lights_areaSamplesMult",  MFnNumericData::kFloat, 2.0);
	nAttr.setMin(0.0001);
	nAttr.setMax(100.0);
	CHECK_MSTATUS(addAttribute( lights_areaSamplesMult ));

	lights_env_resolution = nAttr.create("lights_env_resolution", "lights_env_resolution",  MFnNumericData::kInt, 1000);
	CHECK_MSTATUS(addAttribute( lights_env_resolution ));

	pathtracingSamples = nAttr.create("pathtracingSamples", "pathtracingSamples",  MFnNumericData::kInt, 16);
	CHECK_MSTATUS(addAttribute( pathtracingSamples ));

	lights_areaMethod = eAttr.create("lights_areaMethod", "lights_areaMethod", 2, &stat);
	stat = eAttr.addField( "Simple", 0 );
	stat = eAttr.addField("Reproject", 1);
	stat = eAttr.addField("ReprojectBidir", 2);
	CHECK_MSTATUS(addAttribute(lights_areaMethod));

	raycaster_maxDepth = nAttr.create("raycaster_maxDepth", "raycaster_maxDepth",  MFnNumericData::kInt, 25);
	CHECK_MSTATUS(addAttribute( raycaster_maxDepth ));

	raycaster_minDepth = nAttr.create("raycaster_minDepth", "raycaster_minDepth",  MFnNumericData::kInt, 0);
	CHECK_MSTATUS(addAttribute( raycaster_minDepth ));

	buffer_updateInterval = nAttr.create("buffer_updateInterval", "buffer_updateInterval",  MFnNumericData::kInt, 1000);
	CHECK_MSTATUS(addAttribute( buffer_updateInterval ));

	gi_primaryFile = tAttr.create("gi_primaryFile", "gi_primaryFile",  MFnNumericData::kString);
	CHECK_MSTATUS(addAttribute( gi_primaryFile ));

	gi_secondaryFile = tAttr.create("gi_secondaryFile", "gi_secondaryFile",  MFnNumericData::kString);
	CHECK_MSTATUS(addAttribute( gi_secondaryFile ));

	image_bucketSize = nAttr.create("image_bucketSize", "image_bucketSize",  MFnNumericData::kInt, 32);
	CHECK_MSTATUS(addAttribute( image_bucketSize ));

	color_exit = nAttr.createColor("color_exit", "color_exit");
	nAttr.setDefault(0.0,0.0,0.0);
	CHECK_MSTATUS(addAttribute( color_exit ));

	fb_internalResolutionMult = nAttr.create("fb_internalResolutionMult", "fb_internalResolutionMult",  MFnNumericData::kInt, 1);
	CHECK_MSTATUS(addAttribute( fb_internalResolutionMult ));

	imagefilter_width = nAttr.create("imagefilter_width", "imagefilter_width",  MFnNumericData::kFloat, 1.5);
	nAttr.setMin(1.0);
	nAttr.setMax(64);
	CHECK_MSTATUS(addAttribute( imagefilter_width ));

	imagefilter_blurring = nAttr.create("imagefilter_blurring", "imagefilter_blurring",  MFnNumericData::kFloat, 0.5);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( imagefilter_blurring ));

	system_maxNormalDev = nAttr.create("system_maxNormalDev", "system_maxNormalDev",  MFnNumericData::kFloat, 0.55);
	nAttr.setMin(0.001);
	nAttr.setMax(2.0);
	CHECK_MSTATUS(addAttribute( system_maxNormalDev ));

	progressive_recalculateEvery = nAttr.create("progressive_recalculateEvery", "progressive_recalculateEvery",  MFnNumericData::kInt, 0);
	CHECK_MSTATUS(addAttribute( progressive_recalculateEvery ));

	progressive_adaptivity = nAttr.create("progressive_adaptivity", "progressive_adaptivity",  MFnNumericData::kFloat, 0.0);
	nAttr.setMin(0.0);
	nAttr.setMax(99.0);
	CHECK_MSTATUS(addAttribute( progressive_adaptivity ));

	maxPtSampleIntensity = nAttr.create("maxPtSampleIntensity", "maxPtSampleIntensity",  MFnNumericData::kFloat, 20.0);
	nAttr.setMin(0.0);
	nAttr.setMax(99999.0);
	CHECK_MSTATUS(addAttribute( maxPtSampleIntensity ));

	subdivEnviroThreshold = nAttr.create("subdivEnviroThreshold", "subdivEnviroThreshold",  MFnNumericData::kFloat, 0.005);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( subdivEnviroThreshold ));

	lights_texturedResolution = nAttr.create("lights_texturedResolution", "lights_texturedResolution",  MFnNumericData::kFloat, 0.3);
	nAttr.setMin(0.0001);
	nAttr.setMax(99.0);
	CHECK_MSTATUS(addAttribute( lights_texturedResolution ));

	random_seed = nAttr.create("random_seed", "random_seed",  MFnNumericData::kInt, 1234);
	CHECK_MSTATUS(addAttribute( random_seed ));

	lightSolver_localFrac = nAttr.create("lightSolver_localFrac", "lightSolver_localFrac",  MFnNumericData::kFloat, 0.33);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( lightSolver_localFrac ));

	lightSolver_globalFrac = nAttr.create("lightSolver_globalFrac", "lightSolver_globalFrac",  MFnNumericData::kFloat, 0.33);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( lightSolver_globalFrac ));

	portals_sampleAmount = nAttr.create("portals_sampleAmount", "portals_sampleAmount",  MFnNumericData::kFloat, 0.75);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( portals_sampleAmount ));

	shadowBias = nAttr.create("shadowBias", "shadowBias",  MFnNumericData::kFloat, -6.07);
	CHECK_MSTATUS(addAttribute( shadowBias ));

	resumeRendering = nAttr.create("resumeRendering", "resumeRendering",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( resumeRendering ));

	instance_minSize = nAttr.create("instance_minSize", "instance_minSize",  MFnNumericData::kInt, 50000);
	CHECK_MSTATUS(addAttribute( instance_minSize ));

	gi_ic_incrementalBuild = nAttr.create("gi_ic_incrementalBuild", "gi_ic_incrementalBuild",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( gi_ic_incrementalBuild ));

	gi_ic_incrementalFilename = tAttr.create("gi_ic_incrementalFilename", "gi_ic_incrementalFilename",  MFnNumericData::kString);
	CHECK_MSTATUS(addAttribute( gi_ic_incrementalFilename ));

	gi_ic_hemisphereSubdiv = nAttr.create("gi_ic_hemisphereSubdiv", "gi_ic_hemisphereSubdiv",  MFnNumericData::kInt, 7);
	CHECK_MSTATUS(addAttribute( gi_ic_hemisphereSubdiv ));

	//gi.hdCache.precompDensity
	gi_ic_precompAmount = nAttr.create("gi_ic_precompAmount", "gi_ic_precompAmount",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.0);
	nAttr.setMax(99.0);
	CHECK_MSTATUS(addAttribute( gi_ic_precompAmount ));

	//gi.ic.pathtracingCorners
	gi_ic_pathtracingCorners = nAttr.create("gi_ic_pathtracingCorners", "gi_ic_pathtracingCorners",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( gi_ic_pathtracingCorners ));

	//gi.ic.maxError
	gi_ic_maxGeomError = nAttr.create("gi_ic_maxGeomError", "gi_ic_maxGeomError",  MFnNumericData::kFloat, 0.6);
	nAttr.setMin(0.01);
	nAttr.setMax(10.0);
	CHECK_MSTATUS(addAttribute( gi_ic_maxGeomError ));

	//gi.ic.smoothing
	gi_ic_smoothing = nAttr.create("gi_ic_smoothing", "gi_ic_smoothing",  MFnNumericData::kFloat, 1.8);
	nAttr.setMin(1.0);
	nAttr.setMax(10.0);
	CHECK_MSTATUS(addAttribute( gi_ic_smoothing ));

	//gi.ic.colorThreshold
	gi_ic_colorThreshold = nAttr.create("gi_ic_colorThreshold", "gi_ic_colorThreshold",  MFnNumericData::kFloat, 10.0);
	nAttr.setMin(0.01);
	nAttr.setMax(10.0);
	CHECK_MSTATUS(addAttribute( gi_ic_colorThreshold ));

	//gi.ic.recordSpacingMin
	gi_ic_recordSpacingMin = nAttr.create("gi_ic_recordSpacingMin", "gi_ic_recordSpacingMin",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.01);
	nAttr.setMax(500.0);
	CHECK_MSTATUS(addAttribute( gi_ic_recordSpacingMin ));

	//gi.ic.recordSpacingMax
	gi_ic_recordSpacingMax = nAttr.create("gi_ic_recordSpacingMax", "gi_ic_recordSpacingMax",  MFnNumericData::kFloat, 20.0);
	nAttr.setMin(0.1);
	nAttr.setMax(500.0);
	CHECK_MSTATUS(addAttribute( gi_ic_recordSpacingMax ));

	//gi.ic.useRotGrad
	gi_ic_useRotationGradient = nAttr.create("gi_ic_useRotationGradient", "gi_ic_useRotationGradient",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( gi_ic_useRotationGradient ));

	//gi.ic.useTransGrad
	gi_ic_useTranslationGradient = nAttr.create("gi_ic_useTranslationGradient", "gi_ic_useTranslationGradient",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( gi_ic_useTranslationGradient ));

	//gi.ic.interpolationSchema
	gi_ic_interpolationSchema = eAttr.create("gi_ic_interpolationSchema", "gi_ic_interpolationSchema", 1, &stat);
	stat = eAttr.addField( "Ward", 0 );
	stat = eAttr.addField( "Tabellion", 1 );
	CHECK_MSTATUS(addAttribute( gi_ic_interpolationSchema ));

	//gi.ic.searchStructure
	gi_ic_searchStructure = eAttr.create("gi_ic_searchStructure", "gi_ic_searchStructure", 0, &stat);
	stat = eAttr.addField( "Multiple_octree", 0 );
	stat = eAttr.addField( "Bvh", 1 );
	CHECK_MSTATUS(addAttribute( gi_ic_searchStructure ));

	//gi.ic.relaxedInterpolation
	gi_ic_relaxedInterpolation = nAttr.create("gi_ic_relaxedInterpolation", "gi_ic_relaxedInterpolation",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( gi_ic_relaxedInterpolation ));

	//gi.ic.viz
	gi_ic_vizualization = eAttr.create("gi_ic_vizualization", "gi_ic_vizualization", 2, &stat);
	stat = eAttr.addField("Off", 0);
	stat = eAttr.addField("Dots", 1);
	stat = eAttr.addField("Indirect", 2);
	CHECK_MSTATUS(addAttribute( gi_ic_vizualization ));

	//gi.ic.minInterpSamples
	gi_ic_minInterpSamples = nAttr.create("gi_ic_minInterpSamples", "gi_ic_minInterpSamples",  MFnNumericData::kInt, 2);
	CHECK_MSTATUS(addAttribute( gi_ic_minInterpSamples ));

	//gi.uhdcache.precompDensity
	gi_hdCache_precompMult = nAttr.create("gi_hdCache_precompMult", "gi_hdCache_precompMult",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.0);
	nAttr.setMax(99.0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_precompMult ));

	//gi.hdCache.interpolationCount
	gi_hdCache_interpolationCount = nAttr.create("gi_hdCache_interpolationCount", "gi_hdCache_interpolationCount",  MFnNumericData::kInt, 3);
	CHECK_MSTATUS(addAttribute( gi_hdCache_interpolationCount ));

	//gi.hdCache.dirSensitivity
	gi_hdCache_dirSensitivity = nAttr.create("gi_hdCache_dirSensitivity", "gi_hdCache_dirSensitivity",  MFnNumericData::kFloat, 2.0);
	nAttr.setMin(0.001);
	nAttr.setMax(100.0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_dirSensitivity ));

	//gi.hdCache.posSensitivity
	gi_hdCache_posSensitivity = nAttr.create("gi_hdCache_posSensitivity", "gi_hdCache_posSensitivity",  MFnNumericData::kFloat, 20.0);
	nAttr.setMin(0.0);
	nAttr.setMax(100.0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_posSensitivity ));

	gi_hdCache_normalSensitivity = nAttr.create("gi_hdCache_normalSensitivity", "gi_hdCache_normalSensitivity",  MFnNumericData::kFloat, 3.0);
	nAttr.setMin(0.0);
	nAttr.setMax(10.0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_normalSensitivity ));

	//gi.hdCache.recordQuality
	gi_hdCache_ptSamples = nAttr.create("gi_hdCache_ptSamples", "gi_hdCache_ptSamples",  MFnNumericData::kInt, 256);
	CHECK_MSTATUS(addAttribute( gi_hdCache_ptSamples ));

	//gi.hdCache.smoothing 
	gi_hdCache_smoothing = nAttr.create("gi_hdCache_smoothing", "gi_hdCache_smoothing",  MFnNumericData::kFloat, 2.0);
	nAttr.setMin(1.0);
	nAttr.setMax(10.0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_smoothing ));

	gi_hdCache_glossyThreshold = nAttr.create("gi_hdCache_glossyThreshold", "gi_hdCache_glossyThreshold",  MFnNumericData::kFloat, 0.9);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_glossyThreshold ));

	gi_hdCache_maxRecords = nAttr.create("gi_hdCache_maxRecords", "gi_hdCache_maxRecords",  MFnNumericData::kInt, 100000);
	CHECK_MSTATUS(addAttribute( gi_hdCache_maxRecords ));

	//gi.hdCache.writablePasses
	gi_hdCache_writePasses = nAttr.create("gi_hdCache_writePasses", "gi_hdCache_writePasses",  MFnNumericData::kInt, 0);
	CHECK_MSTATUS(addAttribute( gi_hdCache_writePasses ));

	gi_photons_emitted = nAttr.create("gi_photons_emitted", "gi_photons_emitted",  MFnNumericData::kInt, 5000000);
	CHECK_MSTATUS(addAttribute( gi_photons_emitted ));

	gi_photons_storeDirect = nAttr.create("gi_photons_storeDirect", "gi_photons_storeDirect",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( gi_photons_storeDirect ));

	gi_photons_depth = nAttr.create("gi_photons_depth", "gi_photons_depth",  MFnNumericData::kInt, -1);
	CHECK_MSTATUS(addAttribute( gi_photons_depth ));

	gi_photons_lookupCount = nAttr.create("gi_photons_lookupCount", "gi_photons_lookupCount",  MFnNumericData::kInt, 50);
	CHECK_MSTATUS(addAttribute( gi_photons_lookupCount ));

	gi_photons_filter = eAttr.create("gi_photons_filter", "gi_photons_filter", 1, &stat);
	stat = eAttr.addField( "Constant", 0 );
	stat = eAttr.addField( "Linear", 1 );
	stat = eAttr.addField("Epanechnikov", 2);
	stat = eAttr.addField("Biweight", 3);
	stat = eAttr.addField("Gaussian", 4);
	CHECK_MSTATUS(addAttribute( gi_photons_filter ));

	gi_vpl_emittedCount = nAttr.create("gi_vpl_emittedCount", "gi_vpl_emittedCount",  MFnNumericData::kInt, 1000000);
	CHECK_MSTATUS(addAttribute( gi_vpl_emittedCount ));

	gi_vpl_usedCount = nAttr.create("gi_vpl_usedCount", "gi_vpl_usedCount",  MFnNumericData::kInt, 150);
	CHECK_MSTATUS(addAttribute( gi_vpl_usedCount ));

	gi_vpl_progressiveBatch = nAttr.create("gi_vpl_progressiveBatch", "gi_vpl_progressiveBatch",  MFnNumericData::kInt, 150);
	CHECK_MSTATUS(addAttribute( gi_vpl_progressiveBatch ));

	gi_vpl_clamping = nAttr.create("gi_vpl_clamping", "gi_vpl_clamping",  MFnNumericData::kFloat, 50.0);
	nAttr.setMin(0.0);
	nAttr.setMax(999.0);
	CHECK_MSTATUS(addAttribute( gi_vpl_clamping ));

	//lights.areaMethod
	gi_pathtracing_directMode = eAttr.create("gi_pathtracing_directMode", "gi_pathtracing_directMode", 2, &stat);
	stat = eAttr.addField("Sample Lights", 0);
	stat = eAttr.addField("BSDF", 1);
	stat = eAttr.addField("Mis", 2);
	CHECK_MSTATUS(addAttribute( gi_pathtracing_directMode ));

	buckets_initialSamples = nAttr.create("buckets_initialSamples", "buckets_initialSamples",  MFnNumericData::kInt, 1);
	CHECK_MSTATUS(addAttribute( buckets_initialSamples ));

	buckets_adaptiveSteps = nAttr.create("buckets_adaptiveSteps", "buckets_adaptiveSteps",  MFnNumericData::kInt, 2);
	CHECK_MSTATUS(addAttribute( buckets_adaptiveSteps ));

	buckets_adaptiveThreshold = nAttr.create("buckets_adaptiveThreshold", "buckets_adaptiveThreshold",  MFnNumericData::kFloat, 0.03);
	nAttr.setMin(0.001);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( buckets_adaptiveThreshold ));

	bvh_cost_iteration = nAttr.create("bvh_cost_iteration", "bvh_cost_iteration",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.01);
	nAttr.setMax(1000.0);
	CHECK_MSTATUS(addAttribute( bvh_cost_iteration ));

	bvh_cost_triangle = nAttr.create("bvh_cost_triangle", "bvh_cost_triangle",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.01);
	nAttr.setMax(1000.0);
	CHECK_MSTATUS(addAttribute( bvh_cost_triangle ));

	bvh_leafSizeMin = nAttr.create("bvh_leafSizeMin", "bvh_leafSizeMin",  MFnNumericData::kInt, 2);
	CHECK_MSTATUS(addAttribute( bvh_leafSizeMin ));

	bvh_leafSizeMax = nAttr.create("bvh_leafSizeMax", "bvh_leafSizeMax",  MFnNumericData::kInt, 6);
	CHECK_MSTATUS(addAttribute( bvh_leafSizeMax ));

	colorMapping_gamma = nAttr.create("colorMapping_gamma", "colorMapping_gamma",  MFnNumericData::kFloat, 2.2);
	nAttr.setMin(0.01);
	nAttr.setMax(10.0);
	CHECK_MSTATUS(addAttribute( colorMapping_gamma ));

	colorMapping_colorTemperature = nAttr.create("colorMapping_colorTemperature", "colorMapping_colorTemperature",  MFnNumericData::kFloat, 6500.0);
	nAttr.setMin(1000.0);
	nAttr.setMax(99999.0);
	CHECK_MSTATUS(addAttribute( colorMapping_colorTemperature ));

	colorMapping_useSimpleExposure = nAttr.create("colorMapping_useSimpleExposure", "colorMapping_useSimpleExposure",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( colorMapping_useSimpleExposure ));

	colorMapping_simpleExposure = nAttr.create("colorMapping_simpleExposure", "colorMapping_simpleExposure",  MFnNumericData::kFloat, 0.0);
	nAttr.setSoftMin(-5.0);
	nAttr.setSoftMax( 5.0);
	CHECK_MSTATUS(addAttribute(colorMapping_simpleExposure));

	colorMapping_tint = nAttr.createColor("colorMapping_tint", "colorMapping_tint");
	nAttr.setDefault(1.0,1.0,1.0);
	CHECK_MSTATUS(addAttribute( colorMapping_tint ));

	colorMapping_useContrast = nAttr.create("colorMapping_useContrast", "colorMapping_useContrast",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( colorMapping_useContrast ));

	colorMapping_contrast = nAttr.create("colorMapping_contrast", "colorMapping_contrast",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(1.0);
	nAttr.setMax(99.0);
	CHECK_MSTATUS(addAttribute( colorMapping_contrast ));

	colorMapping_highlightCompression = nAttr.create("colorMapping_highlightCompression", "colorMapping_highlightCompression",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.01);
	nAttr.setMax(99.0);
	CHECK_MSTATUS(addAttribute( colorMapping_highlightCompression ));

	colorMapping_fStop = nAttr.create("colorMapping_fStop", "colorMapping_fStop", MFnNumericData::kFloat, 16.0);
	nAttr.setMin(.001);
	nAttr.setMax(50.0);
	CHECK_MSTATUS(addAttribute(colorMapping_fStop));

	colorMapping_iso = nAttr.create("colorMapping_iso", "colorMapping_iso", MFnNumericData::kFloat, 100.0);
	nAttr.setMin(.001);
	nAttr.setSoftMin(100.00);
	nAttr.setSoftMax(800.0);
	nAttr.setMax(999999.0);
	CHECK_MSTATUS(addAttribute(colorMapping_iso));

	colorMapping_shutterSpeed = nAttr.create("colorMapping_shutterSpeed", "colorMapping_shutterSpeed", MFnNumericData::kFloat, 50.0);
	nAttr.setMin(.001);
	nAttr.setMax(999999.0);
	nAttr.setSoftMin(20.00);
	nAttr.setSoftMax(1000.0);
	CHECK_MSTATUS(addAttribute(colorMapping_shutterSpeed));

	exposure_type = eAttr.create("exposure_type", "exposure_type", 0, &stat);
	stat = eAttr.addField("Simple Exposure", 0);
	stat = eAttr.addField("Photographic Exposure", 1);
	CHECK_MSTATUS(addAttribute(exposure_type));

	ppm_samplesPerIter = nAttr.create("ppm_samplesPerIter", "ppm_samplesPerIter",  MFnNumericData::kInt, 1);
	CHECK_MSTATUS(addAttribute( ppm_samplesPerIter ));

	ppm_photonsPerIter = nAttr.create("ppm_photonsPerIter", "ppm_photonsPerIter", MFnNumericData::kInt, 5000000);
	CHECK_MSTATUS(addAttribute( ppm_photonsPerIter ));

	ppm_alpha = nAttr.create("ppm_alpha", "ppm_alpha",  MFnNumericData::kFloat, 0.666);
	nAttr.setMin(0.01);
	nAttr.setMax(1.0);
	CHECK_MSTATUS(addAttribute( ppm_alpha ));

	ppm_initialRadius = nAttr.create("ppm_initialRadius", "ppm_initialRadius",  MFnNumericData::kFloat, 2.0);
	nAttr.setMin(0.0001);
	nAttr.setMax(200.0);
	CHECK_MSTATUS(addAttribute( ppm_initialRadius ));

	bidir_doMis = nAttr.create("bidir_doMis", "bidir_doMis",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( bidir_doMis ));

	vcm_mode = eAttr.create("vcm_mode", "vcm_mode", 4, &stat);
	stat = eAttr.addField( "Pathtracing", 0 );
	stat = eAttr.addField("Light Tracing", 1);
	stat = eAttr.addField("Progressive Photon Mapping", 2);
	stat = eAttr.addField("Bidir Photon Mapping", 3);
	stat = eAttr.addField("Bidir Pathtracing", 4);
	stat = eAttr.addField("Vcm", 5);
	CHECK_MSTATUS(addAttribute(vcm_mode));

	displace_useProjectionSize = nAttr.create("displace_useProjectionSize", "displace_useProjectionSize",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( displace_useProjectionSize ));

	displace_maxProjectSize = nAttr.create("displace_maxProjectSize", "displace_maxProjectSize",  MFnNumericData::kFloat, 2.0);
	nAttr.setMin(0.01);
	nAttr.setMax(100.0);
	CHECK_MSTATUS(addAttribute( displace_maxProjectSize ));

	displace_maxWorldSize = nAttr.create("displace_maxWorldSize", "displace_maxWorldSize",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.00001);
	nAttr.setMax(10000000);
	CHECK_MSTATUS(addAttribute( displace_maxWorldSize ));

	displace_maxSubdiv = nAttr.create("displace_maxSubdiv", "displace_maxSubdiv",  MFnNumericData::kInt, 100);
	CHECK_MSTATUS(addAttribute( displace_maxSubdiv ));

	renderstamp_use = nAttr.create("renderstamp_use", "renderstamp_use",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( renderstamp_use ));

	renderstamp_inFile = nAttr.create("renderstamp_inFile", "renderstamp_inFile",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( renderstamp_inFile ));

	MFnStringData fnStringData;
	MObject defaultString;
	defaultString = fnStringData.create("Time: %pt | Passes: %pp | Primitives: %si | Rays/s : %pr");
	renderStamp = tAttr.create("renderStamp", "renderStamp", MFnNumericData::kString, defaultString);
	CHECK_MSTATUS(addAttribute(renderStamp));
	

	bgColor = nAttr.createColor("bgColor", "bgColor");
	nAttr.setDefault(1.0,1.0,1.0);
	CHECK_MSTATUS(addAttribute( bgColor ));

	bgType = eAttr.create("bgType", "bgType", 0, &stat);
	stat = eAttr.addField( "Color/Image", 0 );
	stat = eAttr.addField( "PhysicalSky", 1 );
	CHECK_MSTATUS(addAttribute( bgType ));

	pSkyModel = eAttr.create("pSkyModel", "pSkyModel", 2, &stat);
	stat = eAttr.addField( "Preetham", 0 );
	stat = eAttr.addField( "Rawafake", 1 );
	stat = eAttr.addField( "Hosek", 2 );
	CHECK_MSTATUS(addAttribute( pSkyModel ));

	pSkyMultiplier = nAttr.create("pSkyMultiplier", "pSkyMultiplier",  MFnNumericData::kFloat, 1.0);
	CHECK_MSTATUS(addAttribute( pSkyMultiplier ));

	pSkyHorizBlur = nAttr.create("pSkyHorizBlur", "pSkyHorizBlur",  MFnNumericData::kFloat, 0.1);
	CHECK_MSTATUS(addAttribute( pSkyHorizBlur ));

	pSkyGroundColor = nAttr.createColor("pSkyGroundColor", "pSkyGroundColor");
	nAttr.setDefault(0.25,0.25,0.25);
	CHECK_MSTATUS(addAttribute( pSkyGroundColor ));

	pSkyAffectGround = nAttr.create("pSkyAffectGround", "pSkyAffectGround",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( pSkyAffectGround ));

	pSkyPreethamTurb = nAttr.create("pSkyPreethamTurb", "pSkyPreethamTurb",  MFnNumericData::kFloat, 2.5);
	nAttr.setMin(1.7f);
	CHECK_MSTATUS(addAttribute( pSkyPreethamTurb ));

	pSkySunFalloff = nAttr.create("pSkySunFalloff", "pSkySunFalloff",  MFnNumericData::kFloat, 3.0);
	CHECK_MSTATUS(addAttribute( pSkySunFalloff ));

	pSkyZenith = nAttr.createColor("pSkyZenith", "pSkyZenith");
	nAttr.setDefault(0.1,0.1,0.5);
	CHECK_MSTATUS(addAttribute( pSkyZenith ));

	pSkyHorizon = nAttr.createColor("pSkyHorizon", "pSkyHorizon");
	nAttr.setDefault(0.25,0.5,0.5);
	CHECK_MSTATUS(addAttribute( pSkyHorizon ));

	pSkySunGlow = nAttr.create("pSkySunGlow", "pSkySunGlow",  MFnNumericData::kFloat, 1.0);
	CHECK_MSTATUS(addAttribute( pSkySunGlow ));

	pSkySunSideGlow = nAttr.create("pSkySunSideGlow", "pSkySunSideGlow",  MFnNumericData::kFloat, 0.2);
	CHECK_MSTATUS(addAttribute( pSkySunSideGlow ));

	pSkySunBleed = nAttr.create("pSkySunBleed", "pSkySunBleed",  MFnNumericData::kFloat, 1.0);
	CHECK_MSTATUS(addAttribute( pSkySunBleed ));

	sunSizeMulti = nAttr.create("sunSizeMulti", "sunSizeMulti",  MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.1);
	nAttr.setSoftMax(64.0);
	CHECK_MSTATUS(addAttribute( sunSizeMulti ));

	dumpAndResume = nAttr.create("dumpAndResume", "dumpAndResume",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( dumpAndResume ));

	dumpExrFile = tAttr.create("dumpExrFile", "dumpExrFile",  MFnNumericData::kString);
	CHECK_MSTATUS(addAttribute( dumpExrFile ));

	uhdCacheType = eAttr.create("uhdCacheType", "uhdCacheType", 0, &stat);
	stat = eAttr.addField("Still", 0);
	stat = eAttr.addField("Animation", 1);
	CHECK_MSTATUS(addAttribute(uhdCacheType));

	globalVolume = mAttr.create("globalVolume", "globalVolume");
	CHECK_MSTATUS(addAttribute(globalVolume));

	globalMaterialOverride = nAttr.createColor("globalMaterialOverride", "globalMaterialOverride");
	CHECK_MSTATUS(addAttribute(globalMaterialOverride));

	globalDirectOverride = nAttr.createColor("globalDirectOverride", "globalDirectOverride");
	CHECK_MSTATUS(addAttribute(globalDirectOverride));

	globalReflectionOverride = nAttr.createColor("globalReflectionOverride", "globalReflectionOverride");
	CHECK_MSTATUS(addAttribute(globalReflectionOverride));

	globalRefractionOverride = nAttr.createColor("globalRefractionOverride", "globalRefractionOverride");
	CHECK_MSTATUS(addAttribute(globalRefractionOverride));

	useGlobalMaterialOverride = nAttr.create("useGlobalMaterialOverride", "useGlobalMaterialOverride", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(useGlobalMaterialOverride));

	useGlobalDirectOverride = nAttr.create("useGlobalDirectOverride", "useGlobalDirectOverride", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(useGlobalDirectOverride));

	useGlobalReflectionOverride = nAttr.create("useGlobalReflectionOverride", "useGlobalReflectionOverride", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(useGlobalReflectionOverride));

	useGlobalRefractionOverride = nAttr.create("useGlobalRefractionOverride", "useGlobalRefractionOverride", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(useGlobalRefractionOverride));

	lockSamplingPattern = nAttr.create("lockSamplingPattern", "lockSamplingPattern", MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute(lockSamplingPattern));

	uhdPrecision = nAttr.create("uhdPrecision", "uhdPrecision", MFnNumericData::kFloat, 1.0);
	nAttr.setMin(0.01);
	nAttr.setSoftMax(10.0);
	CHECK_MSTATUS(addAttribute(uhdPrecision));
	

	return stat;

}

