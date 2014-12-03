//******************************************************************
//						Agent  类  ( Server 0.6 ）
//											By:	Leo		2008-9-10
//																
//					实现Agent与Server的完整交互过程	
//
//			1：接收Server的信息
//			2：决策
//			3: 发送信息
//
//					具体过程：
//
//			1: 请求Server加载一个Agent，确定Agent的模型（Nao)
//			2: 初始化Agent信息：队伍名称，号码
//			3：开始接收Server信息，进入循环  （接收时需要与Server保持同步）
//			4: 解析信息，并做出决策
//			5: 发送信息，回到步骤 3
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

	void AgentInit();									// 初始化Agent
	void mainLoop();									// Agent的主循环
	void GetWorldModelMsg( );							// 从Server接收WorldModel的信息

	CommandHandle		* mCmdHandle;
private:
	bool ParseWorldModelMsg( const string &msg );									// 解析WorldModel信息
	bool DelayForSynch( float &currSimTime, float &lastSimTime, float timeDiff );	// 与Server同步

private:
	Event wakeUpThinkEvent;
	char strServerMsg[MaxMsgLength];					//待加临界区

	int		mMyPlayerNo;								// 自己的队员号码
	string	mAgentConfPath;								// Agent配置文件的路径

	BasicConfiguration	* mBasicConfig;
	TRoboCupConnection	* mConnection;
	WorldModel			* mWorldModel;

	CommandQuene		* mCmdQuene;
	Brain				* mThink;

	void SetWaitTime( float thinkTime );

	bool IsIntSimTimeFourTimes(float currentTime);						// 判断加载Agent时的仿真时间是否是 4 的整数倍
																		
	void DelayForServer( );												// 用于与Server的同步										
	
	bool InitialAgent( float serverStartTime );							// Initial the agent and do synchronization with server
	bool BeamAgentForSynch( float serverStartTime );					// Beam the agent for the synchronization with server
	
	void SendPlayerInformation();
	void SendPlayerInitializePosition();
	void SendCommand( const char * str );
	void SendCommand();
	void SendZeroCommand();												// Server跳帧时发送“全零”指令（即全部关节角度保持不变）

	void GetMyPlayerNo();
	void GetAgentConfPath( string agetConfPath );
	bool ReadAgentConf();

	Timing currRunTime;

	float mTimeDifferent;
	deque<float> mReceiveTimeList;
	void SortReceiveTimeList();
};
#endif __AGENT_H__