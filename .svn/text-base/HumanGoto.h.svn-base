#ifndef __HUMANGOTO_H__
#define __HUMANGOTO_H__

#include "stdafx.h"
#include "Obstacle.h"
#include "WorldModel.h"
#include "CommandQuene.h"
#include "Situation.h"
#include "Action.h"
#include "Logger.h"

#include <deque>

namespace HGSpeedStatus
{
	enum GogoMode
	{
		//GM_NoChange	= 0,
		//GM_AccFor	= 1,
		//GM_DecFor	= 2,
		//GM_AccTurn	= 4,
		//GM_DecTurn	= 8,
		//GM_AccTrans	= 16,
		//GM_DecTrans	= 32,
		GM_StandBy,
		GM_For,
		GM_Turn,
		GM_Trans,
		GM_CTurn
	};

	enum BodyHeight
	{
		BH_High,
		BH_Low,
	};
};
using namespace HGSpeedStatus;

class HumanGoto
{
public:
	HumanGoto( WorldModel *wm, Situation *situ, CommandQuene *cmdQuene, Action *act );
	~HumanGoto();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	Action *mAct;
	Obstacle *mObstacle;

private:
	const float cForMaxSpeed;
	const float cForMinSpeed;
	const float cTransMaxSpeed;
	const float cTransMinSpeed;
	const float cTurnMaxAngle;
	const float cTurnMinAngle;

	const float cForAcc;
	const float cTransAcc;
	const float cTurnAcc;

	const float cForProp;
	const float cTransProp;
	const float cTurnProp;

	float mForCurrSpeed;
	float mTransCurrSpeed;
	float mTurnCurrSpeed;
	BodyHeight mBodyHeight;
	
	void SpeedLimit( float &forSpeed, float &transSpeed, Angle &turnSpeed );
	void BasicWalkSpeedControl( float &forSpeed, float &transSpeed, float &turnSpeed );
	void BufferSpeedControl();
	bool mIsLastBuffer;
	
	struct SpeedValue
	{
		float gameTime;
		BodyHeight bodyHeight;
		float forSpeed;
		float transSpeed;
		float turnSpeed;
	};
	deque<SpeedValue> mSpeedDeque;
public:
	void ClearSpeedDeque();
	void ClearSpeed();
	void SetSpeed( float forSpeed, float transSpeed, float turnSpeed );
	bool DoHumanGoto();
private:
	void UpdateSpeedDeque();
	
	GogoMode mGotoMode;
	void SetCurrGogoMode( GogoMode gotoMode );
	void SetCurrLongGogoMode( Vector3f tarVec ); 
	void SetCurrNearGotoMode( Vector3f tarVec ); 
	void SetCurrSpeed( Vector3f tarVec );
	void SetCurrSpeed( Angle tarBodyAng );
	void SetCurrForSpeed( float idealForSpeed , float idealTurnSpeed, float idealTransSpeed );
	void SetCurrTurnSpeed( float idealForSpeed, float idealTurnSpeed, float idealTransSpeed );
	void SetCurrTransSpeed( float idealForSpeed, float idealTurnSpeed, float idealTransSpeed );
	void SetCurrStandSpeed();

public:
	bool IsStandingBy();
	bool IsStandingByWithTurn();
	bool IsFullSpeed();
	bool GotoTar( Vector3f tarVec );
	bool GotoTar( Vector3f tarVec, Angle tarBodyAng );
	bool GotoNearTar( Vector3f tarVec, Angle tarBodyAng );
	bool TranstoTar( Vector3f tarVec );
	bool TranstoTar( Vector3f tarVec, Angle tarBodyAng );
	bool noLimitGoTar(Vector3f tarVec, Angle tarBodyAng);
	bool noLimitGoNearTar(Vector3f tarVec, Angle tarBodyAng);
private:
	bool GotoLong( Vector3f tarVec, Angle tarBodyAng );
	bool GotoNear( Vector3f tarVec, Angle tarBodyAng );
	bool TranstoNear( Vector3f tarVec, Angle tarBodyAng );
public:
	bool QuickTurn( Angle tarBodyAng );
	bool CrazyTurn( Angle tarBodyAng );
};

#endif //__HUMANGOTO_H__