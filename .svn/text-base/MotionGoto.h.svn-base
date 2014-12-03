#ifndef __MOTION_GOTO_H__
#define __MOTION_GOTO_H__

#include "WorldModel.h"
#include "CommandQuene.h"
#include "Situation.h"
#include "Action.h"
#include "Logger.h"

namespace gotoEPS
{
	enum GotoEps
	{
		GotoEps_Rough,
		GotoEps_Medium,
		GotoEps_Accurate,
		GotoEPS_Count,
	};
};

using namespace gotoEPS;

class MotionGoto
{
public:
	MotionGoto( WorldModel *wm, Situation *situ, CommandQuene *cmdQuene, Action *act );
	~MotionGoto();

public:
	bool Goto();		// For Test
	bool Goto( Vector3f targetVector );
	bool FastGoto( Vector3f targetVector );
	bool FastGotoDribble( Vector3f targetVector );

	bool Turn( Angle targetAngle );
	bool SmartTurnAllowBack( Angle targetAngle );
	bool SmartTurnAllowTrans( Angle targetAngle );
	
	bool Goto( Vector3f targetVector,Angle targetAngle );
	
	bool GotoHandleBall( Vector3f tarVector3f );
	bool FacingTheBall( Angle &tarAng );
	bool FacingTheBall();
	bool FacingTarget( Vector3f targetVector );

	bool SmartGotoAllowBack( Vector3f targetVector );
	bool SmartGotoAllowBack( Vector3f targetVector, Angle targetAngle );
	bool SmartGotoAllowTrans( Vector3f targetVector );
	bool SmartGotoAllowTrans( Vector3f targetVector, Angle targetAngle );

	bool TurnAroundBall( bool leftTurn );

	bool Trans( float distToTrans );

	bool SlowDownSpeedToStand();

	void SetGotoEps( GotoEps distEps, GotoEps angEps );

	float ForSpeed();
	float TurnSpeed();
	float TranSpeed();

	bool PowerSpeedBack();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	Action *mAct;

private:
	bool mGotoTestVecAndAng;
	Vector3f mGotoTestVector3f;
	Angle mGotoTestAngle;

	void InitGoto();

	Angle AngleLiminit( Angle ang );
	Angle AngleLimit90( Angle ang );
	Angle AngleLimit45( Angle ang );

	float DistToVector3f( Vector3f targetVector );
	Angle AngToTarAngle( Angle targetAngle );
	Angle AngEpsFromDist( Vector3f targetVector );

	bool InEps( Vector3f targetVector,Angle targetAngle );
	bool DistInEps( Vector3f targetVector );
	bool AngInEps( Angle targetAngle );

private:
	float mForStartSpeed;
	float mTurnStartSpeed;
	float mTransStartSpeed;

	float mForMaxSpeed;
	float mTurnMaxSpeed;
	float mTransMaxSpeed;

	float mForMinSpeed;
	float mTurnMinSpeed;
	float mTransMinSpeed;

	float mForAccSpeed;
	float mTurnAccSpeed;
	float mTransAccSpeed;

	float mForProportion;	
	float mTurnProportion;
	float mTransProportion;
	
	float mForSpeed;
	float mTurnSpeed;
	float mTransSpeed;

	GotoEps mDistEps;
	GotoEps mAngEps;
	float mGotoDistEPS[GotoEPS_Count];
	float mGotoAngEPS[GotoEPS_Count];
	float mOverFlowToTarFor;
	float mOverFlowToTarTurn;
	float mOverFlowToTarTrans;

public:
	void ForSpeedLimit( float forSpeed );
	void TurnSpeedLimit( float turnAng );
	void TransSpeedLimit( float tranSpeed );
	void SpeedLimit();

public:
	void ClearSpeed();
	float GetForSpeed();
	float GetTurnSpeed();
	float GetTransSpeed();
	
	void SetForSpeed( float forSpeed );
	void SetTurnSpeed( float turnSpeed );
	void SetTransSpeed( float tranSpeed );

	void SetForAccSpeed( float forAccSpeed );

private:
	bool SmartTurn( Angle targetAngle );
	bool SmartFor( float dist );
	bool SmartTrans( float dist );

public:
	bool SmartGoto( Vector3f targetVector );
	bool SmartGoto( Vector3f targetVector, Angle targetAngle );

	bool SmartTurnForGoto( Angle targetAngle, float distEps );
	bool SmartFastGoto( Vector3f targetVector, float distEps );

private:
	bool IsObstacle( Vector3f tarVector3f, Vector3f obsVector3f );
	
public:
	bool IsOurPlayerObstacle( Vector3f tarVector3f );
	bool IsOppPlayerObstacle( Vector3f tarVector3f );
	Vector3f GetRidOfObstacle( Vector3f tarVector3f );
	
};

#endif //__MOTION_GOTO_H__