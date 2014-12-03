#include "MotionDribble.h"
#define DribbleLog gLog<< "[motion] " << "Dribble "

MotionDribble::MotionDribble( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act )
{
	mWorldModel = wm;
	mSituation = situ;
	mGoto = mtGoto;
	mCmdQuene = cmdQuene;
	mAct = act;

	mDribbleRadius = 0.22f;		// waited to be tested
	mDribbleAngle = 30.0f;		// waited to be tested
	mDribbleAngleEps = 5.0f;	// waited to be tested
}
MotionDribble::~MotionDribble()
{

}

void MotionDribble::InitDribble()
{

}

bool MotionDribble::Dribble()
{
	const float dribbleDist = 1.5f;

	Vector3f ultimateTarget = mWorldModel->mOppGoalCenter;

	Vector3f dribbleTar = ultimateTarget;
	Vector3f sitDribbleTar = ultimateTarget;
	static Vector3f lastSitDribbleTar = ultimateTarget;
	static Angle lastPreDribbleAngle = 0.0f;

	if( !EvaluCurrDribbleTar() )
	{
		sitDribbleTar = mSituation->DribbleTo( ultimateTarget );		
	}
	else
	{
		Angle preAngle;
		Angle preDribbleAng = mWorldModel->mSelf.mPos.angTheta2( mWorldModel->mBall.mPos );
		
		if( fabs(preDribbleAng - lastPreDribbleAngle) < 10.0f )
		{
			preAngle = lastPreDribbleAngle;
		}
		else
		{
			preAngle = preDribbleAng;
		}

		lastPreDribbleAngle = preAngle;

		Ray preDribbleRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, preAngle );

		Vector3f preDribblePos = preDribbleRay.GetPoint( dribbleDist );

		sitDribbleTar = preDribblePos;
	}

	if( sitDribbleTar.distXY2( lastSitDribbleTar ) <= 1.0f )
	{
		dribbleTar = lastSitDribbleTar;
	}
	else
	{
		dribbleTar = sitDribbleTar;
	}

	if( !InDribbleArea( dribbleTar ) )
	{
		DribbleLog << " !InDribbleArea " << endl;
		//cout	   << " !InDribbleArea " << endl;

		// 虽然不在控球区域，但已瞄准球，仍高速前进
		if( InDribbleAngle( dribbleTar ) 
			&& mGoto->FacingTheBall() 
			&& !mGoto->IsOurPlayerObstacle(dribbleTar) 
			//&& !mGoto->IsOppPlayerObstacle(dribbleTar)
			)
		{
			DribbleLog << " !InDribbleArea But Dash" << endl;
			
			DribbleTo( dribbleTar );
			//cout	   << " DribbleTo " << endl;

			//mGoto->SmartFastGoto( mWorldModel->mBall.mPos, 0.2f );

			//mGoto->FastGoto( dribbleTar );
		}
		else 
		{
			dribbleTar = sitDribbleTar;

			GotoDribbleArea( dribbleTar );
		}
	}
	else
	{
		//mGoto->FastGotoDribble( dribbleTar );
		DribbleTo( dribbleTar );
		//mGoto->SmartFastGoto( mWorldModel->mBall.mPos, 0.2f );
	}

	lastSitDribbleTar = sitDribbleTar;

	return true;
}

bool MotionDribble::GotoDribbleArea( Vector3f tarVector3f )
{
	return mGoto->GotoHandleBall( tarVector3f );
	//mGoto->SmartFastGoto( mWorldModel->mBall.mPos, 0.2f );
}

bool MotionDribble::DribbleTo( Vector3f tarVector3f )
{
	//mGoto->FastGotoDribble( tarVector3f );
	//mGoto->FastGoto( tarVector3f );
	//mGoto->SmartFastGoto( mWorldModel->mBall.mPos, 0.2f );
	return mGoto->Goto( tarVector3f );
	//mGoto->SmartGoto( tarVector3f );
}
	
bool MotionDribble::InDribbleRadius()
{
	Circle dribbleCircle( mWorldModel->mBall.mPos, mDribbleRadius );

	return dribbleCircle.isInsideCircle( mWorldModel->mSelf.mPos );
}

bool MotionDribble::InDribbleAngle( Vector3f tarVector3f )
{
	Angle advanceAng = ( tarVector3f - mWorldModel->mSelf.mPos ).angTheta();
	Angle angBetweenTarAndSelf = advanceAng - mWorldModel->mBodyAngle;
	float distToTar = mWorldModel->mSelf.DistXyTo(tarVector3f);

	if( fabs(angBetweenTarAndSelf) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI )
		&& fabs(fabs(angBetweenTarAndSelf) - 180.0f )> Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI )
		)
	{
		return false;
	}

	Line dribbleLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector3f );

	if( dribbleLine.getDistanceWithPoint( mWorldModel->mBall.mPos ) > mDribbleRadius )
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

bool MotionDribble::InDribbleAngleAllowBack( Vector3f tarVector3f )
{
	Angle advanceAng = ( tarVector3f - mWorldModel->mSelf.mPos ).angTheta();
	Angle angBetweenTarAndSelf = advanceAng - mWorldModel->mBodyAngle;
	float distToTar = mWorldModel->mSelf.DistXyTo(tarVector3f);

	if( fabs(angBetweenTarAndSelf) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI ) 
		&& fabs( fabs(angBetweenTarAndSelf) - 180.0f ) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI ) 
		)
	{
		return false;
	}

	Line dribbleLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector3f );

	if( dribbleLine.getDistanceWithPoint( mWorldModel->mBall.mPos ) > mDribbleRadius )
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

bool MotionDribble::InDribbleAngleAllowTrans( Vector3f tarVector3f )
{
	Angle advanceAng = ( tarVector3f - mWorldModel->mSelf.mPos ).angTheta();
	Angle angBetweenTarAndSelf = advanceAng - mWorldModel->mBodyAngle;
	float distToTar = mWorldModel->mSelf.DistXyTo(tarVector3f);

	if( fabs(angBetweenTarAndSelf) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI ) 
		&& fabs( fabs(angBetweenTarAndSelf) - 180.0f ) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI ) 
		&& fabs( fabs(angBetweenTarAndSelf) - 90.0f ) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI ) 
		&& fabs( fabs(angBetweenTarAndSelf) + 90.0f ) > Max( mDribbleAngleEps, (float)atan2(mDribbleRadius,distToTar) * 180.0f / PI ) 
		)
	{
		return false;
	}

	Line dribbleLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector3f );

	if( dribbleLine.getDistanceWithPoint( mWorldModel->mBall.mPos ) > mDribbleRadius )
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

bool MotionDribble::InDribbleArea( Vector3f tarVector3f )
{
	//return InDribbleRadius() && InDribbleAngleAllowTrans( tarVector3f );
	//return InDribbleRadius() && InDribbleAngleAllowBack( tarVector3f );
	float distToBall = ( mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos) );
	float angleToBall = Normalize( mWorldModel->mBodyAngle - (mWorldModel->mBall.mPos - mWorldModel->mSelf.mPos).angTheta() );
	float xDistToBall = -distToBall * cos( angleToBall * PI / 180.0f );
	float yDistToBall = distToBall * sin( angleToBall * PI / 180.0f );

	const float bodyRadius = 0.5f;
	const float xDistEps = 0.11f;

	DribbleLog << " DribbleArea "<< xDistToBall << " " << yDistToBall << " " << angleToBall << endl;

	if( fabs(xDistToBall) > xDistEps )
	{
		DribbleLog << "fabs(xDistToBall) > xDistEps " << endl;

		return false;
	}

	if( fabs(yDistToBall) >  bodyRadius )
	{
		DribbleLog << "fabs(yDistToBall) >  bodyRadius " << endl;

		return false;
	}
	//return InDribbleAngleAllowTrans(tarVector3f) && InDribbleRadius();
	return InDribbleRadius() && InDribbleAngle( tarVector3f );
}

bool MotionDribble::EvaluCurrDribbleTar()
{
	const float dribbleDist = 1.5f;

	Angle preDribbleAng = mWorldModel->mSelf.mPos.angTheta2( mWorldModel->mBall.mPos );
	Ray preDribbleRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, preDribbleAng );

	Vector3f preDribblePos = preDribbleRay.GetPoint( dribbleDist );
	Vector3f currBallPos = mWorldModel->mBall.mPos;

	Angle preDriToOppGoalLeft = preDribblePos.angTheta2( mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos );
	Angle preDriToOppGoalRight = preDribblePos.angTheta2( mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos );
	
	Angle currDriToOppGoalLeft = currBallPos.angTheta2( mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos );
	Angle currDriToOppGoalRight = currBallPos.angTheta2( mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos );
	
	Angle preDiffAng = preDriToOppGoalLeft - preDriToOppGoalRight;
	Angle currDiffAng = currDriToOppGoalLeft - currDriToOppGoalRight;

	if( !mSituation->IsTarInField(preDribblePos) )
	{
		return false;
	}
	else if( preDiffAng <= currDiffAng )
	{
		return true;
	}
	else
	{
		return false;
	}
}
