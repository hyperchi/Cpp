#include "SitDribble.h"
#define SitDribbleLog gLog<< "[sitDri] " << "Dribble "

SitDribble::SitDribble( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo )
{
	mWorldModel = wm;
	mFieldSquare = square;
	mAgentInfo = agentInfo;

	mDribbleThreshold = 5.0f;
	mDribbleUnitAng = 5.0f;	
	mDribbleDist = 1.5f;

	InitialDribble( );
}

SitDribble::~SitDribble()
{

}

void SitDribble::InitialDribble()
{
	ReadConf rC( mWorldModel->GetFormationConfPath() );
	Predicate tempP;

	rC.Tranversal( "DribbleThreshold", tempP );
	tempP.GetValue( "DribbleThreshold", mDribbleThreshold );

	rC.Tranversal( "DribbleUnitAngle", tempP );
	tempP.GetValue( "DribbleUnitAngle", mDribbleUnitAng );
}


bool SitDribble::DribbleSquare( Vector3f &tarDribbleVector )
{
	//Angle bodyAng = mWorldModel->mBodyAngle;
	static Vector3f lastTarDribbleVec = tarDribbleVector;

	IsObstacle( tarDribbleVector );

	if( LastDribbleWeightOK(lastTarDribbleVec) )
	{
		tarDribbleVector = lastTarDribbleVec;

		return true;
	}

	float maxWeight =  ComputeCurrDribbleWeight( tarDribbleVector );

	lastTarDribbleVec = tarDribbleVector;

	if( maxWeight >= mDribbleThreshold )
	{	
		return true;
	}

	return true;
}

float SitDribble::DribbleAngleImpactFactor( float tarTurnAngle )
{
	//tarAngle == 0.0f   return 1.0f;
	//tarAngle == +180.0f || tarAngle == -180.0f	return 0.0f;
	float tempFactor = fabs(tarTurnAngle) * ( -1.0f / 180.0f ) + 1.0f;
	float dribbleFactor = tempFactor * tempFactor;

	return tempFactor;
}

bool SitDribble::IsDribbleToSquareOk( Angle angleToTurn, Vector3f &tarDribbleVector, unsigned int &rowNum, unsigned int &colNum, float &maxWeight )
{
	if( !mFieldSquare->IsInField(tarDribbleVector) )
	{
		return false;
	}

	if( IsObstacle( tarDribbleVector ) )
	{
		return false;
	}

	unsigned int tempRowNum = mFieldSquare->GetSquareRowNum( tarDribbleVector );
	unsigned int tempColNum = mFieldSquare->GetSquareColNum( tarDribbleVector );
	UnitSquare tempSquare = mFieldSquare->GetSqure( tempRowNum, tempColNum );

	rowNum = tempRowNum;
	colNum = tempColNum;
	maxWeight = ComputeDribbleWeight( angleToTurn, tempSquare ); 

	return true;
}

float SitDribble::ComputeDribbleWeight( Angle angleToTurn, UnitSquare square )
{
	float weight = DribbleAngleImpactFactor( angleToTurn ) + square.GetWeight();

	return weight;
}

bool SitDribble::LastDribbleWeightOK( Vector3f &tarDribbleVector )
{
	unsigned int resultRowNum = 0;
	unsigned int resultColNum = 0;
	Angle angleNeedToTurn = 0.0f;
	float lastWeight = 0.0f;

	if( IsDribbleToSquareOk( angleNeedToTurn, tarDribbleVector, resultRowNum, resultColNum, lastWeight ) )
	{
		if( lastWeight > mDribbleThreshold )
		{
			return true;
		}
	}

	return false;
}

float SitDribble::ComputeCurrDribbleWeight( Vector3f &tarDribbleVector )
{
	float maxWeight = 0.0f;
	unsigned int resultRowNum = 0;
	unsigned int resultColNum = 0;

	int checkNum = (int) 180.0f / mDribbleUnitAng;
	Angle angleNeedToTurn = 0.0f;

	Angle bodyAng = mWorldModel->mBodyAngle;
	Vector3f ballPos = mWorldModel->mBall.mPos;

	for( int i = 0; i < checkNum; i ++ )
	{
		for( int j = -1; j < 2; j += 2 )
		{
			angleNeedToTurn = j * i * mDribbleUnitAng;

			Ray tempRay = Ray::MakeRayFromPositionAndAngle( ballPos, bodyAng + angleNeedToTurn );
			Vector3f tempVec = tempRay.GetPoint( mDribbleDist );

			float tempWeight;
			unsigned int tempRowNum = 0;
			unsigned int tempColNum = 0;

			if( IsDribbleToSquareOk( angleNeedToTurn, tempVec, tempRowNum, tempColNum, tempWeight ) )
			{
				if( tempWeight > maxWeight )
				{
					maxWeight = tempWeight;
					resultRowNum = tempRowNum;
					resultColNum = tempColNum;
				}
			}
		}
	}
	
	UnitSquare tempSquare = mFieldSquare->GetSqure( resultRowNum, resultColNum );
	tarDribbleVector = tempSquare.GetCenterVector3f( );

	//cout<< tarDribbleVector.x << " " << tarDribbleVector.y << " " << maxWeight <<  endl;

	return maxWeight;
}

bool SitDribble::IsObstacle( const Vector3f &tarDribbleVector )
{
	Vector3f tarVector = tarDribbleVector;
	const float playerObstacleRadius = 0.15f;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		Line dribbleLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector  );

		if( dribbleLine.getDistanceWithPoint(mWorldModel->mOppTeamPlayer[i].mPos) <= playerObstacleRadius )
		{
			float distBallToTar = ( mWorldModel->mBall.mPos.distXY2( tarVector ) );
			float distObsToTar = ( mWorldModel->mOppTeamPlayer[i].mPos.distXY2( tarVector ) );
			float distObsToBall = ( mWorldModel->mOppTeamPlayer[i].mPos.distXY2( mWorldModel->mBall.mPos ) );

			if( distObsToBall < playerObstacleRadius )
			{
				return true;
			}

			if( distObsToTar < distBallToTar && distObsToBall < distBallToTar )
			{
				return true;
			}
		}	
	}

	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		Line dribbleLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector  );

		if( dribbleLine.getDistanceWithPoint(mWorldModel->mOurTeamPlayer[i].mPos) <= playerObstacleRadius )
		{
			float distBallToTar = ( mWorldModel->mBall.mPos.distXY2( tarVector ) );
			float distObsToTar = ( mWorldModel->mOurTeamPlayer[i].mPos.distXY2( tarVector ) );
			float distObsToBall = ( mWorldModel->mOurTeamPlayer[i].mPos.distXY2( mWorldModel->mBall.mPos ) );

			if( distObsToTar < distBallToTar && distObsToBall < distBallToTar )
			{
				return true;
			}
		}	
	}

	return false;
}


Vector3f SitDribble::DribbleTo(  const Vector3f &tarDribbleVector )
{
	Vector3f ultimateTarget = tarDribbleVector; 
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f tempTarget;
	Vector3f resultTarget;
	const float ballNearOppGoalDist = 1.0f;

	Vector3f oppGoalLeft;
	Vector3f oppGoalRight;

	oppGoalLeft.x = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.x;
	oppGoalLeft.y = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.y - 0.15f;
	oppGoalLeft.z = 0.0f;

	oppGoalRight.x = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos.x;
	oppGoalRight.y = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos.y + 0.15f;
	oppGoalRight.z = 0.0f;


	Angle startAngle = (ultimateTarget - ballPos).angTheta();
	Angle angleNeedToTurn = 0.0f;

	Angle ballToOppGoalLeft  = (oppGoalLeft - mWorldModel->mBall.mPos).angTheta();
	Angle ballToOppGoalRight = (oppGoalRight - mWorldModel->mBall.mPos).angTheta();

	int checkNum = (int) 180.0f / mDribbleUnitAng;

	Ray selfToBall = Ray::MakeRayFromPositionAndAngle( selfPos, (ballPos - selfPos).angTheta() );

	Vector3f predictTarget = selfToBall.GetPoint( mDribbleDist / 2.0f );
	tempTarget = selfToBall.GetPoint( mDribbleDist );


	// 当对手很贴近球时，需要迅速摆脱对手
	float oppMinDistToBall = 100.0f;
	const float oppNearBallDist = 0.5f;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		float tempMinDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		if( tempMinDist <= oppMinDistToBall )
		{
			oppMinDistToBall = tempMinDist;
		}
	}
	
	if( oppMinDistToBall <= oppNearBallDist 
		&& mWorldModel->mBall.DistXyTo( mWorldModel->mOurGoalCenter) >= 5.0f )
	{
		SitDribbleLog << " Opp Player Near Ball " << "-- Get Rid of him !" << endl;

		return tempTarget;
	}

	// 计算带球路线 
	// 情况一：
	float ballToTar = mWorldModel->mBall.DistXyTo( ultimateTarget );
	float predictBallToTarget = predictTarget.distXY2( ultimateTarget );


	if( ballPos.distXY2( ultimateTarget ) <= ballNearOppGoalDist 
		&& ( selfToBall.GetRayAngle() < ballToOppGoalLeft &&  selfToBall.GetRayAngle() > ballToOppGoalRight ) 
		)
	{
		SitDribbleLog << " Very Near OppGoal " << "-- Goal! " << ballPos.distXY2( ultimateTarget ) << endl;

		return tempTarget;
	}


	if( predictBallToTarget < ballToTar 
		//&& !IsObstacle( tempTarget ) 
		&& ( /*mFieldSquare->IsInField( predictTarget ) ||*/ ( selfToBall.GetRayAngle() < ballToOppGoalLeft &&  selfToBall.GetRayAngle() > ballToOppGoalRight ) )
		)
	{
		SitDribbleLog << " Near OppGoal " << "-- Dash! " << endl;

		return tempTarget;
	}
	
	// 情况二：
	for( int i = 0; i < checkNum; i ++ )
	{
		for( int j = -1; j < 2; j +=2 )
		{
			//****************************************
			// 2008-11-30
			//		试图提高进攻效率
			//****************************************
			angleNeedToTurn = j * i * mDribbleUnitAng;
			Angle startFromSelfPosAng = mWorldModel->mSelf.mPos.angTheta2( mWorldModel->mBall.mPos );
			Ray tempRay = Ray::MakeRayFromPositionAndAngle( ballPos, startFromSelfPosAng + angleNeedToTurn );
			
			//angleNeedToTurn = j * i * mDribbleUnitAng;
			//Ray tempRay = Ray::MakeRayFromPositionAndAngle( ballPos, startAngle + angleNeedToTurn );
			tempTarget = tempRay.GetPoint( mDribbleDist );

			Angle tempShootAng = tempTarget.angTheta2( oppGoalLeft ) - tempTarget.angTheta2( oppGoalRight );
			Angle currenShootAng = mWorldModel->mBall.mPos.angTheta2( oppGoalLeft ) - mWorldModel->mBall.mPos.angTheta2( oppGoalRight );

			//if( !IsObstacle( tempTarget ) )
			//{			

				//****************************************
				// 2008-11-30
				//		试图提高进攻效率
				//****************************************
				if( mFieldSquare->IsInField( tempTarget ) 
					/*|| ( tempRay.GetRayAngle() < ballToOppGoalLeft &&  tempRay.GetRayAngle() > ballToOppGoalRight ) */
					&& ( ( tempShootAng >= currenShootAng * 1.05f ) 
						|| tempTarget.distXY2( ultimateTarget ) < ballToTar * 0.8f && tempShootAng >= currenShootAng * 0.7f )
					)

				//if( mFieldSquare->IsInField( tempTarget ) 
				//	/*|| ( tempRay.GetRayAngle() < ballToOppGoalLeft &&  tempRay.GetRayAngle() > ballToOppGoalRight ) */	
				//	&& ( tempShootAng >= currenShootAng * 0.9f )
				//	)
				{	
					resultTarget = tempTarget;

					SitDribbleLog << " No Obstacle  " << "-- OK! " << endl;

					return resultTarget;
				}
			//}

		}
	}

	SitDribbleLog << " No Obstacle Line " << "-- Turn! " << endl;

	// 没有可带球路线
	return ultimateTarget;
}

float SitDribble::DribbleWeight()
{
	const float nearOppGoalDist = 2.1f;
	const float oppDistNearBall = 2.0f;
	const float oppDistControlBall = 0.8f;

	float myDistToOppGoal = mWorldModel->mSelf.DistXyTo( mWorldModel->mOppGoalCenter );

	// 当自己距离对方球门很近时，应该带球
	//		调整的比较少，效率更高
	//	同时，服务器有一个Bug，距离太近的时候大力射门，会判不进
	if( myDistToOppGoal <= nearOppGoalDist )
	{
		SitDribbleLog << "In Front of Their Goal " << "-- Dash! " << endl;

		return 9.5f;
	}

	// 离对方球门越远，越应该带球
	//		保证自己控球，而且带球时路线多变，进攻效果较好
	//		但不能超过传球的阈值
	
	// 首先找到对方距离球最近的距离
	float oppMinDistToBall = 100.0f;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		float tempMinDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );	
		
		if( tempMinDist < oppMinDistToBall )
		{
			oppMinDistToBall = tempMinDist;
		}
	}

	// 如果对方距离球都比较远
	//		则认为不形成障碍
	if( oppMinDistToBall >= oppDistNearBall )
	{
		SitDribbleLog << "No One Can Stop Me " << "-- Dribble! " << endl;

		//float deltaSpeed = mAgentInfo->GetOppMaxSpeed() / mAgentInfo->GetOurMaxSpeed();

		//if( deltaSpeed > 1.2f )
		//{
		//	deltaSpeed = 1.2f;
		//}
		//
		//float tempWeight = 5.0f * deltaSpeed;

		//if( tempWeight > 9.5f )
		//{
		//	tempWeight = 9.5f;
		//}

		//return tempWeight;
		float tempPassWeight = 5.0f;
		float diffStrendgh = 1.0f;

		if( mWorldModel->mOppStrength == OS_Strong )
		{
			diffStrendgh = 1.3f;
		}
		else if( mWorldModel->mOppStrength == OS_Weak )
		{
			diffStrendgh = 1.0f / 1.3f;
		}

		tempPassWeight *= diffStrendgh;

		return tempPassWeight;	
	}

	// 如果对方距离球太近（在可控球半径内）
	//		则应该选择带球，可保证自己控球
	if( oppMinDistToBall <= oppDistControlBall )
	{
		SitDribbleLog << "Let't Player a Game " << "-- See You! " << endl;

		return 6.5f;
	}

	// 上述条件都不满足，则可以考虑传球
	SitDribbleLog << "Ok, Default " << endl;

	return  5.0f;
}
