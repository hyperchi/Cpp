#include "MotionGoto.h"
#define GotoLog gLog<< "[moGoto] " << "Goto "

#define TestSmartGoto

MotionGoto::MotionGoto( WorldModel *wm, Situation *situ, CommandQuene *cmdQuene, Action *act )
{
	mWorldModel = wm;
	mSituation = situ;
	mCmdQuene = cmdQuene;
	mAct = act;

	InitGoto();

	mForStartSpeed		= 0.015f;
	mTurnStartSpeed		= 3.0f;
	mTransStartSpeed	= 0.003f;

	mForMaxSpeed		= 0.03f;	//0.03f
	mTurnMaxSpeed		= 5.0f;
	mTransMaxSpeed		= 0.01f;	//0.007f;

	mForMinSpeed		= -0.03f;
	mTurnMinSpeed		= -5.0f;
	mTransMinSpeed		= -0.01f;	//-0.007f;

	mForAccSpeed		= 0.003f;	//0.0025f;		//0.005f;	//0.0025f
	mTurnAccSpeed		= 5.0f;
	mTransAccSpeed		= 0.01f;			//0.0005f;

	mForProportion		= 5.0f;	
	mTurnProportion		= 1.0f;	//13.2f;		
	mTransProportion	= 3.2f;		//26.0f;

	mForSpeed			= 0.0f;
	mTurnSpeed			= 0.0f;
	mTransSpeed			= 0.0f;

	mGotoDistEPS[GotoEps_Rough]		= 1.0f;
	mGotoDistEPS[GotoEps_Medium]	= 0.5f;
	mGotoDistEPS[GotoEps_Accurate]	= 0.1f;

	mGotoAngEPS[GotoEps_Rough]		= 10.0f;
	mGotoAngEPS[GotoEps_Medium]		= 5.0f;
	mGotoAngEPS[GotoEps_Accurate]	= 2.0f;

	mDistEps = GotoEps_Accurate;
	mAngEps  = GotoEps_Accurate;

	mOverFlowToTarFor = 0.1f;		//wait to be tested
	mOverFlowToTarTurn = 1.2f;		//wait to be tested		
	mOverFlowToTarTrans = 0.1f;		//wait to be tested
}
MotionGoto::~MotionGoto()
{

}

void MotionGoto::InitGoto()
{
	ReadConf rC( mWorldModel->GetAgentConfPath() ); 
	Predicate tempP;

	rC.Tranversal( "Test_Goto_VecAndAng", tempP );
	tempP.GetValue( "Test_Goto_VecAndAng", mGotoTestVecAndAng );

	rC.Tranversal( "Test_Goto_Vector3f", tempP );
	tempP.GetValue( "Test_Goto_Vector3f", mGotoTestVector3f );

	rC.Tranversal( "Test_Goto_Angle", tempP );
	tempP.GetValue( "Test_Goto_Angle", mGotoTestAngle );
}

Angle MotionGoto::AngleLiminit( Angle ang )
{
	// Limit Angle From -180.0f to 180.0f
	while( ang > 180.0f )
	{
		ang -= 360.0f;
	}
	while( ang < -180.0f )
	{
		ang += 360.0f;
	}

	// Limit Angle From -90.0f to 90.0f

	if( ang > 90.0f )
	{
		ang -= 180.0f;
	}

	if( ang < -90.0f )
	{
		ang += 180.0f;
	}
	
	// Limit Angle From -45.0f to 45.0f
	if( ang > 45.0f )
	{
		ang -= 90.0f;
	}

	if( ang < -45.0f )
	{
		ang += 90.0f;
	}

	return ang;
}

Angle MotionGoto::AngleLimit90( Angle ang )
{
	// Limit Angle From -180.0f to 180.0f
	while( ang > 180.0f )
	{
		ang -= 360.0f;
	}
	while( ang < -180.0f )
	{
		ang += 360.0f;
	}

	// Limit Angle From -90.0f to 90.0f
	// 为防止角度突变导致的摇摆，此处做了修正
	// 即只有“很背对”目标点的时候，才会采用后退式走法

	if( ang > 120.0f )
	{
		ang -= 180.0f;
	}

	if( ang < -120.0f )
	{
		ang += 180.0f;
	}

	return ang;
}

Angle MotionGoto::AngleLimit45( Angle ang )
{
	// Limit Angle From -180.0f to 180.0f
	while( ang > 180.0f )
	{
		ang -= 360.0f;
	}
	while( ang < -180.0f )
	{
		ang += 360.0f;
	}

	// Limit Angle From -90.0f to 90.0f

	if( ang > 90.0f )
	{
		ang -= 180.0f;
	}

	if( ang < -90.0f )
	{
		ang += 180.0f;
	}

	// Limit Angle From -45.0f to 45.0f

	if( ang > 45.0f )
	{
		ang -= 90.0f;
	}
	
	if( ang < -45.0f )
	{
		ang += 90.0f;
	}

	return ang;
}



bool MotionGoto::Goto()
{
	//static unsigned int mGotoCycle = mWorldModel->mCurrentSimCycle;

	if( mGotoTestVecAndAng )
	{
		return Goto( mGotoTestVector3f, mGotoTestAngle );
	}
	else
	{
		//return Goto( mGotoTestAngle );
		return Goto( mGotoTestVector3f );
	}
}

bool MotionGoto::Goto( Vector3f targetVector )
{
	Vector3f tarPos = GetRidOfObstacle( targetVector );

	float distToTarget = DistToVector3f( tarPos );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );
	float angleToTarVector = Normalize( (tarPos - mWorldModel->mSelf.mPos).angTheta() );
	float angleEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(tarPos) );
		  
	//GotoLog<< "my position " << mWorldModel->mSelf.mPos.x << " " << mWorldModel->mSelf.mPos.y << endl;
	//GotoLog<< "target pos  " << targetVector.x << " " << targetVector.y << endl;
	//GotoLog<< "distToTarget " << distToTarget << endl;
	//cout<< " AngEpsFromDist " << AngEpsFromDist(targetVector) 
	//	<< " distToTarget " << distToTarget 
	//	<< endl;
	distEps = 0.03f;

	if( distToTarget <= distEps )
	{
		if( fabs(GetTransSpeed()) > EPS )
		{
			TransSpeedLimit( mTransSpeed * 0.95f );

			mAct->CrazyTrans( mTransSpeed );

			return false;
		}
		else if( fabs(GetTurnSpeed()) > EPS )
		{
			TurnSpeedLimit( 0.0f );

			mAct->CrazyTurn( mTurnSpeed );

			return false;
		}
		else
		{
			ForSpeedLimit( 0.0f );
			TurnSpeedLimit( 0.0f );
			TransSpeedLimit( 0.0f );

			GotoLog << "Goto( Vector3f targetVector )" << " -- In Position " << endl;

			mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

			return true;
		}	
	}
	else
	{
		if( fabs(mTransSpeed) > mTransAccSpeed / 10.0f )
		{
			TransSpeedLimit( mTransSpeed * 0.95f );

			mAct->CrazyTrans( mTransSpeed );

			return false;
		}
		else if( fabs(mTransSpeed) > EPS ) 
		{
			GotoLog << "Goto Slow Trans " << endl;

			TransSpeedLimit( 0.0f );

			mAct->CrazyTrans( mTransSpeed );
		}
		else if( fabs(AngToTarAngle(angleToTarVector) ) > angleEps * 2.0f 
			&& fabs(fabs(AngToTarAngle(angleToTarVector)) - 180.0f) > angleEps * 2.0f 
			)
		{
			GotoLog << "Goto Turn " << endl;

			//**********************************
			// 为了能倒退走路
			//**********************************
			Angle tempAngle;

			if( AngToTarAngle(angleToTarVector) > 90.0f )
			{
				tempAngle = angleToTarVector - 180.0f;
			}
			else if( AngToTarAngle(angleToTarVector) < -90.0f )
			{
				tempAngle = angleToTarVector + 180.0f;
			}
			else
			{
				tempAngle = angleToTarVector;
			}

			GotoLog	<< angleToTarVector << " " << AngToTarAngle(angleToTarVector) << " " << angleToTarVector << " " << tempAngle << endl;

			Turn( tempAngle );
		}
		else
		{
			float tempSpeed = sqrt( 2 * fabs(distToTarget)/ (mForAccSpeed * mForProportion) ) * mForAccSpeed;
			
			//TurnSpeedLimit( 0.0f );
			//TransSpeedLimit( 0.0f );
			
			if( fabs(mTurnSpeed) > mTurnAccSpeed || fabs(mTransSpeed) > mTransAccSpeed )
			{
				GotoLog <<"Goto Slow Turn and Trans " << endl;
	
				SlowDownSpeedToStand();
			}
			else if( fabs(mTurnSpeed) > EPS || fabs(mTransSpeed) > EPS )
			{
				GotoLog <<"Goto Clear speed " << endl;

				ClearSpeed();

				mAct->Stand();
			}
			else
			{
				GotoLog<< "Goto Walk" << endl;
				
				if( fabs(AngToTarAngle(angleToTarVector) ) < 90.0f )
				{
					ForSpeedLimit( tempSpeed );
				}
				else
				{
					ForSpeedLimit( -tempSpeed );
				}

				mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
			}
		}
	}

	return false;
}

bool MotionGoto::FastGoto( Vector3f targetVector )
{
	if( fabs( GetTransSpeed() ) > mTransAccSpeed / 10.0f )
	{
		TransSpeedLimit( mTransSpeed * 0.95f );

		mAct->CrazyTrans( mTransSpeed );

		return false;
	}
	else if( fabs( GetTransSpeed() ) > EPS )
	{
		ClearSpeed();

		mAct->Stand();

		return false;	
	}
	else if( fabs( GetTurnSpeed() ) > EPS )
	{
		TurnSpeedLimit( 0.0f );

		mAct->CrazyTurn( mTurnSpeed );

		return false;
	}

	const float unitForAccSpeed = 0.0031f;

	if( mForSpeed < mForAccSpeed * 2.0f )
	{
		SetForAccSpeed( unitForAccSpeed * 1.5f );
	}

	if( mForSpeed < mForMaxSpeed )
	{
		ForSpeedLimit( mForMaxSpeed);
	}

	mAct->Walk( mForSpeed, 0.0f, 0.0f );

	SetForAccSpeed( unitForAccSpeed );

	return true;
}

bool MotionGoto::FastGotoDribble( Vector3f targetVector )
{
	Vector3f vectorToDribble = mWorldModel->mBall.mPos - ( targetVector - mWorldModel->mBall.mPos ).normalize( 0.22f );
	
	float distToTar = mWorldModel->mSelf.DistXyTo( vectorToDribble);
	float angleToTar = Normalize( mWorldModel->mBodyAngle - (vectorToDribble - mWorldModel->mSelf.mPos).angTheta() );
	float xDistToTar = -distToTar * cos( angleToTar * PI / 180.0f );
	float yDistToTar = distToTar * sin( angleToTar * PI / 180.0f );
	float distToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

	const float miniTransDist = 0.0025f;
	const float bodyRadius = 0.8f;

	GotoLog << " yDistToTar " << yDistToTar << endl;

	if( distToBall > 0.5f )
	{
		FastGoto( targetVector );

		return false;
	}

	if( yDistToTar > 0.0f )
	{
		if( yDistToTar > bodyRadius )
		{
			if( fabs( GetTurnSpeed() ) > EPS )
			{
				TurnSpeedLimit( 0.0f );

				mAct->CrazyTurn( mTurnSpeed );

				return false;
			}
			else if( fabs( GetForSpeed() ) > EPS )
			{
				ForSpeedLimit( 0.0f );

				mAct->Walk( mForSpeed, 0.0f, 0.0f );

				return false;
			}
			else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 3.0f )
			{
				mAct->Stand();
				ClearSpeed();
			}
			else
			{
				//mAct->CrazyTrans( -miniTransDist );
				mAct->SteadyTrans( -0.002f );
				SetTransSpeed( -miniTransDist );
			}

			return false;
		}
		else
		{
			FastGoto( targetVector );
		}
	}
	else /*if( yDistToBall <= 0.0f )*/
	{
		if( yDistToTar < -bodyRadius )
		{
			if( fabs( GetTurnSpeed() ) > EPS )
			{
				TurnSpeedLimit( 0.0f );

				mAct->CrazyTurn( mTurnSpeed );

				return false;
			}
			else if( fabs( GetForSpeed() ) > EPS )
			{
				ForSpeedLimit( 0.0f );

				mAct->Walk( mForSpeed, 0.0f, 0.0f );

				return false;
			}
			else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 3.0f )
			{
				mAct->Stand();
				ClearSpeed();
			}
			else
			{
				//mAct->CrazyTrans( miniTransDist );
				mAct->SteadyTrans( 0.002f );
				SetTransSpeed( miniTransDist );
			}
			return false;
		}
		else
		{
			FastGoto( targetVector );
		}
	}

	return true;
}

bool MotionGoto::Turn( Angle targetAngle )
{
	Angle angToTarget = Normalize( AngToTarAngle( targetAngle ) );

	float temAng;

	if( fabs(angToTarget) > mGotoAngEPS[mAngEps] * 4.0f )
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;

		}
	}
	else
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
	}

	//ForSpeedLimit( fabs(mForSpeed - mForAccSpeed/3.0f) );
	//ForSpeedLimit( 0.0f );
	//TurnSpeedLimit( temAng );
	//TransSpeedLimit( 0.0f );

	if( fabs(mForSpeed) > EPS || fabs(mTransSpeed) > EPS )
	{
		//mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
		//mAct->Walk( mForSpeed, 0.0f, 0.0f );
		GotoLog <<"Turn Slow Trans, turn and for" << endl;
		if( fabs(mTransSpeed) > EPS )
		{
			TransSpeedLimit( 0.0f );
			mAct->CrazyTrans( mTransSpeed );
		}
		else if( fabs( mTurnSpeed) > EPS )
		{
			TurnSpeedLimit( 0.0f );
			mAct->CrazyTurn( mTurnSpeed );
		}
		else
		{
			//if( !mWorldModel->mIsStable )
			//{
			//	SetForSpeed( -mForAccSpeed );
			//}
			//else
			//{
			//	if( mWorldModel->mBodyFaceTo.angPhi() > 7.0f )
			//	{
			//		//ForSpeedLimit( fabs(mForSpeed + mForAccSpeed/3.0f) );
			//		SetForSpeed( mForAccSpeed );
			//	}
			//	else if( mWorldModel->mBodyFaceTo.angPhi() < -7.0f )
			//	{
			//		SetForSpeed( -mForAccSpeed );
			//	}
			//	else
			//	{
			//		ForSpeedLimit( fabs(mForSpeed - mForAccSpeed/3.0f) );
			//	}
			//}
			//ForSpeedLimit( fabs(mForSpeed - mForAccSpeed/3.0f) );
			ForSpeedLimit( 0.0f );

			mAct->Walk( mForSpeed, 0.0f, 0.0f );
		}
	}
	else
	{
			TurnSpeedLimit( temAng );
			GotoLog <<"Turn  CrazyTurn" << endl;

			mAct->CrazyTurn( mTurnSpeed );
	}

	return false;
}

bool MotionGoto::SmartTurnAllowBack( Angle targetAngle )
{
	Angle angToTarget;

	// 防止决策摇摆
	if( fabs( fabs( AngToTarAngle( targetAngle ) ) - 120.0f ) < 5.0f )
	{
		angToTarget = AngToTarAngle( targetAngle );
	}
	else
	{
		angToTarget = AngleLimit90( AngToTarAngle( targetAngle ) );
	}

	float temAng;

	if( fabs(angToTarget) > mGotoAngEPS[mAngEps] * 4.0f )
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;

		}
	}
	else
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
	}
	//cout<< angToTarget << " " << mTurnSpeed << " " << temAng << endl;

	ForSpeedLimit( 0.0f );
	TurnSpeedLimit( temAng );
	TransSpeedLimit( 0.0f );

	if( fabs(mForSpeed) > EPS || fabs(mTransSpeed) > EPS )
	{
		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
	}
	else
	{
		mAct->CrazyTurn( mTurnSpeed );
	}

	return false;
}

bool MotionGoto::SmartTurnAllowTrans( Angle targetAngle )
{
	Angle angToTarget;

	// 防止决策摇摆
	if( fabs( fabs( AngToTarAngle( targetAngle ) ) - 45.0f ) < 5.0f )
	{
		angToTarget = AngToTarAngle( targetAngle );
	}
	else
	{
		angToTarget = AngleLimit45( AngToTarAngle( targetAngle ) );
	}

	float temAng;

	if( fabs(angToTarget) > mGotoAngEPS[mAngEps] * 4.0f )
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed;

		}
	}
	else
	{
		if( angToTarget >= 0.0f )
		{
			temAng = sqrt( 2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
		else
		{
			temAng = -sqrt( -2.0f * angToTarget / (mTurnAccSpeed * mTurnProportion ) ) * mTurnAccSpeed * 0.1f;
		}
	}

	//cout<< angToTarget << " " << mTurnSpeed << " " << temAng << endl;

	ForSpeedLimit( 0.0f );
	TurnSpeedLimit( temAng );
	TransSpeedLimit( 0.0f );

	if( fabs(mForSpeed) > EPS || fabs(mTransSpeed) > EPS )
	{
		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
	}
	else
	{
		mAct->CrazyTurn( mTurnSpeed );
	}


	return false;
}


bool MotionGoto::Goto( Vector3f targetVector,Angle targetAngle )
{
	float distToTarget = DistToVector3f( targetVector );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );
	
	float angleToTarVector = Normalize( (targetVector - mWorldModel->mSelf.mPos).angTheta() );
	float angleToTarVecEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(targetVector) );

	float angleToTarAng = AngToTarAngle( targetAngle );
	float angleToTarAngEps = Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn );
	
	if( distToTarget > distEps )
	{
		Goto( targetVector );

		return false;
	}
	else if( fabs(angleToTarAng) > angleToTarAngEps)
	{
		Turn( targetAngle );
		
		return false;
	}	
	else
	{
		ForSpeedLimit( 0.0f );
		TurnSpeedLimit( 0.0f );
		TransSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

		return true;
	}
}

bool MotionGoto::GotoHandleBall( Vector3f tarVector3f )
{
	const float ballRadiusEps =  mWorldModel->mBallRadius;
	const float bodyRadiusEps = mWorldModel->mBodyRadius * 1.5f;
	const float gotoRadius = 0.17f;
	const float minDistToBall = 0.005f;

	Vector3f tarBeforeAction = mWorldModel->mBall.mPos - ( tarVector3f - mWorldModel->mBall.mPos ).normalize( gotoRadius );
	Vector3f minTarBeforeAction = mWorldModel->mBall.mPos - ( tarVector3f - mWorldModel->mBall.mPos ).normalize( minDistToBall );
	
	//Angle minTarToBallAng = minTarBeforeAction.angTheta2( mWorldModel->mBall.mPos );
	Angle minTarToBallAng = mWorldModel->mBall.mPos.angTheta2( tarVector3f );
	Angle deltaAng = asin( ballRadiusEps / (minDistToBall + ballRadiusEps) ) * 180.0f / PI;

	Angle boundRayAng_Left = minTarToBallAng + deltaAng;
	Angle boundRayAng_Right = minTarToBallAng - deltaAng;
	Ray boundLine_Left = Ray::MakeRayFromPositionAndAngle( minTarBeforeAction, boundRayAng_Left );
	Ray boundLine_Right = Ray::MakeRayFromPositionAndAngle( minTarBeforeAction, boundRayAng_Right );

	Angle minTarToSelfAng = minTarBeforeAction.angTheta2( mWorldModel->mSelf.mPos );

	float selfDistToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );
	float selfDistToTar = mWorldModel->mSelf.DistXyTo( tarBeforeAction );

	if( minTarToSelfAng <= boundRayAng_Left + 40.0f
		&& minTarToSelfAng >= boundRayAng_Right - 40.0f )
	{
		GotoLog << "GotoHandleBall: " << " In Front of Ball: " << minTarToSelfAng << " " << minTarToBallAng << endl;

		if( minTarToSelfAng >= minTarToBallAng )
		{
			Angle deltaAngLeft = boundRayAng_Left + 60.0f;
			Ray deltaRayLeft = Ray::MakeRayFromPositionAndAngle( minTarBeforeAction, deltaAngLeft );
			Vector3f tempPos = deltaRayLeft.GetPoint( (ballRadiusEps + minDistToBall) * 8.0f );
			//Vector3f tempPos = boundLine_Left.GetPoint( (ballRadiusEps + minDistToBall) * 4.0f );

			GotoLog << tempPos.x << " " << tempPos.y << endl;

			return Goto( tempPos );
		}
		else
		{
			Angle deltaAngRight = boundRayAng_Right - 60.0f;
			Ray deltaRayRight = Ray::MakeRayFromPositionAndAngle( minTarBeforeAction, deltaAngRight );
			Vector3f tempPos = deltaRayRight.GetPoint( (ballRadiusEps + minDistToBall) * 8.0f );

			//Vector3f tempPos = boundLine_Right.GetPoint( (ballRadiusEps + minDistToBall) * 4.0f );

			GotoLog << tempPos.x << " " << tempPos.y << endl;

			return Goto( tempPos );
		}
	}
	else
	{
		GotoLog << "GotoHandleBall: " << " Behind " << endl;
		

		if( selfDistToBall < gotoRadius - minDistToBall * 2.0f )
		{
			GotoLog << "GotoHandleBall: " << "Too Near Ball: " << selfDistToBall << " " << gotoRadius - minDistToBall * 2.0f  << endl;
			
			if( selfDistToBall < gotoRadius * 0.4f )
			{
				//腿把球夹住了。通常是由于在球前面摔倒后，起立时导致
				//cout<< "夹球!! " << endl;
				GotoLog << "GotoHandleBall: " << "夹球"<< endl;
				Goto( mWorldModel->mOppGoalCenter );

				return false;
			}
			else if( fabs(GetTurnSpeed()) > EPS || fabs(GetTransSpeed()) > EPS )
			{
				GotoLog << "GotoHandleBall: " << "SlowDownSpeedToStand" << endl;
				
				SlowDownSpeedToStand();
			}
			else if( GetForSpeed() > EPS )
			{
				GotoLog << "GotoHandleBall: " << "ForSpeedLimit" << endl;
				
				ForSpeedLimit( 0.0f );
				mAct->Walk( GetForSpeed(), 0.0f, 0.0f );
			}
			else
			{	
				GotoLog << "GotoHandleBall: " << "Backward" << endl;

				float angleToTarVector = Normalize( (tarVector3f - mWorldModel->mSelf.mPos).angTheta() );

				if( fabs(AngToTarAngle(angleToTarVector) ) < 90.0f )
				{
					mAct->Walk( -0.005f, 0.0f, 0.0f );
					SetForSpeed( -0.005f );
				}
				else
				{
					mAct->Walk( 0.005f, 0.0f, 0.0f );
					SetForSpeed( 0.005f );
				}	
			}		

			return false;
		}
		else
		{
			if( selfDistToTar > bodyRadiusEps )
			{
				GotoLog << "GotoHandleBall: " << "Too Far: " << selfDistToTar << " " << bodyRadiusEps << endl;
				
				Goto( tarBeforeAction );
			}
			else
			{
				if( fabs( mWorldModel->mBodyAngle - minTarToBallAng ) > 5.0f 
					&& fabs(fabs( mWorldModel->mBodyAngle - minTarToBallAng ) - 180.0f ) > 5.0f 
					)
				{
					GotoLog << "GotoHandleBall: " << "Diff Angle: " << mWorldModel->mBodyAngle << " " << minTarToBallAng << endl;
	
					Angle tempAngle;

					if( Normalize(minTarToBallAng) > 90.0f )
					{
						tempAngle = Normalize(minTarToBallAng) - 180.0f;
					}
					else if( Normalize(minTarToBallAng) < -90.0f )
					{
						tempAngle = Normalize(minTarToBallAng) + 180.0f;
					}
					else
					{
						tempAngle = Normalize(minTarToBallAng);
					}

					Turn( tempAngle );
				}
				else
				{	
					float distToTempTar = mWorldModel->mSelf.DistXyTo( tarBeforeAction );
					Angle angleToTempTar = Normalize( mWorldModel->mBodyAngle - (tarBeforeAction - mWorldModel->mSelf.mPos ).angTheta() );

					float xDistToTempTar = -distToTempTar * cos( angleToTempTar * PI / 180.0f );
					float yDistToTempTar = distToTempTar * sin( angleToTempTar * PI / 180.0f );
					
					if( xDistToTempTar < -0.05f )
					{
						if( fabs(GetTurnSpeed()) > EPS
							|| fabs(GetTransSpeed()) > EPS
							)
						{
							SlowDownSpeedToStand();
						}
						else
						{
							ForSpeedLimit( mForMaxSpeed * 0.5f );
							mAct->Walk( mForSpeed, 0.0f, 0.0f );
							//mAct->Walk( mForAccSpeed * 2.0f, 0.0f, 0.0f );
						}
					}
					else if( xDistToTempTar > 0.05f )
					{
						if( fabs(GetTurnSpeed()) > EPS
							|| fabs(GetTransSpeed()) > EPS
							)
						{
							SlowDownSpeedToStand();
						}
						else
						{
							ForSpeedLimit( mForMinSpeed * 0.5f );
							mAct->Walk( mForSpeed, 0.0f, 0.0f );
							//mAct->Walk( mForAccSpeed * 2.0f, 0.0f, 0.0f );
						}
					}
					else if( yDistToTempTar > 0.0f )
					{
						if( fabs(GetTurnSpeed()) > EPS
							|| fabs(GetForSpeed()) > EPS
							)
						{
							SlowDownSpeedToStand();
						}
						else
						{
							//mAct->CrazyTrans( 0.0015f );
							mAct->SteadyTrans( 0.002f );
						}
					}
					else if( yDistToTempTar < 0.0f )
					{
						if( fabs(GetTurnSpeed()) > EPS
							|| fabs(GetForSpeed()) > EPS
							)
						{
							SlowDownSpeedToStand();
						}
						else
						{
							//mAct->CrazyTrans( -0.0015f );
							mAct->SteadyTrans( -0.002f );
						}
					}
					else
					{
						mAct->Stand();
					}
					
				}
			}

			return true;
		}
	}
	
	return false;
	//Vector3f tarPos = tarVector3f;

	//const float bodyRadius = mWorldModel->mBodyRadius;	
	////const float ballRadius = mWorldModel->mBallRadius;
	////const float gotoRadius = 0.2f;
	////const float gotoRadius = 0.17;
	//const float shootAreaDist = 0.02f;

	//Vector3f tarDribbleTo = mWorldModel->mBall.mPos - ( tarVector3f - mWorldModel->mBall.mPos ).normalize( gotoRadius );
	//Angle angDribbleTo = (tarPos - mWorldModel->mBall.mPos).angTheta();

	//float distBodyToBall = mWorldModel->mBall.DistXyTo( mWorldModel->mSelf.mPos );
	//float distBodyToTar = mWorldModel->mSelf.DistXyTo( tarDribbleTo );
	//float distTarToBall  = mWorldModel->mBall.DistXyTo( tarDribbleTo );

	//Line lineBodyToTar = Line::makeLineFromTwoPoints( mWorldModel->mSelf.mPos, mWorldModel->mBall.mPos );
	//float lineDistToBall = lineBodyToTar.getDistanceWithPoint( mWorldModel->mBall.mPos );

	//Angle tempAng;

	//static bool isGotoInPosition = false;
	//// 如果距离球比较远，则直接冲过去
	//if( distBodyToTar > gotoRadius + shootAreaDist )
	////if( distBodyToBall > gotoRadius + shootAreaDist )
	//{
	//	if( isGotoInPosition )
	//	{
	//		GotoLog << "Goto In Position"<< " -- Goto Ball" << endl;

	//		//Goto( mWorldModel->mBall.mPos );
	//		isGotoInPosition = Goto( tarDribbleTo );

	//		//Goto( tarPos );

	//		return false;
	//	}
	//	else
	//	{
	//		GotoLog << "Goto 距离球比较远 " << endl;

	//		isGotoInPosition = Goto( tarDribbleTo );
	//		//isGotoInPosition = Goto( tarPos );

	//		return false;	
	//	}		
	//}
	//
	//isGotoInPosition = false;	

	//// 如果距离球过近，则应该考虑后退
	//if( distBodyToBall < gotoRadius - shootAreaDist * 2.0f )
	//{
	//	if( distBodyToBall < gotoRadius * 0.3f )
	//	{
	//		//腿把球夹住了。通常是由于在球前面摔倒后，起立时导致
	//		//cout<< "夹球!! " << endl;
	//		GotoLog << "夹球!! " << endl;
	//		Goto( mWorldModel->mOppGoalCenter );

	//		return false;
	//	}
	//	else if( fabs(GetTurnSpeed()) > EPS || fabs(GetTransSpeed()) > EPS )
	//	{
	//		GotoLog << "SlowDownSpeedToStand" << endl;
	//		SlowDownSpeedToStand();
	//	}
	//	else if( GetForSpeed() > EPS )
	//	{
	//		GotoLog << "ForSpeedLimit" << endl;
	//		ForSpeedLimit( 0.0f );
	//		mAct->Walk( GetForSpeed(), 0.0f, 0.0f );
	//	}
	//	else
	//	{
	//		GotoLog << "Backward" << endl;
	//		mAct->Walk( -0.005f, 0.0f, 0.0f );
	//		SetForSpeed( -0.005f );
	//	}		

	//	return false;
	//}
	//else
	//{
	//	// 距离刚刚好的时候，判断是否面对球
	//	//		没有面对球，就转身去面对球
	//	Angle ballToSelf = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mSelf.mPos );
	//	Angle ballToOppGoal = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOppGoalCenter );

	//	if( fabs(ballToSelf - ballToOppGoal) > 90.0f )
	//	//if( mWorldModel->mSelf.mPos.x < mWorldModel->mBall.mPos.x )
	//	{
	//		if( fabs(mWorldModel->mBodyAngle - angDribbleTo) > 5.0f )
	//		{
	//			GotoLog << "turn 1" << endl;

	//			//Turn( mWorldModel->mSelf.ThetaTo( tarDribbleTo ) );
	//			Turn( angDribbleTo );

	//			return false;
	//		}
	//	}
	//	else if( !FacingTheBall() )
	//	{
	//		if( fabs(GetForSpeed()) > EPS
	//			|| fabs(GetTransSpeed()) > EPS
	//			)
	//		{
	//			GotoLog << "turn slow down" << endl;

	//			SlowDownSpeedToStand();

	//			return false;
	//		}
	//		else
	//		{
	//			GotoLog << "turn 2" << endl;

	//			Turn( mWorldModel->mSelf.ThetaTo( mWorldModel->mBall.mPos) );

	//			return false;
	//		}
	//	}
	//}
	//

	//Angle relaAngle = Normalize( mWorldModel->mSelf.ThetaTo( tarPos ) - mWorldModel->mBodyAngle );


	//float distToTar = ( mWorldModel->mSelf.DistXyTo( tarPos ) );
	//float angleToTar = Normalize( mWorldModel->mBodyAngle - (tarPos - mWorldModel->mSelf.mPos).angTheta() );
	//float xDistToBall = -distToTar * cos( angleToTar * PI / 180.0f );
	//float yDistToBall = distToTar * sin( angleToTar * PI / 180.0f );

	//// 面对球的时候，考虑是否需要绕球转
	//if( relaAngle < 0.0f )
	////if( yDistToBall < 0.0f )
	//{
	//	//if( GetTurnSpeed() > EPS || GetTransSpeed() > EPS )
	//	//{
	//	//	GotoLog << "trans slow down" << endl;

	//	//	if( GetTurnSpeed() > EPS )
	//	//	{
	//	//		TurnSpeedLimit( 0.0f );
	//	//		mAct->CrazyTurn( GetTurnSpeed() );
	//	//	}
	//	//	else
	//	//	{
	//	//		TransSpeedLimit( 0.0f );
	//	//		mAct->CrazyTrans( GetTransSpeed() );
	//	//	}
	//	//}
	//	//else 
	//	if( fabs( GetForSpeed() ) > EPS )
	//	{
	//		ForSpeedLimit( 0.0f );
	//		mAct->Walk( GetForSpeed(), 0.0f, 0.0f );
	//	}
	//	else
	//	{
	//		//if( !mWorldModel->mIsStable )
	//		//{
	//		//	mAct->Stand();
	//		//	ClearSpeed();
	//		//}
	//		//else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 3.0f )
	//		//{
	//		//	mAct->Stand();
	//		//	ClearSpeed();
	//		//}
	//		//else
	//		//{
	//			//if( mWorldModel->mSelf.mPos.x < mWorldModel->mBall.mPos.x )
	//			//{
	//			//	GotoLog << "Left Trans" << endl;

	//			//	mAct->CrazyTrans( -0.002f );
	//			//	
	//			//	SetTransSpeed( -0.002f );
	//			//}
	//			//else
	//			//{
	//				GotoLog << "LeftTurnAroundBall" << endl;

	//				mAct->LeftTurnAroundBall();
	//				SetTurnSpeed( -1.5f );
	//				SetTransSpeed( -0.002f );
	//			//}
	//		//}
	//	}	
	//}
	//else
	//{
	//	//if( GetTurnSpeed() < -EPS || GetTransSpeed() < -EPS )
	//	//{
	//	//	GotoLog << "trans slow down" << endl;

	//	//	if( GetTurnSpeed() < -EPS )
	//	//	{
	//	//		TurnSpeedLimit( 0.0f );
	//	//		mAct->CrazyTurn( GetTurnSpeed() );
	//	//	}
	//	//	else
	//	//	{
	//	//		TransSpeedLimit( 0.0f );
	//	//		mAct->CrazyTrans(GetTransSpeed() );
	//	//	}
	//	//	//mAct->Stand();
	//	//	//mGoto->ClearSpeed();
	//	//	//mGoto->SlowDownSpeedToStand();
	//	//}
	//	//else 
	//	if( fabs(GetForSpeed()) > EPS )
	//	{
	//		ForSpeedLimit( 0.0f );
	//		mAct->Walk( GetForSpeed(), 0.0f, 0.0f );
	//	}
	//	else
	//	{
	//		/*if( !mWorldModel->mIsStable )
	//		{
	//			mAct->Stand();
	//			ClearSpeed();
	//		}
	//		else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 3.0f )
	//		{
	//			mAct->Stand();
	//			ClearSpeed();
	//		}*/
	//		//else
	//		//{
	//			//if( mWorldModel->mSelf.mPos.x < mWorldModel->mBall.mPos.x )
	//			//{
	//			//	GotoLog << "Right Trans" << endl;

	//			//	mAct->CrazyTrans( 0.002f );

	//			//	SetTransSpeed( 0.002f );
	//			//}
	//			//else
	//			//{
	//				GotoLog << "LeftTurnAroundBall" << endl;

	//				mAct->RightTurnAroundBall();
	//				SetTurnSpeed( 1.5f );
	//				SetTransSpeed( 0.002f );
	//			//}		
	//		//}
	//	}
	//}	

	//return true;
}

bool MotionGoto::FacingTheBall()
{
	//float distToTar = mWorldModel->mSelf.DistXyTo(mWorldModel->mBall.mPos);
	//Angle angToBall = ( mWorldModel->mBall.mPos - mWorldModel->mSelf.mPos ).angTheta() - mWorldModel->mBodyAngle;
	//Angle angEps = 10.0f;

	//if( fabs(angToBall) > angEps )
	//{
	//	return false;
	//}

	//return true;
	return FacingTarget( mWorldModel->mBall.mPos );
}

bool MotionGoto::FacingTarget( Vector3f targetVector )
{
	float distToTar = mWorldModel->mSelf.DistXyTo( targetVector );
	Angle angToTarget = ( targetVector - mWorldModel->mSelf.mPos ).angTheta() - mWorldModel->mBodyAngle;
	Angle angEps = 5.0f;

	if( fabs(angToTarget) > angEps
		&& fabs(fabs(angToTarget) -180.0f ) > angEps
		)
	{
		return false;
	}

	return true;
}

bool MotionGoto::SmartGotoAllowBack( Vector3f targetVector )
{
	float distToTarget = DistToVector3f( targetVector );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );
	float angleToTarVector = AngleLimit90( Normalize( (targetVector - mWorldModel->mSelf.mPos).angTheta() ) );
	float angleEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(targetVector) );

	if( distToTarget <= distEps )
	{
		ForSpeedLimit( 0.0f );
		TurnSpeedLimit( 0.0f );
		TransSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

		return true;
	}
	else
	{
		if( fabs(mTransSpeed) > EPS ) 
		{
			TransSpeedLimit( 0.0f );

			mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
		}
		else 
			if( fabs(AngToTarAngle(angleToTarVector) ) > angleEps 
			&& fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) > angleEps
			)
		{
			SmartTurnAllowBack( angleToTarVector );
		}
		else
		{
			float tempSpeed = sqrt( 2 * fabs(distToTarget)/ (mForAccSpeed * mForProportion) ) * mForAccSpeed;

			if( fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) < angleEps )
			{
				tempSpeed = -tempSpeed;
			}

			ForSpeedLimit( tempSpeed );
			TurnSpeedLimit( 0.0f );
			TransSpeedLimit( 0.0f );

			mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
		}
	}

	return false;
}

bool MotionGoto::SmartGotoAllowBack( Vector3f targetVector, Angle targetAngle )
{
	float distToTarget = DistToVector3f( targetVector );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );

	float angleToTarVector = AngleLimit90( Normalize( (targetVector - mWorldModel->mSelf.mPos).angTheta() ) );
	float angleToTarVecEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(targetVector) );

	float angleToTarAng = AngToTarAngle( targetAngle );
	float angleToTarAngEps = Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn );

	if( distToTarget > distEps )
	{
		Goto( targetVector );

		return false;
	}
	else if( fabs(angleToTarAng) > angleToTarAngEps
		&& fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) > angleToTarAngEps )
	{
		SmartTurnAllowBack( targetAngle );

		return false;
	}	
	else
	{
		ForSpeedLimit( 0.0f );
		TurnSpeedLimit( 0.0f );
		TransSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

		return true;
	}
}

bool MotionGoto::SmartGotoAllowTrans( Vector3f targetVector )
{
	float distToTarget = DistToVector3f( targetVector );
	float distEps = Max( mGotoDistEPS[mDistEps], mOverFlowToTarFor );
	float angleToTarVector = AngleLimit45( Normalize( (targetVector - mWorldModel->mSelf.mPos).angTheta() ) );
	float angleEps = Max( Max( mGotoAngEPS[mAngEps], mOverFlowToTarTurn ), AngEpsFromDist(targetVector) );

	if( distToTarget <= distEps )
	{
		ForSpeedLimit( 0.0f );
		TurnSpeedLimit( 0.0f );
		TransSpeedLimit( 0.0f );

		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

		return true;
	}
	else
	{
		if( fabs(AngToTarAngle(angleToTarVector) ) > angleEps 
			&& fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) > angleEps
			&& fabs( fabs(AngToTarAngle(angleToTarVector)) - 90.0f ) > angleEps * 2.0f
			)
		{
			if( fabs( mTransSpeed) > EPS )
			{
				TransSpeedLimit( 0.0f );

				mAct->CrazyTrans( mTransSpeed );
				
				return false;
			}
			else
			{
				//cout<< "SmartTurnAllowTrans" << endl;
				SmartTurnAllowTrans( angleToTarVector );

				return false;
			}
		}
		else
		{
			if( fabs( fabs(AngToTarAngle(angleToTarVector)) - 90.0f ) < 10.0f )
			{
				if( fabs( mTurnSpeed ) > EPS || fabs( mForSpeed) > EPS )
				{
					ForSpeedLimit( 0.0f );
					TurnSpeedLimit( 0.0f );
					TransSpeedLimit( 0.0f );

					mAct->Walk( mForSpeed, mTurnSpeed, 0.0f );

					return false;
				}
				else
				{
					float tempSpeed = sqrt( 2 * fabs(distToTarget)/ (mTransAccSpeed * mTransProportion) ) * mTransAccSpeed;

					ForSpeedLimit( 0.0f );
					TurnSpeedLimit( 0.0f );
					TransSpeedLimit( tempSpeed );

					//cout<< " Trans " << mTransSpeed << endl;	

					mAct->CrazyTrans( mTransSpeed );

					return false;
				}
			}
			else
			{
				if( fabs( mTurnSpeed ) > EPS || fabs( mTransSpeed) > EPS )
				{
					ForSpeedLimit( 0.0f );
					TurnSpeedLimit( 0.0f );
					TransSpeedLimit( 0.0f );

					mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

					return false;
				}
				else
				{
					float tempSpeed = sqrt( 2 * fabs(distToTarget)/ (mForAccSpeed * mForProportion) ) * mForAccSpeed;

					if( fabs( fabs(AngToTarAngle(angleToTarVector)) - 180.0f ) < angleEps )
					{
						tempSpeed = -tempSpeed;
					}

					ForSpeedLimit( tempSpeed );
					TurnSpeedLimit( 0.0f );
					TransSpeedLimit( 0.0f );

					mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );

					return false;
				}	
			}	
		}
	}

	return false;
}

bool MotionGoto::SmartGotoAllowTrans( Vector3f targetVector, Angle targetAngle )
{

}

bool MotionGoto::TurnAroundBall( bool leftTurn )
{
	if( !SlowDownSpeedToStand() )
	{
		return false;
	}
	else if( leftTurn )
	{
		mAct->LeftTurnAroundBall();
	}
	else 
	{
		mAct->RightTurnAroundBall();
	}

	return true;
}

bool MotionGoto::Trans( float distToTrans )
{
	float tempSpeed = - sqrt( 2 * fabs(distToTrans)/ (mTransAccSpeed * mTransProportion) ) * mTransAccSpeed;

	if( distToTrans < 0.0f )
	{
		tempSpeed = -tempSpeed;
	}

	ForSpeedLimit( 0.0f );
	TurnSpeedLimit( 0.0f );
	TransSpeedLimit( tempSpeed );

	if( fabs(mForSpeed) > EPS || fabs(mTurnSpeed) > EPS )
	{
		mAct->Walk( mForSpeed, mTurnSpeed, mTransSpeed );
	}
	else
	{
		mAct->CrazyTrans( mTransSpeed );
	}
}

bool MotionGoto::SlowDownSpeedToStand()
{
	if( fabs(mTransSpeed) > mTransAccSpeed / 10.0f )
	{
		TransSpeedLimit( mTransSpeed * 0.95f );

		mAct->CrazyTrans( mTransSpeed );

		return false;
	}
	else if( fabs(mTransSpeed) > EPS )
	{
		ClearSpeed();

		mAct->Stand();

		return false;	
	}
	else if( fabs(mForSpeed) > mForAccSpeed  )
	{		
		ForSpeedLimit( mForSpeed * 0.5f);

		mAct->Walk( mForSpeed, 0.0f, 0.0f );

		return false;
	}
	else if( fabs(mForSpeed) > EPS )
	{
		ClearSpeed();

		mAct->Stand();

		return false;
	}
	else if( fabs( mTurnSpeed) > mTurnAccSpeed )
	{
		TurnSpeedLimit( 0.0f );

		mAct->CrazyTurn( mTurnSpeed );

		return false;
	}
	else if( fabs(mTurnSpeed) > EPS )
	{
		ClearSpeed();

		mAct->Stand();

		return false;
	}
	else
	{
		ClearSpeed();

		mAct->Stand();
		
		return true;
	}
}


void MotionGoto::SetGotoEps( GotoEps distEps, GotoEps angEps )
{
	mDistEps = distEps;
	mAngEps  = angEps;
}

float MotionGoto::DistToVector3f( Vector3f targetVector )
{
	return mWorldModel->mSelf.DistXyTo( targetVector );
}

Angle MotionGoto::AngToTarAngle( Angle targetAngle )
{
	return targetAngle - mWorldModel->mBodyAngle;
}

Angle MotionGoto::AngEpsFromDist( Vector3f targetVector )
{
	const float lateralDistEps = mWorldModel->mBallRadius;
	const float distToTar = DistToVector3f( targetVector );

	return (float)asin( (double)lateralDistEps / (double)distToTar ) * 180.0f / PI * 0.9f;
}

bool MotionGoto::InEps( Vector3f targetVector,Angle targetAngle )
{
	return ( DistInEps( targetVector ) && AngInEps( targetAngle ) );
}

bool MotionGoto::DistInEps( Vector3f targetVector )
{
	float distToTarget = DistToVector3f( targetVector );

	if( distToTarget <= mGotoDistEPS[mDistEps] )
	{
		GotoLog << "[EPS] " << "Dist to Target In Eps" << endl;

		return true;
	}
	else
	{
		GotoLog << "[EPS] " << "Dist to Target Not In Eps" << endl;

		return false;
	}
}

bool MotionGoto::AngInEps( Angle targetAngle )
{
	Angle angToTarget = AngToTarAngle( targetAngle );

	if( fabs( angToTarget ) <= mGotoAngEPS[mAngEps] )
	{
		GotoLog << "[EPS] " << "Angle to Target In Eps" << endl;

		return true;
	}
	else
	{
		GotoLog << "[EPS] " << "Angle to Target Not In Eps" << endl;

		return false;
	}
}

float MotionGoto::ForSpeed()
{
	return mForSpeed;
}

float MotionGoto::TurnSpeed()
{
	return mTurnSpeed;
}

float MotionGoto::TranSpeed()
{
	return mTransSpeed;
}

void MotionGoto::ForSpeedLimit( float forSpeed )
{
	if( forSpeed >= 0.0f )
	{
		float unitForAccSpeed = mForAccSpeed;

		if( fabs(mForSpeed) <= mForAccSpeed * 5.0f )
		{
			unitForAccSpeed *= 1.5f;
		}

		if( forSpeed > mForSpeed + mForAccSpeed )
		{
			mForSpeed += unitForAccSpeed;
		}
		else if ( forSpeed < mForSpeed - mForAccSpeed )
		{
			if( fabs(mForSpeed) <= mForAccSpeed * 3.0f )
			{
				mForSpeed -= mForAccSpeed * 0.8f;
			}
			else if( fabs(mForSpeed) <= mForAccSpeed )
			{
				mForSpeed -= mForAccSpeed * 1.0f;
			}
			else
			{
				mForSpeed -= mForAccSpeed * 0.25f;
			}
		}
		else
		{
			mForSpeed = forSpeed;
		}
	}
	else
	{
		if( forSpeed > mForSpeed + mForAccSpeed )
		{
			mForSpeed += mForAccSpeed * 0.9f;
		}
		else if( forSpeed < mForSpeed - mForAccSpeed )
		{
			mForSpeed -= mForAccSpeed;
		}
	}
	
	SpeedLimit( );
}

void MotionGoto::TurnSpeedLimit( float turnAng )
{
	if ( turnAng > mTurnSpeed + mTurnAccSpeed )
	{
		mTurnSpeed += mTurnAccSpeed;
	}
	else if( turnAng < mTurnSpeed - mTurnAccSpeed )
	{
		mTurnSpeed -= mTurnAccSpeed; 
	}
	else  
	{
		mTurnSpeed = turnAng;
	}

	SpeedLimit( );
}

void MotionGoto::TransSpeedLimit( float tranSpeed )
{
	if( tranSpeed > mTransSpeed + mTransAccSpeed )
	{
		mTransSpeed += mTransAccSpeed;
	}
	else if( tranSpeed < mTransSpeed - mTransAccSpeed )
	{
		mTransSpeed -= mTransAccSpeed * 0.5f;
	}
	else
	{
		mTransSpeed = tranSpeed;
	}

	SpeedLimit( );
}
void MotionGoto::SpeedLimit()
{
	if( mForSpeed > mForMaxSpeed )
	{
		mForSpeed = mForMaxSpeed;
	}
	else if( mForSpeed < mForMinSpeed )
	{
		mForSpeed = mForMinSpeed;
	}
	if ( mTurnSpeed > mTurnMaxSpeed )
	{
		mTurnSpeed = mTurnMaxSpeed;
	}
	else if ( mTurnSpeed < mTurnMinSpeed )
	{
		mTurnSpeed = mTurnMinSpeed;
	}
	if ( mTransSpeed > mTransMaxSpeed )
	{
		mTransSpeed = mTransMaxSpeed;
	}
	else if ( mTransSpeed < mTransMinSpeed )
	{
		mTransSpeed = mTransMinSpeed;
	}
}

void MotionGoto::ClearSpeed()
{
	mForSpeed = 0.0f;
	mTransSpeed = 0.0f;
	mTurnSpeed = 0.0f;
}

float MotionGoto::GetForSpeed()
{
	return mForSpeed;
}

float MotionGoto::GetTurnSpeed()
{
	return mTurnSpeed;
}

float MotionGoto::GetTransSpeed()
{
	return mTransSpeed;
}

void MotionGoto::SetForSpeed( float forSpeed )
{
	mForSpeed = forSpeed;
}

void MotionGoto::SetTurnSpeed( float turnSpeed )
{
	mTurnSpeed = turnSpeed;
}

void MotionGoto::SetTransSpeed( float tranSpeed )
{
	mTransSpeed = tranSpeed;
}

void MotionGoto::SetForAccSpeed( float forAccSpeed )
{
	mForAccSpeed = forAccSpeed;
}

bool MotionGoto::IsObstacle( Vector3f tarVector3f, Vector3f obsVector3f )
{
	const float obstacleRadius = 0.5f;

	Angle selfToTarAng = mWorldModel->mSelf.mPos.angTheta2( tarVector3f );
	Line selfToTarLine = Line::makeLineFromPositionAndAngle( mWorldModel->mSelf.mPos, selfToTarAng );
	
	float obsDistToLine = selfToTarLine.getDistanceWithPoint( obsVector3f );
	float obsDistToTar = obsVector3f.distXY2( tarVector3f );
	float obsDistToSelf = obsVector3f.distXY2( mWorldModel->mSelf.mPos );
	float selfDistToTar = mWorldModel->mSelf.DistXyTo( tarVector3f );

	float selfToObsDist = mWorldModel->mSelf.DistXyTo( obsVector3f );

	float minObsDist = Min( selfToObsDist * 0.8f, obstacleRadius );

	if( obsDistToLine <= obstacleRadius )
	{
		if( obsDistToTar <= selfDistToTar 
			&& obsDistToSelf <= selfDistToTar )
		{
			return true;
		}
	}
	
	return false;
}	

bool MotionGoto::IsOurPlayerObstacle( Vector3f tarVector3f )
{
	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		if( IsObstacle( tarVector3f, mWorldModel->mOurTeamPlayer[i].mPos ) )
		{
			//GotoLog << "IsOurPlayerObstacle " << mWorldModel->mOurTeamPlayer[i].mMyPlayerNo << endl;

			return true;
		}
	}

	return false;
}

bool MotionGoto::IsOppPlayerObstacle( Vector3f tarVector3f )
{
	const float minDist = 1.0f;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		float oppPlayerDistToTar = mWorldModel->mOppTeamPlayer[i].DistXyTo( tarVector3f );
		float oppPlayerDistToSelf = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mSelf.mPos );

		if( oppPlayerDistToTar <= minDist )
		{
			continue;
		}
		else if( oppPlayerDistToSelf <= minDist * 0.8f )
		{
			continue;
		}
		else
		{
			if( IsObstacle( tarVector3f, mWorldModel->mOppTeamPlayer[i].mPos ) )
			{
				//GotoLog << "IsOppPlayerObstacle " << mWorldModel->mOppTeamPlayer[i].mMyPlayerNo << endl;
				
				return true;
			}
		}
	}

	return false;
}

Vector3f MotionGoto::GetRidOfObstacle( Vector3f tarVector3f )
{
	const Angle unitAngle = 3.0f;

	Vector3f resultVector = tarVector3f;
	Vector3f resultVectorLeft = tarVector3f;
	Vector3f resultVectorRight = tarVector3f;

	unsigned int computeTime = 0;
	unsigned int leftComputeTime = 0;
	unsigned int rightComputeTime = 0;

	while( computeTime < 20 )
	{
		float selfDistToTar = mWorldModel->mSelf.DistXyTo( resultVectorLeft );
		Angle selfAngToTar = mWorldModel->mSelf.mPos.angTheta2( resultVectorLeft );

		if( IsOurPlayerObstacle( resultVectorLeft ) 
			|| IsOppPlayerObstacle( resultVectorLeft ) 
			)
		{			
			Angle deltaAng = unitAngle + selfAngToTar;
			Ray deltaRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, deltaAng );
			Vector3f deltaVec = deltaRay.GetPoint( selfDistToTar );

			resultVectorLeft = deltaVec;
		}
		else
		{
			//return resultVector;
			break;
		}

		computeTime ++;
		leftComputeTime ++;
	}

	computeTime = 0;

	while( computeTime < 20 )
	{
		float selfDistToTar = mWorldModel->mSelf.DistXyTo( resultVectorRight );
		Angle selfAngToTar = mWorldModel->mSelf.mPos.angTheta2( resultVectorRight );

		if( IsOurPlayerObstacle( resultVectorRight ) 
			|| IsOppPlayerObstacle( resultVectorRight ) 
			)
		{			
			Angle deltaAng = -unitAngle + selfAngToTar;
			Ray deltaRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, deltaAng );
			Vector3f deltaVec = deltaRay.GetPoint( selfDistToTar );

			resultVectorRight = deltaVec;
		}
		else
		{
			//return resultVector;
			break;
		}

		computeTime ++;
		rightComputeTime ++;
	}

	if( leftComputeTime <= rightComputeTime )
	{
		return resultVectorLeft;
	}
	else
	{
		return resultVectorRight;
	}
}

bool MotionGoto::PowerSpeedBack()
{
	float backAccSpeed = mForAccSpeed;
	static unsigned int time = 0;

	if( time < 30 )
	{
		if( mForSpeed > mForMinSpeed )
		{
			mForSpeed -= mForAccSpeed;
		}
	}
	else
	{
		if( mForSpeed < 0.0f )
		{
			mForSpeed += mForAccSpeed;
		}
	}

	time ++;

	mAct->Walk( mForSpeed, 0.0f, 0.0f );
}

