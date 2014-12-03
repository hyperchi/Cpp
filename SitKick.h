#ifndef __SITKICK_H__
#define __SITKICK_H__

#include "WorldModel.h"
#include "AgentInfo.h"
#include "SitUnitSquare.h"
#include "ConfFileRead.h"
#include "Logger.h"

class SitKick
{
public:
	SitKick( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo );
	~SitKick();

private:
	WorldModel *mWorldModel;
	FieldSquare *mFieldSquare;
	AgentInfo *mAgentInfo;

public:
	bool KickSquare( Vector3f &tarKickVector );
	Vector3f KickTo( const Vector3f &tarKickVector, float kickDist );
	Vector3f PassTo();


private:
	bool IsObstacle( const Vector3f &tarKickVector );

public:
	float ShootWeight();
	float PassWeight();
};

#endif //__SITKICK_H__