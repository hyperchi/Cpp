#include "Brain.h"
#define BrainLog gLog << "[Brain ]"
#define HearSayLog gHearSayLog << "[hearsay]"
#define PeocessingLog gProcessingLog <<"[Brain ] "<<mWorldModel->mSimTime
Brain::Brain( WorldModel *worldModel, CommandQuene *cmdQuene )
{
	mWorldModel = worldModel;
	mCmdQuene = cmdQuene;
	mFormation = new Formation( mWorldModel );

	mSituation = new Situation( mWorldModel, mFormation );

	mVision = new Vision( mWorldModel );

	mMotion = new Motion( mWorldModel, mCmdQuene, mSituation );

	mBrainTest = false;

	mCoach = Coach::GetInstance(mWorldModel);

	mSay = new Say(mWorldModel,mCmdQuene);

	InitBrain();
}
Brain::~Brain()
{
	if( mFormation ) 
	{
		delete mFormation;
		mFormation = NULL;
	}
	if( mSituation ) 
	{
		delete mSituation;
		mSituation = NULL;
	}
	if( mVision ) 
	{
		delete mVision;
		mVision = NULL;
	}
	if( mMotion ) 
	{
		delete mMotion;
		mMotion = NULL;
	}
	if( mSay ) 
	{
		delete mSay;
		mSay = NULL;
	}
}
//******************************************************************
//		相当于决策的“main函数”
//******************************************************************
void Brain::MainThink()
{
	static unsigned int beamTime = 0;
	static unsigned int isInitialed = false;
	static bool isNetStateTested = false;
	static bool isActionCleared = false;
	static PlayModeT lastPlayModeT = PM_UNKNOWN;
	PlayModeT currPlayModeT = mWorldModel->mPlayMode;
	//ThinkSwingHead();
	//return;
	
	mVision->UpdatePos();
	//ThinkHear_Say();
	//mSituation->Update();

	
	mVision->SetTurnNeckAng(mMotion->mYawAng,mMotion->mPitchAng);
	//mSituation->Update();
    mCoach->Update();
   
	if( mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF 
		|| mWorldModel->mPlayMode == PM_GOAL_LEFT
		|| mWorldModel->mPlayMode == PM_GOAL_RIGHT
		//|| mWorldModel->mPlayMode == PM_PLAY_ON
		)
	{
		if( lastPlayModeT != currPlayModeT )
		{
			 
			mWorldModel->InitBodyRotation();
			
			mMotion->HMotionResetFrameNum();
			 
		}

		if( !isActionCleared )
		{
			mMotion->mAct->ClearJoint();
			isActionCleared = true;
			 
		}
		if( beamTime < 60 )
		{
			 
			beamTime ++;

			if( mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF )
			{
				
				//ThinkBeam();
				ThinkBeamInitial();
			}
			else
			{
				
				ThinkBeamInitial();
			}
		}
		else if( !isInitialed )
		{
			if( mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF )
			{
				mMotion->DoMotion( MT_InitialStand );
			}
			else
			{
				//mMotion->DoMotion( MT_Stand );
				
				mMotion->DoMotion( MT_InitialStand );
				
			}

			isInitialed = true;
		}
		else if ( !isNetStateTested )
		{
			
			isNetStateTested = mMotion->DoMotion( MT_TestNetState );
			 }	
		else
		{
			 
			mMotion->DoMotion( MT_StandBy );
			
		}
	}
	else
	{
		beamTime = 0;
		isInitialed = false;
		isNetStateTested = false;
		isActionCleared = false;

		if( mBrainTest )
		{
			 
			ThinkTest();
			 
		}
		else
		{
			if( mVision->NeedToLocateBall() )
			{
				mMotion->DoMotion( MT_LocateBall );
			}
			else if( mFormation->GetMyRole() == PR_Goalie )
			{
				 
				ThinkGoalie();
				
			}
			else
			{
				 
				ThinkNormal();
				
			}
		}
	}

	lastPlayModeT = currPlayModeT;
}
//******************************************************************
//		初始化Brain类所需要的参数
//			从Agent配置文件中读取
//******************************************************************
void Brain::InitBrain()
{	
	ReadConf rC( mWorldModel->GetAgentConfPath() ); 
	Predicate tempP;

	rC.Tranversal( "BrainTest", tempP );
	tempP.GetValue( "BrainTest", mBrainTest );
}

//******************************************************************
//		比赛准备阶段的决策
//			1、将Agent Beam到目标点
//			2、将Agent 从初始姿势（各关节角度为0）过渡到站立的预备姿势
//			3、测试动作延迟的周期
//
//		返回值:	true	--	准备阶段的决策全部完成
//				false	--	准备阶段的决策未全部完成	
//******************************************************************
bool Brain::ThinkPrepare()
{
	static bool isInitialed = false;
	static bool isNetStateTested = false;

	if( mWorldModel->mCurrentSimCycle < 10 )
	{
		mMotion->DoMotion( MT_Beam );
	}
	else if( !isInitialed )
	{
		mMotion->DoMotion( MT_InitialStand );
		isInitialed = true;
	}
	else if( !isNetStateTested )
	{
		isNetStateTested = mMotion->DoMotion( MT_TestNetState );
	}
	else
	{
		return true;
	}

	return false;
}
//******************************************************************
//		将Agent Beam到目标点
//******************************************************************
void Brain::ThinkBeam()
{
	mMotion->DoMotion( MT_Beam );
}

//******************************************************************
//		当比赛模式切换并且允许 Beam 时，将 Agent Beam到指定点
//			并且将 Agent 各关节还原到 待命 状态
//******************************************************************
void Brain::ThinkBeamInitial()
{
	mMotion->DoMotion( MT_BeamInitial );
}

//******************************************************************
//		测试用决策
//******************************************************************
void Brain::ThinkTest()
{
	//static bool isInitialed = false;
	//static bool isNetStateTested = false;

	//if( mWorldModel->mCurrentSimCycle < 10 )
	//{
	//	ThinkBeam( );
	//}
	//else if( !isInitialed )
	//{
	//	mMotion->DoMotion( MT_InitialStand );
	//	isInitialed = true;
	//}
	//else if ( !isNetStateTested )
	//{
	//	isNetStateTested = mMotion->DoMotion( MT_TestNetState );
	//}
	//else if( mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF )
	//{
	//	mMotion->DoMotion( MT_StandBy );
	//}
	//else
	//{	
	//	//mMotion->DoMotion( MT_StandBy ); //用于假想对手
	//	mMotion->DoMotion( MT_Test );		
	//}
	mMotion->DoMotion( MT_Test );	
	//mMotion->DoMotion( MT_Shoot );	
	//mMotion->DoMotion( MT_Dribble );	
}

void Brain::ThinkSwingHead()
{
	mMotion->DoMotion( MT_SwingHead );
}
void Brain::ThinkHear_Say()
{
	HearSayLog << mWorldModel->mGameTime << endl;
	unsigned int ourPlayersISeeNum = mWorldModel->mOurPlayers.size();
	unsigned int oppPlayersISeeNum = mWorldModel->mOurPlayers.size();
	bool getHearMsg = mWorldModel->mHearMsg.ParseHearMsg(mWorldModel->mFieldLength,mWorldModel->mFieldWidth);
	//Our1,			//一个我方球员
	//Our2,			//两个我方球员
	//OurAll,			//三个我方球员
	//Opp1,			//一个对方球员
	//Opp2,			//两个对方球员
	//OppAll,			//三个对方球员
	//Our1Opp1,		//一个我方+一个对方
	//Our1Opp2,		//一个我方+两个对方
	//Our2Opp1,		//两个我方+一个对方
	//Our1Ball,		//一个我方+一个球
	//Our2Ball,		//两个我方+一个球
	//OurPBallPOpp,	//一个我方+一个球+一个对方
	//Opp1Ball,		//一个对方+一个球
	//Opp2Ball,		//两个对方+一个球
	if( getHearMsg )
	{
		HearSayLog << "heard message: " << mWorldModel->mHearMsg.mHeardMessage << endl;

		if( mWorldModel->mHearMsg.sayMode == Say_Char )
		{
			HearSayLog << "hear char" << endl;
		}
		else
		{
			if( mWorldModel->mHearMsg.controlMode == Our1 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Our2 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == OurAll )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Opp1 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Opp2 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == OppAll )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Our1Opp1 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Our1Opp2 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Our2Opp1 )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Our1Ball )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Our2Ball )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == OurPBallPOpp )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Opp1Ball )
			{

			}
			else if( mWorldModel->mHearMsg.controlMode == Opp2Ball )
			{

			}
			else
			{
				HearSayLog << "HearMsg controlMode Error! " << mWorldModel->mHearMsg.controlMode << endl;
			}
		}
	}
	//Our1,			//一个我方球员
	//Our2,			//两个我方球员
	//OurAll,		//三个我方球员
	////Opp1,			//一个对方球员
	////Opp2,			//两个对方球员
	////OppAll,		//三个对方球员
	//Our1Opp1,		//一个我方+一个对方
	//Our1Opp2,		//一个我方+两个对方
	//Our2Opp1,		//两个我方+一个对方
	//Our1Ball,		//一个我方+一个球
	//Our2Ball,		//两个我方+一个球
	//OurPBallPOpp,	//一个我方+一个球+一个对方
	////Opp1Ball,		//一个对方+一个球
	////Opp2Ball,		//两个对方+一个球
	ControlType sayControlType;
	if( ourPlayersISeeNum == 0 )
	{
		HearSayLog << "SayMag ourPlayersISeeNum Error! " << ourPlayersISeeNum << endl;
	}
	else if( ourPlayersISeeNum == 1 )	
	{
		if( mWorldModel->bSeeBall )	
		{
			if( oppPlayersISeeNum >= 1)
			{
				mSay->SetControl(OurPBallPOpp,Say_Pos);
				sayControlType = OurPBallPOpp;
			}
			else
			{
				mSay->SetControl(Our1Ball,Say_Pos);
				sayControlType = Our1Ball;
			}
		}
		else
		{
			if( oppPlayersISeeNum >= 2)
			{
				mSay->SetControl(Our1Opp2,Say_Pos);
				sayControlType = Our1Opp2;
			}
			else if( oppPlayersISeeNum >= 1 )
			{
				mSay->SetControl(Our1Opp1,Say_Pos);
				sayControlType = Our1Opp1;
			}
			else
			{
				mSay->SetControl(Our1,Say_Pos);
				sayControlType = Our1;
			}
		}
	}
	else if( ourPlayersISeeNum == 2 )
	{
		if( mWorldModel->bSeeBall )	
		{
			mSay->SetControl(Our2Ball,Say_Pos);
			sayControlType = Our2Ball;
		}
		else
		{
			if( oppPlayersISeeNum >=1 )
			{
				mSay->SetControl(Our2Opp1,Say_Pos);
				sayControlType = Our2Opp1;
			}
			else
			{
				mSay->SetControl(Our2,Say_Pos);
				sayControlType = Our2;
			}

		}
	}
	else if( ourPlayersISeeNum == 3 )
	{
		if( mWorldModel->bSeeBall )	
		{
			mSay->SetControl(Our2Ball,Say_Pos);
			sayControlType = Our2Ball;
		}
		else
		{
			mSay->SetControl(OurAll,Say_Pos);
			sayControlType = OurAll;
		}
	}
	else
	{
		HearSayLog << "SayMag ourPlayersISeeNum Error! " << ourPlayersISeeNum << endl;
	}
	
	HearSayLog << "SayMag controlHead " << sayControlType << endl << endl << endl;
	//cout << "set control : " << mSay->SetControl(OurAll,Say_Pos) << endl;
	//mSay->SetControl(Our1Ball,Say_Pos);
	mSay->SayObjectPos(mWorldModel->mSelf.mPos.x,mWorldModel->mSelf.mPos.y);
	mSay->SayObjectPos(mWorldModel->mBall.mPos.x,mWorldModel->mBall.mPos.y);
	mSay->SendSay();
	//
	//	cout << "Parse end!" << endl;
}
//******************************************************************
//		判断当前动作是否完成
//
//		返回值:	true	--	当前动作已完成
//				false	--	当前动作未完成
//******************************************************************
bool Brain::IsActionDone()
{
	return mMotion->IsActionDone();
}

//******************************************************************
//		执行决策出的动作
//******************************************************************
void Brain::Do()
{
	mMotion->Do();
}