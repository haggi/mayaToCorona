#ifndef LightMaterialOverride_H
#define LightMaterialOverride_H

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
// the node defined in enviromentPortal.cpp. This provides draw support in
// Viewport 2.0.
//

#include <maya/MPxSurfaceShadingNodeOverride.h>

class LightMaterialOverride : public MHWRender::MPxSurfaceShadingNodeOverride
{
public:
	static MHWRender::MPxSurfaceShadingNodeOverride* creator(const MObject& obj);

	virtual ~LightMaterialOverride();

	virtual MHWRender::DrawAPI supportedDrawAPIs() const;
	virtual MString fragmentName() const;
	virtual MString primaryColorParameter() const;

private:
	LightMaterialOverride(const MObject& obj);
};

#endif // _LightMaterialOverride
