#include "MotionKick.h"
#define KickLog gLog<< "[moKick] " << "Kick "

MotionKick::MotionKick( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act )
{
	mWorldModel = wm;
	mSituation = situ;
	mGoto = mtGoto;
	mCmdQuene = cmdQuene;
	mAct = act;

	mKickRadius = 0.22f;			// waited to be tested
	mKickAngleEps = 5.0f;		// waited to be tested
}
MotionKick::~MotionKick()
{

}

float MotionKick::GetKickDist()
{
	const float powerKickDist = 5.5f;
	
	return powerKickDist;
}


bool MotionKick::Kick()
{
	Vector3f ultimateTarget = mWorldModel->mOppGoalCenter; 

	KickToTar( ultimateTarget );
}

bool MotionKick::Pass()
{
	Vector3f ultimateTarget = mSituation->PassTo();

	Vector3f passTar = ultimateTarget;
	Vector3f sitPassTar = ultimateTarget;
	static Vector3f lastPassTar = ultimateTarget;

	if( sitPassTar.distXY2( lastPassTar ) < 4.0f )
	{	
		passTar = lastPassTar;
	}
	else
	{
		passTar = sitPassTar;
	}

	lastPassTar = sitPassTar;

	Vector3f tarBeforePass = mWorldModel->mBall.mPos - ( sitPassTar - mWorldModel->mBall.mPos ).normalize( 0.05f );


	if( !InKickArea( passTar ) )
	{	
		KickLog << "!InKickArea" << endl;

		if( InKickAngle( passTar ) && mGoto->FacingTheBall() )
		{
			mGoto->Goto( tarBeforePass );
		}
		else
		{
			GotoKickArea( passTar );
		}
	}
	else
	{
		KickTo( passTar );
	}

	return true;


}


bool MotionKick::KickToTar( Vector3f tarVector3f )
{
	Vector3f ultimateTarget = tarVector3f; 
	Vector3f tarBeforeKick = mWorldModel->mBall.mPos - ( ultimateTarget - mWorldModel->mBall.mPos ).normalize( 0.05f );

	Vector3f kickTar = ultimateTarget;
	Vector3f sitKickTar = ultimateTarget;
	static Vector3f lastKickTar = ultimateTarget;

	sitKickTar = mSituation->KickTo( ultimateTarget, GetKickDist() );

	if( sitKickTar.distXY2( lastKickTar ) < 4.0f )
	{	
		kickTar = lastKickTar;
	}
	else
	{
		kickTar = sitKickTar;
	}

	lastKickTar = sitKickTar;

	if( !InKickArea( kickTar ) )
	{	
		//if( InKickAngle( kickTar ) && mGoto->FacingTheBall() )
		//{
		//	//mGoto->Goto( tarBeforeKick );
		//	GotoKickArea( kickTar );
		//}
		//else
		//{
			//GotoKickArea( kickTar );
			GotoKickArea( kickTar );
		//}
	}
	else
	{
		KickTo( kickTar );
	}

	return true;
}

bool MotionKick::GotoKickArea( Vector3f tarVector3f )
{
	return mGoto->GotoHandleBall( tarVector3f );
}

bool MotionKick::KickTo( Vector3f tarVector3f )
{
	KickLog << "KickTo: " << tarVector3f.x << " " << tarVector3f.y << endl;

	return PowerKick();
}

bool MotionKick::SoftKick()
{

}

bool MotionKick::PowerKick()
{
	KickLog << "PowerKick" << endl;

	float distToBall = ( mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos) );
	float angleToBall = Normalize( mWorldModel->mBodyAngle - (mWorldModel->mBall.mPos - mWorldModel->mSelf.mPos).angTheta() );
	float xDistToBall = -distToBall * cos( angleToBall * PI / 180.0f );
	float yDistToBall = distToBall * sin( angleToBall * PI / 180.0f );

	const float miniTransDist = 0.0015f;

	//if( fabs(mGoto->GetForSpeed()) > EPS 
	//	|| fabs(mGoto->GetTurnSpeed()) > EPS 
	//	//|| fabs(mGoto->GetTransSpeed()) > EPS 
	//	)
	//{
	//	mAct->Stand();
	//	mGoto->ClearSpeed();
	//}
	//else if( !mWorldModel->mIsStable )
	//{
	//	mAct->Stand();
	//	mGoto->ClearSpeed();
	//}
	//else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 3.0f )
	//{
	//	mAct->Stand();
	//	mGoto->ClearSpeed();
	//}
	//else if( xDistToBall > -0.15f )
	//{
	//	mAct->Walk( -0.002f, 0.0f, 0.0f );
	//	mGoto->SetForSpeed( -0.0025f );
	//}
	//else if( xDistToBall < -0.18f )
	//{
	//	mAct->Walk( 0.002f, 0.0f, 0.0f );
	//	mGoto->SetForSpeed( 0.0025f );
	//}
	//else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 0.10f )
	//{
	//	mAct->Stand();
	//	mGoto->ClearSpeed();
	//}
	//else 

	Angle angBodyToBall = mWorldModel->mSelf.mPos.angTheta2( mWorldModel->mBall.mPos );
	Angle diffBodyAngToBall = Normalize( angBodyToBall - mWorldModel->mBodyAngle );

	//cout<< angBodyToBall << " " << diffBodyAngToBall << endl;
	
	if( fabs(diffBodyAngToBall) > 90.0f )
	{
		Angle tempAng;

		if( diffBodyAngToBall > 0.0f )
		{
			tempAng = angBodyToBall + 85.0f;
		}
		else
		{
			tempAng = angBodyToBall - 85.0f;
		}

		mGoto->Turn( tempAng );

		return false;
	}
	/*else if( fabs(diffBodyAngToBall) > 10.0f )
	{
		Angle tempAng = angBodyToBall;

		mGoto->Turn( tempAng );

		return false;
	}*/

	if( xDistToBall > -0.15f )
	{
		if( fabs(mGoto->GetTransSpeed()) > EPS 
			|| fabs(mGoto->GetTurnSpeed()) > EPS
			)
		{
			mGoto->SlowDownSpeedToStand();

			return false;
		}
		else
		{
			mAct->Walk( -0.002f, 0.0f, 0.0f );
			mGoto->SetForSpeed( -0.0025f );
		}
	}
	else if( xDistToBall < -0.18f )
	{
		if( fabs(mGoto->GetTransSpeed()) > EPS 
			|| fabs(mGoto->GetTurnSpeed()) > EPS
			)
		{
			mGoto->SlowDownSpeedToStand();

			return false;
		}
		else
		{
			mAct->Walk( 0.002f, 0.0f, 0.0f );
			mGoto->SetForSpeed( 0.0025f );
		}	
	}
	else if( yDistToBall > 0.0f )
	{
		//if( fabs(mGoto->GetTransSpeed()) > EPS )
		//{
		//	mAct->Stand();
		//	mGoto->ClearSpeed();
		//}
		//else 
		if( yDistToBall < 0.021f )
		{
			if( fabs(mGoto->GetForSpeed()) > EPS 
				|| fabs(mGoto->GetTurnSpeed()) > EPS 
				)
			{
				mGoto->SlowDownSpeedToStand();

				return false;
			}
			else
			{
				//mAct->CrazyTrans( -miniTransDist );
				mAct->SteadyTrans( -0.002f );
				mGoto->SetTransSpeed( -miniTransDist );
			}
		}
		else if( yDistToBall > 0.089f )
		{
			if( fabs(mGoto->GetForSpeed()) > EPS 
				|| fabs(mGoto->GetTurnSpeed()) > EPS 
				)
			{
				mGoto->SlowDownSpeedToStand();

				return false;
			}
			else
			{
				//mAct->CrazyTrans( miniTransDist );
				mAct->SteadyTrans( 0.002f );
				mGoto->SetTransSpeed( miniTransDist );
			}	
		}
		else if( fabs(mGoto->GetForSpeed()) > EPS 
				|| fabs(mGoto->GetTurnSpeed()) > EPS 
				|| fabs(mGoto->GetTransSpeed()) > EPS )
		{
			mAct->Stand();
			mGoto->ClearSpeed();
		}
		else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 0.05f )
		{
			mAct->Stand();
			mGoto->ClearSpeed();
		}
		else
		{
			KickLog << " angleToBall " << angleToBall
					<< " xDistToBall " << xDistToBall
					<< " yDistToBall " << yDistToBall 
					<< endl;

			KickLog<< " RightStraightKick " << endl;
			
			mAct->RightStraightKick();
		}
	}
	else /*if( yDistToBall <= 0.0f )*/
	{
		if( yDistToBall > -0.021f )
		{
			if( fabs(mGoto->GetForSpeed()) > EPS 
				|| fabs(mGoto->GetTurnSpeed()) > EPS 
				)
			{
				mGoto->SlowDownSpeedToStand();

				return false;
			}
			else
			{
				//mAct->CrazyTrans( miniTransDist );
				mAct->SteadyTrans( 0.002f );
				mGoto->SetTransSpeed( miniTransDist );
			}	
		}
		else if( yDistToBall < -0.089f )
		{
			if( fabs(mGoto->GetForSpeed()) > EPS 
				|| fabs(mGoto->GetTurnSpeed()) > EPS 
				)
			{
				mGoto->SlowDownSpeedToStand();

				return false;
			}
			else
			{
				//mAct->CrazyTrans( -miniTransDist  );
				mAct->SteadyTrans( -0.002f );
				mGoto->SetTransSpeed( -miniTransDist );
			}	
		}
		else if( fabs(mGoto->GetForSpeed()) > EPS 
			|| fabs(mGoto->GetTurnSpeed()) > EPS 
			|| fabs(mGoto->GetTransSpeed()) > EPS )
		{
			mAct->Stand();
			mGoto->ClearSpeed();
		}
		else if( fabs(mWorldModel->mBodyFaceTo.angPhi()) > 0.10f )
		{
			mAct->Stand();
			mGoto->ClearSpeed();
		}
		else
		{
			KickLog << " angleToBall " << angleToBall
				<< " xDistToBall " << xDistToBall
				<< " yDistToBall " << yDistToBall 
				<< endl;

			KickLog<< " LeftStraightKick " << endl;

			mAct->LeftStraightKick();
		}
	}
	
	return true;
}

bool MotionKick::InKickAngle( Vector3f tarVector3f )
{
	Angle advanceAng = ( tarVector3f - mWorldModel->mSelf.mPos ).angTheta();
	Angle angBetweenTarAndSelf = advanceAng - mWorldModel->mBodyAngle;
	float distToTar = mWorldModel->mSelf.DistXyTo(tarVector3f);

	if( fabs(angBetweenTarAndSelf) > Max( mKickAngleEps, (float)atan2(mKickRadius,distToTar) * 180.0f / PI ) 
		&& fabs( fabs(angBetweenTarAndSelf) - 180.0f ) > Max( mKickAngleEps, (float)atan2(mKickRadius,distToTar) * 180.0f / PI )
		)
	{
		return false;
	}

	Line kickLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector3f );

	if( kickLine.getDistanceWithPoint( mWorldModel->mBall.mPos ) > mKickRadius )
	{
		return false;
	}

	Circle circleBallAndTar( tarVector3f, mWorldModel->mBall.DistXyTo(tarVector3f) );

	if( circleBallAndTar.isInsideCircle( mWorldModel->mSelf.mPos ) )
	{
		return false;
	}

	KickLog << "InKickAngle" << endl;

	return true;
}

bool MotionKick::InKickAngleAllowBack( Vector3f tarVector3f )
{
	Angle advanceAng = ( tarVector3f - mWorldModel->mSelf.mPos ).angTheta();
	Angle angBetweenTarAndSelf = advanceAng - mWorldModel->mBodyAngle;
	float distToTar = mWorldModel->mSelf.DistXyTo(tarVector3f);

	if( fabs(angBetweenTarAndSelf) > Max( mKickAngleEps, (float)atan2(mKickAngleEps,distToTar) * 180.0f / PI ) 
		&& fabs( fabs(angBetweenTarAndSelf) - 180.0f ) > Max( mKickAngleEps, (float)atan2(mKickAngleEps,distToTar) * 180.0f / PI ) )
	{
		return false;
	}

	Line kickLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector3f );

	if( kickLine.getDistanceWithPoint( mWorldModel->mBall.mPos ) > mKickRadius )
	{
		return false;
	}

	Circle circleBallAndTar( tarVector3f, mWorldModel->mBall.DistXyTo(tarVector3f) );

	if( circleBallAndTar.isInsideCircle( mWorldModel->mSelf.mPos ) )
	{
		return false;
	}

	return true;
}


bool MotionKick::InKickDist()
{
	Circle kickCircle( mWorldModel->mBall.mPos, mKickRadius );

	return kickCircle.isInsideCircle( mWorldModel->mSelf.mPos );
}

bool MotionKick::InKickArea( Vector3f tarVector3f )
{
	//return InKickAngleAllowBack( tarVector3f ) && InKickDist( );
	return InKickAngle( tarVector3f ) && InKickDist( );

}
