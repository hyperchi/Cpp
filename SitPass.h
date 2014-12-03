#ifndef __SITPASS_H__
#define __SITPASS_H__

#include "WorldModel.h"
#include "AgentInfo.h"
#include "SitUnitSquare.h"
#include "ConfFileRead.h"
#include "Logger.h"

class SitPass
{
public:
	SitPass( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo );
	~SitPass();

private:
	WorldModel *mWorldModel;
	FieldSquare *mFieldSquare;
	AgentInfo *mAgentInfo;

public:
	bool PassSquare( Vector3f &tarDribbleVector );
};


#endif //__SITPASS_H__