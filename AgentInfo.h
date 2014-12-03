#ifndef __AGENTINFO_H__
#define __AGENTINFO_H__

#include "Geometry.h"
#include "Logger.h"
#include "WorldModel.h"
#include <vector>

#define HistoryNum 20
#define SimStepTime 0.02f
#define PlayerOnField 10

//class AgentInfo
//{
//public:
//	AgentInfo();
//	~AgentInfo();
//
//private:
//	void AgentInfoInit();
//
//private:
//	Vector3f mPos[HistoryNum];				// UpperTorso的 HistoryNum 个历史位置
//	float mVelX[HistoryNum - 1];			// UpperTorso的 HistoryNum - 1 个历史速度（自身X轴方向）
//												// mVelX 大：前进快；反之前进慢
//	float mVelY[HistoryNum - 1];			// UpperTorso的 HistoryNum - 1 个历史速度（自身Y轴方向）
//												// mVelY 大：平移快；反之评议慢
//	float mVelZ[HistoryNum - 1];			// UpperTorso的 HistoryNum - 1 个历史速度（自身Z轴方向）
//												// mVelZ 大：颠簸厉害，即稳定性差；反之稳定性好
//	float mMaxSpeedX;
//	float mMaxSpeedY;
//
//	
//	Angle mBodyAngle[HistoryNum];			// Agent的HistoryNum个历史身体朝向
//	Angle mTurnVel[HistoryNum - 1];			// Agent绕Z轴（即水平旋转的角速度）
//												// mTurnVel 大：转身快；反之转身慢
//	float mMaxTurnSpeed;
//
//	unsigned int mFallTimes;				// Agent摔倒的次数
//	unsigned int mFallFaceUpTimes;			// Agent仰面摔倒的次数
//
//private:
//	vector<float> mNetSkipState;			// 统计 Server 跳帧 （Skipping）时间和次数
//
//public:
//	void UpdateAgentInfo( Vector3f bodyPos, Angle bodyAng, bool isFalled, bool isFaceUpFalled );			// 更新AgentInfo
//
//private:
//	void UpdateAgentVel();
//	void UpdateAgentTurnVel();
//	void UpdateAgentFallTime( bool isFalled, bool isFaceUpFalled );
//
//public:
//	float GetMaxSpeedX();
//	float GetMaxSpeedY();
//	
//	float GetMaxTurnSpeed();
//
//	float GetEvaluUpDownBump();
//
//	unsigned int GetFallTimes();
//	unsigned int GetFaceUpFallTimes();
//	unsigned int GetFaceDownFallTimes();
//
//	
//	void SetNetSkipTime( float skipTime );
//	unsigned int GetNetSkipNum();
//
//	void LogAgentInfo();
//
//private:
//	float mOppPlayerPos[PlayerOnField][HistoryNum];
//	float mOurPlayerPos[PlayerOnField][HistoryNum];
//	float mOppMaxSpeed;
//	float mOurMaxSpeed;
//
//public:
//	Update();
//};
//
//extern AgentInfo gAgentInfo;

class AgentInfo
{
public:
	AgentInfo( WorldModel *wm );
	~AgentInfo();

private:
	WorldModel *mWorldModel;

private:
	Vector3f mOppPlayerPos[PlayerOnField][HistoryNum];
	Vector3f mOurPlayerPos[PlayerOnField][HistoryNum];
	Vector3f mBallPos[HistoryNum];

	float mOppMaxSpeed;		// 改成平均速度了
	float mOurMaxSpeed;		// 改成平均速度了

	Vector3f mBallMoveTo;	// 球的运动方向
	float mBallSpeed;		// 球的速度（平均速度）

	Vector3f mBallAveragePos;

public:
	void Update();

	float GetOppMaxSpeed();
	float GetOurMaxSpeed();
	
	Vector3f GetBallMoveToPos();
	float GetBallSpeed();

	float GetBallAveragePosX();
};

#endif //__AGENTINFO_H__