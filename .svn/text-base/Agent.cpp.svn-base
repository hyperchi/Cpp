#include "Agent.h"
#include <unistd.h>
#include "linuxthread.h"
#define AgentLog gLog << "[Agent ] "

/***********************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
CommandHandle *gCmdHandle = NULL;
bool gParseCommandError = false;
// long gReceiveMessageNum = 0;
// long gSendCommandNum = 1;
/*********************************************************
* 函数名 ：static void ElsfTimer(int signo)
*
* 参数  ：int signo
*
* 功能描述 ：得到当前时间。
*    ElsfTimer 是中断响应函数，把发消息的部分丢在这里面
* 返回值 ：无
**********************************************************/
static void ElsfTimer(int signo)
{
	signal(SIGALRM, SIG_IGN);
	//
	//struct timeval  tp;
	//struct tm *tm;

	//////tp.tv_sec 秒。 tp.tv_usec 微妙
	//gettimeofday(&tp,NULL);

	//tm=localtime(&tp.tv_sec);

	//long usec = tp.tv_usec;
	//AgentLog << "EksfTime Usec " << usec << endl;
	////printf(" usec = %ld \n",tp.tv_usec);
	if( !gParseCommandError )
	{
		gCmdHandle->SendCommand();
	}
	else
	{
		string zeroMsg = "(he1 0.00)(he2 0.00)(lae1 0.00)(lae2 0.00)(lae3 0.00)(lae4 0.00)(lle1 0.00)(lle2 0.00)(lle3 0.00)(lle4 0.00)(lle5 0.00)(lle6 0.00)(rae1 0.00)(rae2 0.00)(rae3 0.00)(rae4 0.00)(rle1 0.00)(rle2 0.00)(rle3 0.00)(rle4 0.00)(rle5 0.00)(rle6 0.00)";
		gCmdHandle->SendCommand( zeroMsg.data() );
	}
// 	AgentLog << " gSendCommandNum " << gSendCommandNum << endl;
// 	gSendCommandNum ++;
}

/*********************************************************
* 函数名 ：staitc void InitTime(void)
*
* 参数  ：无
*
* 功能描述 ：初始化定时器。
*    
* 返回值 ：无
**********************************************************/
static void InitTime(int tv_sec,int tv_usec)
{
	AgentLog << "InitTime " << tv_usec << endl;

	struct timeval  tp;
	struct tm *tm;

	gettimeofday(&tp,NULL);
	tm=localtime(&tp.tv_sec);
	long usec = tp.tv_usec;
	struct itimerval value;

	signal(SIGALRM, ElsfTimer);

	value.it_value.tv_sec = tv_sec;  //秒
	value.it_value.tv_usec = tv_usec; // 纳秒
	value.it_interval.tv_sec = tv_sec;
	value.it_interval.tv_usec = tv_usec;
	setitimer(ITIMER_REAL, &value, NULL);
}

/************************************************/



Agent::Agent( BasicConfiguration * basicConf, TRoboCupConnection * connection, WorldModel * wm )
{
	mBasicConfig    = basicConf;
	mConnection     = connection;
	mWorldModel     = wm;
	
	mCmdQuene		= new CommandQuene;
	mCmdHandle		= new CommandHandle( mConnection, mCmdQuene );

	mThink			= new Brain( mWorldModel, mCmdQuene );
	
	AgentInit();
	
	wakeUpThinkEvent.ResetEvent();
	mCmdHandle->SendCommand( "(scene rsg/agent/nao/nao.rsg)" );		// 请求Server加载一个Agent（模型是Nao）
	//mCmdHandle->SendCommand( "(scene rsg/agent/soccerbot058/soccerbot.rsg)" );		// 请求Server加载一个Agent（模型是Nao）
	//gSendCommandNum ++;
	mTimeDifferent = 0.0f;
}
Agent::~Agent()
{
	if( mCmdQuene ) 
	{
		delete mCmdQuene;
		mCmdQuene = NULL;
	}
	if( mCmdHandle ) 
	{
		delete mCmdHandle;
		mCmdHandle = NULL;
	}
	if( mThink ) 
	{
		delete mThink;
		mThink = NULL;
	}
}

void Agent::AgentInit()
{
	GetMyPlayerNo();
}

void Agent::SetWaitTime(  float thinkTime  )
{
	float meanFloat = 0.0f;
	int count = 0;
	int minReceiveTime = -1;
	int maxReceiveTime = -1;
	float tempMaxReceiveTime = -100.0f;
	float tempMinReceiveTime = 100.0f;

	//SortReceiveTimeList();
	//deque<float> thisCycleReceiveTime;
	//for( int i = 1; i < mReceiveTimeList.size(); i = i + 2 )
	//{
	//	thisCycleReceiveTime.push_back( mReceiveTimeList.at(i) );
	//}

	//for( int i = 2; i < thisCycleReceiveTime.size() - 2; i = i++ )
	//{
	//	meanFloat += mReceiveTimeList.at(i);
	//	count ++;
	//}

	for( int i = 1; i < mReceiveTimeList.size(); i = i + 2 )
	{
		if( mReceiveTimeList[i] > tempMaxReceiveTime )
		{
			tempMaxReceiveTime = mReceiveTimeList[i];
			maxReceiveTime = i;
		}
		if( mReceiveTimeList[i] < tempMinReceiveTime )
		{
			tempMinReceiveTime = mReceiveTimeList[i];
			minReceiveTime = i;
		}
	}

	for( int i = 1; i < mReceiveTimeList.size(); i = i + 2 )
	{
		if( i != maxReceiveTime && i != minReceiveTime )
		{
			meanFloat += mReceiveTimeList[i];
			count ++;
		}
	}

	meanFloat = meanFloat / (float)count;

	// 4(opp) vs 3(us) 0.006f ---- 0.014f
	// 3(opp) vs 3(us) 0.006f ---- 0.016f
	// 3(us)  vs 3(opp)0.006f ---- 0.014f
	float basicDiffTime = 0.008f;
	if( mWorldModel->mTeamSide == SD_RIGHT )
	{
		basicDiffTime = 0.010f;
	}
 	if( mWorldModel->mMyPlayerNo == 4 )
 	{
 		mTimeDifferent = meanFloat - basicDiffTime - 0.0f - thinkTime;
 	}
 	else if( mWorldModel->mMyPlayerNo == 1 )
 	{
 		mTimeDifferent = meanFloat - basicDiffTime - 0.0016f - thinkTime;
 	}
 	else
 	{
 		mTimeDifferent = meanFloat - basicDiffTime - 0.0032f - thinkTime;
 	}

	//if( mWorldModel->mGameTime < 0.02f )
	//{
	//	mTimeDifferent = 0.0f;
	//}

	AgentLog << " meanFloat " << meanFloat << " mTimeDifferent " << mTimeDifferent << " mWorldModel->mMyPlayerNo " << mWorldModel->mMyPlayerNo << endl;

	//if( mTimeDifferent > 0.019f )
	//{
	//	mTimeDifferent = 0.019f;
	//}
}

void Agent::mainLoop()
{	
	string msg;
	bool agentInitialed = false;
	bool agentBeamed = false;

	currRunTime.restartTime();
	mReceiveTimeList.resize( 20 );

	float currReceiveMsgTime;
	float lastReceiveMsgTime;

	gCmdHandle = mCmdHandle;
	float justBeforeThinkTime = 0.0f;
	float justAfterThinkTime = 0.0f;

	while( true )
	{	
		AgentLog << "WaitEvent " << currRunTime.getElapsedTime(1) << endl;
		//GetWorldModelMsg();
		//const struct timespec rem = { 0, 20*1000.0f };
		//wakeUpThinkEvent.WaitEvent(&rem);
		wakeUpThinkEvent.WaitEvent(NULL);
		AgentLog << "WaitEvent time: pass" << endl;	
		wakeUpThinkEvent.ResetEvent();
		float beforeThinkTime = currRunTime.getElapsedTime(1);
		AgentLog << "Receive time: " << currRunTime.getElapsedTime(1) << endl;	
		lastReceiveMsgTime = currReceiveMsgTime;
		currReceiveMsgTime = currRunTime.getElapsedTime(1);
		mReceiveTimeList.push_front( currReceiveMsgTime - lastReceiveMsgTime );
		mReceiveTimeList.pop_back();
	
		msg = string(strServerMsg);
		gParseCommandError = false;

		if( !ParseWorldModelMsg( msg ) )
		{
			gParseCommandError = true;
			//continue;
		}

		static float serverStartTime = mWorldModel->mSimTime;

		if( !agentInitialed )
		{	
			agentInitialed = InitialAgent( serverStartTime );
		}
		else if( !agentBeamed )
		{
			agentBeamed = BeamAgentForSynch( serverStartTime );
		}
		else
		{	
			if( !gParseCommandError )
			{ 
				justBeforeThinkTime = currRunTime.getElapsedTime(1);
				mThink->MainThink();
				justAfterThinkTime = currRunTime.getElapsedTime(1);
			}
			AgentLog << "just think time " << (justAfterThinkTime - justBeforeThinkTime) * 1000.0f << endl; 
			//SetWaitTime( currRunTime.getElapsedTime(1) - beforeThinkTime );
			AgentLog << "MainThink " << (currRunTime.getElapsedTime(1) - beforeThinkTime) * 1000.0f << endl;;
			//DelayForServer();
			SendCommand();	
			AgentLog << "MainThink " << (currRunTime.getElapsedTime(1) - beforeThinkTime) * 1000.0f << endl;;
		}
	}
}

//******************************************************************
//			从Server接收WorldModel信息，保存在 serverMsg 中
//******************************************************************
void Agent::GetWorldModelMsg()
{
	char ServerMsg[MaxMsgLength];		//待加临界区
	int faileReceiveNum = 0;
	float currSimTime = mWorldModel->mSimTime;
	float lastSimTime = mWorldModel->mSimTime;
 	while(1)
 	{
 		lastSimTime = currSimTime;
 		currSimTime = mWorldModel->mSimTime;
 		if( fabs(lastSimTime - currSimTime) > EPS )
 		{
 			faileReceiveNum = 0;
 		}
 
 		if( mConnection->getMessage( ServerMsg, MaxMsgLength ) )
 		{
 			AgentLog << "SetEvent " << currRunTime.getElapsedTime( 1 ) << endl;
//  			AgentLog << " gReceiveMessageNum " << gReceiveMessageNum << endl;
//  			gReceiveMessageNum ++;
//  			if( gReceiveMessageNum > gSendCommandNum + 1 )
//  			{
//  				AgentLog << "Send Command Error! " << gReceiveMessageNum << " " << gSendCommandNum << endl;
//   				gCmdHandle->SendCommand();
//   				gReceiveMessageNum = 0;
//   				gSendCommandNum = 0;
//  			}
 			strcpy(strServerMsg,ServerMsg);
 			signal(SIGALRM, SIG_IGN);
 			wakeUpThinkEvent.SetEvent();
 		}
 		else
 		{
 			faileReceiveNum ++;
 		}
 
 		if( faileReceiveNum >= 10 )
 		{
 			//AgentLog<< "Network Error: Receive Message Failded " << endl;
 			//exit(1);
		}
 	}
}

//******************************************************************
//			解析并更新WorldModel信息
//******************************************************************
bool Agent::ParseWorldModelMsg( const string &msg )
{
	int leftNum = 0;
	int rightNum = 0;
	int lastRightPos = 0;
	int currRightPos = 0;
	string finalMsg = msg;
	for( int i = 0; i < msg.size(); i ++ )
	{
		if( msg[i] == '(' )
		{
			leftNum ++;
		}
		if( msg[i] == ')' )
		{
			rightNum ++;
			lastRightPos = currRightPos;
			currRightPos = i;
		}

		if( rightNum > leftNum )
		{
			if( lastRightPos+1 < msg.size())
			{
				finalMsg = msg.substr(0,lastRightPos+1);
				break;
			}
		}
	}
// 	AgentLog << "ParseWorldModelMsg " << leftNum << " " << rightNum << endl;
// 
// 	if( leftNum < rightNum )
// 	{
// 		int subRightNum = 0;
// 		int rightPointNum = 0;
// 		AgentLog << "leftNum < rightNum " << endl;
// 		for( int i = 0; i < msg.size(); i ++ )
// 		{
// 			if( msg[i] == ')' )
// 			{
// 				subRightNum ++;
// 				if(subRightNum == leftNum)
// 				{
// 					rightPointNum = i;
// 					break;
// 				}
// 			}
// 		}
// 		AgentLog << rightPointNum << " " << msg[rightPointNum] << endl;;
// 		finalMsg = msg.substr(0,rightPointNum);
// 	}
	leftNum = 0;
	rightNum = 0;
	for( int i = 0; i < finalMsg.size(); i ++ )
	{
		if( finalMsg[i] == '(' )
		{
			leftNum ++;
		}
		if( finalMsg[i] == ')' )
		{
			rightNum ++;
		}
	}
	AgentLog << "ParseWorldModelMsg " << leftNum << " " << rightNum << endl;
	AgentLog << finalMsg << endl;

	if ( mWorldModel->WorldModelParse( finalMsg ) )
	{
		mWorldModel->WorldModelUpdate();

		return true;
	}
	else
	{
		AgentLog<< " [Error] WorldModel Parse Error! " << endl;
		
		return false;
	}	
}

bool Agent::IsIntSimTimeFourTimes(float currentTime)
{
	int iTime = (int)( currentTime * 100.0f + 0.5f );

	if( iTime % 4 == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*******************************************************************
// 延时环节，避免发送命令过快，导致服务器未收到命令时就仿真下一个周期
//*******************************************************************
void Agent::DelayForServer()
{
	static int sleepNum = 0;
	sleepNum ++;
	if( mTimeDifferent <= 0.0f )
	{
		mTimeDifferent = 0.0f;
	}
	if( sleepNum > 25 )
	{
		InitTime(0,(int)(mTimeDifferent * 1000000.0f));
		//usleep( mTimeDifferent * 1000000.0f );
	}
}

bool Agent::InitialAgent( float serverStartTime )
{
	static unsigned int waitForInitNum = 0;

	waitForInitNum ++;

	SendPlayerInformation( );

	return true;
	
	//if( IsIntSimTimeFourTimes( serverStartTime ) )
	//{
	//	if( waitForInitNum == 1 )
	//	{
	//		SendPlayerInformation( );

	//		return true;
	//	}
	//}
	//else
	//{
	//	if( waitForInitNum == 2 )
	//	{
	//		SendPlayerInformation( );

	//		return true;
	//	}
	//}

	//return false;
}

bool Agent::BeamAgentForSynch( float serverStartTime )
{
	static unsigned int beamNum = 0;
	SendPlayerInitializePosition( );
	beamNum ++;

	return beamNum > 10;
	//return true;
}

//******************************************************************
//		发送Agent初始化信息：队伍名称，号码
//******************************************************************
void Agent::SendPlayerInformation()
{
	mCmdHandle->SendPlayerInformation( mBasicConfig->mMyPlayerNo, mBasicConfig->mMyTeamName );
	//gSendCommandNum ++;
}

//******************************************************************
//	 Move Agent
//			将Agent Move到一个指定的点（x、y、z）和方向（角度）
//******************************************************************
void Agent::SendPlayerInitializePosition()
{
	AgentLog << mWorldModel->mTeamName << " " << mWorldModel->mOppTeamName << endl;

	//if( mWorldModel->mOppTeamName != "" )
	//{
	//	mCmdHandle->SendPlayerBeamPosition( 5.5f, -3.5f, 0.0f );
	//}
	//else
	//{
	//	mCmdHandle->SendPlayerBeamPosition( -5.5f, 3.5f, 0.0f );
	//
	mCmdHandle->SendPlayerBeamPosition( -0.5f, 3.5f - (float)mWorldModel->mMyPlayerNo, 0.0f );
	//gSendCommandNum ++;
}

//******************************************************************
//			向Server发送一个字符串 str
//******************************************************************
void Agent::SendCommand( const char * str )
{
	mCmdHandle->SendCommand( str );
	//gSendCommandNum ++;
}

//******************************************************************
//			向Server发送消息队列中的消息
//******************************************************************
void Agent::SendCommand()
{
	
	mCmdHandle->SendCommand();
	//gSendCommandNum ++;
}

void Agent::SendZeroCommand()
{
	string zeroMsg = "(he1 0.00)(he2 0.00)(lae1 0.00)(lae2 0.00)(lae3 0.00)(lae4 0.00)(lle1 0.00)(lle2 0.00)(lle3 0.00)(lle4 0.00)(lle5 0.00)(lle6 0.00)(rae1 0.00)(rae2 0.00)(rae3 0.00)(rae4 0.00)(rle1 0.00)(rle2 0.00)(rle3 0.00)(rle4 0.00)(rle5 0.00)(rle6 0.00)";
	
	SendCommand( zeroMsg.data() );
	//gSendCommandNum ++;
}

//******************************************************************
//			得到自己的号码
//******************************************************************
void Agent::GetMyPlayerNo()
{
	mMyPlayerNo = mBasicConfig->mMyPlayerNo;
}

//******************************************************************
//			得到Agent配置文件的路径
//******************************************************************
void Agent::GetAgentConfPath(string agetConfPath)
{
	mAgentConfPath = agetConfPath;
}	

//******************************************************************
//			读取Agent配置文件的信息
//******************************************************************
bool Agent::ReadAgentConf()
{
	GetAgentConfPath( mBasicConfig->mMyAgentConf );

	FILE *acFile;

	AgentLog<< "AgentConf Path " << mAgentConfPath << endl; 

	if( ( acFile = fopen( mAgentConfPath.c_str(),"r" ) ) == NULL )
	{
		cout<< " [Warning] Can't open AgentConf File ! " << endl;
		return false;
	}

	AgentLog<< " Read AgentConf Successfully !" << endl;
	return true;
}
void Agent::SortReceiveTimeList()
{
	deque<float> tempTimeList = mReceiveTimeList;

	for( int i = 0; i < tempTimeList.size(); i ++ )
	{
		float maxTime = 0.0f;
		unsigned int coutNum = i;
		for( int j = i; j < tempTimeList.size(); j ++ )
		{
			if( tempTimeList.at(j) > maxTime )
			{
				maxTime = tempTimeList.at(j);
				coutNum = j;
			}
		}
		float temp = tempTimeList.at(i);
		tempTimeList.at(i) = maxTime;
		tempTimeList.at(coutNum) = temp;
	}

	mReceiveTimeList = tempTimeList;
// 	AgentLog << "tempTimeList" << endl;
// 	for( int i = 0; i < tempTimeList.size(); i ++ )
// 	{
// 		AgentLog << tempTimeList.at(i) << endl;
// 	}
// 	AgentLog << endl;
}
