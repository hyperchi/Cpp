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
//	Vector3f mPos[HistoryNum];				// UpperTorso�� HistoryNum ����ʷλ��
//	float mVelX[HistoryNum - 1];			// UpperTorso�� HistoryNum - 1 ����ʷ�ٶȣ�����X�᷽��
//												// mVelX ��ǰ���죻��֮ǰ����
//	float mVelY[HistoryNum - 1];			// UpperTorso�� HistoryNum - 1 ����ʷ�ٶȣ�����Y�᷽��
//												// mVelY ��ƽ�ƿ죻��֮������
//	float mVelZ[HistoryNum - 1];			// UpperTorso�� HistoryNum - 1 ����ʷ�ٶȣ�����Z�᷽��
//												// mVelZ �󣺵������������ȶ��Բ��֮�ȶ��Ժ�
//	float mMaxSpeedX;
//	float mMaxSpeedY;
//
//	
//	Angle mBodyAngle[HistoryNum];			// Agent��HistoryNum����ʷ���峯��
//	Angle mTurnVel[HistoryNum - 1];			// Agent��Z�ᣨ��ˮƽ��ת�Ľ��ٶȣ�
//												// mTurnVel ��ת��죻��֮ת����
//	float mMaxTurnSpeed;
//
//	unsigned int mFallTimes;				// Agentˤ���Ĵ���
//	unsigned int mFallFaceUpTimes;			// Agent����ˤ���Ĵ���
//
//private:
//	vector<float> mNetSkipState;			// ͳ�� Server ��֡ ��Skipping��ʱ��ʹ���
//
//public:
//	void UpdateAgentInfo( Vector3f bodyPos, Angle bodyAng, bool isFalled, bool isFaceUpFalled );			// ����AgentInfo
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

	float mOppMaxSpeed;		// �ĳ�ƽ���ٶ���
	float mOurMaxSpeed;		// �ĳ�ƽ���ٶ���

	Vector3f mBallMoveTo;	// ����˶�����
	float mBallSpeed;		// ����ٶȣ�ƽ���ٶȣ�

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