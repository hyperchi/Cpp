#include "WorldModel.h"

WorldModel::WorldModel( BasicConfiguration * basicConf )
{
	mBasicConfig		= basicConf;
	
	mServerType			= New_Server;

	mSimTime			= 0.0f;
	mCurrentSimCycle	= 0;
	mLastSimTime		= 0.0f;
	mGameTime			= 0.0f;
	mSimStepTime		= 0.02f;
		
	mTeamName			= "AmoiensisNQ";
	mTeamSide			= SD_UNKNOWN;
	mMyPlayerNo			= 0;
	mPlayMode			= PM_BEFORE_KICK_OFF;
	mOurScore			= 0;
	mOppScore			= 0;
	mPlayerTotleNum		= 4;
	mPlayerNumOnField	= 0;
	mOurPlayerNumOnField = 0;
	mOppPlayerNumOnField = 0;

	//******************************************************
	//         改为从worldModel.conf文件中读取
	//******************************************************

	//mGoalWidth			= 1.40f;
	//mGoalHeight			= 0.8f;
	//mGoalDepth			= 0.4f;
	//mFieldLength		= 12.0f;
	//mFieldWidth			= 8.0f;	
	//mFlagCenterHeight	= 0.0f;
	//mBallRadius			= 0.042f;
	//mOurGoalCenter.x	= -mFieldLength / 2.0f;
	//mOppGoalCenter.x	=  mFieldLength / 2.0f;

	mBeginToFall		= false;
	mIsFalled			= false;
	mIsFaceUpFalled		= false;

	isBallRolling		= false;
	ballStateChange		= false;

	iniPos.x			= -2.0f;
	iniPos.y			= 0.0f;
	iniPos.z			= 0.4f;

	mOurPlayers.resize(0);
	mOppPlayers.resize(0);

	WorldModelInit();
}
WorldModel::~WorldModel()
{

}