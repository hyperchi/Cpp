//******************************************************************
//						Brain  类  ( Server 0.6 ）
//											By:	Leo		2008-9-10
//																
//						Agent 的决策类	
//
//******************************************************************
#ifndef __BRAIN_H__
#define __BRAIN_H__

#include "ConfFileRead.h"
#include "EnumType.h"
#include "WorldModel.h"
#include "Situation.h"
#include "Formation.h"
#include "CommandQuene.h"
#include "Motion.h"
#include "Vision.h"
#include "coach.h"
#include "Logger.h"
#include "Say.h"

class Brain
{
public:
	Brain( WorldModel *wm, CommandQuene *cmdQuene );
	~Brain();

private:
	WorldModel *mWorldModel;
	CommandQuene *mCmdQuene;
	Situation *mSituation;
	Vision *mVision;
	Motion *mMotion;
	Formation *mFormation;
	Coach *mCoach;
	Say *mSay;

public:
	void MainThink();		// Main决策函数

public:
	void ThinkBeam();
	void ThinkBeamInitial();

private:
	bool mBrainTest;
	void InitBrain();

	bool ThinkPrepare();
	
	void ThinkTest();
	void ThinkSwingHead();

	void ThinkHear_Say();
private:
	void ThinkNormal();		// 普通队员（非守门员）决策函数

	void ThinkNormalAttack( BasicStrategy basicStrategy );
	void ThinkNormalDefense( BasicStrategy basicStrategy );
	void ThinkInitialStrategy();

private:
	void ThinkGoalie();		// 守门员决策函数
	void ThinkKickOffBall();
	void ThinkDefendPos();
	void ThinkClearBall();
	void ThinkDefendSuper();
	void ThinkDefendBall();
	void ThinkGoalKick();
	void ThinkGoalieOther();

private:
	bool IsActionDone();
	void Do();
};

#endif //__BRAIN_H__