#include "RunPosition.h"

#define RunPosLog gLog<< "[runPos] "

RunPosition::RunPosition( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act )
{
	mWorldModel = wm;
	mSituation = situ;
	mGoto = mtGoto;
	mCmdQuene = cmdQuene;
	mAct = act;
}
RunPosition::~RunPosition()
{


}

bool RunPosition::ToPosition()
{
	AttDefkTrend attDefWeight = mSituation->AttackWeight();

	Vector3f sitTarPos = mSituation->AttackRunPos( attDefWeight );
	
	Vector3f tarPos(0.0f, 0.0f, 0.0f);
	static Vector3f lastTarPos(0.0f, 0.0f, 0.0f);
	static float startSmartGotoDist = 0.0f;

	if( sitTarPos.distXY2(lastTarPos) <= 0.5f )
	{
		tarPos = lastTarPos;
	}
	else
	{
		tarPos = sitTarPos;
		startSmartGotoDist = mWorldModel->mSelf.DistXyTo( tarPos );
	}

	lastTarPos = tarPos;

	RunPosLog << "Run To: " << tarPos.x << " " << tarPos.y << endl;

	const float runPosDistEps = 0.1f;
	const float smartGotoDistEps = 1.0f;
	const float smartGotoMinDist = 5.0f;
	const float ourPlayerInPosRadius = 1.0f;
	const float ballToOurGoalMinDist = 2.5f;

	float ballToOurGoal = mWorldModel->mBall.DistXyTo( mWorldModel->mOurGoalCenter );

	if( ballToOurGoal >= ballToOurGoalMinDist )
	{
		for( unsigned int i = 0; i < mWorldModel->mOurPlayerNumOnField; i ++ )
		{
			float tempDist = mWorldModel->mOurTeamPlayer[i].DistXyTo( tarPos );

			// 如果队友已经在站位点，则自己就不需要再过去了
			if( tempDist <= ourPlayerInPosRadius )
			{
				Angle tempAng = tarPos.angTheta2( mWorldModel->mSelf.mPos );
				Ray tempRay = Ray::MakeRayFromPositionAndAngle( tarPos, tempAng );
				Vector3f tempPos = tempRay.GetPoint( ourPlayerInPosRadius + 0.5f );

				tarPos = tempPos;

				break;
			}
		}
	}
	

	Vector3f tarToFace = mWorldModel->mBall.mPos;
	Angle angleToFace = Normalize( (tarToFace - mWorldModel->mSelf.mPos).angTheta() );

	if( mWorldModel->mSelf.DistXyTo(tarPos) <= runPosDistEps )
	{
		RunPosLog << "In Position! " << endl;

		if( mGoto->FacingTarget( tarToFace ) )
		{
			if( fabs(mGoto->GetForSpeed()) > EPS
				|| fabs(mGoto->GetTurnSpeed()) > EPS 
				|| fabs(mGoto->GetTransSpeed()) > EPS 
				)
			{
				mGoto->SlowDownSpeedToStand();

				return false;
			}
			else
			{
				mAct->Stand();
				mGoto->ClearSpeed();

				return true;
			}
		}
		else
		{
			if( fabs(mGoto->GetForSpeed()) > EPS
				|| fabs(mGoto->GetTransSpeed()) > EPS 
				)
			{
				mGoto->SlowDownSpeedToStand();

				return false;
			}
			else
			{
				mGoto->Turn( angleToFace );
			}		
		}

		return true;
	}
	else
	{
		//if(  startSmartGotoDist >= smartGotoMinDist )
		//{
		//	mGoto->SmartFastGoto( tarPos, smartGotoDistEps );
		//}
		//else
		//{
			mGoto->Goto( tarPos );
		//}
	}

	return false;
}

bool RunPosition::DeadBallToPosition( bool ourKick )
{
	const float minDistToBall = 3.1f;
	const float gotoKickDist = 0.2f;
	static bool inPosition = false;

	if( ourKick )
	{
		if( mSituation->IShouldGotoControlBall() )
		{	
			Vector3f gotoPos = mWorldModel->mBall.mPos - ( mWorldModel->mOppGoalCenter - mWorldModel->mBall.mPos ).normalize( 1.2f );
			float myDistToPos = mWorldModel->mSelf.DistXyTo( gotoPos );

			if( myDistToPos >= gotoKickDist && !inPosition )
			{
				mGoto->Goto( gotoPos );

				inPosition = true;

				return false;
			}
			else
			{
				//mGoto->Goto( mWorldModel->mBall.mPos );
				

				return true;
			}
		}
		else
		{
			ToPosition();

			inPosition = false;

			return false;
		}
	}
	else
	{
		Angle gotoAng = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mSelf.mPos );
		Ray gotoRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, gotoAng );
		Vector3f gotoPos = gotoRay.GetPoint( minDistToBall );

		Angle angleToFace = Normalize( (mWorldModel->mBall.mPos - mWorldModel->mSelf.mPos).angTheta() );
		
		mGoto->Goto( gotoPos, angleToFace );

		return false;
	}
}


