#ifndef CoronaSurfaceOverride_H
#define CoronaSurfaceOverride_H

//-
// ===========================================================================
// Copyright 2012 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//+

//
// This is the MPxSurfaceShadingNodeOverride implementation to go along with
// the node defined in CoronaSurface.cpp. This provides draw support in
// Viewport 2.0.
//

#include <maya/MPxSurfaceShadingNodeOverride.h>

class CoronaSurfaceOverride : public MHWRender::MPxSurfaceShadingNodeOverride
{
public:
	static MHWRender::MPxSurfaceShadingNodeOverride* creator(const MObject& obj);

	virtual ~CoronaSurfaceOverride();

	virtual MHWRender::DrawAPI supportedDrawAPIs() const;

	virtual MString fragmentName() const;
	virtual void getCustomMappings(
		MHWRender::MAttributeParameterMappingList& mappings);

	virtual MString primaryColorParameter() const;
	virtual MString transparencyParameter() const;
	virtual MString bumpAttribute() const;

private:
	CoronaSurfaceOverride(const MObject& obj);
	MString mfragmentName;
};

#endif // _CoronaSurfaceOverride
