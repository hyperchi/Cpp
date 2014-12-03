#include "AgentInfo.h"
#define AgentInfoLog gLog<< "[A_Info] "

AgentInfo::AgentInfo( WorldModel *wm )
{
	mWorldModel = wm;

	mOppMaxSpeed = 0.0f;
	mOurMaxSpeed = 0.0f;
	mBallSpeed = 0.0f;

	mBallAveragePos.x = 0.0f;
	mBallAveragePos.y = 0.0f;
	mBallAveragePos.z = 0.0f;
}
AgentInfo::~AgentInfo()
{

}

void AgentInfo::Update()
{	
	const float ourMaxSpeedLimit = 0.7f;
	const float oppMaxSpeedLimit = 1.0f;

	static float countCycle = 1.0f;

	for( unsigned int i = HistoryNum - 1; i > 0; i -- )
	{
		for( unsigned int j = 0; j < PlayerOnField; j ++ )
		{
			mOppPlayerPos[j][i] = mOppPlayerPos[j][i-1];
			mOurPlayerPos[j][i] = mOurPlayerPos[j][i-1];
		}

		mBallPos[i] = mBallPos[i-1];
	}

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		mOppPlayerPos[i][0] = mWorldModel->mOppTeamPlayer[i].mPos;
	}

	for( unsigned int i = 0; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		mOurPlayerPos[i][0] = mWorldModel->mOurTeamPlayer[i].mPos;
	}

	mBallPos[0] = mWorldModel->mBall.mPos;

	for( unsigned int i = mWorldModel->mOppPlayerNumOnField; i < PlayerOnField; i ++ )
	{
		Vector3f zeroVector(0.0f, 0.0f, 0.0f);
		mOppPlayerPos[i][0] = zeroVector;
	}

	for( unsigned int i = mWorldModel->mOurPlayerNumOnField; i < PlayerOnField; i ++ )
	{
		Vector3f zeroVector(0.0f, 0.0f, 0.0f);
		mOurPlayerPos[i][0] = zeroVector;
	}

	//cout<< mWorldModel->mOppTeamPlayer[0].mPos.x << endl;

	float tempOppMaxSpeed;
	float tempOurMaxSpeed;
	float averOppSpeed = 0.0f;
	float averOurSpeed = 0.0f;
	
	for( unsigned int i = 0; i < PlayerOnField; i ++ )
	{
		tempOppMaxSpeed = mOppPlayerPos[i][0].distXY2( mOppPlayerPos[i][HistoryNum - 1] ) / ( SimStepTime * HistoryNum );
		tempOurMaxSpeed = mOurPlayerPos[i][0].distXY2( mOurPlayerPos[i][HistoryNum - 1] ) / ( SimStepTime * HistoryNum );

		//cout<<  mOppPlayerPos[i][0].distXY2( mOppPlayerPos[i][1] ) << endl;
		//if( tempOppMaxSpeed > mOppMaxSpeed && tempOppMaxSpeed < oppMaxSpeedLimit )
		//{
		//	mOppMaxSpeed = tempOppMaxSpeed;
		//}

		if( tempOppMaxSpeed > averOppSpeed )
		{
			averOppSpeed = tempOppMaxSpeed;
		}

		if( tempOurMaxSpeed > averOurSpeed )
		{
			averOurSpeed = tempOurMaxSpeed;

		}

		//if( tempOurMaxSpeed > mOurMaxSpeed && tempOurMaxSpeed < ourMaxSpeedLimit )
		//{
		//	mOurMaxSpeed = tempOurMaxSpeed;
		//}
	}

	mOppMaxSpeed = averOppSpeed;
	mOurMaxSpeed = averOurSpeed;


	// 球的速度（平均速度）
	mBallSpeed = mBallPos[0].distXY2( mBallPos[HistoryNum - 1] ) / ( SimStepTime * HistoryNum );
	
	// 球的运动方向
	//mBallMoveTo = ( mBallPos[0] - mBallPos[HistoryNum - 1] ) / HistoryNum;
	mBallMoveTo = mBallPos[0] - mBallPos[1];

	mBallAveragePos = mBallAveragePos * (countCycle - 1.0f)/(countCycle) + mWorldModel->mBall.mPos / (countCycle);

	float fieldLength = mWorldModel->mFieldLength;

	if( mBallAveragePos.x >= fieldLength / 10.0f )
	{
		mWorldModel->mOppStrength = OS_Weak;
	}
	else if( mBallAveragePos.x <= -fieldLength / 10.0f )
	{
		mWorldModel->mOppStrength = OS_Strong;
	}
	else
	{
		mWorldModel->mOppStrength = OS_Normal;
	}

	if( mWorldModel->mOurScore < mWorldModel->mOppScore )
	{
		mWorldModel->mOppStrength = OS_Strong;
	}

	//AgentInfoLog << "OppMaxSpeed: "  << GetOppMaxSpeed() 
	//			 << " OurMaxSpeed: " << GetOurMaxSpeed() 
	//			 << " Ball Speed: "  << GetBallSpeed()
	//			 << " Ball Moving To: " << GetBallMoveToPos().x << " " << GetBallMoveToPos().y
	//			 << endl;

	//AgentInfoLog << "BallAveragePos: " << mBallAveragePos.x << " " << mBallAveragePos.y
	//			 << endl;

	//AgentInfoLog << "OurPlayerNumOnField: " << mWorldModel->mOppPlayerNumOnField << " "
	//	         << "OppPlayerNumOnField: " << mWorldModel->mOppPlayerNumOnField << " "
	//			 << endl;

	countCycle += 1.0f;
}

float AgentInfo::GetOppMaxSpeed()
{
	return mOppMaxSpeed + 0.01f;	// 防止除数为0
}

float AgentInfo::GetOurMaxSpeed()
{
	return mOurMaxSpeed + 0.01f;	// 防止除数为0
}

Vector3f AgentInfo::GetBallMoveToPos()
{
	return mBallMoveTo;
}

float AgentInfo::GetBallSpeed()
{
	return mBallSpeed + 0.01f;		// 防止除数为0
}

float AgentInfo::GetBallAveragePosX()
{
	return mBallAveragePos.x;
}

