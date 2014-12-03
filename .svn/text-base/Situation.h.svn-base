#ifndef __SITUATION_H__
#define __SITUATION_H__

#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

#include "AgentInfo.h"
#include "WorldModel.h"
#include "Formation.h"
#include "SitUnitSquare.h"
#include "SitDribble.h"
#include "SitKick.h"
#include "SitPass.h"
#include "SitRun.h"
#include "coach.h"
#include "ConfFileRead.h"
#include "Logger.h"

class Situation
{
public:
	Situation( WorldModel *wm, Formation *formation );
	~Situation();

private:
	WorldModel *mWorldModel;
	Formation *mFormation;
	AgentInfo *mAgentInfo;
	SitDribble *mSitDribble;
	SitKick *mSitKick;
	SitPass *mSitPass;
	SitRun *mSitRun;
	Coach *mCoach;

	float mOppMaxSpeed;
	float mOurMaxSpeed;
	unsigned int mOppGetUpCycle;
	unsigned int mOurGetUpCycle;

public:
	FieldSquare *mFieldSquare;

public:
	void Update();

	float OppMaxSpeed();
	float OurMaxSpeed();

	float DistMostNearOurGoal();
	unsigned int PlayerMostNearOurGoal();
	
	void OppDistMostNearBall( float &minDist, unsigned int &playerNum );		// 判断对方哪个队员距离球最近
	void OurDistMostNearBall( float &minDist, unsigned int &playerNum );		// 判断我方哪个队员距离球最近
	void OurOtherDistMostNearBall( float &minDist, unsigned int &playerNum );	// 判断我方哪个队员（除自己）距离球最近

	bool WeControlBall();
	bool IShouldGotoControlBall();
	bool SecondNearToBall();
	bool NearoppPlayer();
	bool ShouldAttack();
	AttDefkTrend AttackWeight();

	Vector3f InterceptPos();

	Vector3f DribbleTo( Vector3f tarDribbleVector );
	Vector3f KickTo( Vector3f tarKickVector, float kickDist );
	//Vector3f PassTo(  Vector3f tarKickVector, float kickDist );
	Vector3f PassTo();
	Vector3f AttackRunPos( AttDefkTrend attDefTrend );

	AttackApproach EvaluAttackApproach();				// 评估进攻途径
	AttackApproach AttackOrDefense();

	bool goalieLookSharp();
	bool goalieCatchBall();
	bool goaliePlayerExp();
	bool CaculatePlayerExp();

	bool goalieBack();
	bool goalieDeadBall();
	bool NotGoalKick();

	void OppDistMostNearOurGoal(float &minDist, unsigned int &playerNum );

	void PrintApproach( AttackApproach approach );

private:
	unsigned int OurNearPlayerToBall();		// 我方离球比我近的队员数目

private:
	unsigned int mOurControlBallCycle;
	unsigned int mOppControlBallCycle;

	unsigned int GetOurControlBallCycle();
	unsigned int GetOppControlBallCycle();

	// new 2009 robocup in Graz
public:
	bool IsTarInField( Vector3f tarVector );
	void OurMinDistToBall( float &minDist, unsigned int &playerNum );
	void OppMinDistToBall( float &minDist, unsigned int &playerNum );
	void OppMinDistToBall( Vector3f &oppMostNearPos);
	bool IControlingBall();
	bool WeControlingBall();
	bool SelfDistToBallMin();
	BasicStrategy GetBasicStrategy();

	int RealPlayerNo(int num,ObjectType obj);

	GoalieState GetGoalieState();
	void GetGoalieDefendBall(Vector3f& pos, Angle& ang);
	int CaculateDropDownSide();
	int GetGoalieDefendPos(Vector3f& pos, Angle& ang);
	bool GoalieDefendSuper();
	bool DefinePenltySmall(Vector3f pos);
	bool DefinePenlty(Vector3f pos);
	bool OppKickBall();
	void LookOppGoal(Vector3f& pos,Angle& ang);
	bool GoalieCanCatchBall(int& direction);
	bool GoalieFace2Ball();
	bool GoalieTurnOnly();
	bool BallAfterGoalie();
	Angle GoalieTurnAngle();
	void GetGoalieSuperTarget(Vector3f& pos,Angle& ang);
	float CacHistoryBallSpeed();
	bool OppNotControlBall();
	bool WeControlBallExpGoalie();
};


#endif //__SITUATION_H__