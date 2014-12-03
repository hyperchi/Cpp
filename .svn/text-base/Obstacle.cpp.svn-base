#include "Obstacle.h"
#define OBSLog gSpeedLog << "[Obstac] "

Obstacle *Obstacle::mInstance = NULL;  

Obstacle::Obstacle( WorldModel *wm )
{
	mWorldModel = wm;
}
Obstacle::~Obstacle()
{
	if( mInstance ) 
	{
		delete mInstance;
		mInstance = NULL;
	}
}
bool Obstacle::IsObstacle( Vector3f tarGoto, Vector3f obs, float radius )
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Angle selfToTarAng = selfPos.angTheta2( tarGoto );
	Line selfToTarLine = Line::makeLineFromPositionAndAngle( selfPos, selfToTarAng );

	float obsDistToLine = selfToTarLine.getDistanceWithPoint( obs );
	Vector3f obsNearestPointInLine = selfToTarLine.getPointOnLineClosestTo( obs );
	float obsDistToNearestPointInLine = obs.distXY2(obsNearestPointInLine);

	if( radius > 0.15f )	// 判断player
	{
		if( obs.distXY2( tarGoto ) < 0.1f )
		{
			return false;
		}
	}
// 	else
// 	{
// 		if( obs.distXY2( tarGoto ) < 0.1f )
// 		{
// 			return true;
// 		}
// 	}

	if( obsDistToLine > radius )
	{
		return false;
	}

	if( obs.distXY2(selfPos) < 0.15f )
	{
		return false;
	}

// 	if( obsDistToNearestPointInLine < 0.1f )
// 	{
// 		return false;
// 	}

	if( selfToTarLine.isInBetween(obsNearestPointInLine, selfPos, tarGoto ) )
	{
		return true;
	}

	return false;
}
bool Obstacle::IsPlayerObstacle( Vector3f tarGoto, Vector3f playerVector3f )
{
	const float playerRadius = 0.5f;
	return IsObstacle( tarGoto, playerVector3f, playerRadius );
}
bool Obstacle::IsOurPlayerObstacle( Vector3f tarGoto )
{
	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		if( mWorldModel->mOurPlayers.at(i).mMyPlayerNo == mWorldModel->mMyPlayerNo )
		{
			continue;
		}
		if( IsPlayerObstacle( tarGoto, mWorldModel->mOurPlayers.at(i).mPos ) )
		{
			return true;
		}
	}

	return false;
}
bool Obstacle::IsOppPlayerObstacle( Vector3f tarGoto )
{
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		if( IsPlayerObstacle( tarGoto, mWorldModel->mOppPlayers.at(i).mPos ) )
		{
			return true;
		}
	}

	return false;
}
Vector3f Obstacle::GetRidOfObstacle( Vector3f tarGoto )
{
	const Angle unitAngle = 3.0f;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f avoidGoalpostGoto = tarGoto;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;

	if( ballPos.distXY2(oppGoalCenter) < 2.0f )
	{
		return tarGoto;
	}
	
	//避开球门柱
	Vector3f oppGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	Vector3f oppGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos;
	Vector3f ourGoalLeft = mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos;
	Vector3f ourGoalRight = mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos;
	oppGoalLeft.x += 0.1f;			// 把球门柱的影响设大一些
	oppGoalRight.x += 0.1f;
	ourGoalLeft.x -= 0.1f;
	ourGoalRight.x -= 0.1f;
	oppGoalLeft.y += 0.1f;
	oppGoalRight.y -= 0.1f;
	ourGoalLeft.y += 0.1f;
	ourGoalRight.y -= 0.1f;
// 	Line oppGoalLeftLine = Line::makeLineFromPositionAndAngle(oppGoalLeft,0.0f);
// 	Line oppGoalRightLine = Line::makeLineFromPositionAndAngle(oppGoalRight,0.0f);
// 	Line ourGoalLeftLine = Line::makeLineFromPositionAndAngle(ourGoalLeft,180.0f);
// 	Line ourGoalRightLine = Line::makeLineFromPositionAndAngle(ourGoalRight,180.0f);
// 	Line selfToTarLine = Line::makeLineFromPositionAndAngle(selfPos,selfPos.angTheta2(tarGoto));
// 	Vector3f interceptPos_1 = oppGoalLeftLine.getIntersection(oppGoalLeftLine);
// 	Vector3f interceptPos_2 = oppGoalLeftLine.getIntersection(oppGoalRightLine);
// 	Vector3f interceptPos_3 = oppGoalLeftLine.getIntersection(ourGoalLeftLine);
// 	Vector3f interceptPos_4 = oppGoalLeftLine.getIntersection(ourGoalRightLine);
	bool neetToAvoidDoorpost = false;
	if( fabs(selfPos.x) > mWorldModel->mFieldLength * 0.5f && fabs(selfPos.y) < mWorldModel->mFieldWidth * 0.5f )
	{
		if( IsObstacle(tarGoto,oppGoalLeft,0.2f)
			|| IsObstacle(tarGoto,oppGoalRight,0.2f)
			|| IsObstacle(tarGoto,ourGoalLeft,0.2f)
			|| IsObstacle(tarGoto,ourGoalRight,0.2f) )
		{
			neetToAvoidDoorpost = true;
		}
	}

	if( neetToAvoidDoorpost )
	{
		if(fabs(selfPos.y) > mWorldModel->mGoalWidth * 0.5f)
		{
			avoidGoalpostGoto.x = 0.0f;
			avoidGoalpostGoto.y = selfPos.y;
		}
// 		else if( fabs(selfPos.x) < mWorldModel->mFieldLength * 0.5f + mWorldModel->mGoalDepth )
// 		{
// 			avoidGoalpostGoto.x = 0.0f;
// 			avoidGoalpostGoto.y = selfPos.y;
// 		}
		else if( fabs(selfPos.x) < mWorldModel->mFieldLength * 0.5f + mWorldModel->mGoalDepth )
		{
			avoidGoalpostGoto.x = selfPos.x;
			avoidGoalpostGoto.y = 2.0f;
		}
	}

	Vector3f avoidBallPos = AvoidBall( avoidGoalpostGoto );
	Vector3f resultVector = avoidBallPos;
	Vector3f resultVectorLeft = avoidBallPos;
	Vector3f resultVectorRight = avoidBallPos;
	unsigned int computeTime = 0;
	unsigned int leftComputeTime = 0;
	unsigned int rightComputeTime = 0;	

	while( computeTime < 20 )
	{
		float selfDistToTar = selfPos.distXY2( resultVectorLeft );
		Angle selfAngToTar = selfPos.angTheta2( resultVectorLeft );

		if( IsOurPlayerObstacle( resultVectorLeft ) 
			|| IsOppPlayerObstacle( resultVectorLeft ) 
			)
		{			
			Angle deltaAng = unitAngle + selfAngToTar;
			Ray deltaRay = Ray::MakeRayFromPositionAndAngle( selfPos, deltaAng );
			Vector3f deltaVec = deltaRay.GetPoint( selfDistToTar );

			resultVectorLeft = deltaVec;
		}
		else
		{
			break;
		}

		computeTime ++;
		leftComputeTime ++;
	}

	computeTime = 0;

	while( computeTime < 20 )
	{
		float selfDistToTar = selfPos.distXY2( resultVectorRight );
		Angle selfAngToTar = selfPos.angTheta2( resultVectorRight );

		if( IsOurPlayerObstacle( resultVectorRight ) 
			|| IsOppPlayerObstacle( resultVectorRight ) 
			)
		{			
			Angle deltaAng = -unitAngle + selfAngToTar;
			Ray deltaRay = Ray::MakeRayFromPositionAndAngle( selfPos, deltaAng );
			Vector3f deltaVec = deltaRay.GetPoint( selfDistToTar );

			resultVectorRight = deltaVec;
		}
		else
		{
			break;
		}

		computeTime ++;
		rightComputeTime ++;
	}

	OBSLog << "leftComputeTime " << leftComputeTime << " rightComputeTime " << rightComputeTime << endl;
	if( leftComputeTime < rightComputeTime)
	//if( selfPos.distXY2(resultVectorLeft) <= selfPos.distXY2(resultVectorRight) )
	{
		return resultVectorLeft;
	}
	else
	{
		return resultVectorRight;
	}
}

bool Obstacle::IsBallObstacle( Vector3f tarGoto )
{
	const float ballRadius = 0.14f;
	Vector3f ballPos = mWorldModel->mBall.mPos;

	return IsObstacle( tarGoto, ballPos, ballRadius );
}
Vector3f Obstacle::AvoidBall( Vector3f tarGoto )
{
	const float avoidBallRadius = 0.25f;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f oppGoalPos = mWorldModel->mOppGoalCenter;

	if( !IsBallObstacle(tarGoto) )
	{
		return tarGoto;
	}

	if( tarGoto.x > ballPos.x )
	{
		return tarGoto;
	}

	Angle ballToOppGoalAng = ballPos.angTheta2( oppGoalPos );
	Angle ballToOppGoalAngLeft = ballPos.angTheta2( oppGoalPos ) + 100.0f;
	Angle ballToOppGoalAngRight = ballPos.angTheta2( oppGoalPos ) - 100.0f;
	Ray avoidBallPosRayLeft = Ray::MakeRayFromPositionAndAngle( ballPos, ballToOppGoalAngLeft );
	Ray avoidBallPosRayRight = Ray::MakeRayFromPositionAndAngle( ballPos, ballToOppGoalAngRight );
	Vector3f avoidBallPosLeft = avoidBallPosRayLeft.GetPoint( avoidBallRadius );
	Vector3f avoidBallPosRight = avoidBallPosRayRight.GetPoint( avoidBallRadius );

	float selfDistToPosLeft = selfPos.distXY2( avoidBallPosLeft );
	float selfDistToPosRight = selfPos.distXY2( avoidBallPosRight );

	if( selfDistToPosLeft < selfDistToPosRight )
	{
		return avoidBallPosLeft;
	}
	else
	{
		return avoidBallPosRight;
	}
}

