#ifndef __SITRUN_H__
#define __SITRUN_H__

#include "WorldModel.h"
#include "AgentInfo.h"
#include "SitUnitSquare.h"
#include "ConfFileRead.h"
#include "Logger.h"

class SitRun
{
public:
	SitRun( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo );
	~SitRun();

private:
	WorldModel *mWorldModel;
	FieldSquare *mFieldSquare;
	AgentInfo *mAgentInfo;

public:
	Vector3f AttackRunPos( AttDefkTrend attDefTrend );

private:
	Vector3f FullAttackRunPos();
	Vector3f TrendAttackRunPos();
	Vector3f NormalAttackRunPos();

	Vector3f FullDefenceRunPos();
	Vector3f TrendDefenceRunPos();
	Vector3f NormalDefenceRunPos();
};

#endif //__SITRUN_H__