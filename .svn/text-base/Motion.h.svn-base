#ifndef __MOTION_H__
#define __MOTION_H__

#include <vector>
#include <map>

#include "ConfFileRead.h"
#include "WorldModel.h"
#include "CommandQuene.h"
#include "Situation.h"
#include "MotionGoto.h"
#include "HumanGoto.h"
#include "Dribble.h"
#include "Kick.h"
#include "HandleBall.h"
#include "MotionDribble.h"
#include "MotionKick.h"
#include "MotionPass.h"
#include "RunPosition.h"
#include "Action.h"
#include "Logger.h"
#include "Formation.h"

namespace motiontype
{
	enum MotionType
	{
		MT_Beam,
		MT_InitialStand,
		MT_BeamInitial,
		MT_TestNetState,
		MT_StandBy,
		MT_Stand,
		MT_DeadBallStand,
		//MT_GetUp,
		//MT_Goto,
		//MT_Dribble,
		MT_GoalieClearBall,
		MT_GoalieKickOffBall,
		MT_GoalieDefendPos,
		MT_GoalieDefendBall,
		MT_GoalieDefendSuper,
		MT_GoalieDeadBall,
		MT_DropDownLeft,
		MT_DropDownRight,
		MT_GoalieOther,
		MT_Attack,
		//MT_Intercept,
		MT_Defense,
		MT_Test,
		MT_SwingHead,

		MT_Dribble,
		MT_Pass,
		MT_Shoot,
		MT_RunPosition,
		MT_Intercept,
		MT_ClearBall,
		MT_StandPosition,
		MT_LocateBall,
		MT_InitStrategy,

		MT_CornerBall,

		MT_Block,

	};
};

using namespace motiontype;


class Motion
{
public:
	Motion( WorldModel *wm, CommandQuene *cmdQuene,Situation *mSit );
	~Motion();

public:
	bool DoMotion( MotionType motionType );
	bool IsActionDone();
	bool Do();

private:
	WorldModel *mWorldModel;
	CommandQuene *mCmdQuene;
	Situation *mSituation;
	MotionGoto *mGoto;
	MotionDribble *mDribble;
	MotionKick *mKick;
	MotionPass *mPass;
	RunPosition *mRunPosition;

	HumanGoto *mHGoto;
	Dribble *mHDribble;
	Kick *mHKick;
	Formation *mFormation;

public:
	Action *mAct;
public:
	Angle mYawAng;       
	Angle mPitchAng;
	
private:
	// 和 WorldModel 里面的内容重复了
	//struct BeamPara
	//{
	//	unsigned int playerNo;
	//	float beamPara[3];
	//};

	//vector<BeamPara> mBeamPara;
	bool mMotionTestGoto;
	
	AttackApproach mAttackApproach;

	void InitMotion();

private:
	bool MotionInitialStand();
	bool MotionBeam();
	bool MotionBeamInitial();
	bool MotionGetUp( bool reverseGetUp );
	bool MotionSideDownGetUp();
	bool MotionTest();

	bool MotionDeadBallStand();

	bool MotionVision();
public:
	void SetAttackApproach( AttackApproach attackApproach );

private:
	float mShouldGotoTime;
	bool HMotionIShosuldKick();
	bool HMotionDribble();
	bool HMotionPass();
	bool HMotionShoot();
	bool HMotionRunPosition();
	bool HMotionRunPositionDoGoto( Vector3f tarGoto, Angle tarAngle );
	bool HMotionIntercept();
	bool HMotionClearBall();
	bool HMotionStandPosition();
	bool HMotionBlock();

	bool HMotionGoalieKickBall();
	bool HMotionGoalieClearBall();
	bool HMotionGoalieDefendPos();
	bool HMotionGoalieDefendBall();
	bool HMotionGoalieDefendSuper();
	bool HMotionGoalieDeadBall();
	bool HMotionGoalieOther();
	bool HMotionLocateBall();
	bool HMotionCornerBall();
	bool HMotionInitialStrategy();
public:
	bool HMotionResetFrameNum();
};

#endif //__MOTION_H__