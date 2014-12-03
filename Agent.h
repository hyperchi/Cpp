//******************************************************************
//						Agent  ��  ( Server 0.6 ��
//											By:	Leo		2008-9-10
//																
//					ʵ��Agent��Server��������������	
//
//			1������Server����Ϣ
//			2������
//			3: ������Ϣ
//
//					������̣�
//
//			1: ����Server����һ��Agent��ȷ��Agent��ģ�ͣ�Nao)
//			2: ��ʼ��Agent��Ϣ���������ƣ�����
//			3����ʼ����Server��Ϣ������ѭ��  ������ʱ��Ҫ��Server����ͬ����
//			4: ������Ϣ������������
//			5: ������Ϣ���ص����� 3
//
//******************************************************************
#ifndef __AGENT_H__
#define __AGENT_H__

#include "BasicConfigure.h"
#include "Logger.h"
#include "Timer.h"
#include "Connection.h"
#include "CommandQuene.h"
#include "CommandHandle.h"
#include "WorldModel.h"
#include "Attitude.h"
#include "Brain.h"
#include "AgentInfo.h"
#include "linuxthread.h"
#include <deque>

#define MaxMsgLength 10000

class Agent
{
public:
	
	Agent( BasicConfiguration * basicConf, TRoboCupConnection * connection, WorldModel * wm );
	~Agent();

	void AgentInit();									// ��ʼ��Agent
	void mainLoop();									// Agent����ѭ��
	void GetWorldModelMsg( );							// ��Server����WorldModel����Ϣ

	CommandHandle		* mCmdHandle;
private:
	bool ParseWorldModelMsg( const string &msg );									// ����WorldModel��Ϣ
	bool DelayForSynch( float &currSimTime, float &lastSimTime, float timeDiff );	// ��Serverͬ��

private:
	Event wakeUpThinkEvent;
	char strServerMsg[MaxMsgLength];					//�����ٽ���

	int		mMyPlayerNo;								// �Լ��Ķ�Ա����
	string	mAgentConfPath;								// Agent�����ļ���·��

	BasicConfiguration	* mBasicConfig;
	TRoboCupConnection	* mConnection;
	WorldModel			* mWorldModel;

	CommandQuene		* mCmdQuene;
	Brain				* mThink;

	void SetWaitTime( float thinkTime );

	bool IsIntSimTimeFourTimes(float currentTime);						// �жϼ���Agentʱ�ķ���ʱ���Ƿ��� 4 ��������
																		
	void DelayForServer( );												// ������Server��ͬ��										
	
	bool InitialAgent( float serverStartTime );							// Initial the agent and do synchronization with server
	bool BeamAgentForSynch( float serverStartTime );					// Beam the agent for the synchronization with server
	
	void SendPlayerInformation();
	void SendPlayerInitializePosition();
	void SendCommand( const char * str );
	void SendCommand();
	void SendZeroCommand();												// Server��֡ʱ���͡�ȫ�㡱ָ���ȫ���ؽڽǶȱ��ֲ��䣩

	void GetMyPlayerNo();
	void GetAgentConfPath( string agetConfPath );
	bool ReadAgentConf();

	Timing currRunTime;

	float mTimeDifferent;
	deque<float> mReceiveTimeList;
	void SortReceiveTimeList();
};
#endif __AGENT_H__