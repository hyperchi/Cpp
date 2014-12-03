#ifndef __KICK_H__
#define __KICK_H__

#include "stdafx.h"
#include "WorldModel.h"
#include "CommandQuene.h"
#include "Situation.h"
#include "Logger.h"
#include "HumanGoto.h"

class Kick
{
public:
	Kick( WorldModel *wm, Situation *situ, HumanGoto *hGoto, CommandQuene *cmdQuene, Action *act );
	~Kick();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	HumanGoto *mHGoto;
	Action *mAct;
public:
	bool IsalreadyStand;
	bool IsalreadyTurn;

private:
	bool BallInShootArea();

	bool GetShootViability( Vector3f tarDribbleTo );
	bool GetPassViability( Vector3f tarDribbleTo );
	bool GetKickAttackViability( Vector3f tarDribbleTo );

	bool IsBehindBallKickPos( Vector3f tarKickTo );
public:
	bool IsInKickArea( Vector3f tarKickTo );
	bool Shoot();
	bool Pass();
	bool KickAttack();
	bool DoKickAction( Vector3f tarKickTo );
};

#endif //__KICK_H__