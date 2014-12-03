//#ifndef WIN32

#include <iostream>     // needed for cout

#include "BasicConfigure.h"
#include "Connection.h"
#include "CommandHandle.h"
#include "CommandQuene.h"
#include "WorldModel.h"
#include "Agent.h"
#include "AgentInfo.h"
#include "Logger.h"
#include <pthread.h>
#include <stdexcept>  
using namespace std;

bool StartAgent( int argc, char* argv[], 
				 BasicConfiguration ** basicconf, TRoboCupConnection ** connection, WorldModel **wm, Agent **agent );
void StopAgent ( BasicConfiguration ** basicconf, TRoboCupConnection ** connection, WorldModel **wm, Agent **agent );

#define EXEC_MAIN      /*!< For debugging other parts, undef this */

#ifdef EXEC_MAIN

Agent * globalAgent          = NULL;	

void* threadReceiveMsg(void *p/*pthread_attr_t* agentt*/)
{
	//Agent* agent = (Agent*)agentt;
	globalAgent->GetWorldModelMsg();
}


int main(int argc, char* argv[])
{
	BasicConfiguration * basicConfigure = NULL;	
	TRoboCupConnection * connection		= NULL;
	WorldModel         * wm             = NULL;	
	Agent			   * agent          = NULL;	

	if( !StartAgent( argc, argv, &basicConfigure, &connection, &wm, &agent ) )
	{
		return 1;
	}
	globalAgent = agent;
	pthread_t id;
	int i,ret;
	ret=pthread_create(&id,NULL, threadReceiveMsg,NULL);
	if(ret!=0)
	{
		cout << "Receive time: Create pthread error!\n"<<endl;
		//exit (1);
	}
	agent->mainLoop();

	StopAgent( &basicConfigure, &connection, &wm, &agent );
	return 0;
}

#endif // EXEC_MAIN

bool StartAgent(int argc, char* argv[], 
				 BasicConfiguration ** basicconf, TRoboCupConnection ** connection, WorldModel **wm, Agent **agent )
{
	StopAgent( basicconf,connection, wm, agent );

	*basicconf = new BasicConfiguration;
	(*basicconf)->ConfigureArguments(argc,argv);

	gLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo );
	string agentInfoLogName = "Vision";
	gVisionInfoLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo, agentInfoLogName);
	string agentSpeedLogName = "Speed";
	gSpeedLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo, agentSpeedLogName);
	string agentDribbleLogName = "Dribble";
	gDribbleLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo, agentDribbleLogName);
	//string agentKickLogName = "Kick";
	//gKickLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo, agentKickLogName);
	string hearSayLogName = "Hear_Say";
	gHearSayLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo, hearSayLogName);
	string processingLogName = "Processing";
	gProcessingLog.Init( (*basicconf)->mMyTeamName, (*basicconf)->mMyPlayerNo, processingLogName );

	*connection = new TRoboCupConnection( (*basicconf)->mHostIp.data(), (*basicconf)->mHostPort );

	if( !(*connection)->connected() )
	{
		delete *connection;
		return false;
	}
	
	*wm = new WorldModel( *basicconf );

	*agent = new Agent( *basicconf, *connection, *wm );
		
	return true;
}

void StopAgent ( BasicConfiguration ** basicconf, TRoboCupConnection ** connection, WorldModel **wm, Agent **agent )
{	
	if( *wm )
	{
		delete *wm;
		*wm = NULL;
	}

	if( *connection )
	{
		delete *connection;
		*connection = NULL;
	}

	if( *basicconf )
	{
		delete *basicconf;
		*basicconf = NULL;
	}

	if( *agent )
	{
		delete *agent;
		*agent = NULL;
	}
}
//#endif