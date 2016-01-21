#include "coronaOSLMapUtil.h"
#include "world.h"

static Logging logger;

Corona::SharedPtr<Corona::Abstract::Map> getOslTexMap(MString& attributeName, MFnDependencyNode& depFn, ShadingNetwork& sn, OSL::OSLShadingNetworkRenderer *oslRenderer)
{
	MStatus status;

	MAYATO_OSLUTIL::OSLUtilClass OSLShaderClass;
	OSLShaderClass.oslRenderer = oslRenderer;

	size_t numNodes = sn.shaderList.size();
	MString OSLInterfaceName = depFn.name() + "_" + attributeName + "_OSLInterface";
	MString shaderGroupName = depFn.name() + "_" + attributeName + "_OSLShadingGroup";
	OSL::ShaderGroupRef shaderGroup = oslRenderer->shadingsys->ShaderGroupBegin(shaderGroupName.asChar());
	OSLShaderClass.group = shaderGroup.get();

	MObject thisMObject = depFn.object();
	MString outPlugName;
	MString connectedObjectName = getObjectName(getOtherSideSourceNode(attributeName, thisMObject, true, outPlugName));

	Logging::debug(MString("getOslTexMap: ") + connectedObjectName + "." + outPlugName + " is connected with " + depFn.name() + "." + attributeName);
	MPlug shaderPlug = depFn.findPlug(attributeName);

	OSLShaderClass.createOSLProjectionNodes(shaderPlug);

	for (int shadingNodeId = 0; shadingNodeId < numNodes; shadingNodeId++)
	{
		ShadingNode snode = sn.shaderList[shadingNodeId];
		Logging::debug(MString("ShadingNode Id: ") + shadingNodeId + " ShadingNode name: " + snode.fullName);
		//OSLShaderClass.createOSLHelperNodes(sn.shaderList[shadingNodeId]);
		OSLShaderClass.createOSLShadingNode(sn.shaderList[shadingNodeId]);
		//OSLShaderClass.connectProjectionNodes(sn.shaderList[shadingNodeId].mobject);

		if (snode.fullName == connectedObjectName.asChar())
		{
			//OSLShaderClass.createOSLHelperNodes(sn.shaderList[sn.shaderList.size() - 1]);
			Logging::debug(MString("connected node found: ") + snode.fullName + " search output attr.");

			for (size_t outId = 0; outId < snode.outputAttributes.size(); outId++)
			{
				ShaderAttribute& sa = snode.outputAttributes[outId];
				if (MString(sa.name.c_str()) == outPlugName)
				{
					Logging::debug(MString("connected out attr found: ") + sa.name.c_str() + " ");

					MString destParam;
					MString sourceParam = outPlugName;
					MString sourceNode = connectedObjectName;
					if ((sa.type == "color") || (sa.type == "vector"))
					{
						// lets see if we have a color helper node
						MString helperNodeName = "";// OSLShaderClass.createPlugHelperNodeName(attributeName.asChar(), thisMObject, false);
						Logging::debug(MString("Interface connection - color/vector attribute ") + sa.name.c_str() + " search for helper node " + helperNodeName);
						if (OSLShaderClass.doesOSLNodeAlreadyExist(helperNodeName))
						{
							Logging::debug(MString("Found helper node name."));
							sourceParam = "outputValue";
							sourceNode = helperNodeName;
						}
						destParam = "inVector";
					}
					if (sa.type == "float")
					{
						destParam = "inFloat";
					}
					if (sa.type == "int")
					{
						destParam = "inInt";
					}
					if (sa.type == "bool")
					{
						destParam = "inBool";
					}

					if (sourceParam == "output")
						sourceParam = "outOutput";

					MAYATO_OSL::OSLParamArray params;
					// if we have a color/vector input, try to find a multiplier attribute
					MString multiplierName = attributeName + "Multiplier";
					MPlug multiplierAttribute = depFn.findPlug(multiplierName, true, &status);
					if (status)
					{
						Logging::debug(MString("Found multiplier attribute: ") + multiplierName);
						float multiplier = multiplierAttribute.asFloat();
						float offset = 0.0f;
						if ((attributeName == "refractionIndex") || (attributeName == "reflectionIor"))
						{
							offset = -1.0f;
						}
						MAYATO_OSL::OSLParameter parmA("multiplier", multiplier);
						params.push_back(parmA);
						MAYATO_OSL::OSLParameter parmB("offset", offset);
						params.push_back(parmB);
					}
					//Logging::debug(MString("creating OSLInterface shader ") + OSLInterfaceName);
					MAYATO_OSL::OSLNodeStruct oslNode;
					//bool success = oslRenderer->shadingsys->Shader("surface", "OSLInterface", OSLInterfaceName.asChar());
					oslNode.nodeName = OSLInterfaceName;
					oslNode.typeName = "OSLInterface";
					oslNode.paramArray = params;
					OSLShaderClass.oslNodeArray.push_back(oslNode);
					MAYATO_OSL::Connection c;
					c.sourceNode = sourceNode;
					c.sourceAttribute = sourceParam;
					c.destNode = OSLInterfaceName;
					c.destAttribute = destParam;
					OSLShaderClass.addConnectionToList(c);
					//Logging::debug(MString("connecting ") + sourceNode + "." + sourceParam + " -> " + OSLInterfaceName + "." + destParam);
					//success = oslRenderer->shadingsys->ConnectShaders(sourceNode.asChar(), sourceParam.asChar(), OSLInterfaceName.asChar(), destParam.asChar());
					break;
				}
			}
			break;
		}
	}

	OSLShaderClass.cleanupShadingNodeList();
	OSLShaderClass.createAndConnectShaderNodes();


	if (!oslRenderer->shadingsys->ShaderGroupEnd())
	{
		Logging::debug("Problem finishing shader group");
	}
	std::string serialized;
	oslRenderer->shadingsys->getattribute(shaderGroup.get(), "pickle", serialized);
	Logging::debug(MString("Serialized: ") + serialized.c_str());

	Corona::SharedPtr<Corona::Abstract::Map> oslMapp = new OSLMap;
	OSLMap *oslMap = (OSLMap *)oslMapp.getReference();
	oslMap->oslRenderer = oslRenderer;
	oslMap->shaderGroup = shaderGroup;
	
	if (depFn.object().hasFn(MFn::kLight))
		oslMap->isLightMap = true;

	if (attributeName == "normalCamera")
	{
		oslMap->bumpType = OSLMap::NONE;
		// we only support direct bumpmap connections
		MPlug ncPlug = depFn.findPlug("normalCamera");
		if (ncPlug.isConnected())
		{
			MPlugArray pa;
			ncPlug.connectedTo(pa, true, false);
			if (pa.length() > 0)
			{
				for (uint pId = 0; pId < pa.length(); pId++)
				{
					if (pa[pId].node().hasFn(MFn::kBump) || pa[pId].node().hasFn(MFn::kBump3d))
					{
						MFnDependencyNode bumpFn(pa[pId].node());
						MPlug interpPlug = bumpFn.findPlug("bumpInterp");
						if (interpPlug.asInt() == 0)
							oslMap->bumpType = OSLMap::BUMP;
						if (interpPlug.asInt() == 1)
							oslMap->bumpType = OSLMap::NORMALTANGENT;
						if (interpPlug.asInt() == 2)
							oslMap->bumpType = OSLMap::NORMALOBJECT;
						if (pa[pId].node().hasFn(MFn::kBump3d))
							oslMap->bumpType = OSLMap::BUMP3D;
					}
				}
			}
		}
	}
	return oslMapp;
}
