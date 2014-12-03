//#include "HumanGoto.h"
#include "Dribble.h"
#define HMGotoLog gSpeedLog<< "[HuGoto] "
#define HMSpeedLog gSpeedLog << "[Speed ] "
#define ProcessingLog gProcessingLog<<"[HumanGoto] "
#define MotionLog gLog<< "[Motion] "
HumanGoto::HumanGoto( WorldModel *wm, Situation *situ, CommandQuene *cmdQuene, Action *act ):
cForMaxSpeed( 0.08f ),
cForMinSpeed( -0.05f ),
cTransMaxSpeed( 0.05f ),
cTransMinSpeed( -0.05f ),
cTurnMaxAngle( 30.0f ),
cTurnMinAngle( -30.0f ),
cForAcc( 0.015f ),	//0.0095f
cTransAcc( 0.01f ),
cTurnAcc( 10.0f ),
cForProp( 0.3f ),
cTransProp( 0.3f ),
cTurnProp( 0.65f )
{
	mWorldModel = wm;
	mSituation = situ;
	mCmdQuene = cmdQuene;
	mAct = act;

	mForCurrSpeed = 0.0f;
	mTransCurrSpeed = 0.0f;
	mTurnCurrSpeed = 0.0f;

	mIsLastBuffer = false;

	mSpeedDeque.resize( 10 );
	ClearSpeedDeque();

	mObstacle = Obstacle::GetInstance( mWorldModel );
	//mObstacle = new Obstacle( mWorldModel );
}
HumanGoto::~HumanGoto()
{

}


void HumanGoto::SpeedLimit(float &forSpeed, float &transSpeed,  Angle &turnSpeed )
{
	// 前进加速控制
	//if( fabs(mSpeedDeque.at(0).forSpeed) <= cForAcc * 4.5f )
	float forReducePro = 0.8f;
	float currGameTime = mWorldModel->mGameTime;
	static float lastCallHumanGotoTime = 0.0f;
	if( mSpeedDeque.at(0).forSpeed < 0.0f || mSpeedDeque.at(1).forSpeed < 0.0f )
	{
		if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 3.0f * forReducePro )
		{
			forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 3.0f * forReducePro;
		}	
	}
	else if( fabs(mSpeedDeque.at(0).forSpeed) <= cForAcc )
 	{	
		if( currGameTime - lastCallHumanGotoTime > 0.5f || fabs(mSpeedDeque.at(0).turnSpeed) > 0.02f )
		{
// 			if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 3.5f )
// 			{
// 				forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 3.5f;
// 			}	
			if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 2.0f )
			{
				forSpeed = mSpeedDeque.at(0).forSpeed  - 0.02f;
			}
		}
// 		else if( fabs(mSpeedDeque.at(0).transSpeed) > EPS || fabs(mSpeedDeque.at(0).turnSpeed) > 0.02f || 
// 			fabs(mSpeedDeque.at(1).transSpeed) > EPS || fabs(mSpeedDeque.at(1).turnSpeed) > 0.02f )
// 		{
// 			if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 3.8f )
// 			{
// 				forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 3.8f;
// 			}	
// 		}
		else 
		{
////////////////////////////////////////////////////
			if(  fabs(mSpeedDeque.at(0).turnSpeed) > 0.02f
// 				|| fabs(mSpeedDeque.at(1).turnSpeed) > 0.02f
// 				|| fabs(mSpeedDeque.at(2).turnSpeed) > 0.02f
				)
			{
				if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 3.5f * forReducePro )
				{
					forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 3.5f * forReducePro;
				}	
			}
////////////////////////////////////////////////////
			else if( mWorldModel->mGameTime < 1.0f )
			{
				if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 3.8f * forReducePro )
				{
					forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 3.8f * forReducePro;
				}
			}
			else
			{
				if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 4.0f * forReducePro )
				{
					forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 4.0f * forReducePro;
				}
			}
		}
	}
 	else
 	{
		//if( fabs(mSpeedDeque.at(0).transSpeed) > EPS  
		//	|| fabs(mSpeedDeque.at(1).transSpeed) > EPS  
		//	|| fabs(mSpeedDeque.at(2).transSpeed) > EPS  
		//)
		//{
		//	if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 1.0f * forReducePro  )
		//	{
		//		forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 1.0f * forReducePro ;
		//	}	
		//}
		//else if(  fabs(mSpeedDeque.at(0).turnSpeed) > 0.02f
		//		 || fabs(mSpeedDeque.at(1).turnSpeed) > 0.02f
		//		 || fabs(mSpeedDeque.at(2).turnSpeed) > 0.02f )
		//{
		//	if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 0.5f * forReducePro  )
		//	{
		//		forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 0.5f * forReducePro ;
		//	}	
		//}
		//else 
		//{
			if( mWorldModel->mGameTime < 1.0f )
			{
				if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 3.0f * forReducePro  )
				{
					forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 3.0f * forReducePro ;
				}
			}
			else
			{
				if( forSpeed > mSpeedDeque.at(0).forSpeed + cForAcc * 4.0f * forReducePro  )
				{
					forSpeed = mSpeedDeque.at(0).forSpeed + cForAcc * 4.0f * forReducePro ;
				}
			}
		//}
 	}

	// 前进减速控制
	if( mSpeedDeque.at(0).forSpeed >= cForMaxSpeed * 0.9f )
	{	
		if( forSpeed <= mSpeedDeque.at(0).forSpeed - cForAcc * 1.5f )
		{	
			forSpeed = mSpeedDeque.at(0).forSpeed - cForAcc * 1.5f;
		}
		turnSpeed = 0.0f;
	} 
	else if( mSpeedDeque.at(0).forSpeed >= cForMaxSpeed * 0.4f )
	{
		if( forSpeed <= mSpeedDeque.at(0).forSpeed - cForAcc * 2.0f )
		{	
			forSpeed = mSpeedDeque.at(0).forSpeed - cForAcc * 2.0f;
		} 
	}
	else 
	{
		if( forSpeed <= mSpeedDeque.at(0).forSpeed - cForAcc * 1.5f )
		{	
			forSpeed = mSpeedDeque.at(0).forSpeed - cForAcc * 1.5f;
		} 
	}
	//if( forSpeed <= mSpeedDeque.at(0).forSpeed - cForAcc * 3.6f )
	//{	
	//	forSpeed = mSpeedDeque.at(0).forSpeed - cForAcc * 3.6f;
	//} 
	
	if( mSpeedDeque.at(0).forSpeed > mSpeedDeque.at(1).forSpeed ) 
	{
		if( forSpeed < mSpeedDeque.at(0).forSpeed )
		{
			forSpeed = mSpeedDeque.at(0).forSpeed;
		}
	}
	else if( mSpeedDeque.at(0).forSpeed < mSpeedDeque.at(1).forSpeed ) 
	{
		if( forSpeed > mSpeedDeque.at(0).forSpeed )
		{
			forSpeed = mSpeedDeque.at(0).forSpeed;
		}
	}
	if( mSpeedDeque.at(0).forSpeed < 0.0f && forSpeed > 0.0f )
	{
		forSpeed = 0.0f;
	}

	// 前进综合控制
	if( mSpeedDeque.at(0).forSpeed < mSpeedDeque.at(2).forSpeed 
		&& mSpeedDeque.at(1).forSpeed < mSpeedDeque.at(2).forSpeed
		&& mSpeedDeque.at(0).forSpeed > 0.0f )
	{
		if( forSpeed > mSpeedDeque.at(0).forSpeed )
		{
			forSpeed = mSpeedDeque.at(0).forSpeed;
		}
	}
	if( mSpeedDeque.at(0).forSpeed < mSpeedDeque.at(1).forSpeed )
	{
		if( forSpeed > mSpeedDeque.at(0).forSpeed )
		{
			forSpeed = mSpeedDeque.at(0).forSpeed;
		}
	}

//  	if( fabs(mSpeedDeque.at(1).turnSpeed) > 0.5f + EPS 
// 		/*|| ( fabs(mSpeedDeque.at(1).transSpeed) > 0.01f + EPS && fabs(mSpeedDeque.at(0).transSpeed) > 0.01f + EPS ) */
// //  		|| fabs(mSpeedDeque.at(2).turnSpeed) > 0.5f + EPS 
// //   		|| fabs(mSpeedDeque.at(3).turnSpeed) > 5.0f + EPS 
// 	)
//  	{
//  		if( fabs(forSpeed - mSpeedDeque.at(0).forSpeed) > EPS )
//  		{
//  			forSpeed = mSpeedDeque.at(0).forSpeed;
//  		}
//  	}

	// 改变转身方向控制
	if( turnSpeed * mSpeedDeque.at(0).turnSpeed < 0.0f)
	{
		turnSpeed = 0.0f;
	}

	// 转身速度控制
	if( turnSpeed > mSpeedDeque.at(0).turnSpeed + cTurnAcc * 1.0f )
	{
		turnSpeed = mSpeedDeque.at(0).turnSpeed + cTurnAcc * 1.0f;
	}
	else if( turnSpeed < mSpeedDeque.at(0).turnSpeed - cTurnAcc * 1.0f )
	{
		turnSpeed = mSpeedDeque.at(0).turnSpeed - cTurnAcc * 1.0f;
	}

	if( fabs(turnSpeed - mSpeedDeque.at(0).turnSpeed) > EPS 
		&& fabs(mSpeedDeque.at(0).turnSpeed - mSpeedDeque.at(1).turnSpeed) > EPS )
	{
		turnSpeed = mSpeedDeque.at(0).turnSpeed;
	}

	// 平移速度控制
	if( currGameTime - lastCallHumanGotoTime > 0.5f )
	{
		if( transSpeed > mSpeedDeque.at(0).transSpeed + transSpeed * 0.2f )
		{
			transSpeed = mSpeedDeque.at(0).transSpeed + transSpeed * 0.2f;
		}	
		else if( transSpeed < mSpeedDeque.at(0).transSpeed - transSpeed * 0.2f )
		{
			transSpeed = mSpeedDeque.at(0).transSpeed - transSpeed * 0.2f;
		}
	}
	else if( fabs(mSpeedDeque.at(0).transSpeed) < EPS )
	{
		if( mSpeedDeque.at(0).forSpeed > 0.04f )
		{
			if( transSpeed > mSpeedDeque.at(0).transSpeed + cTransAcc * 0.05f )
			{
				transSpeed = mSpeedDeque.at(0).transSpeed + cTransAcc * 0.05f ;
			}
			else if( transSpeed < mSpeedDeque.at(0).transSpeed - cTransAcc * 0.05f  )
			{
				transSpeed = mSpeedDeque.at(0).transSpeed - cTransAcc * 0.05f ; 
			}
		}
		else if( transSpeed > mSpeedDeque.at(0).transSpeed + cTransAcc * 0.1f )
		{
			transSpeed = mSpeedDeque.at(0).transSpeed + cTransAcc * 0.1f ;
		}
		else if( transSpeed < mSpeedDeque.at(0).transSpeed - cTransAcc * 0.1f  )
		{
			transSpeed = mSpeedDeque.at(0).transSpeed - cTransAcc * 0.1f ; 
		}
	}
	else if( transSpeed > mSpeedDeque.at(0).transSpeed + cTransAcc )
	{
		transSpeed = mSpeedDeque.at(0).transSpeed + cTransAcc;
	}
	else if( transSpeed < mSpeedDeque.at(0).transSpeed - cTransAcc )
	{
		transSpeed = mSpeedDeque.at(0).transSpeed - cTransAcc; 
	}

	if( transSpeed * mSpeedDeque.at(0).transSpeed < 0.0f || mSpeedDeque.at(0).transSpeed * mSpeedDeque.at(1).transSpeed < 0.0f )
	{
		if( 0.0f > mSpeedDeque.at(0).transSpeed + cTransAcc )
		{
			transSpeed = mSpeedDeque.at(0).transSpeed + cTransAcc;
		}
		else if( 0.0f < mSpeedDeque.at(0).transSpeed - cTransAcc )
		{
			transSpeed = mSpeedDeque.at(0).transSpeed - cTransAcc; 
		}
		else 
		{
			transSpeed = 0.0f;
		}
	}

	// 最大/最小速度控制
	if( forSpeed >= cForMaxSpeed )
	{
		if( forSpeed >= cForMaxSpeed + 0.002f - EPS )
		{
			if( mSpeedDeque.at(0).forSpeed < cForMaxSpeed + 0.001f && mSpeedDeque.at(0).forSpeed > cForMaxSpeed - 0.001f )
			{
				forSpeed = cForMaxSpeed + 0.003f;
			}
			else
			{
				forSpeed = cForMaxSpeed;
			}
		}
		else
		{
			forSpeed = cForMaxSpeed;
		}
	}
	else if( forSpeed <= cForMinSpeed )
	{
		forSpeed = cForMinSpeed;
	}
	if( transSpeed >= cTransMaxSpeed )
	{
		transSpeed = cTransMaxSpeed;
	}
	else if( transSpeed <= cTransMinSpeed )
	{
		transSpeed = cTransMinSpeed;
	}
	if( turnSpeed >= cTurnMaxAngle )
	{
		turnSpeed = cTurnMaxAngle;
	}
	else if( turnSpeed <= cTurnMinAngle )
	{
		turnSpeed = cTurnMinAngle;
	}

	if( forSpeed >= cForMaxSpeed - EPS )
	{
		turnSpeed = 0.0f;
	}
	else if( fabs(forSpeed) <= EPS )
	{
		if( fabs(turnSpeed) < 0.03f )
		{
			turnSpeed = 0.0f;
		}
	}

	//综合速度控制
// 	if( mIsLastBuffer )
// 	{
// 		cout<< "mIsLastBuffer" << endl;
// 		forSpeed = 0.0f;
// 		transSpeed = 0.0f;
// 		turnSpeed = 0.0f;
// 	}

	//if( fabs(transSpeed) < cTransAcc && forSpeed > 0.05f )
	//{
	//	transSpeed = 0.0f;
	//}

	if( fabs(turnSpeed - 0.3f) < EPS )
	{
		turnSpeed = 0.2f;
	}
	else if( fabs(turnSpeed + 0.3f) < EPS )
	{
		turnSpeed = -0.2f;
	}
 	if( fabs(turnSpeed) < 0.02f - EPS )
 	{
 		turnSpeed = 0.0f;
	}
	//if( fabs(transSpeed) < 0.001f )
	//{
	//	transSpeed = 0.0f;
	//}

	lastCallHumanGotoTime = currGameTime;
}

void HumanGoto::BufferSpeedControl()
{
	HMGotoLog << " Buffer Speed Control " << mGotoMode << endl;
	bool shouldDoBuffer = false;

	if( fabs(mTransCurrSpeed) > cTransAcc * 0.5f || fabs(mTurnCurrSpeed) > 0.03f )
	{
		shouldDoBuffer = true;
	}

	if( !shouldDoBuffer )
	{
		return;
	}

	float buffForSpeed = mForCurrSpeed;
	float buffTransSpeed = mTransCurrSpeed;
	float buffTurnSpeed = mTurnCurrSpeed;

	//mForCurrSpeed -= 0.02f;
}


bool HumanGoto::DoHumanGoto()
{
	HMGotoLog << " currWalkMode " << mGotoMode <<"  Simtime:"<<mWorldModel->mSimTime<< endl;
	ProcessingLog << "time:"<<mWorldModel->mSimTime<<"  mGotoMode:"<< mGotoMode<<"\n";
	HMGotoLog << "DoHumanGoto  " <<"(Simtime "<<mWorldModel->mSimTime<< " )"<< mForCurrSpeed << " " << mTransCurrSpeed << " " << mTurnCurrSpeed << endl;

	static float LastTurnAng = 0.0f;
	static GogoMode LastGotoMode = GM_For; 
	static float LastTransSpeed = 0.0f;

	if (fabs(LastTurnAng)<EPS && LastGotoMode!=GM_Trans && mGotoMode!=GM_Trans)
	{
		mAct->ResetFrameNum();
	}
	if (LastGotoMode !=GM_Trans  && mGotoMode == GM_Trans)
	{
		mAct->ResetFrameNum();
	}
	if (fabs(LastTransSpeed)<EPS && LastGotoMode==GM_Trans && mGotoMode==GM_Trans && fabs(LastTurnAng)<EPS)
	{
		mAct->ResetFrameNum();
	}

	if (mAct->IsLastActAdj)
	{
		mAct->IsLastActAdj = false;
		mAct->ResetFrameNum();
	}
	if (LastGotoMode!=GM_Turn && mGotoMode==GM_Turn)
	{
		mAct->ResetFrameNum();
	}

	if( mGotoMode == GM_For )
	{
		ProcessingLog<<"cycle "<<mAct->GetCycle()<<"\n";
		if (mTurnCurrSpeed >= 0.0f  &&  mAct->GetFootStep() == LeftLegStay && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTurnCurrSpeed = 0.0f;
		}
		else if ( mTurnCurrSpeed <= 0.0f && mAct->GetFootStep() == RightLegStay && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTurnCurrSpeed = 0.0f;
		}

		if ( mTransCurrSpeed <= 0.0f && mAct->GetFootStep() == RightLegStay && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTransCurrSpeed = 0.0f;
		}
		else if ( mTransCurrSpeed >= 0.0f && mAct->GetFootStep() == LeftLegStay && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTransCurrSpeed = 0.0f;
		}
		HMGotoLog << "DoHumanGoto beforecontrol "<< mForCurrSpeed << " " << mTransCurrSpeed << " " << mTurnCurrSpeed << endl;
        BasicWalkSpeedControl(mForCurrSpeed, mTransCurrSpeed, mTurnCurrSpeed);	
		HMGotoLog << "DoHumanGoto afrercontrol "<< mForCurrSpeed << " " << mTransCurrSpeed << " " << mTurnCurrSpeed << endl;
		mAct->HumanWalk( mForCurrSpeed, mTransCurrSpeed, mTurnCurrSpeed );

	}
	
	if ( mGotoMode == GM_Trans)
	{
		BasicWalkSpeedControl(mForCurrSpeed, mTransCurrSpeed, mTurnCurrSpeed);
	    if ( mTransCurrSpeed <= 0.0f && mAct->GetFootStep() == RightLegStay && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTransCurrSpeed = 0.00f;
		}
		else if ( mTransCurrSpeed >= 0.0f && mAct->GetFootStep() == LeftLegStay && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTransCurrSpeed = -0.00f;
			
		}

		mAct->HumanWalk( mForCurrSpeed, mTransCurrSpeed, mTurnCurrSpeed );

	}

	if( mGotoMode == GM_Turn )
	{
		ProcessingLog<<"6\n";
       // BasicWalkSpeedControl(mForCurrSpeed, mTransCurrSpeed, mTurnCurrSpeed);
		Angle quickTurnSpeed = mTurnCurrSpeed;
		if( quickTurnSpeed > 30.0f )
		{	
			quickTurnSpeed = 30.0f;
		}
		else if( quickTurnSpeed < -30.0f )
		{	
			quickTurnSpeed = -30.0f;
		}
		
		if( mAct->GetFootStep() == LeftLegStay && quickTurnSpeed > 0.0f && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTurnCurrSpeed = 0.0f;
			mAct->HumanQuickTurn( 0.0f );
		}
		else if( mAct->GetFootStep() == RightLegStay && quickTurnSpeed < 0.0f && mAct->GetFrameNum() < Cycle_Normal)
		{
			mTurnCurrSpeed = 0.0f;
			mAct->HumanQuickTurn( 0.0f );
		}
		else
		{
			mAct->HumanQuickTurn( quickTurnSpeed );
		}

	}
	if ( mGotoMode == GM_CTurn)
	{
		mAct->HumanCrazyTurn( mTurnCurrSpeed );


	}
	
	UpdateSpeedDeque();

	LastGotoMode = mGotoMode;
	LastTurnAng = mTurnCurrSpeed;
	LastTransSpeed = mTransCurrSpeed;
	
	return true;
}


void HumanGoto::BasicWalkSpeedControl( float &forSpeed, float &transSpeed, float &turnSpeed )
{
	if (transSpeed > cTransMaxSpeed)
	{
		transSpeed = cTransMaxSpeed; 
	}
	else if (transSpeed < cTransMinSpeed)
	{
		transSpeed = cTransMinSpeed; 
	}

	if (forSpeed > cForMaxSpeed)
	{
		forSpeed = cForMaxSpeed; 
	}
	else if (forSpeed < cForMinSpeed)
	{
		forSpeed = cForMinSpeed; 
	}

	if (turnSpeed > cTurnMaxAngle)
	{
		turnSpeed = cTurnMaxAngle; 
	}
	else if (turnSpeed < cTurnMinAngle)
	{
		turnSpeed = cTurnMinAngle; 
	}

	if (mSpeedDeque[0].forSpeed + cForAcc < forSpeed)
	{
		forSpeed = mSpeedDeque[0].forSpeed + cForAcc;
	}
	
	if (mSpeedDeque[1].forSpeed + cForAcc < forSpeed)
	{
		forSpeed = mSpeedDeque[1].forSpeed + cForAcc;
	}
	

	if (mSpeedDeque[0].forSpeed - (cForAcc+0.01f) > forSpeed)
	{
		forSpeed = mSpeedDeque[0].forSpeed - (cForAcc+0.01f);
	}
	
	if (mSpeedDeque[1].forSpeed - (cForAcc+0.01f) > forSpeed)
	{
		forSpeed = mSpeedDeque[1].forSpeed - (cForAcc+0.01f);
	}
/*

	if ( mSpeedDeque[1].turnSpeed +cTurnAcc < turnSpeed )
	{
		turnSpeed = mSpeedDeque[1].turnSpeed +cTurnAcc;
	}
	else if (mSpeedDeque[1].turnSpeed - cTurnAcc > turnSpeed)
	{
		turnSpeed = mSpeedDeque[1].turnSpeed - cTurnAcc;
	}
*/
	if (mSpeedDeque[0].transSpeed + cTransAcc < transSpeed)
	{
		transSpeed = mSpeedDeque[0].transSpeed + cTransAcc;
	} 
	else if (mSpeedDeque[0].transSpeed - (cTransAcc + 0.01f) > transSpeed)
	{
		transSpeed = mSpeedDeque[0].transSpeed - (cTransAcc + 0.01f);
	}
}
void HumanGoto::ClearSpeedDeque()
{
	for( int i = 0; i < mSpeedDeque.size(); i ++ )
	{
		mSpeedDeque.at(i).gameTime = mWorldModel->mGameTime;
		mSpeedDeque.at(i).bodyHeight = BH_High;
		mSpeedDeque.at(i).forSpeed = 0.0f;
		mSpeedDeque.at(i).transSpeed = 0.0f;
		mSpeedDeque.at(i).turnSpeed = 0.0f;
	}
	ClearSpeed();
}

void HumanGoto::ClearSpeed()
{
	mForCurrSpeed = 0.0f;
	mTransCurrSpeed = 0.0f;
	mTurnCurrSpeed = 0.0f;

	mAct->SetFootStep();
}
void HumanGoto::SetSpeed( float forSpeed, float transSpeed, float turnSpeed )
{
	mForCurrSpeed = forSpeed;
	mTransCurrSpeed = transSpeed;
	mTurnCurrSpeed = turnSpeed;
}
void HumanGoto::UpdateSpeedDeque()
{
	SpeedValue currSpeedValue;
	currSpeedValue.gameTime = mWorldModel->mGameTime;
	currSpeedValue.bodyHeight = mBodyHeight;
	currSpeedValue.forSpeed = mForCurrSpeed;
	currSpeedValue.transSpeed = mTransCurrSpeed;
	currSpeedValue.turnSpeed = mTurnCurrSpeed;

	mSpeedDeque.push_front( currSpeedValue );
	mSpeedDeque.pop_back();
}

void HumanGoto::SetCurrGogoMode( GogoMode gotoMode )
{
	mGotoMode = gotoMode;
}

void HumanGoto::SetCurrLongGogoMode( Vector3f tarVec )
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Angle bodyAng = mWorldModel->mBodyAngle;
	float distToTar = selfPos.distXY2( tarVec );
	Angle angToTar = (tarVec - selfPos).angTheta();
	Angle angSelfToTar = Normalize( angToTar - bodyAng );
// 	float forDistToTar = fabs( distToTar * cos( angSelfToTar * PI / 180.0f ) );
// 	float transDistToTar = fabs( distToTar * sin( angSelfToTar * PI / 180.0f ) );
	float forDistToTar = distToTar * cos( angSelfToTar * PI / 180.0f );
	float transDistToTar = distToTar * sin( angSelfToTar * PI / 180.0f );
	
	HMGotoLog << "LongGogoMode distToTar " << distToTar << " angSelfToTar " << angSelfToTar << " forDistToTar " << forDistToTar << " transDistToTar " << transDistToTar << endl;

	const float minAngleDist = 0.1f;
	const Angle angEpsMin = 5.0f;
	const Angle angEpsMax = 10.0f;
	Angle angEps;	
	//angEps = 10.0f;
	angEps = 1.0f * ( distToTar - 1 ) + 10.0f;
	if( angEps < angEpsMin )
	{
		angEps = angEpsMin;
	}
	else if( angEps > angEpsMax )
	{
		angEps = angEpsMax;
	}

	const Angle angEpsLarger = 45.0f;
	Angle angEpsTiny = 45.0f;
	if( fabs(mTurnCurrSpeed) > 0.03f )
	{
		angEpsTiny = 10.0f;
	}

	if( ( fabs(angSelfToTar) > angEpsLarger 
		|| fabs(angSelfToTar) > angEpsTiny
		|| fabs(angSelfToTar) > angEps && fabs(mForCurrSpeed) < EPS && fabs(mTransCurrSpeed) < EPS ) 
//  		&& ( ( fabs( fabs(angSelfToTar ) - 180.0f )> angEpsLarger ||
//  		fabs( fabs(angSelfToTar) - 180.0f ) > angEps && fabs(mForCurrSpeed) < EPS && fabs(mTransCurrSpeed) < EPS ) )
		)
	{
		mGotoMode = GM_Turn;
	}
	else if( distToTar > 0.1f ) 
	{
		if( fabs(forDistToTar) >= fabs(transDistToTar) 
			/*&& fabs(angSelfToTar) < angEpsMin*/ )
		{
			mGotoMode = GM_For;
		}
		else
		{
			mGotoMode = GM_Trans;
		}
	}
	else
	{
		mGotoMode = GM_Turn;
	}


	mGotoMode = GM_For;

// 	else
// 	{
// 		mGotoMode = GM_StandBy;
// 	}
}

void HumanGoto::SetCurrNearGotoMode( Vector3f tarVec )
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Angle bodyAng = mWorldModel->mBodyAngle;
	float distToTar = selfPos.distXY2( tarVec );
	Angle angToTar = (tarVec - selfPos).angTheta();
	Angle angSelfToTar = Normalize( angToTar - bodyAng );
	float forDistToTar = distToTar * cos( angSelfToTar * PI / 180.0f );
	float transDistToTar = distToTar * sin( angSelfToTar * PI / 180.0f );

	HMGotoLog << "NearGotoMode distToTar " << distToTar << " angSelfToTar " << angSelfToTar << " forDistToTar " << forDistToTar << " transDistToTar " << transDistToTar << endl;

	float distEps = 0.1f;
	Angle angEps = 12.0f;

    mGotoMode = GM_For;
	if (fabs(forDistToTar)<0.01f && fabs(transDistToTar)<0.01f && fabs(angSelfToTar)>0.1f)
	{
		

		mGotoMode = GM_Turn;
	}

// 	else if( fabs(angSelfToTar) > angEps )
// 	{
// 		mGotoMode = GM_Turn;
// 	}
// 	else
// 	{
// 		mGotoMode = GM_StandBy;
// 	}
}

void HumanGoto::SetCurrSpeed( Vector3f tarVec )
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Angle bodyAng = mWorldModel->mBodyAngle;
	float distToTar = selfPos.distXY2( tarVec );
	Angle angToTar = (tarVec - selfPos).angTheta();
	Angle angSelfToTar = Normalize( angToTar - bodyAng );
	float forDistToTar = distToTar * cos( angSelfToTar * PI / 180.0f ) ;
	float transDistToTar = distToTar * sin( angSelfToTar * PI / 180.0f ) ;

	float idealForSpeed = forDistToTar * cForProp;
	Angle idealTurnSpeed = angSelfToTar * cTurnProp;
	float idealTransSpeed = transDistToTar * cTransProp;
	HMGotoLog << "SetCurrSpeed( Vector3f tarVec ) " <<"(Simtime "<<mWorldModel->mSimTime<< " ) "<<mGotoMode<< " "<<idealForSpeed << " " <<idealTransSpeed  << " " << idealTurnSpeed << endl;
	//if( fabs(angSelfToTar) > 90.0f )
	//{
	//	idealTurnSpeed = -idealTurnSpeed;
	//	//idealTransSpeed = -idealTransSpeed;
	//}
	

	if( mGotoMode == GM_For )
	{
		HMGotoLog<<"mGotoMode == GM_For"<<endl;
		SetCurrForSpeed( idealForSpeed, idealTurnSpeed, idealTransSpeed );
	}
	else if( mGotoMode == GM_Turn )
	{
		HMGotoLog<<"mGotoMode == GM_Turn"<<endl;
		SetCurrTurnSpeed(  idealForSpeed, idealTurnSpeed, idealTransSpeed  );
	}
	else if( mGotoMode == GM_Trans )
	{
		SetCurrTransSpeed(  idealForSpeed, idealTurnSpeed, idealTransSpeed  );
	}
	else
	{
		SetCurrStandSpeed();
	}
	
}

void HumanGoto::SetCurrSpeed( Angle tarBodyAng )
{
	Angle bodyAng = mWorldModel->mBodyAngle;
	Angle diffBodyAngToTarBodyAng = Normalize( tarBodyAng - bodyAng );
	Angle idealTurnSpeed = diffBodyAngToTarBodyAng * cTurnProp;
	HMGotoLog << "SetCurrSpeed( Angle tarBodyAng ) " << idealTurnSpeed << endl;

	SetCurrTurnSpeed(  0.0f, idealTurnSpeed, 0.0f  );
}

void HumanGoto::SetCurrForSpeed( float idealForSpeed , float idealTurnSpeed, float idealTransSpeed )
{
	const float transMax = 0.0f;
	const float forMax_1 = cForMaxSpeed;
	const float forMax_2 = 0.05f;
	const float backMax_1 = cForMinSpeed;
	const float backMax_2 = -0.0f;
	const float turnMax_1 = 15.0f;
	const float turnMax_2 = -15.0f;

	float forIdealSpeed = idealForSpeed;
	float turnIdealSpeed = idealTurnSpeed;
	float transIdealSpeed = idealTransSpeed;

	if( transIdealSpeed > transMax )
	{
		transIdealSpeed = transMax;
	}
	else if( transIdealSpeed < -transMax )
	{
		transIdealSpeed = -transMax;
	}

	if( fabs(mTransCurrSpeed) > transMax )
	{
		mTransCurrSpeed = transIdealSpeed;
	}

	if (idealForSpeed>=0.055f && idealTurnSpeed>=10.0f)
	{
		forIdealSpeed = 0.05f;
	}
	if (idealTurnSpeed > turnMax_1)
	{
		turnIdealSpeed = turnMax_1;
	} 
	else if (idealTurnSpeed < turnMax_2)
	{
		turnIdealSpeed = turnMax_2;
	}
    mForCurrSpeed = forIdealSpeed;
	mTurnCurrSpeed = turnIdealSpeed;


	HMGotoLog << "SetCurrForSpeed  " <<"(Simtime "<<mWorldModel->mSimTime<< " )"<< mForCurrSpeed << " " << mTransCurrSpeed << " " << mTurnCurrSpeed << endl;

}
void HumanGoto::SetCurrTurnSpeed( float idealForSpeed , float idealTurnSpeed, float idealTransSpeed )
{
	const float transMax = 0.015f;
	if( fabs(mTransCurrSpeed) > transMax )
	{
		//mTransCurrSpeed *= 0.01f;
		mTransCurrSpeed=transMax;
		return;
	}
	//mTransCurrSpeed = 0.0f;
	
	const float turnMax = 30.0f;
	float forMax;
	if( fabs(idealTurnSpeed) > turnMax )
	{
		forMax = -0.002f * ( turnMax - 10.0f ) + 0.04f;
	}
	else
	{
		forMax = -0.002f * ( fabs(idealTurnSpeed) - 10.0f ) + 0.04f;
	}

	float backMax = -0.03f;

 	if( forMax < 0.015f )
 	{
 		forMax = 0.015f;
 	}

	if( mForCurrSpeed > forMax - EPS || mForCurrSpeed < backMax + EPS )
	{
		mForCurrSpeed *= 0.01f;
		//mForCurrSpeed = 0.0f;
		return;
	}

	mForCurrSpeed = 0.0f;
	mTurnCurrSpeed = idealTurnSpeed;
	HMGotoLog<<"mTurnCurrSpeed= "<<idealTurnSpeed<<endl;
}

void HumanGoto::SetCurrTransSpeed( float idealForSpeed , float idealTurnSpeed, float idealTransSpeed )
{
	const float forMax = 0.05f;
	const float turnMax = 0.00f;
	float forIdealSpeed = idealForSpeed;
	
	if( forIdealSpeed > forMax )
	{
		forIdealSpeed = forMax;
	}
	else if( forIdealSpeed < -forMax )
	{
		forIdealSpeed = -forMax;
	}

	mForCurrSpeed = forIdealSpeed;

	float turnIdealSpeed = idealTurnSpeed;
	if( turnIdealSpeed > turnMax )
	{
		turnIdealSpeed = turnMax ;
	}
	else if( turnIdealSpeed < -turnMax )
	{
		turnIdealSpeed = -turnMax ;
	}
	mTurnCurrSpeed = turnIdealSpeed;
	mTransCurrSpeed = idealTransSpeed;

     ProcessingLog << "SetCurrTransSpeed " <<"(Simtime "<<mWorldModel->mSimTime<< " )"<< mForCurrSpeed << " " << mTransCurrSpeed << " " << mTurnCurrSpeed << endl;
}

void HumanGoto::SetCurrStandSpeed()
{
// 	if( fabs(mForCurrSpeed) >= cForMaxSpeed * 0.5f
// 		|| fabs(mTransCurrSpeed) >= cTransMaxSpeed
// 		|| fabs(mTurnCurrSpeed) >= cTurnMaxAngle
// 		)
// 	{
// 		mForCurrSpeed * 0.5f;
// 		mTransCurrSpeed *= 0.5f;
// 		mTurnCurrSpeed *= 0.5f;
// 	}
// 	else
// 	{
// 		mForCurrSpeed = 0.0f;
// 		mTransCurrSpeed = 0.0f;
// 		mTurnCurrSpeed = 0.0f;
// 	}
	mForCurrSpeed = 0.0f;
	mTransCurrSpeed = 0.0f;
	mTurnCurrSpeed = 0.0f;
}
bool HumanGoto::IsStandingBy()
{
	return fabs(mForCurrSpeed) < EPS && fabs(mTransCurrSpeed) < EPS && fabs(mTurnCurrSpeed) < EPS;
}
bool HumanGoto::IsStandingByWithTurn()
{
	return fabs(mForCurrSpeed) < EPS && fabs(mTransCurrSpeed) < EPS /*&& fabs(mTurnCurrSpeed) < EPS*/;
}
bool HumanGoto::IsFullSpeed()
{
	return ( mForCurrSpeed > cForMaxSpeed - EPS ) || ( fabs(mTransCurrSpeed) > cTransMaxSpeed - EPS )
		|| ( mSpeedDeque.at(0).forSpeed > cForMaxSpeed - EPS  ) || ( fabs(mSpeedDeque.at(0).transSpeed) > cTransMaxSpeed - EPS )
		|| ( mSpeedDeque.at(1).forSpeed > cForMaxSpeed - EPS  ) || ( fabs(mSpeedDeque.at(1).transSpeed) > cTransMaxSpeed - EPS )
		/*|| ( mSpeedDeque.at(2).forSpeed > cForMaxSpeed - EPS  ) || ( fabs(mSpeedDeque.at(2).transSpeed) > cTransMaxSpeed - EPS )*/;
}
bool HumanGoto::GotoTar( Vector3f tarVec )
{
	return GotoTar( tarVec, mWorldModel->mBodyAngle );
}

bool HumanGoto::GotoTar( Vector3f tarVec, Angle tarBodyAng )
{
	gProcessingLog << " GotoTar   time:"<<mWorldModel->mSimTime<<"\n";

	const float cNearTarDist = 1.0f;
	int inGuardDistNumS = 0;												//小的弹开距离为0.4
	int inGuardDistNumB = 0;
	int selfInDist = 0;
	int ourForbidDistNum = 0;
	int oppForbidDistNum = 0;
	Vector3f ballPos = mWorldModel->mBall.mPos;												    //不被弹出的与球保持一定距离的位置
	float tempDist = 1.25f;													//初始为1
	float shouldMoveDistS = 0.6f;	
	float shouldMoveDistB = 1.3f;																			//站位的0.4米内有队友需站在另一位置,f
	float myDistToBall = mWorldModel->mSelf.DistXyTo(ballPos);
	if(mWorldModel->mOurPlayers.size() > 0)
	{
		for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		{
			if ( mWorldModel->mOurPlayers.at(i).mMyPlayerNo == mWorldModel->mSelf.mMyPlayerNo)
			{
			

			}

			else 
			{
				tempDist= mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos);

				if(tempDist <= shouldMoveDistS)
				{
					inGuardDistNumS ++;
				}
				else if(tempDist > shouldMoveDistS && tempDist <= shouldMoveDistB)
				{
					inGuardDistNumB ++;
				}
				if ( mWorldModel->mOurPlayers.at(i).mPos.x < -8.6 &&  fabs(mWorldModel->mOurPlayers.at(i).mPos.y) < 1.9)
				{
					ourForbidDistNum ++;
				}
			}
		}		
	}
	if (mWorldModel->mOppPlayers.size() > 0)
	{
		for(int i = 0;i < mWorldModel->mOppPlayers.size();i ++)
		{
			if (mWorldModel->mBall.mPos.x < 0)
			{
				if ( mWorldModel->mOppPlayers.at(i).mPos.x < -8.6 &&  fabs(mWorldModel->mOppPlayers.at(i).mPos.y) < 1.9)
				{
					oppForbidDistNum ++;
				}
			}
			else if (mWorldModel->mBall.mPos.x > 0)
			{
				if ( mWorldModel->mOppPlayers.at(i).mPos.x > 8.6 &&  fabs(mWorldModel->mOppPlayers.at(i).mPos.y) < 1.9)
				{
					oppForbidDistNum ++;
				}
			}
		}

	}
	int forbitDistNum = ourForbidDistNum + oppForbidDistNum;
	/*if ((inGuardDistNumS >= 1 || inGuardDistNumB >= 2 || forbidDistNum >= 4) && selfInDist == 0)
	{
	HMGotoLog << "backPos " << myDistToBall << endl;		
	}*/
	Vector3f backPos = tarVec;

	float selfDistToGoal = mWorldModel->mSelf.DistXyTo(mWorldModel->mOurGoalCenter);

	if ((inGuardDistNumS > 1 || inGuardDistNumB > 2 || forbitDistNum > 4) && myDistToBall > 0.3)     //距离小于0.25，认为在控球
	{
		Vector3f ourGoalCenter = mWorldModel->mOurGoalCenter;

		Vector3f selfPos = mWorldModel->mSelf.mPos;

		Angle ballToSelfAngle = ballPos.angTheta2( selfPos );

		Angle ourCenterToSelfAngle = ourGoalCenter.angTheta2( selfPos );

		Ray ballToMyself = Ray::MakeRayFromPositionAndAngle(ballPos,ballToSelfAngle);

		Ray ourCenterToMyself = Ray::MakeRayFromPositionAndAngle(ourGoalCenter,ourCenterToSelfAngle);

		float backDist = 2.7;

		if (ourForbidDistNum > 3 && selfDistToGoal < 2.3 )
		{
			HMGotoLog << "forbid" << endl;
			ProcessingLog<<"Position has been changed in HumanGoto Because of limit:"<<endl;
			backPos = ourCenterToMyself.GetPoint(backDist);
			

		}
		else if (inGuardDistNumB > 2 && myDistToBall > 1.0 && myDistToBall < 2.0)
		{
			HMGotoLog << "Big" << endl;
			ProcessingLog<<"Position has been changed in HumanGoto Because of limit:"<<endl;
			backDist = 1.3;

			backPos = ballToMyself.GetPoint(backDist);			
		}
		else if (inGuardDistNumS > 1 && myDistToBall > 0.3 && myDistToBall < 1.0)
		{
			HMGotoLog << "Small" << endl;
			ProcessingLog<<"Position has been changed in HumanGoto Because of limit:"<<endl;
			backDist = 0.8;

			backPos = ballToMyself.GetPoint(backDist);			
		}


	}
	//for (int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
	//{
	//	if (mWorldModel->mOurPlayers.at(i).DistXyTo(backPos) < 0.2)
	//	{

	//	}
	//}
	tarVec = backPos;

	HMGotoLog << "tarVec " << tarVec.x << " " << tarVec.y << " tarBodyAng " << tarBodyAng << endl;
	ProcessingLog<<"tarVec in HumanGoto:"<<tarVec.x<<"  "<<tarVec.y<<"  "<<mWorldModel->mGameTime<<endl;

	float distToTar = mWorldModel->mSelf.DistXyTo( tarVec );

	if( distToTar <= cNearTarDist )
	{ 
		GotoNear( tarVec, tarBodyAng );
	}
	else
	{
		GotoLong( tarVec, tarBodyAng );
	}

	ProcessingLog<<"tarVec after gotoNear/far:"<<tarVec.x<<"  "<<tarVec.y<<"  "<<mWorldModel->mGameTime<<endl;

	return DoHumanGoto();

}
bool HumanGoto::GotoNearTar( Vector3f tarVec, Angle tarBodyAng )
{
	HMGotoLog << endl << endl;
	HMGotoLog << "tarVec GotoNearTar" << tarVec.x << " " << tarVec.y << " tarBodyAng " << tarBodyAng << endl;

	GotoNear( tarVec, tarBodyAng );
	
	return DoHumanGoto();
}

bool HumanGoto::GotoLong( Vector3f tarVec, Angle tarBodyAng )
{
	Vector3f tarGoto = mObstacle->GetRidOfObstacle( tarVec );
	HMGotoLog << " GotoLongTar " << tarVec.x << " " << tarVec.y << " GetRidOfObstacle " << tarGoto.x << " " << tarGoto.y << endl;

	SetCurrLongGogoMode( tarGoto );
	SetCurrSpeed( tarGoto );

	return true;
}
bool HumanGoto::GotoNear( Vector3f tarVec, Angle tarBodyAng )
{
	Vector3f tarGoto = mObstacle->GetRidOfObstacle( tarVec );
	HMGotoLog << " GotoNearTar " << tarVec.x << " " << tarVec.y << " GetRidOfObstacle " << tarGoto.x << " " << tarGoto.y << endl;
	Ray selfToBall = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, mWorldModel->mSelf.ThetaTo(mWorldModel->mBall.mPos));
	Ray ballToChange = Ray::MakeRayFromPositionAndAngle(mWorldModel->mBall.mPos,90);
	float changeDir = 0.3f;
	Vector3f changeTo = ballToChange.GetPoint(changeDir);
	bool inRigrtDir = false;
	float shouldChangeDir = 2.5f;
	float shouldChangeAngle = 45.0f;
	const float nearDistEps = 0.1f;
	const Angle nearAngEps = 5.0f;
	float distOppToBall = 100.0f;
	Vector3f currSelfPos = mWorldModel->mSelf.mPos;
	float distSelfToTar = currSelfPos.distXY2( tarGoto );
	float distSelfToBall = currSelfPos.distXY2(mWorldModel->mBall.mPos);
	Angle angSelfToTar = Normalize( tarBodyAng - mWorldModel->mBodyAngle );

	if( distSelfToTar>= nearDistEps )
	{
		HMGotoLog << "mGotoMode = GM_Turn" << endl;
		SetCurrNearGotoMode(tarGoto);

		SetCurrSpeed( tarGoto );		
	}
	/*
	else if( fabs(angSelfToTar) > nearAngEps )
	{
	HMGotoLog<<"SetCurrGogoMode(GM_Turn) \n";
	SetCurrGogoMode(GM_Turn);

	SetCurrSpeed( tarBodyAng );
	}
	*/
	else
	{
		HMGotoLog << "distSelfToTar< nearDistEps" << endl;
		SetCurrNearGotoMode(tarGoto);

		SetCurrSpeed( tarGoto );
	}
/*
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		if(selfToBall.InRightDir(mWorldModel->mOppPlayers.at(i).mPos) &&  distSelfToBall < 1.5f)
		{
			Ray ballToOpp = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, mWorldModel->mBall.ThetaTo(mWorldModel->mOppPlayers.at(i).mPos));

			Angle rayDeltaAngle = fabs(ballToOpp.GetRayAngle()-selfToBall.GetRayAngle());

			Player opp = mWorldModel->mOppPlayers.at(i);

			distOppToBall = opp.DistXyTo(mWorldModel->mBall.mPos);

			if(rayDeltaAngle < shouldChangeAngle && distOppToBall < shouldChangeDir && mWorldModel->mSelf.mPos.x < 8.5f)
			{					
				TranstoTar(changeTo);

				HMGotoLog << "changeDir" << endl;
			}			
		}
	}

	return true;
*/
	
}
bool HumanGoto::QuickTurn( Angle tarBodyAng )
{
	SetCurrGogoMode(GM_Turn);
	SetCurrSpeed( tarBodyAng );
	return DoHumanGoto();
}
bool HumanGoto::CrazyTurn( Angle tarBodyAng )
{
	SetCurrGogoMode(GM_CTurn);
	SetCurrSpeed( tarBodyAng );
	return DoHumanGoto();
}

bool HumanGoto::TranstoTar( Vector3f tarVec )
{
	return TranstoTar( tarVec, mWorldModel->mBodyAngle );
}
bool HumanGoto::TranstoTar( Vector3f tarVec, Angle tarBodyAng )
{
	gProcessingLog << " TranstoTar   time:"<<mWorldModel->mSimTime<<"\n";

	const float cNearTarDist = 1.0f;
	HMGotoLog << endl << endl;
	HMGotoLog << "tarVec " << tarVec.x << " " << tarVec.y << " tarBodyAng " << tarBodyAng << endl;

	float distToTar = mWorldModel->mSelf.DistXyTo( tarVec );


	TranstoNear( tarVec, tarBodyAng );

	return DoHumanGoto();
}
bool HumanGoto::TranstoNear( Vector3f tarVec, Angle tarBodyAng )
{
	Vector3f tarGoto = tarVec;
	//Vector3f tarGoto = mObstacle->GetRidOfObstacle( tarVec );
	HMGotoLog << " TranstoNearTar " << tarVec.x << " " << tarVec.y << " GetRidOfObstacle " << tarGoto.x << " " << tarGoto.y << endl;

	const float nearDistEps = 0.1f;
	const Angle nearAngEps = 5.0f;
	Vector3f currSelfPos = mWorldModel->mSelf.mPos;
	float distSelfToTar = currSelfPos.distXY2( tarGoto );
	Angle angSelfToTar = Normalize( tarBodyAng - mWorldModel->mBodyAngle );


	HMGotoLog<<"SetCurrGogoMode(GM_Trans) \n";
	SetCurrGogoMode(GM_Trans);


	SetCurrSpeed( tarGoto );

	return true;
}
bool HumanGoto::noLimitGoTar(Vector3f tarVec, Angle tarBodyAng)
{


	gProcessingLog << " GotoTar   time:"<<mWorldModel->mSimTime<<"\n";

	const float cNearTarDist = 1.0f;
	HMGotoLog << endl << endl;
	HMGotoLog << "tarVec " << tarVec.x << " " << tarVec.y << " tarBodyAng " << tarBodyAng << endl;

	float distToTar = mWorldModel->mSelf.DistXyTo( tarVec );

	if( distToTar <= cNearTarDist )
	{ 
		GotoNear( tarVec, tarBodyAng );
	}
	else
	{
		GotoLong( tarVec, tarBodyAng );
	}

	return DoHumanGoto();

}
bool HumanGoto::noLimitGoNearTar(Vector3f tarVec, Angle tarBodyAng)
{




	Vector3f tarGoto = mObstacle->GetRidOfObstacle( tarVec );
	HMGotoLog << " GotoNearTar " << tarVec.x << " " << tarVec.y << " GetRidOfObstacle " << tarGoto.x << " " << tarGoto.y << endl;

	const float nearDistEps = 0.1f;
	const Angle nearAngEps = 5.0f;
	Vector3f currSelfPos = mWorldModel->mSelf.mPos;
	float distSelfToTar = currSelfPos.distXY2( tarGoto );
	Angle angSelfToTar = Normalize( tarBodyAng - mWorldModel->mBodyAngle );

	if( distSelfToTar>= nearDistEps )
	{
		HMGotoLog << "mGotoMode = GM_Turn" << endl;
		SetCurrNearGotoMode(tarGoto);

		SetCurrSpeed( tarGoto );		
	}
	/*
	else if( fabs(angSelfToTar) > nearAngEps )
	{
	HMGotoLog<<"SetCurrGogoMode(GM_Turn) \n";
	SetCurrGogoMode(GM_Turn);

	SetCurrSpeed( tarBodyAng );
	}
	*/
	else
	{
		HMGotoLog << "distSelfToTar< nearDistEps" << endl;
		SetCurrNearGotoMode(tarGoto);

		SetCurrSpeed( tarGoto );
	}

}