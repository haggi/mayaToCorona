#ifndef MTAP_CMD_H
#define MTAP_CMD_H

#include <string.h>
#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>
#include <maya/MString.h>

#define MAYATOCMDNAME "mayatoCorona"

class  MayaToCorona: public MPxCommand
{
public:
					MayaToCorona();
	virtual			~MayaToCorona(); 
	static MSyntax	newSyntax();

	MStatus     	doIt( const MArgList& args );
	static void*	creator();
	void setLogLevel();

private:
};

#endif