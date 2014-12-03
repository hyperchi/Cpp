#include "Motion.h"
#define MotionLog gLog<< "[Motion] "
#define ProcessingLog gProcessingLog<<"[Motin] "
Motion::Motion( WorldModel *wm, CommandQuene *cmdQuene,Situation *mSit )
{
	mWorldModel = wm;
	mCmdQuene = cmdQuene;
	
	mSituation = mSit;

	mFormation = new Formation( mWorldModel );

	mAct = new Action( mWorldModel, mCmdQuene );
	mGoto = new MotionGoto( mWorldModel, mSituation, mCmdQuene, mAct );
	mDribble = new MotionDribble( mWorldModel, mSituation, mGoto, mCmdQuene, mAct );
	mKick = new MotionKick( mWorldModel, mSituation, mGoto, mCmdQuene, mAct );
	mPass = new MotionPass( mWorldModel, mSituation, mGoto, mCmdQuene, mAct );
	mRunPosition = new RunPosition( mWorldModel, mSituation, mGoto, mCmdQuene, mAct );

	mHGoto = new HumanGoto( mWorldModel, mSituation, mCmdQuene, mAct );
	mHDribble = new Dribble( mWorldModel, mSituation, mHGoto, mCmdQuene, mAct );
	mHKick = new Kick( mWorldModel, mSituation, mHGoto, mCmdQuene, mAct );

	mShouldGotoTime = -10.0f;
	InitMotion( );
}
Motion::~Motion()
{
	if( mAct ) 
	{
		delete mAct;
		mAct = NULL;
	}
	if( mGoto ) 
	{
		delete mGoto;
		mGoto = NULL;
	}
	if( mDribble ) 
	{
		delete mDribble;
		mDribble = NULL;
	}
	if( mKick ) 
	{
		delete mKick;
		mKick = NULL;
	}
	if( mPass ) 
	{
		delete mPass;
		mPass = NULL;
	}
	if( mRunPosition ) 
	{
		delete mRunPosition;
		mRunPosition = NULL;
	}
	if( mHGoto ) 
	{
		delete mHGoto;
		mHGoto = NULL;
	}
	if( mHDribble ) 
	{
		delete mHDribble;
		mHDribble = NULL;
	}
	if( mHKick ) 
	{
		delete mHKick;
		mHKick = NULL;
	}
}

bool Motion::DoMotion( MotionType motionType )
{
	static bool lastCycleFalledDown = false;
	static bool lastGetUpActionDone = true;
	
	if( motionType == MT_SwingHead )
	{	
		if( IsActionDone() )
		{
			mAct->SwingHead();
		}
		Do();

		return true;
	}

	if( motionType == MT_BeamInitial || motionType == MT_Beam )
	{
		MotionBeamInitial();
		//mGoto->ClearSpeed();
		mHGoto->ClearSpeed();

		Do();

		return true;
	}

	if( lastCycleFalledDown )
	{
		if( IsActionDone() )
		{
			lastGetUpActionDone = true;
		}
		else
		{
			lastGetUpActionDone = false;
		}
	}
	static int getUpNum = 0;

	if( mWorldModel->mIsFalled )
	{
		if( mWorldModel->mIsSideFalled )
		{
			if( lastGetUpActionDone )
			{
				MotionSideDownGetUp();
			}
		}
		else if( lastGetUpActionDone )
		{
			const int countGetUpNum = 8;
			getUpNum ++;
			bool reverseGetUp = ( getUpNum % 10 >= countGetUpNum  );	// getUpNum % 8 == 0 - 4 :��������
																	// getUpNum % 8 == 5 - 7 :��������
			MotionGetUp(reverseGetUp);
			lastGetUpActionDone = false;		
			//mGoto->ClearSpeed();
			mHGoto->ClearSpeedDeque();
		}

		lastCycleFalledDown = true;
	}
	else 
		if( IsActionDone() )
	{
		lastCycleFalledDown = false;
		lastGetUpActionDone = false;
		getUpNum = 0;

		if( motionType == MT_Beam )
		{
			MotionBeam();
		}
		else if( motionType == MT_InitialStand )
		{
			MotionInitialStand();
		}
		else if( motionType == MT_TestNetState )
		{
			mAct->TestNetState();
		}
		else if ( motionType == MT_StandBy )
		{
			mAct->StandBy();
		}
		else if( motionType == MT_Stand )
		{
			mAct->Stand();
		}
		else if( motionType == MT_DeadBallStand )
		{
			MotionLog << "MotionDeadBallStand " << endl;

			MotionDeadBallStand();
		}
		else if( motionType == MT_GoalieDeadBall)
		{
			HMotionGoalieDeadBall();
		}
		else if( motionType == MT_GoalieClearBall )
		{
			HMotionGoalieClearBall();
		}
		else if( motionType == MT_GoalieKickOffBall)
		{
			HMotionGoalieKickBall();
		}
		else if( motionType == MT_GoalieDefendPos)
		{
			HMotionGoalieDefendPos();
		}
		else if( motionType == MT_GoalieDefendBall)
		{
			HMotionGoalieDefendBall();
		}
		else if( motionType == MT_GoalieDefendSuper)
		{
			HMotionGoalieDefendSuper();
		}
		else if( motionType == MT_DropDownLeft)
		{
			mAct->DropDownLeft();
		}
		else if( motionType == MT_DropDownRight)
		{
			mAct->DropDownRight();
		}
		else if( motionType == MT_GoalieOther)
		{
			HMotionGoalieOther();
		}
		else if (motionType == MT_CornerBall)
		{
			MotionLog << "HMotionCornerBall " << endl;
			HMotionCornerBall();
		}
		else if ( motionType == MT_Test )
		{
			MotionTest();
		}
		//else if( motionType == MT_Attack )
		//{
		//	//MotionAttack();
		//}
		//else if( motionType == MT_Intercept )
		//{
		//	//MotionIntercept();
		//}
		//else if( motionType == MT_Defense )
		//{
		//	//MotionDefense();
		//}
		else if( motionType == MT_Dribble )
		{
			MotionLog << "HMotionDribble " << endl;
			HMotionDribble();
		}
		else if( motionType == MT_Pass )
		{
			MotionLog << "HMotionPass " << endl;
			HMotionPass();
		}
		else if( motionType == MT_Shoot )
		{
			MotionLog << "HMotionShoot " << endl;
			HMotionShoot();
		}
		else if( motionType == MT_RunPosition )
		{
			MotionLog << "HMotionRunPosition " << endl;
			HMotionRunPosition();
		}
		else if( motionType == MT_Intercept )
		{
			MotionLog << "HMotionIntercept " << endl;
			HMotionIntercept();
		}
		else if( motionType == MT_ClearBall )
		{
			MotionLog << "HMotionClearBall " << endl;
			HMotionClearBall();
		}
		else if( motionType == MT_StandPosition )
		{
			MotionLog << "HMotionStandPosition " << endl;
			HMotionStandPosition();
		}
		else if (motionType == MT_Block)
		{
			HMotionBlock();
		}
		else if( motionType == MT_LocateBall )
		{
			MotionLog << "HMotionLocateBall " << endl;
			HMotionLocateBall();
		}
		else if( motionType == MT_InitStrategy )
		{
			MotionLog << "HMotionInitialStrategy " << endl;
			HMotionInitialStrategy();
		}
		
		else
		{
			MotionLog << "Error Code: " << "I don't know what to do !! " << endl;
			mAct->Stand();
		}
	}
	
	Do( );
}

bool Motion::IsActionDone()
{
	return mAct->IsActionDone();
}

bool Motion::Do()
{
	MotionVision();

	return mAct->Do();
}

void Motion::InitMotion()
{
	ReadConf rC( mWorldModel->GetAgentConfPath() ); 
	Predicate tempP;
	//BeamPara tempBeam;

	//mBeamPara.clear();

	//rC.Tranversal( "Beam", tempP );

	//multimap<string,Predicate>::iterator cp = tempP.child.begin();

	//while( cp != tempP.child.end() )
	//{
	//	if( (cp->second).attr.size() != 5 )
	//	{
	//		break;
	//	}

	//	tempBeam.playerNo = (unsigned int) atoi( ((cp->second)).attr[0].c_str() );

	//	tempBeam.beamPara[0] = (float) atof( (cp->second).attr[1].c_str() );
	//	tempBeam.beamPara[1] = (float) atof( (cp->second).attr[2].c_str() );
	//	tempBeam.beamPara[2] = (float) atof( (cp->second).attr[3].c_str() );

	//	mBeamPara.push_back( tempBeam );

	//	cp ++;
	//}

	rC.Tranversal( "Motion_Test_Goto", tempP );
	tempP.GetValue( "Motion_Test_Goto", mMotionTestGoto );
}

bool Motion::MotionInitialStand()
{
	return mAct->InitialStand();
}

bool Motion::MotionBeam()
{ 
	bool isBeamed = false;

	//for( unsigned int i = 0; i < mBeamPara.size(); i ++ )
	//{
	//	if( mWorldModel->mMyPlayerNo == mBeamPara[i].playerNo )
	//	{
	//		//if( mWorldModel->mTeamSide == SD_LEFT )
	//		//{
	//		//	mAct->Beam( mBeamPara[i].beamPara[0], mBeamPara[i].beamPara[1], mBeamPara[i].beamPara[2] );
	//		//}
	//		//else 
	//		//{
	//		//	mAct->Beam( -mBeamPara[i].beamPara[0], -mBeamPara[i].beamPara[1], -mBeamPara[i].beamPara[2] );
	//		//}
	//		mAct->Beam( mBeamPara[i].beamPara[0], mBeamPara[i].beamPara[1], mBeamPara[i].beamPara[2] );
	//		
	//		isBeamed = true;
	//	}
	//}
	mAct->Beam( mWorldModel->mInitBeamPos.beamPara[0], mWorldModel->mInitBeamPos.beamPara[1], mWorldModel->mInitBeamPos.beamPara[2] );

	return true;
}

bool Motion::MotionBeamInitial()
{
	bool beamDefense = false;
	if( (mWorldModel->mPlayMode == PM_GOAL_LEFT && mWorldModel->mTeamSide == SD_LEFT)
		|| (mWorldModel->mPlayMode == PM_GOAL_RIGHT && mWorldModel->mTeamSide == SD_RIGHT) )
	{
		beamDefense = true;
	}
	else if( mWorldModel->mGameTime < 10.0f && mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF && mWorldModel->mTeamSide == SD_RIGHT )
	{
		beamDefense = true;
	}
	else if( mWorldModel->mGameTime > 280.0f && mWorldModel->mPlayMode == PM_BEFORE_KICK_OFF && mWorldModel->mTeamSide == SD_LEFT )
	{
		beamDefense = true;
	}
	else
	{
		beamDefense = false;
	}

	if( beamDefense )
	{
		mAct->BeamInitial( mWorldModel->mInitBeamPos.beamPara[0], mWorldModel->mInitBeamPos.beamPara[1], mWorldModel->mInitBeamPos.beamPara[2] );
		//mAct->BeamInitial( mWorldModel->mDefenseBeamPos.beamPara[0], mWorldModel->mDefenseBeamPos.beamPara[1], mWorldModel->mDefenseBeamPos.beamPara[2] );
	}
	else
	{
		mAct->BeamInitial( mWorldModel->mInitBeamPos.beamPara[0], mWorldModel->mInitBeamPos.beamPara[1], mWorldModel->mInitBeamPos.beamPara[2] );
	}
// 	if( (mWorldModel->mPlayMode == PM_GOAL_LEFT && mWorldModel->mTeamSide == SD_LEFT)
// 		|| (mWorldModel->mPlayMode == PM_GOAL_RIGHT && mWorldModel->mTeamSide == SD_RIGHT) )
// 	{
// 		mAct->BeamInitial( mWorldModel->mDefenseBeamPos.beamPara[0], mWorldModel->mDefenseBeamPos.beamPara[1], mWorldModel->mDefenseBeamPos.beamPara[2] );
// 	}
// 	else
// 	{
// 		mAct->BeamInitial( mWorldModel->mInitBeamPos.beamPara[0], mWorldModel->mInitBeamPos.beamPara[1], mWorldModel->mInitBeamPos.beamPara[2] );
// 	}
	return true;
}

bool Motion::MotionGetUp( bool reverseGetUp )
{
	//return true;
	if( !reverseGetUp )
	{
		if( mWorldModel->mIsFaceUpFalled )
		{
			return mAct->FaceUpGetUp();
		}
		else
		{
			return mAct->FaceDownGetUp();
		}
	}
	else
	{
		if( mWorldModel->mIsFaceUpFalled )
		{
			return mAct->FaceDownGetUp();
		}
		else
		{
			return mAct->FaceUpGetUp();
		}
	}

}

bool Motion::MotionSideDownGetUp()
{
	return mAct->SwingArm();
}	

bool Motion::MotionTest()
{
	//cout<< mWorldModel->mSelf.mPos.x << " " << mWorldModel->mSelf.mPos.y << " " << mWorldModel->mGameTime << endl;
	static unsigned int num = 0;
	if( mMotionTestGoto )
	{
		mHDribble->DribbleAttack();
		//mAct->CrazyTurn( 5.0f );
		return true;
	}
	else
	{
		//std::cout<<"hello\n\n";
		return mAct->Test();
	}	
}

void Motion::SetAttackApproach( AttackApproach attackApproach )
{
	mAttackApproach = attackApproach;
}

bool Motion::MotionVision()
{
	//mAct->SetTurnNeckAng( 100.0f * sin(mWorldModel->mSimTime), 45.0f * sin(mWorldModel->mSimTime) );
	//MotionLog << "SetTurnNeckAng " << mYawAng << " " << mPitchAng << endl;
	mAct->SetTurnNeckAng( mYawAng,mPitchAng );
}
bool Motion::HMotionIShosuldKick()
{
	//return false;
	if( mWorldModel->mBall.mPos.x < 0.0f )
	{
		return false;
	}

	if( !mHKick->IsInKickArea(mWorldModel->mOppGoalCenter) )
	{
		return false;
	}

	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f oppGoalPos = mWorldModel->mOppGoalCenter;

	if( ballPos.distXY2(oppGoalPos) < 2.0f )
	{
		return false;
	}


	if( mHGoto->IsFullSpeed() )
	{
		return false;
	}

	if( mWorldModel->mPlayMode == PM_KICK_OFF_LEFT ||  mWorldModel->mPlayMode == PM_KICK_OFF_RIGHT
		|| mWorldModel->mPlayMode == PM_KICK_IN_LEFT ||  mWorldModel->mPlayMode == PM_KICK_IN_RIGHT 
		/*|| mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT*/ ||  mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT 
		)
	{
		return false;
	}

	//if( ballPos.x > mWorldModel->mFieldLength * 0.5f * 0.6f 
	//	&& fabs(ballPos.y) > mWorldModel->mFieldWidth * 0.5f * 0.5f
	//	)
	//{
	//	return false;
	//}

	//float obsDist = 1.0f;
	//if( ballPos.distXY2(oppGoalPos) < obsDist )
	//{
	//	return false;
	//}

	float agentRadius = 0.3f;
	if( ballPos.distXY2(oppGoalPos) > 5.5f )
	{
		agentRadius = 1.0f;
	}
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		Vector3f oppPlayerPos = mWorldModel->mOppPlayers.at(i).mPos;
		if( oppPlayerPos.distXY2(ballPos) < agentRadius )
		{
			return false;
		}
	}

// 	const float iControlBallRadius = 0.3f;
// 	if( selfPos.distXY2(ballPos) > iControlBallRadius )
// 	{
// 		return false;
// 	}

	Ray selfToOppGoalRay = Ray::MakeRayFromPositionAndAngle(selfPos,selfPos.angTheta2(oppGoalPos));
	Vector3f ballProjectionInRay = selfToOppGoalRay.getPointOnLineClosestTo(ballPos);
	if( selfToOppGoalRay.isInBetween(ballProjectionInRay,selfPos,oppGoalPos) )
	{
		return true;
	}

	return false;
}
bool Motion::HMotionDribble()
{
	ProcessingLog<<"Dribble "<< " SimTime: "<<mWorldModel->mSimTime<<" GameTime: "<<mWorldModel->mGameTime<<"\n";
	float currTime = mWorldModel->mGameTime;

	if( mHGoto->IsFullSpeed() )
	{
		mHKick->IsalreadyStand = false;
		mHKick->IsalreadyTurn = false;
		return mHDribble->DribbleAttack();
	}
	/*
	else if( currTime <= mShouldGotoTime + 3.5f )
	{
		return HMotionShoot();
	}
	
	else if( HMotionIShosuldKick() )
	{
		mShouldGotoTime = mWorldModel->mGameTime;
		return HMotionShoot();
	}*/
	else
	{
		mHKick->IsalreadyStand = false;
		mHKick->IsalreadyTurn = false;
		ProcessingLog<<"4\n";
		return mHDribble->DribbleAttack();
	}
}
bool Motion::HMotionPass()
{

}
bool Motion::HMotionBlock()
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	float ActionSpeedRate =1.4f;//�ҷ���Ա�ķ�Ӧϵ��

	Vector3f oppMostNearPos ;
	mSituation->OppMinDistToBall(oppMostNearPos);

	Angle oppMostNearToBallAngle = Normalize(oppMostNearPos.angTheta2(ballPos));
	Ray oppDribbleRay = Ray::MakeRayFromPositionAndAngle(oppMostNearPos,oppMostNearToBallAngle);
	Angle oppPlayerToourPlayerAngle = oppMostNearPos.angTheta2(selfPos);
	Ray oppToMselfRay = Ray::MakeRayFromPositionAndAngle(oppMostNearPos,oppPlayerToourPlayerAngle);
	float oppToMselfDis = oppMostNearPos.distXY2(selfPos);
	Vector3f midPosInoppToMself = oppToMselfRay.GetPoint(oppToMselfDis);
	Ray plumpRay = Ray::MakeRayFromPositionAndAngle(midPosInoppToMself,(oppPlayerToourPlayerAngle+90.0f));
	Vector3f plumpRayPoint = plumpRay.GetPoint(3.0f);
	Line plumpLine = Line::makeLineFromTwoPoints(midPosInoppToMself,plumpRayPoint);
	Vector3f oppDribbleRayPoint = oppDribbleRay.GetPoint(3.0f);
	Line oppDribbleLine = Line::makeLineFromTwoPoints(oppDribbleRayPoint,oppMostNearPos);
	Vector3f interceptPoint = oppDribbleLine.getIntersection(plumpLine);
	float selfToInterceptPointDist = selfPos.distXY2(interceptPoint);
	Vector3f interceptPos = oppDribbleRay.GetPoint( selfToInterceptPointDist*ActionSpeedRate );

	ProcessingLog<<"MyBlockPos=="<<interceptPos.x<<"   "<<interceptPos.y<<endl;
	
	mHGoto->GotoTar( interceptPos );
}
bool Motion::HMotionShoot()
{
	mHKick->KickAttack();
}
bool Motion::HMotionRunPosition()
{

	if ( /*( mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT && mWorldModel->mTeamSide == SD_LEFT )
		||*/ ( mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT && mWorldModel->mTeamSide == SD_RIGHT )
		)
	{
		Vector3f waitPos(0.0f, 0.0f, 0.0f);
		return HMotionRunPositionDoGoto( waitPos, 0.0f );
	}
	const float waitCircleRadius = 1.0f;
	const float agentRadius = 0.1f;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f ourGoalCenter = mWorldModel->mOurGoalCenter;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f ourGoalLeft = mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos;
	Vector3f ourGoalRight = mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos;
	Angle selfToBallAngle = selfPos.angTheta2( ballPos );
	Angle ballToOurGoalAngle = ballPos.angTheta2( ourGoalCenter );

	Angle ourGoalToBallAngle = ourGoalCenter.angTheta2(ballPos);

	Angle ballToOppGoalAngle = ballPos.angTheta2( oppGoalCenter );
	float distToBall = selfPos.distXY2( ballPos );

	//Line ballToleftGoalLine = Line::makeLineFromTwoPoints(ballPos,ourGoalLeft);
	//Line ballTorightGoalLine = Line::makeLineFromTwoPoints(ballPos,ourGoalRight);
	
	Angle ballToGoalLeftAngle = ballPos.angTheta2(ourGoalLeft);
	Angle ballToGoalRightAngle = ballPos.angTheta2(ourGoalRight);
	Angle ballmidAngleToGoal = ( ballToGoalLeftAngle + ballToGoalRightAngle )/2;
	Ray ballToOurGoalmidRay = Ray::MakeRayFromPositionAndAngle(ballPos,ballmidAngleToGoal);
	Vector3f midLinePoint = ballToOurGoalmidRay.GetPoint(5.0f);
	Line midLineinGoal = Line::makeLineFromTwoPoints(ballPos,midLinePoint);
	Line Goalline = Line::makeLineFromTwoPoints(ourGoalLeft,ourGoalRight);
	Vector3f midLineInterceptGoalline = Goalline.getIntersection(midLineinGoal);
	Angle midLineAngle = midLineInterceptGoalline.angTheta2(ballPos);
	Ray midLineRay = Ray::MakeRayFromPositionAndAngle(midLineInterceptGoalline,midLineAngle);
	int forbidDistNum = 0;
	Ray ballToOurGoalRay = Ray::MakeRayFromPositionAndAngle( ballPos, ballToOurGoalAngle );
	Vector3f runPositionPos = ballToOurGoalRay.GetPoint( waitCircleRadius );
	Ray ballToOppGoalRay = Ray::MakeRayFromPositionAndAngle( ballPos, ballToOppGoalAngle );
	Vector3f selfOnRayPoint = ballToOppGoalRay.getPointOnLineClosestTo( selfPos );
	int inGuardDistNumS = 0;												//С�ĵ�������Ϊ0.4
	int inGuardDistNumB = 0;
	Vector3f safePos;													    //�������������򱣳�һ�������λ��
	float tempDist = 1.25f;													//��ʼΪ1
	float shouldMoveDist = 0.5f;											//վλ��0.4�����ж�����վ����һλ��,f
	if(mWorldModel->mOurPlayers.size() > 0)
	{
		/*for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		{
		tempDist= mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos);

		if(tempDist <= 0.5)
		{
		inGuardDistNumS ++;
		}
		else if(tempDist > 0.5 && tempDist <= 1.0)
		{
		inGuardDistNumB ++;
		}
		}	*/	
	}
	//	if (ballPos.x > -mWorldModel->mFieldLength*0.1f)
	//	{
	float toGoalDistRadius = 4.0f;		

	if (mFormation->GetMyRole()==PR_Guard_1)
	{
		Ray GuardToGoal = Ray::MakeRayFromPositionAndAngle( ourGoalCenter,ourGoalToBallAngle);			

			Vector3f GuardDefendPos = midLineRay.GetPoint( toGoalDistRadius * 0.3f);

		//GuardDefendPos.y+=waitCircleRadius*1.5f;
			MotionLog<<"GuardDefendPos =="<<GuardDefendPos.x<<"  "<<GuardDefendPos.y<<endl;

			return HMotionRunPositionDoGoto( GuardDefendPos, selfToBallAngle );

		


	}
	if (mFormation->GetMyRole()==PR_Guard_2)
	{
		Ray GuardToGoal = Ray::MakeRayFromPositionAndAngle( ourGoalCenter,ourGoalToBallAngle);

			Vector3f GuardDefendPos = midLineRay.GetPoint( toGoalDistRadius * 0.7f );

		//GuardDefendPos.y-=waitCircleRadius*1.5f;

					
			/*safePos = selfPos;*/

			/*	for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
			if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
			{
			safePos.x += 0.8;
			safePos.y += 0.8;
			}*/

			MotionLog<<"MyPos =="<<safePos.x<<"  "<<safePos.y<<endl;
			MotionLog<<"GuardDefendPos =="<<GuardDefendPos.x<<"  "<<GuardDefendPos.y<<endl;
			return HMotionRunPositionDoGoto( GuardDefendPos, selfToBallAngle );
		}
	if (mFormation->GetMyRole()==PR_Guard_3)
	{
		Ray GuardToGoal = Ray::MakeRayFromPositionAndAngle( ourGoalCenter,ourGoalToBallAngle);			

				Vector3f GuardDefendPos = midLineRay.GetPoint( toGoalDistRadius * 1.1f );

				//GuardDefendPos.y-=waitCircleRadius*1.5f;


					/*safePos = selfPos;*/

					/*	for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		 {
		 if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
		 {
		 safePos.x += 0.8;
		 safePos.y += 0.8;
		 }
		 }*/

			MotionLog<<"GuardDefendPos =="<<GuardDefendPos.x<<"  "<<GuardDefendPos.y<<endl;
			return HMotionRunPositionDoGoto( GuardDefendPos, selfToBallAngle );

	}
//	}
	//	if( ballPos.x > -mWorldModel->mFieldLength * 0.5f * 0.2f)
	//	{
	int xSmallThanMeNum = 0;
	if ((mFormation->GetMyRole() == PR_Center_1
		|| mFormation->GetMyRole() == PR_Center_2
		|| mFormation->GetMyRole() == PR_Center_3
		|| mFormation->GetMyRole() == PR_Center_4
		|| mFormation->GetMyRole() == PR_Forward_1
		|| mFormation->GetMyRole() == PR_Forward_2)
		&& (mWorldModel->mSelf.mPos.x < -7.2))
	{

		float myX = mWorldModel->mSelf.mPos.x;
		float otherX = 0.0;
		for (int i = 0; i < mWorldModel->mOurPlayers.size();i ++)
		{
			otherX = mWorldModel->mOurPlayers.at(i).mPos.x;

			if (myX > otherX)
			{
				xSmallThanMeNum ++;
			}
		}
	}	

	if (xSmallThanMeNum >= 4)
	{
		if (mFormation->GetMyRole() == PR_Center_1)
		{
			runPositionPos.x = -7.0;

			runPositionPos.y = 5.0;

		//	cout << "state" << endl;
		}
		else if (mFormation->GetMyRole() == PR_Center_2)
		{
			runPositionPos.x = -5.0;

			runPositionPos.y = 5.0;

		//	cout << "state-5" << endl;
		}
		if (mFormation->GetMyRole() == PR_Center_3)
		{
			runPositionPos.x = -6.5;

			runPositionPos.y = -5.0;

		//	cout << "state-6" << endl;
		}
		if (mFormation->GetMyRole() == PR_Center_4)
		{
			runPositionPos.x = -6,0;

			runPositionPos.y = 0.0;

		//	cout << "state-7" << endl;
		}
		if (mFormation->GetMyRole() == PR_Forward_1)
		{
			runPositionPos.x = -7.0;

			runPositionPos.y = 2.5;

		//	cout << "state-8" << endl;
		}
		if (mFormation->GetMyRole() == PR_Forward_2)
		{
			runPositionPos.x = -7.0;

			runPositionPos.y = -2.5;

		//	cout << "state-9" << endl;
		}
		return HMotionRunPositionDoGoto( runPositionPos, selfToBallAngle );
	}
	
	float ballToOurGoalDist = ballPos.distXY2(ourGoalCenter);
	Ray oppGoalToBall = Ray::MakeRayFromPositionAndAngle( oppGoalCenter,oppGoalCenter.angTheta2(ballPos) );
		Vector3f ForwardPos = oppGoalToBall.GetPoint( ballToOurGoalDist * 1.2f );

	if (mFormation->GetMyRole()==PR_Forward_1)
	{

		//	ForwardPos.y+=waitCircleRadius*2;

		/*ForwardPos.x = ballPos.x - 2.5;

		ForwardPos.y = ballPos.y + 1.0;*/

		ForwardPos.x = ballPos.x - 2.5;

		ForwardPos.y = ballPos.y + 1.5;

		if( selfPos.distXY2(ForwardPos) < 0.5/*agentRadius*/ )
		{		
			/*safePos = selfPos;
			for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
			if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
			{
			safePos.x += 0.8;
			safePos.y += 0.8;
			}
			}*/

			return HMotionRunPositionDoGoto( ForwardPos, selfToBallAngle );
			/*	return HMotionRunPositionDoGoto( ForwardPos, selfToBallAngle );*/
		}
		else
		{
			if(inGuardDistNumS > 0)
			{
				safePos = ForwardPos;
				if(safePos.x > 0)
				{
					safePos.x += 0.7;
				}
				else
				{
					safePos.x -= 0.7;
				}
				if(safePos.y > 0)
				{
					safePos.y += 0.7;
				}
				else
				{
					safePos.y -= 0.7;
				}

				for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
				{
					if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
					{
						safePos.x += 0.8;
						safePos.y += 0.8;
					}
				}

				return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
			}
			else if(inGuardDistNumB >= 2)
			{
				safePos = ForwardPos;
				if(safePos.x > 0)
				{
					safePos.x += 1.2;
				}
				else
				{
					safePos.x -= 1.2;
				}
				if(safePos.y > 0)
				{
					safePos.y += 1.2;
				}
				else
				{
					safePos.y -= 1.2;
				}

				for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
				{
					if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
					{
						safePos.x += 0.8;
						safePos.y += 0.8;
					}
				}

				return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
			}
			safePos = ForwardPos;

			for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
				if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
				{
					safePos.x += 0.8;
					safePos.y += 0.8;
				}
			}
			return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
		}
	}
	if (mFormation->GetMyRole()==PR_Forward_2)
	{
		ForwardPos.y-=waitCircleRadius*2;


		ForwardPos.x = ballPos.x - 2.5;

		ForwardPos.y = ballPos.y - 1.5;

		if( selfPos.distXY2(ForwardPos) < 0.5/*agentRadius*/)
		{	
			/*safePos = selfPos;

			for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
			if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
			{
			safePos.x += 0.8;
			safePos.y += 0.8;
			}
			}*/
			return HMotionRunPositionDoGoto( selfPos, selfToBallAngle );
		}
		else
		{
			if(inGuardDistNumS > 0)
			{
				safePos = ForwardPos;
				if(safePos.x > 0)
				{
					safePos.x += 0.7;
				}
				else
				{
					safePos.x -= 0.7;
				}
				if(safePos.y > 0)
				{
					safePos.y += 0.7;
				}
				else
				{
					safePos.y -= 0.7;
				}

				for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
				{
					if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
					{
						safePos.x += 0.8;
						safePos.y += 0.8;
					}
				}

				return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
			}
			else if(inGuardDistNumB >= 2)
			{
				safePos = ForwardPos;
				if(safePos.x > 0)
				{
					safePos.x += 1.2;
				}
				else
				{
					safePos.x -= 1.2;
				}
				if(safePos.y > 0)
				{
					safePos.y += 1.2;
				}
				else
				{
					safePos.y -= 1.2;
				}

				for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
				{
					if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
					{
						safePos.x += 0.8;
						safePos.y += 0.8;
					}
				}

				return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
			}
			safePos = ForwardPos;
			for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
				if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
				{
					safePos.x += 0.8;
					safePos.y += 0.8;
				}
			}
			return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
		}
	}

	if( ballPos.x < -mWorldModel->mFieldLength * 0.5f * 0.2f )
	{
		float ballToOurGoalDist = ballPos.distXY2(ourGoalCenter);
		Ray ourGoalToBall = Ray::MakeRayFromPositionAndAngle( ourGoalCenter,ourGoalCenter.angTheta2(ballPos) );
		Vector3f blockPos = ourGoalToBall.GetPoint( ballToOurGoalDist * 0.7f );
		return HMotionRunPositionDoGoto( blockPos, selfToBallAngle );
	}

	if( ballToOppGoalRay.isInBetween(selfPos, ballPos, oppGoalCenter ) )
	{
		if( distToBall < 1.0f )
		{
			Ray avoidPosRay_1 = Ray::MakeRayFromPositionAndAngle( ballPos, ballToOppGoalAngle + 100.0f );
			Ray avoidPosRay_2 = Ray::MakeRayFromPositionAndAngle( ballPos, ballToOppGoalAngle - 100.0f );
			Vector3f avoidPos_1 = avoidPosRay_1.GetPoint( waitCircleRadius );
			Vector3f avoidPos_2 = avoidPosRay_2.GetPoint( waitCircleRadius );

			if( selfPos.distXY2(avoidPos_1) < selfPos.distXY2(avoidPos_2) )
			{
				return HMotionRunPositionDoGoto( avoidPos_1, selfToBallAngle );
			}
			else
			{
				return HMotionRunPositionDoGoto( avoidPos_2, selfToBallAngle );
			}
		}
	}	

	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		Player ourPlayerPos = mWorldModel->mOurPlayers.at(i);
		if( ourPlayerPos.mMyPlayerNo == mWorldModel->mMyPlayerNo )
		{
			continue;
		}

		if( ourPlayerPos.DistXyTo( runPositionPos ) < agentRadius )
		{
			runPositionPos = ballToOurGoalRay.GetPoint( waitCircleRadius * 1.2f );
			//waitCircleRadius*=1.2f;
		}
	}	

	if (mFormation->GetMyRole()==PR_Center_1)
	{
		
		runPositionPos = ballToOurGoalRay.GetPoint( waitCircleRadius);		
	}

	if (mFormation->GetMyRole()==PR_Center_2)
	{
		/*runPositionPos = ballToOurGoalRay.GetPoint( waitCircleRadius *0.5f );
		runPositionPos.y+=waitCircleRadius*2;*/
		
		
		runPositionPos.x = ballPos.x - 0.8;

		/*runPositionPos.y = ballPos.y + 2.0;*/

		runPositionPos.y = ballPos.y + 2.0;
	}
	if (mFormation->GetMyRole()==PR_Center_3)
	{
		/*runPositionPos = ballToOurGoalRay.GetPoint( waitCircleRadius);
		runPositionPos.x+=waitCircleRadius*2;*/

		runPositionPos.x = ballPos.x - 0.8;

		runPositionPos.y = ballPos.y - 2.0;
	}
	if (mFormation->GetMyRole()==PR_Center_4)
	{
		/*runPositionPos = ballToOurGoalRay.GetPoint( waitCircleRadius*0.5f);
		runPositionPos.y-=waitCircleRadius*2;*/
		/*runPositionPos = ballPos;*/
		float sureWeControlBallPosX = -2.0;		

		if (mSituation->WeControlBall() && mWorldModel->mBall.mPos.x > sureWeControlBallPosX)
		{
			for (int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
				if (mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 5
					&& mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos) < 0.5)
				{
					runPositionPos.x = ballPos.x - 0.8;

					runPositionPos.y = ballPos.y + 2.0;
				}
				else if (mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 6
					&& mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos) < 0.5)
				{
					runPositionPos.x = ballPos.x - 0.8;

					runPositionPos.y = ballPos.y - 2.0;
				}
				else if (mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 8
					&& mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos) < 0.5)
				{
					runPositionPos.x = ballPos.x - 2.5;

					runPositionPos.y = ballPos.y + 1.5;
				}
				else if (mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 9
					&& mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos) < 0.5)
				{	
					runPositionPos.x = ballPos.x - 2.5;

					runPositionPos.y = ballPos.y - 1.5;
				}
			}
		}
		else
		{
			runPositionPos.x = ballPos.x - 2.0;

			runPositionPos.y = ballPos.y ;
		}
		
	}
	
	if( selfPos.distXY2(runPositionPos) < agentRadius )
	{
		/*safePos = runPositionPos;

		for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		{
		if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
		{
		safePos.x += 0.8;
		safePos.y += 0.8;
		}
		}

		return HMotionRunPositionDoGoto( safePos, selfToBallAngle );*/
		return HMotionRunPositionDoGoto( selfPos, selfToBallAngle );

	}
	else
	{
		if(inGuardDistNumS > 0)
		{
			safePos = runPositionPos;

			if(safePos.x > 0)
			{
				safePos.x += 0.7;
			}
			else
			{
				safePos.x -= 0.7;
			}
			if(safePos.y > 0)
			{
				safePos.y += 0.7;
			}
			else
			{
				safePos.y -= 0.7;
			}
			for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
				if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
				{
					safePos.x += 0.8;
					safePos.y += 0.8;
				}
			}

			return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
		}
		else if(inGuardDistNumB >= 2)
		{
			safePos = runPositionPos;
			if(safePos.x > 0)
			{
				safePos.x += 1.2;
			}
			else
			{
				safePos.x -= 1.2;
			}
			if(safePos.y > 0)
			{
				safePos.y += 1.2;
			}
			else
			{
				safePos.y -= 1.2;
			}

			for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
			{
				if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
				{
					safePos.x += 0.8;
					safePos.y += 0.8;
				}
			}

			return HMotionRunPositionDoGoto( safePos, selfToBallAngle );
		}
		safePos = runPositionPos;
		for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		{
			if(safePos.distXY2(mWorldModel->mOurPlayers.at(i).mPos) < shouldMoveDist)
			{
				safePos.x += 0.8;
				safePos.y += 0.8;
			}
		}
		return HMotionRunPositionDoGoto( runPositionPos, selfToBallAngle );
	}
}
bool Motion::HMotionRunPositionDoGoto( Vector3f tarGoto, Angle tarAngle )
{
	Vector3f finalGotoPos = tarGoto;
	// 	if( finalGotoPos.x > -1.0f )
	// 	{
	// 		finalGotoPos.x = -1.0f;
	// 	}
	// 	else
	gProcessingLog << "HMotionRunPositionDoGoto    time:"<<mWorldModel->mSimTime<<"\n";

	if( finalGotoPos.x < -mWorldModel->mFieldLength * 0.5f + 0.05f )
	{
		finalGotoPos.x = -mWorldModel->mFieldLength * 0.5f + 0.05f;
	}
	if( finalGotoPos.y > mWorldModel->mFieldWidth * 0.5f + 1.0f )
	{
		finalGotoPos.y = mWorldModel->mFieldWidth * 0.5f + 1.0f;
	}
	else if( finalGotoPos.y < -mWorldModel->mFieldWidth * 0.5f - 1.0f )
	{
		finalGotoPos.y = -mWorldModel->mFieldWidth * 0.5f - 1.0f;
	}

	if( mWorldModel->mSelf.DistXyTo(finalGotoPos) < 0.2f )
	{
		return mHGoto->QuickTurn( tarAngle );
	}
	else
	{
		return mHGoto->GotoTar( finalGotoPos, tarAngle );
	}
}
bool Motion::HMotionIntercept()
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	float ActionSpeedRate =1.4f;//�ҷ���Ա�ķ�Ӧϵ��
	/*if( selfPos.x > ballPos.x - 0.1f 
		&& ballPos.x < mWorldModel->mFieldLength * 0.5f - 0.5f 
		)
	{
		
		//HMDribbleLog << " ----- Dribble Code 0-0" << endl;
		Vector3f beforeDribblePos_1(ballPos.x-0.8f, ballPos.y + 0.2f, 0.0f);
		Vector3f beforeDribblePos_2(ballPos.x-0.8f, ballPos.y - 0.2f, 0.0f);
		Vector3f gotoBeforeDribblePos_1 = beforeDribblePos_1;
		Vector3f gotoBeforeDribblePos_2 = beforeDribblePos_2;
		Vector3f beforeDribblePos;
		if( selfPos.distXY2(gotoBeforeDribblePos_1) < selfPos.distXY2(gotoBeforeDribblePos_2) )
		{
			beforeDribblePos = gotoBeforeDribblePos_1;
		}
		else
		{
			beforeDribblePos = gotoBeforeDribblePos_2;
		}
		cout<<"coming uppppppp"<<endl;
		return mHGoto->GotoTar( beforeDribblePos );
		//return DoGotoAction( beforeDribblePos);
	}*/


	float ourMinDistToBall;
	unsigned int ourPlayerMinToBall;

	mSituation->OurMinDistToBall( ourMinDistToBall, ourPlayerMinToBall );

	if( ourPlayerMinToBall != mWorldModel->mMyPlayerNo && ! mSituation->SecondNearToBall() )
	{
		MotionLog << "HMotionIntercept-->HMotionRunPosition " << endl;
		return HMotionRunPosition();
	}
	else if (mSituation->SecondNearToBall() && mWorldModel->mMyPlayerNo > 4)
	{
		ActionSpeedRate = 1.4f;
		MotionLog<<"I should Intercept in second position "<<endl;
		//cout<<"I should Intercept in second position "<<mWorldModel->mMyPlayerNo<<endl;
	}
	else if (ourPlayerMinToBall == mWorldModel->mMyPlayerNo)
	{
		MotionLog<<"I should Intercept in firstposition "<<endl;
	//	cout<<"I should Intercept in first position "<<mWorldModel->mMyPlayerNo<<endl;
		return HMotionDribble();
	}
	else
	{
		MotionLog << "HMotionIntercept-->HMotionRunPosition " << endl;
		return HMotionRunPosition();
	}

	const float controlBallMinDist = 0.2f;
	//Vector3f selfPos = mWorldModel->mSelf.mPos;
	//Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f oppGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	Vector3f oppGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos;
	Angle angBallToOppGoal = Normalize( ballPos.angTheta2( oppGoalCenter ) );
	Angle angBallToOppGoalLeft = Normalize( ballPos.angTheta2( oppGoalLeft ) );
	Angle angBallToOppGoalRight = Normalize( ballPos.angTheta2( oppGoalRight ) );
	//Angle angBallToOppGoalLeft = Normalize( angBallToOppGoal + 100.0f );
	//Angle angBallToOppGoalRight = Normalize( angBallToOppGoal - 100.0f );
	Angle angBallToSelf = Normalize( ballPos.angTheta2( selfPos ) );
	//MotionLog << "angBallToOppGoal " << angBallToOppGoal 
	//	      << " angBallToOppGoalLeft " << angBallToOppGoalLeft 
	//		  << " angBallToOppGoalRight " << angBallToOppGoalRight 
	//		  << " angBallToSelf " << angBallToSelf 
	//		  << endl; 
	
	//������λ�㣺�Է��������Ͼ�������Ա�Ⱦ�ĵ�
	Vector3f oppMostNearPos ;
	mSituation->OppMinDistToBall(oppMostNearPos);
	
	ProcessingLog<<"oppMostNearcurrentPos=="<<oppMostNearPos.x<<"   "<<oppMostNearPos.y<<endl;

	Angle oppMostNearToBallAngle = Normalize(oppMostNearPos.angTheta2(ballPos));
	Ray oppDribbleRay = Ray::MakeRayFromPositionAndAngle(oppMostNearPos,oppMostNearToBallAngle);
	Angle oppPlayerToourPlayerAngle = oppMostNearPos.angTheta2(selfPos);
	Ray oppToMselfRay = Ray::MakeRayFromPositionAndAngle(oppMostNearPos,oppPlayerToourPlayerAngle);
	float oppToMselfDis = oppMostNearPos.distXY2(selfPos);
	Vector3f midPosInoppToMself = oppToMselfRay.GetPoint(oppToMselfDis);
	Ray plumpRay = Ray::MakeRayFromPositionAndAngle(midPosInoppToMself,(oppPlayerToourPlayerAngle+90.0f));
	Vector3f plumpRayPoint = plumpRay.GetPoint(3.0f);
	Line plumpLine = Line::makeLineFromTwoPoints(midPosInoppToMself,plumpRayPoint);
	Vector3f oppDribbleRayPoint = oppDribbleRay.GetPoint(3.0f);
	Line oppDribbleLine = Line::makeLineFromTwoPoints(oppDribbleRayPoint,oppMostNearPos);
	Vector3f interceptPoint = oppDribbleLine.getIntersection(plumpLine);
	float selfToInterceptPointDist = selfPos.distXY2(interceptPoint);

	

	const float interceptRadius = 1.0f;
	Vector3f interceptPos;
	static Vector3f lastInterceptPos = ballPos;
	if( selfPos.distXY2(ballPos) <= controlBallMinDist )
	{
		mHDribble->DribbleAttack();
	}
	else 
	{
		
		//I'm in front of the  ball
		Angle angBallToOurGoal = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter );
		Ray rayBallToOurGoal = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, angBallToOurGoal );
		Vector3f currInterceptPos = oppDribbleRay.GetPoint( selfToInterceptPointDist*ActionSpeedRate);
		Angle angBallToLastInterPos = Normalize( ballPos.angTheta2( lastInterceptPos ) );

	//	currInterceptPos.x-=0.6f;//�ڶ������϶�Ավλ��Ը�����

       if( lastInterceptPos.distXY2( currInterceptPos ) <= interceptRadius*0.5f )
		{
			interceptPos = lastInterceptPos;
		}
		else
		{
			interceptPos = currInterceptPos;
		}


		interceptPos = currInterceptPos;
		lastInterceptPos = interceptPos;
		ProcessingLog<<"intercept::"<<mWorldModel->mMyPlayerNo<<endl;
		ProcessingLog<<"mycurrentPos=="<<selfPos.x<<"   "<<selfPos.y<<endl;
		//ProcessingLog<<"oppMostNearcurrentPos=="<<oppMostNearPos.x<<"   "<<oppMostNearPos.y<<endl;
		ProcessingLog<<"currInterceptPos.x===="<<currInterceptPos.x<<"   currInterceptPos.y==== "<<currInterceptPos.y<<"   "<<endl;
		ProcessingLog<<"interceptPos.x===="<<interceptPos.x<<"   interceptPos.y==== "<<interceptPos.y<<"   "<<mWorldModel->mGameTime<<endl;
		//mHGoto->GotoTar( interceptPos );
		mHGoto->noLimitGoTar(interceptPos,mWorldModel->mBodyAngle);
	}


	return true;
}
bool Motion::HMotionClearBall()
{
	//������λ�㣺�Է��������Ͼ�������Ա�Ⱦ�ĵ�
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f oppMostNearPos ;
	float MinDist;
	unsigned int DistMinNum ;
	mSituation->OurMinDistToBall(MinDist,DistMinNum);
	mSituation->OppMinDistToBall(oppMostNearPos);

	ProcessingLog<<"oppMostNearcurrentPos=="<<oppMostNearPos.x<<"   "<<oppMostNearPos.y<<endl;

	Angle oppMostNearToBallAngle = Normalize(oppMostNearPos.angTheta2(ballPos));
	Ray oppDribbleRay = Ray::MakeRayFromPositionAndAngle(oppMostNearPos,oppMostNearToBallAngle);
	Angle oppPlayerToourPlayerAngle = oppMostNearPos.angTheta2(selfPos);
	Ray oppToMselfRay = Ray::MakeRayFromPositionAndAngle(oppMostNearPos,oppPlayerToourPlayerAngle);
	float oppToMselfDis = oppMostNearPos.distXY2(selfPos);
	Vector3f midPosInoppToMself = oppToMselfRay.GetPoint(oppToMselfDis);
	Ray plumpRay = Ray::MakeRayFromPositionAndAngle(midPosInoppToMself,(oppPlayerToourPlayerAngle+90.0f));
	Vector3f plumpRayPoint = plumpRay.GetPoint(3.0f);
	Line plumpLine = Line::makeLineFromTwoPoints(midPosInoppToMself,plumpRayPoint);
	Vector3f oppDribbleRayPoint = oppDribbleRay.GetPoint(3.0f);
	Line oppDribbleLine = Line::makeLineFromTwoPoints(oppDribbleRayPoint,oppMostNearPos);
	Vector3f interceptPoint = oppDribbleLine.getIntersection(plumpLine);
	float selfToInterceptPointDist = selfPos.distXY2(interceptPoint);
	float oppDisToBall = oppMostNearPos.distXY2(ballPos);
	float mDistToBall = selfPos.distXY2(ballPos);

	float ActionSpeedRate =1.45f;//�ҷ���Ա�ķ�Ӧϵ��
	float BlockDist = 0.3f;
	Vector3f mBlockPos = oppDribbleRay.GetPoint(selfToInterceptPointDist*ActionSpeedRate);
	MotionLog<<"ClearBall : "<<mWorldModel->mMyPlayerNo<<endl;
	MotionLog<<"my current Pos===="<<selfPos.x<<"   "<<selfPos.y<<endl;
	MotionLog<<"my Blocking Pos===="<<mBlockPos.x<<"   "<<mBlockPos.y<<endl;
	MotionLog<<"DistMinNum==="<< DistMinNum<<" mWorldModel->mMyPlayerNo  "<<mWorldModel->mMyPlayerNo<<endl;
	
/*	int inGetballAreaNum = 0;												
	float GetBallRadius = 1.3f;
	float tempDist;

	if(mWorldModel->mOurPlayers.size() > 0)
	{
		for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		{
			tempDist= mWorldModel->mOurPlayers.at(i).DistXyTo(mWorldModel->mBall.mPos);

			if( tempDist <= GetBallRadius )
			{
				inGetballAreaNum ++;
			}
		}		
	}

	if ( inGetballAreaNum > 2) 
	{
		
	}*/

	if (mSituation->IControlingBall() ||(mWorldModel->mMyPlayerNo==DistMinNum && mDistToBall<oppDisToBall*0.7f))
	{
		MotionLog<<"mDis===  "<<mDistToBall<<"oppDist*0.7===="<<oppDisToBall*0.7f<<endl;
		//cout<<"just Clearing Ball!"<<mWorldModel->mMyPlayerNo<<endl;
		return mHDribble->DribbleDefense();
		
	}
	else
	{
		MotionLog<<"going toooooooooooo Block Pos  "<<mWorldModel->mMyPlayerNo<<endl;
		mHGoto->GotoTar(mBlockPos);
		
	}

	
}
bool Motion::HMotionGoalieDeadBall()
{
	MotionLog << "goalie dead ball\n";

	Vector3f tarPos;
	Angle tarAng;	
	if ((mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT && mWorldModel->mTeamSide == SD_LEFT)
		|| (mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT && mWorldModel->mTeamSide == SD_RIGHT))
	{
		tarPos.x = -(mWorldModel->mFieldLength/2 - 0.4);
		if (mWorldModel->mBall.mPos.y > 0)
		{			
			tarPos.y = mWorldModel->mGoalWidth/2;			
		}
		else
		{
			tarPos.y = -mWorldModel->mGoalWidth/2 ;
		}
		tarPos.z = 0;
		tarAng = tarPos.angTheta2(mWorldModel->mBall.mPos);
		MotionLog << "corner kick tarPos = " << tarPos.x << " " << tarPos.y << " tarAng = " << tarAng << endl;
	}
	else
	{
		mSituation->LookOppGoal(tarPos,tarAng);	
		MotionLog << "tarPos :" << tarPos.x << " " << tarPos.y << " tarAng = " << tarAng << endl;
	}
	Angle errAng = fabs(Normalize(mWorldModel->mBodyAngle - tarAng));
	float errDist = mWorldModel->mSelf.mPos.distXY2(tarPos);
	if (errAng < 5 && errDist < 0.2)
	{
		mAct->Stand();
	}
	else
	{
		mHGoto->GotoTar(tarPos,tarAng);
	}
	return true;
}
bool Motion::HMotionGoalieOther()
{
	Vector3f tarPos;
	Angle tarAng;
	mSituation->LookOppGoal(tarPos,tarAng);
	MotionLog << "target pos:" << tarPos.x << " " << tarPos.y << " target angle :" << tarAng;
	Angle errAng = fabs(Normalize(mWorldModel->mBodyAngle - tarAng));
	float errDist = mWorldModel->mSelf.mPos.distXY2(tarPos);
	if (errAng < 10 && errDist < 0.3)
	{
		mAct->Stand();
	}
	else
	{
		mHGoto->GotoTar(tarPos,tarAng);
	}
}
bool Motion::HMotionGoalieKickBall()
{
	MotionLog << "goalie kick ball\n";
	mHDribble->DribbleAttack();
	MotionLog << "goalie kick ball end\n";
	return true;
}
bool Motion::HMotionGoalieClearBall()
{
	MotionLog << "clear ball" << endl;
	//Vector3f tarPos;
	//Angle tarAng;
	//tarPos = mWorldModel->mBall.mPos;
	//tarAng = mWorldModel->mSelf.ThetaTo(mWorldModel->mBall.mPos);
	//mSituation->GetGoalieClearBall(tarPos,tarAng);
	//mHGoto->GotoTar(tarPos,tarAng);
	mHDribble->DribbleAttack();
	MotionLog << "clear ball end" << endl;
	return true;
}
bool Motion::HMotionGoalieDefendBall()
{
	MotionLog << "defend ball" << endl;
	Vector3f tarPos;
	Angle tarAng;
	/*if (mSituation->Defend2Super())
	{
		MotionLog << "Defend 2 Super" << endl;
		HMotionGoalieDefendSuper();
		return true;
	}*/
	mSituation->GetGoalieDefendBall(tarPos,tarAng);
	MotionLog << "target pos:" << tarPos.x << " " << tarPos.y << " target angle :" << tarAng;
	mHGoto->GotoTar(tarPos,tarAng);
	MotionLog << "defend ball end" << endl;
	return true;
}
bool Motion::HMotionGoalieDefendPos()
{
	Vector3f tarPos;
	Angle tarAng;
	switch (mSituation->GetGoalieDefendPos(tarPos,tarAng))
	{
		MotionLog << "target pos:" << tarPos.x << " " << tarPos.y << " target angle :" << tarAng;
	case 0:
		MotionLog << "Defend Pos clear ball" << endl;
		HMotionGoalieClearBall();
		MotionLog << "Defend Pos clear ball end" << endl;
		break;
	case 1:
	//	MotionLog << "Defend Pos" << endl;
	//	MotionLog << "Pos" << tarPos.x << tarPos.y << endl;
	//	Angle errAng = fabs(Normalize(mWorldModel->mBodyAngle - tarAng));
	//	Circle tarCircle;
	//	float tarRadius = 0.2f;
	//	tarCircle.setCircle(tarPos,tarRadius);
	//	MotionLog << "err angle = " << errAng<< endl;
	//	MotionLog << "err dist = " << mWorldModel->mSelf.mPos.distXY2(tarPos);
	///*	if (errAng < 5 && tarCircle.isInsideCircle(mWorldModel->mSelf.mPos))
	//	{
	//		MotionLog << "Defend Pos stand" << endl;
	//		mAct->Stand();
	//		break;
	//	}	*/
	//	MotionLog << "Goalie defend pos :" << tarPos.x << " " << tarPos.y << endl;

	//	MotionLog << "Goalie defend ang :" << tarAng << endl;
	//	MotionLog << "Self angle " << mWorldModel->mBodyAngle << endl;				
		//cout << "tarPos"<< tarPos.x << " "<<tarPos.y << endl;

		Vector3f standPos = mWorldModel->mOurGoalCenter;	

		standPos.x = -10.1;
		if (mWorldModel->mSelf.mPos.x == tarPos.x && mWorldModel->mSelf.mPos.y != tarPos.y)
		{

			return mHGoto->TranstoTar(tarPos,tarAng);			
		}
		
		else if (fabs(mWorldModel->mSelf.mPos.x - tarPos.x) < 0.1 && fabs(mWorldModel->mSelf.mPos.y == tarPos.y) < 0.3)
		{

			//return mAct->HumanQuickTurn(tarAng);

			Angle tarBodyAng = 0.0;
			return mHGoto->CrazyTurn(tarBodyAng);
			//mHGoto->QuickTurn(tarAng);
		}
		else if(mWorldModel->mSelf.mPos.distXY2(standPos) > 0.7)
		{
			
			/*cout << "dist3" << mWorldModel->mSelf.mPos.distXY2(standPos) << endl;*/
			return mHGoto->TranstoTar(tarPos,tarAng);	
			//return mHGoto->GotoTar(tarPos,tarAng);						
		}

		//cout << "MGoaliePos" << endl;
		MotionLog << "Defend Pos end" << endl;
		break;
	}
	return true;
}
bool Motion::HMotionGoalieDefendSuper()
{
	Vector3f tarPos;
    Angle tarAng;
	switch (mSituation->CaculateDropDownSide())
	{
	case 0:
		MotionLog << "super left" << endl;
		mAct->DropDownLeft();
		MotionLog << "super left end" << endl;
		break;
	case 1:
		MotionLog << "super right" << endl;
		mAct->DropDownRight();
		MotionLog << "super right end" << endl;
		break;
	case 2:
		MotionLog << "super turn" << endl;
		tarAng = mSituation->GoalieTurnAngle();
		mHGoto->QuickTurn(tarAng);
		MotionLog << "super turn end" << endl;
	case 3:
		MotionLog << "super go to drop target" << endl;		
		mSituation->GetGoalieSuperTarget(tarPos,tarAng);
		mHGoto->GotoTar(tarPos,tarAng);
		MotionLog << "super go to drop target end" << endl;
		break;
	case 4:
		MotionLog << "super clear ball" << endl;
		HMotionGoalieKickBall();
		MotionLog << "super clear ball end" << endl;
		break;
	case 5:
		MotionLog << "super ball middle with me" << endl;
		//mAct->Stand();
		HMotionGoalieKickBall();
		MotionLog << "super ball middle with me end" << endl;
		break;
	}
	return true;
}
bool Motion::HMotionCornerBall()
{
	if( mSituation->IShouldGotoControlBall() )
	{
		Vector3f firstGoPos;

		firstGoPos.x = 9.5;

		firstGoPos.y = 7.0;

		if (mWorldModel->mSelf.mPos.distXY2(firstGoPos) < 0.2)
		{
			Vector3f lastGoPos;

			lastGoPos.x = 11.5;

			lastGoPos.y = 7.0;

			mHGoto->GotoTar(lastGoPos);
		}
		else
		{
			mHGoto->GotoTar(firstGoPos);
		}
	}
	return true;
}
bool Motion::HMotionStandPosition()
{
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f oppPlayerNearestBallPos = ballPos;
	float minDist = 100.0f;
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		Vector3f oppPlayerPos = mWorldModel->mOppPlayers.at(i).mPos;
		float oppPlayerDistToBall = oppPlayerPos.distXY2(ballPos);
		if( oppPlayerDistToBall < minDist )
		{
			oppPlayerNearestBallPos = oppPlayerPos;
			minDist = oppPlayerDistToBall;
		}
	}

	Vector3f blockPos = ( ballPos + oppPlayerNearestBallPos ) * 0.5f;

	//Angle tarBodyAngle = ballPos.angTheta2(mWorldModel->mOppGoalCenter);
	Angle tarBodyAngle = mWorldModel->mBodyAngle;
	return mHGoto->GotoNearTar(blockPos,tarBodyAngle);
}
bool Motion::MotionDeadBallStand()
{
	int ourScore = mWorldModel->mOurScore;
	int oppScore = mWorldModel->mOppScore;
	int leadScore = ourScore - oppScore;

	if( leadScore <= -2 )
	{
		float protectBallDist = 0.5f;
		Angle protectBallAng = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mSelf.mPos );
		Ray protectBallRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, protectBallAng );
		Vector3f protectBallPos = protectBallRay.GetPoint( protectBallDist );

		mHGoto->GotoTar( protectBallPos );

		return true;
	}

	const float minDistToBall = 3.2f;
	const float goalKickDist = 3.0f;
	const float goalKickWaitdist = 4.5f;
	const Angle goalKickAngle = 0.0f;

	Vector3f ourGoalPos = mWorldModel->mOurGoalCenter;
	Vector3f ourGoalLeft = mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos;
	Vector3f ourGoalRight = mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Angle selfToBallAngle = selfPos.angTheta2( ballPos );

	bool ourKick;
	unsigned int caseNum = 0;	// 1 -- �ҷ�������������		--- dribble
								// 2 -- �Է���������			--- wait
								// 3 -- �Է�������				--- wait
								// 4 -- �Է��г�����			--- wait
								// 5 -- �ҷ�������				--- dribble

	if( ( mWorldModel->mPlayMode == PM_KICK_IN_RIGHT && mWorldModel->mTeamSide == SD_LEFT ) 
		|| ( mWorldModel->mPlayMode == PM_KICK_IN_LEFT && mWorldModel->mTeamSide == SD_RIGHT )
		|| ( mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT && mWorldModel->mTeamSide == SD_LEFT )
		|| ( mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT && mWorldModel->mTeamSide == SD_RIGHT )
		)
	{
		ourKick = false;
		caseNum = 2;
	}
	else if( ( mWorldModel->mPlayMode == PM_GOAL_KICK_LEFT && mWorldModel->mTeamSide == SD_RIGHT )
		|| ( mWorldModel->mPlayMode == PM_GOAL_KICK_RIGHT && mWorldModel->mTeamSide == SD_LEFT )
		)
	{
		ourKick = false;
		caseNum = 3;
	}
	else if( ( mWorldModel->mPlayMode == PM_KICK_OFF_LEFT && mWorldModel->mTeamSide == SD_RIGHT )
		|| ( mWorldModel->mPlayMode == PM_KICK_OFF_RIGHT && mWorldModel->mTeamSide == SD_LEFT )
		)
	{
		ourKick = false;
		caseNum = 4;
	}
	else
	{
		ourKick = true;
		if( ( mWorldModel->mPlayMode == PM_KICK_IN_LEFT && mWorldModel->mTeamSide == SD_LEFT )
			|| ( mWorldModel->mPlayMode == PM_KICK_IN_RIGHT && mWorldModel->mTeamSide == SD_RIGHT )
			|| ( mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT && mWorldModel->mTeamSide == SD_LEFT )
			|| ( mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT && mWorldModel->mTeamSide == SD_RIGHT )
			)
		{
			caseNum = 1;
		}
		else if( ( mWorldModel->mPlayMode == PM_GOAL_KICK_LEFT && mWorldModel->mTeamSide == SD_LEFT )
			|| ( mWorldModel->mPlayMode == PM_GOAL_KICK_RIGHT && mWorldModel->mTeamSide == SD_RIGHT )
			)
		{
			caseNum = 5;
		}
	}

	unsigned int myNo = mWorldModel->mMyPlayerNo;
	bool myRoleIsForward = true;
	if( mWorldModel->mMyPlayerNo == 5 )
	{
		myRoleIsForward = true;
	}
	else
	{
		myRoleIsForward = false;
	}
	//bool bIshouldGoForward = true;
	//for( int i = 0; i < mWorldModel->mOurPlayers.size(); i++ )
	//{
	//	if( mWorldModel->mOurPlayers.at(i).mMyPlayerNo == myNo )
	//	{
	//		continue;
	//	}
	//	else if( mWorldModel->mOurPlayers.at(i).mPos.x > selfPos.x + 1.0f )
	//	{
	//		bIshouldGoForward = false;
	//	}
	//}

	//myRoleIsForward = myRoleIsForward && bIshouldGoForward;

	if( ourKick )
	{
		if( caseNum == 5 )
		{
			float gotoPosX = -mWorldModel->mFieldLength / 2.0f + 2.0f;
			float gotoPosY = 0.0f;
			if( myRoleIsForward )
			{
				gotoPosY = 1.0f;
			}	
			else
			{
				gotoPosY = -1.0f;
			}

			Vector3f gotoPos( gotoPosX, gotoPosY, 0.0f );
			
			mHGoto->GotoTar( gotoPos,selfToBallAngle );
			return false;
		}
		else
		{
			if( myRoleIsForward )
			{
				HMotionDribble();
				return false;
			}
			else
			{
				return HMotionRunPosition();
			}
		}
	}
	else
	{
		if( caseNum == 2 )	// �Է�������������
		{
			Ray waitPosRay = Ray::MakeRayFromPositionAndAngle( ballPos, ballPos.angTheta2(ourGoalPos) );

			float waitPosDist = 1.5f;

			Vector3f waitPos= waitPosRay.GetPoint( waitPosDist );

			if( myRoleIsForward )
			{
				
				mHGoto->GotoTar( waitPos,selfToBallAngle );
			}
			else
			{
				return HMotionRunPosition();
			}

		}
		else if( caseNum == 3 )				// �Է�������
		{
			float gotoPosX_3 = -1.0f;
			float gotoPosX_4 = mWorldModel->mFieldLength / 2.0f - 3.0f;
			float gotoPosX_defualt = mWorldModel->mFieldLength / 2.0f - 4.0f;
			float gotoPosY_3 = 0.0f;
			float gotoPosY_4 = mWorldModel->mBall.mPos.y;
			float gotoPosY_defualt = 1.0f;

			if( myRoleIsForward )
			{
				Vector3f gotoPos( gotoPosX_4, gotoPosY_3, 0.0f );
				mHGoto->GotoTar( gotoPos,selfToBallAngle );
			}
			else
			{
				return HMotionRunPosition();
			}

			return false;
		}
		else								// �Է��г�����
		{
			mAct->Stand();
			return false;
		}
	}
}
bool Motion::HMotionResetFrameNum()
{
	return mAct->ResetFrameNum();
}
bool Motion::HMotionLocateBall()
{
	MotionLog << "HMotionLocateBall" << endl;
	mHGoto->CrazyTurn( mWorldModel->mBodyAngle + 30.0f );
}
bool Motion::HMotionInitialStrategy()
{
	int myNum = mWorldModel->mMyPlayerNo;
	if( myNum == 4 )
	{
		Vector3f kickTar(0.5f, 0.5f, 0.0f);
		return mHKick->DoKickAction( kickTar );
	}
	else
	{
		return mAct->StandBy();
	}
}


