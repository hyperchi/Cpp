#include "coach.h"
#define CoachLog gLog << "[coach ] "

Coach *Coach::mInstance = NULL;  
Coach::Coach( WorldModel *wm )
{
	mWorldModel = wm;

	mOppMaxAverSpeed = 0.0f;
	mSelfMaxAverSpeed = 0.0f;
	mBallAverPos = 0.0f;
}
Coach::~Coach()
{

}
void Coach::Update()
{
	mOppAverSpeed = OppAverSpeed();
	mSelfAverSpeed = SelfAverSpeed();
	BallAverPos();

	if( mOppAverSpeed > mOppMaxAverSpeed * 0.99f )
	{
		mOppMaxAverSpeed = mOppAverSpeed;
	}
	if( mSelfAverSpeed > mSelfMaxAverSpeed * 0.99f )
	{
		mSelfMaxAverSpeed = mSelfAverSpeed;
	}

	if( mWorldModel->mGameTime < 50.0f )
	{
		mOppStrength = OS_Strong;
	}
	else 
	{
		if( mOppMaxAverSpeed < 4.0f )
		{
			mOppStrength = OS_Weak;
		}
		else if( mOppMaxAverSpeed > 4.5f )
		{
			mOppStrength = OS_Strong;
		}
		else
		{
			mOppStrength = OS_Normal;
		}
	}
	float ballAverCountMinTime = 0.0f;
	if( mWorldModel->mTeamSide == SD_LEFT )
	{
		ballAverCountMinTime = 50.0f;
	}
	else
	{
		ballAverCountMinTime = 100.0f;
	}

	if( mWorldModel->mGameTime > ballAverCountMinTime )
	{
		if( mBallAverPos < -1.0f )
		{
			mOppStrength = OS_Strong;
		}
		else if( mBallAverPos > 3.0f )
		{
			mOppStrength = OS_Weak;
		}
	}

	int ourScore = mWorldModel->mOurScore;
	int oppScore = mWorldModel->mOppScore;
	int leadScore = ourScore - oppScore;

	if( leadScore < 0 )
	{
		mOppStrength = OS_Strong;
	}
	else if( leadScore > 1 )
	{
		mOppStrength = OS_Weak;
	}

	CoachLog << " oppAverSpeed " << mOppAverSpeed << " OppMaxAverSpeed " << mOppMaxAverSpeed 
			 << " selfAverSpeed " << mSelfAverSpeed << " SelfMaxAverSpeed " << mSelfMaxAverSpeed
			 << " ballAverPos " << mBallAverPos 
			 << " oppStrength " << mOppStrength << endl;
}
float Coach::SelfAverSpeed()
{
	const unsigned int countCycle = 1000;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	float averSpeed = -1.0f;

	static PlayModeT lastPlayMode = mWorldModel->mPlayMode;
	PlayModeT currPlayMode = mWorldModel->mPlayMode;

	if( currPlayMode == PM_PLAY_ON && lastPlayMode != PM_PLAY_ON 
		|| currPlayMode != PM_PLAY_ON )
	{
		mSelfPos.clear();
	}

	if( currPlayMode == PM_PLAY_ON  )
	{
		if( mSelfPos.size() < countCycle )
		{
			mSelfPos.push_back( selfPos );
		}
		else
		{
			mSelfPos.push_back( selfPos );
			mSelfPos.pop_front();

			Vector3f &firstPos = mSelfPos.front();
			Vector3f &lastPos = mSelfPos.back();

			averSpeed = fabs( lastPos.distXY2( firstPos) );
		}
	}

	lastPlayMode = currPlayMode;

	return averSpeed;
}
float Coach::OppAverSpeed()
{
	const unsigned int countCycle = 1000;
	static int oppForwardPlayerNum = -1;
	float averSpeed = -1.0f;

	static PlayModeT lastPlayMode = mWorldModel->mPlayMode;
	PlayModeT currPlayMode = mWorldModel->mPlayMode;

	if( mWorldModel->mOppPlayers.size() == 0 )
	{
		return 0.0f;
	}

	if( mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF  )
	{
		float xMinest = 100.0f;
		for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
		{
			float tempPlayerX = mWorldModel->mOppPlayers.at(i).mPos.x;
			if( tempPlayerX < xMinest )
			{
				xMinest = tempPlayerX;
				oppForwardPlayerNum = mWorldModel->mOppPlayers.at(i).mMyPlayerNo;
			}
		}
		CoachLog << "oppForwardPlayerNum " << oppForwardPlayerNum << endl;
	}

	Vector3f currOppForwardPos(0.0f, 0.0f, 0.0f);

	if( currPlayMode == PM_PLAY_ON && lastPlayMode != PM_PLAY_ON 
		|| currPlayMode != PM_PLAY_ON )
	{
		mOppPos.clear();
	}

	if( mWorldModel->mPlayMode == PM_PLAY_ON  )
	{
		for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
		{
			if( mWorldModel->mOppPlayers.at(i).mMyPlayerNo == oppForwardPlayerNum )
			{
				currOppForwardPos = mWorldModel->mOppPlayers.at(i).mPos;
			}
		}
	}

	if( mOppPos.size() < countCycle )
	{
		mOppPos.push_back( currOppForwardPos );
	}
	else
	{
		mOppPos.push_back( currOppForwardPos );
		mOppPos.pop_front();

		Vector3f &firstPos = mOppPos.front();
		Vector3f &lastPos = mOppPos.back();

		averSpeed = fabs( lastPos.distXY2( firstPos) );
	}

	lastPlayMode = currPlayMode;

	return averSpeed;
}
void Coach::BallAverPos()
{
	static unsigned int countCycle = 1;
	PlayModeT currPlayMode = mWorldModel->mPlayMode;
	float ballPosX = mWorldModel->mBall.mPos.x;

	if( currPlayMode == PM_PLAY_ON )
	{
		countCycle ++;
		mBallAverPos = ( mBallAverPos * (countCycle - 1) + ballPosX ) / countCycle ;
	}
}
OppStrength Coach::GetOppStrength()
{
	return mOppStrength;
}

