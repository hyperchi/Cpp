#include "Kick.h"
#define HMKickLog gLog<< "[hmKick] " << "Kick "
#define ProcessingLog gProcessingLog<<"[Kick] "
Kick::Kick( WorldModel *wm, Situation *situ, HumanGoto *hGoto, CommandQuene *cmdQuene, Action *act )
{
	mWorldModel = wm;
	mSituation = situ;
	mHGoto = hGoto;
	mCmdQuene = cmdQuene;
	mAct = act;
}
Kick::~Kick()
{

}
bool Kick::BallInShootArea()
{
	const float ballToOppGoalDistMin = 4.0f;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f oppGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	Vector3f oppGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos;
	oppGoalLeft.z = 0.0f;
	oppGoalRight.z = 0.0f;

	float ballToOppGoalDist = ballPos.distXY2( oppGoalCenter );

	if( !mSituation->mFieldSquare->IsInerField(ballPos) )
	{
		HMKickLog << " BallInShootArea " << " Ball not IsInerField " << endl;
		return false;
	}

	if( ballToOppGoalDist >= ballToOppGoalDistMin )
	{
		HMKickLog << " BallInShootArea " << " ballToOppGoalDist >= kickDist " << ballToOppGoalDist << endl;
		return false;
	}

	const Angle ballToOppGoalAngMin = 30.0f;
	Angle ballToOppGoalLeft = Normalize( ballPos.angTheta2(oppGoalLeft) );
	Angle ballToOppGoalRight = Normalize( ballPos.angTheta2(oppGoalRight) );
	Angle ballToOppGoalAng = Normalize( ballToOppGoalLeft - ballToOppGoalRight );
	if( ballToOppGoalAng <= ballToOppGoalAngMin )
	{
		HMKickLog << " BallInShootArea " << "  ballToOppGoal < ballToOppGoalAngMin " << ballToOppGoalAng << endl;		
		return false;
	}

	HMKickLog << " BallInShootArea " << " OK " << ballToOppGoalAng << " " << ballToOppGoalAng << endl;		
	return true;
}
bool Kick::GetShootViability( Vector3f tarDribbleTo )
{

}
bool Kick::GetPassViability( Vector3f tarDribbleTo )
{

}
bool Kick::GetKickAttackViability( Vector3f tarDribbleTo )
{

}
bool Kick::IsBehindBallKickPos( Vector3f tarKickTo )
{
	const float kickparaDistEps = -0.4f;
	const float kickvertDistEps = 0.3f;
	Vector3f currMyPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;

	Ray rayBehindBallKick = Ray::MakeRayFromPositionAndAngle( ballPos, ballPos.angTheta2(tarKickTo) );
	Vector3f posBehindBallKick = rayBehindBallKick.GetPoint( kickparaDistEps );
	
	Ray verticalRay_1 = Ray::MakeRayFromPositionAndAngle( posBehindBallKick, Normalize( ballPos.angTheta2(tarKickTo) + 90.0f ));
	Ray verticalRay_2 = Ray::MakeRayFromPositionAndAngle( posBehindBallKick, Normalize( ballPos.angTheta2(tarKickTo) - 90.0f ));
	Ray verticalRay_3 = Ray::MakeRayFromPositionAndAngle( ballPos, Normalize( ballPos.angTheta2(tarKickTo) + 90.0f ));
	Ray verticalRay_4 = Ray::MakeRayFromPositionAndAngle( ballPos, Normalize( ballPos.angTheta2(tarKickTo) - 90.0f ));
	Vector3f posVerticalBallKick_1 = verticalRay_1.GetPoint( kickparaDistEps );
	Vector3f posVerticalBallKick_2 = verticalRay_2.GetPoint( kickparaDistEps );
	Vector3f posVerticalBallKick_3 = verticalRay_3.GetPoint( kickparaDistEps );
	Vector3f posVerticalBallKick_4 = verticalRay_4.GetPoint( kickparaDistEps );

	Triangle beforeKickTriangle_1(ballPos,posVerticalBallKick_1,posVerticalBallKick_2);
	Triangle beforeKickTriangle_2(posBehindBallKick,posVerticalBallKick_3,posVerticalBallKick_4);
	return beforeKickTriangle_1.IsInTriangle( currMyPos ) && beforeKickTriangle_2.IsInTriangle( currMyPos );
}
bool Kick::IsInKickArea( Vector3f tarKickTo )
{
	float distToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos);
	float angleToBall = ( mWorldModel->mBodyAngle - (mWorldModel->mBall.mPos - mWorldModel->mSelf.mPos).angTheta() );
	float xDistToBall = -distToBall * cos( angleToBall * PI / 180.0f );
	float yDistToBall = distToBall * sin( angleToBall * PI / 180.0f );

	Angle angleToTar = Normalize(mWorldModel->mSelf.mPos.angTheta2( tarKickTo ) - mWorldModel->mBodyAngle );
	HMKickLog << "IsInKickArea " << distToBall << " " 
								 << xDistToBall << " "
								 << yDistToBall << " "
								 << angleToBall << " "
								 << angleToTar
 								 << endl;
// 	if( fabs(angleToTar - angleToBall) > 30.0f )
// 	{
// 		return false;
// 	}
//	”“Ω≈Ãﬂ«Ú«¯”Ú =	[		-0.236  0.007
// 							-0.236  0.09
// 							-0.274  0.007
// 							-0.274  0.09
// 					];
	if( !IsBehindBallKickPos(tarKickTo) )
	{
		HMKickLog << "IsInKickArea " << "!IsBehindBallKickPos" << endl;
		return false;
	}

	if( xDistToBall <= -0.0f 
		&& xDistToBall >= -0.4f )
	{
		if( ( yDistToBall >= 0.0f && yDistToBall <= 0.2f ) 
			|| ( yDistToBall <= -0.0f && yDistToBall >= -0.2f ) )
		{
			return true;
		}
	}

	return false;
}
//	x:	-0.17 ~ -0.24		
//	y:	0.02 ~ 0.08 ”“Ω≈
//		-0.02 ~ -0.08◊ÛΩ≈
//		-0.22 -0.07 ◊Ó‘∂ 	
bool Kick::DoKickAction( Vector3f tarKickTo )
{
	HMKickLog << "DoKickAction" << endl;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f oppGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	Vector3f oppGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;

	Angle ballToOppGoalLeft = Normalize( ballPos.angTheta2(oppGoalLeft) );
	Angle ballToOppGoalRight = Normalize( ballPos.angTheta2(oppGoalRight) );
	Angle tarBallTraceAng = Normalize( ballToOppGoalRight + 0.5f * (ballToOppGoalLeft-ballToOppGoalRight) );

	float distToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos);
	float angleToBall = Normalize( mWorldModel->mBodyAngle - (mWorldModel->mBall.mPos - mWorldModel->mSelf.mPos).angTheta() );
	float xDistToBall = -distToBall * cos( angleToBall * PI / 180.0f );
	float yDistToBall = distToBall * sin( angleToBall * PI / 180.0f );
	Angle diffAngleToTar;
	Angle tarAngle;
	if( tarKickTo.distXY2(oppGoalCenter) < EPS )
	{
		diffAngleToTar = Normalize(tarBallTraceAng - mWorldModel->mBodyAngle);
		tarAngle = tarBallTraceAng;
	}
	else
	{
		diffAngleToTar = Normalize(mWorldModel->mSelf.mPos.angTheta2( tarKickTo ) - mWorldModel->mBodyAngle );
		tarAngle = mWorldModel->mSelf.mPos.angTheta2( tarKickTo );
	}

	float deltaDist = 0.06f;
	if( ( ballPos.x > mWorldModel->mFieldLength * 0.5f * 0.6f 
		&& fabs(ballPos.y) < mWorldModel->mFieldWidth * 0.5f * 0.5f
		) 
		|| selfPos.distXY2(tarKickTo) < 1.0f 
		)
	{
		deltaDist = 0.035f;
	}

	const float maxXDistToBall = -0.17f + deltaDist;
	const float minXDistToBall = -0.19f + deltaDist;
	const float centerXDistToBall = ( maxXDistToBall + minXDistToBall ) / 2.0f;
	const float maxYDistToBall = 0.08f;
	const float minYDistToBall = 0.01f;
	const float centerYDistToBall = ( maxYDistToBall + minYDistToBall ) / 2.0f;;
	if( IsInKickArea(tarKickTo) )
	{
	//	cout<< "------IsInKickArea-------- " << xDistToBall << " " << yDistToBall << " " << diffAngleToTar << endl;
		HMKickLog << "DoKickAction " << "Get Ready to Kick" << endl;
		bool inStrictKickArea = true;
		float forSpeed = 0.0f;
		float transSpeed = 0.0f;
		//mAct->HumanTurnAndTrans( mForCurrSpeed, mTransCurrSpeed, mTurnCurrSpeed );
		//special
		/*
		if(1)
		{
			HMKickLog << "go kick" << endl;
			if( !mHGoto->IsStandingBy() )
			{
				mHGoto->ClearSpeed();
				mAct->Stand();
			}	
			else 
			{
				cout<< "------IsInKickArea-------- " << xDistToBall << " " << yDistToBall << " " << diffAngleToTar << endl;
				if( yDistToBall > 0.0f )
				{
					//cout<< "NewKickRight" << endl;
					HMKickLog << "NewKickRight " << "Get Ready to Kick" << endl;
					mAct->NewKickRight();
				}
				else
				{
					//cout<< "NewKickLeft" << endl;
					HMKickLog << "NewKickLeft " << "Get Ready to Kick" << endl;
					mAct->NewKickLeft();
				}
			}
		}*/
	//special
		if( xDistToBall <= minXDistToBall )
		{
			forSpeed = ( centerXDistToBall - xDistToBall ) * 0.35f;
			//forSpeed = 0.0051f;
			inStrictKickArea = false;
		}
		else if( xDistToBall >= maxXDistToBall )
		{
			//forSpeed = -0.007f;
			forSpeed = ( centerXDistToBall - xDistToBall ) * 0.35f;
			//forSpeed = -0.00505f;
			inStrictKickArea = false;
		}
 		if( yDistToBall <= minYDistToBall && yDistToBall >= 0.0f )
 		{
 			//transSpeed = 0.02f;
			transSpeed = ( centerYDistToBall - yDistToBall ) * 0.15f;

			//transSpeed = 0.00505f;

			transSpeed = 0.00505f;

			transSpeed = 0.00505f;
			inStrictKickArea = false;
 		}
 		else if( yDistToBall >= -minYDistToBall && yDistToBall <= 0.0f )
 		{
 			//transSpeed = -0.02f;
			transSpeed = ( -centerYDistToBall - yDistToBall ) * 0.15f;
			transSpeed = -0.00505f;
			inStrictKickArea = false;
 		}
 		else 
			if( yDistToBall >= maxYDistToBall )
		{
			//transSpeed = -0.02f;
			//transSpeed = ( centerYDistToBall - yDistToBall ) * 0.02f;
			transSpeed = -0.00505f;
			//transSpeed = 0.00505f;
			inStrictKickArea = false;
		}
		else if( yDistToBall <= -maxYDistToBall )
		{
			//transSpeed = 0.02f;
			//transSpeed = ( -centerYDistToBall - yDistToBall ) * 0.02f;
			transSpeed = 0.00505f;
			//transSpeed = -0.00505f;
			inStrictKickArea = false;
		}
		
		Angle diffAngleEps= 15.0f;


		if( fabs(diffAngleToTar) >= diffAngleEps) //&& !IsalreadyTurn)

		if( fabs(diffAngleToTar) >= diffAngleEps )

		{

			
			std::cout<<"turn :"<<diffAngleToTar<<"\n";

			if( !mHGoto->IsStandingBy() && !IsalreadyStand)
			{
				IsalreadyStand = true;
				mHGoto->ClearSpeed();
				mAct->Stand();
			}
			else
		{
				IsalreadyTurn = true;
				IsalreadyStand = true;
				//mHGoto->CrazyTurn( Normalize(tarAngle) *0.8f );
				mAct->CrazyTurn(diffAngleToTar);
			}
			/*
			if( !mHGoto->IsStandingBy() && !IsalreadyStand)
			{
				IsalreadyStand = true;
				mHGoto->ClearSpeed();
				mAct->Stand();
			}
			else
			{
				IsalreadyTurn = true;
				IsalreadyStand = true;
				mHGoto->CrazyTurn( Normalize(tarAngle) *0.8f );
				//mAct->CrazyTurn(diffAngleToTar);
			}
			*/


			ProcessingLog<<"--------------1111---------------"<<diffAngleToTar<<"\n";
			//std::cout<<"--------------1111---------------"<<diffAngleToTar<<"\n";
			mHGoto->QuickTurn( Normalize(tarAngle) * 0.9f );
		}
		else
		if( !inStrictKickArea )
		{
			HMKickLog << "no area" << endl;
		//	cout<< "    " << forSpeed << "			" << transSpeed << " "	<<endl;
			if (!mAct->IsLastActAdj)
			{
				mAct->ResetFrameNum();
			}
			mAct->IsLastActAdj = true;
			mAct->HumanSteadyAdjust( forSpeed, transSpeed, 0.0f );

		}
		
		else
		{
			HMKickLog << "go kick" << endl;
 			if( !mHGoto->IsStandingBy() )
 			{
 				mHGoto->ClearSpeed();
 				mAct->Stand();
 			}	
 			else 
			{
				//cout<< "------IsInKickArea-------- " << xDistToBall << " " << yDistToBall << " " << diffAngleToTar << endl;
				if( yDistToBall > 0.0f )
				{
					//cout<< "NewKickRight" << endl;
					HMKickLog << "NewKickRight " << "Get Ready to Kick" << endl;
					mAct->NewKickRight();
				}
				else
				{
					//cout<< "NewKickLeft" << endl;
					HMKickLog << "NewKickLeft " << "Get Ready to Kick" << endl;
					mAct->NewKickLeft();
				}
			}
		}
	}
	else
	{
		HMKickLog << "last" << endl;
		const float distBeforeKick =-0.17f;
		Angle angToTar = Normalize( mWorldModel->mBall.mPos.angTheta2( tarKickTo ) );
		Ray tarBeforeKickRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, angToTar );
		Vector3f posBeforeKick = tarBeforeKickRay.GetPoint( distBeforeKick );

		mHGoto->GotoTar( posBeforeKick, angToTar );
	}
}
bool Kick::Shoot()
{

}
bool Kick::Pass()
{

}
bool Kick::KickAttack()
{
	const float distBeforeKick =4.0f;
	Angle angToTar = Normalize( mWorldModel->mSelf.mPos.angTheta2( mWorldModel->mBall.mPos ) );
	Ray tarBeforeKickRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, angToTar );
	Vector3f posBeforeKick = tarBeforeKickRay.GetPoint( distBeforeKick );
	DoKickAction( posBeforeKick );
// 	if( BallInShootArea() )
// 	{
// 		Shoot();
// 	}
}

