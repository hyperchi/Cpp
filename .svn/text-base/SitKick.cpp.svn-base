#include "SitKick.h"
#define SitKickLog gLog<< "[sitKic] "

SitKick::SitKick( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo )
{
	mWorldModel = wm;
	mFieldSquare = square;
	mAgentInfo = agentInfo;
}
SitKick::~SitKick()
{

}

bool SitKick::KickSquare( Vector3f &tarKickVector )
{
	return true;
}

Vector3f SitKick::KickTo( const Vector3f &tarKickVector, float kickDist )
{
	//mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	
	// 定义可射门区域，比球门略小
	Vector3f oppGoalLeftKickTo;		
	Vector3f oppGoalRightKickTo;
	oppGoalLeftKickTo.x = mWorldModel->mFieldLength / 2.0f;
	oppGoalLeftKickTo.y = mWorldModel->mGoalWidth / 2.2f;		//比球门略小
	oppGoalRightKickTo.x = mWorldModel->mFieldLength / 2.0f;
	oppGoalRightKickTo.y = -mWorldModel->mGoalWidth / 2.2f;

	Angle ballToOppGoalLeft  = ( oppGoalLeftKickTo - mWorldModel->mBall.mPos ).angTheta();
	Angle ballToOppGoalRight = ( oppGoalRightKickTo - mWorldModel->mBall.mPos ).angTheta();

	Vector3f ultimateTarget = tarKickVector;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f tempTarget;
	Vector3f resultTarget;

	const float kickUnitAngle = 10.0f;
	int checkNum = (int) 180.0f / kickUnitAngle;
	Angle startAngle = (ultimateTarget - ballPos).angTheta();
	Angle angleNeedToTurn = 0.0f;

	// 计算踢球路线 （需要避开障碍物）
	for( int i = 0; i < checkNum; i ++ )
	{
		for( int j = -1; j < 2; j +=2 )
		{
			angleNeedToTurn = j * i * kickUnitAngle;

			Ray tempRay = Ray::MakeRayFromPositionAndAngle( ballPos, startAngle + angleNeedToTurn );
			tempTarget = tempRay.GetPoint( kickDist );

			if( !IsObstacle( tempTarget ) )
			{			
				if( /*mFieldSquare->IsInField( tempTarget ) 
					||*/ ( tempRay.GetRayAngle() < ballToOppGoalLeft &&  tempRay.GetRayAngle() > ballToOppGoalRight ) 
					)
				{	
					resultTarget = tempTarget;

					return resultTarget;
				}
			}
		}
	}

	// 没有可踢球路线
	return ultimateTarget;
}

//*******************************************************************
//	判断最优接球者(距离最合适)
//*******************************************************************
Vector3f SitKick::PassTo()
{
	const float distToPassInFrontOfPlayer = 1.0f;
	const float passDist = 5.5f;
	const float passDistEps = 2.0f;

	float minDistOurPlayerToPassPoint = 100.0f;
	Vector3f playerTarToPass;

	for( unsigned int i = 0; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		float tempDist = mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		if( fabs( tempDist - passDist ) < minDistOurPlayerToPassPoint )
		{
			playerTarToPass = mWorldModel->mOurTeamPlayer[i].mPos;
		}
	}

	if( fabs(playerTarToPass.distXY2( mWorldModel->mBall.mPos ) - passDist) <= passDistEps )
	{
		Vector3f tarPassTo = playerTarToPass + ( mWorldModel->mOppGoalCenter - playerTarToPass ).normalize( 1.0f );

		return tarPassTo;
	}
	else
	{
		Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;

		return KickTo( oppGoalCenter, passDist );
	}
}

bool SitKick::IsObstacle( const Vector3f &tarKickVector )
{
	Vector3f tarVector = tarKickVector;
	const float playerObstacleRadius = 0.5f;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		Line kickLine = Line::makeLineFromTwoPoints( mWorldModel->mBall.mPos, tarVector  );

		if( kickLine.getDistanceWithPoint(mWorldModel->mOppTeamPlayer[i].mPos) <= playerObstacleRadius )
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

	// 评价射门路线时，只要队友没有摔倒，就不将其视为障碍物
	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		// 重心高度：0.17f  wait to be tested
		if( mWorldModel->mOurTeamPlayer[i].mPos.z > 0.17f )
		{
			continue;
		}

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

float SitKick::ShootWeight()
{
	const float shootableRadius = 4.0f;		//waited to be tested
	const Angle shootableAngle = 20.0f;		//waited to be tested
	
	float shootDist = mWorldModel->mBall.DistXyTo( mWorldModel->mOppGoalCenter );
	Angle ballToLeftOppGoal = mWorldModel->mBall.ThetaTo( mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos );
	Angle ballToRightOppGoal = mWorldModel->mBall.ThetaTo( mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos ); 
	Angle shootAngle = Normalize( ballToLeftOppGoal - ballToRightOppGoal );

	// 进入射门区域
	if( shootDist <= shootableRadius )		
	{
		// 进入射门角度
		if( fabs(shootAngle) >= shootableAngle )
		{
			// 没有障碍物
			if( !IsObstacle( mWorldModel->mOppGoalCenter) )
			{
				// 返回最大的优先权
				//		比带球的最高优先权略低
				//		参见 SitDribble.cpp： DribbleWeight()
				return 9.0f;
			}
			else // 有障碍物阻挡
			{
				return 6.1f;	// 考虑传球,不能高于射门阈值
			}
		}
		else // 没有射门角度
		{
				return 2.1f;	// 考虑传球或带球，不能高于带球阈值
		}
	}
	else // 没有进入射门区域
	{
		return 6.0f * shootableRadius / shootDist; // 距离越远，权值越低
	}
}

float SitKick::PassWeight()
{
	const float passableRadius = 5.5f;		//waited to be tested
	const float agentMoveRadius = 2.0f;
	const float passRadiusEps = 2.0f;
	bool passble = false;

	vector<unsigned int> passToPlayerNum;   // 存储的是数组顺序，而非球员号码
	passToPlayerNum.resize( 4 );			// 球员数量，多出一个作为预留量

	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		if( mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos ) < passableRadius + agentMoveRadius 
			&& mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos ) > passableRadius - agentMoveRadius
			)
		{
			Ray passRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, mWorldModel->mBall.ThetaTo( mWorldModel->mOurTeamPlayer[i].mPos ) );
			Vector3f ballStopPos = passRay.GetPoint( passableRadius ); 

			if( mFieldSquare->IsInField( ballStopPos ) )
			{
				passble = true;
			}
		}

		passToPlayerNum.push_back( i );
	}
	
	// 所有队友都不在传球范围内
	if( !passble )
	{
		SitKickLog << "Pass Weight: " << "No Companion In Position " << endl;
		
		//float deltaSpeed = mAgentInfo->GetOppMaxSpeed() / mAgentInfo->GetOurMaxSpeed();

		//if( deltaSpeed > 1.2f )
		//{
		//	deltaSpeed = 1.2f;
		//}
	
		//float tempPassWeight = 5.0f / deltaSpeed;

		//if( tempPassWeight > 9.3f )
		//{
		//	tempPassWeight = 9.3f;
		//}
		float tempPassWeight = 4.8f;
		float diffStrendgh = 1.0f;
		
		if( mWorldModel->mOppStrength == OS_Strong )
		{
			diffStrendgh = 1.3f;
		}
		else if( mWorldModel->mOppStrength == OS_Weak )
		{
			diffStrendgh = 1.0f / 1.3f;
		}
		
		tempPassWeight /= diffStrendgh;

		return tempPassWeight;	
		// 考虑传球或带球
		//	自己比对方走的越快，越应该加强传球
	}
	
	// 判断可传球队员距离对方的最小距离
	const float passOppRadius = 1.0f;	// 传球点半径范围内不能有对方球员
	const float minPlayerShootAngle = 40.0f;
	
	passble = false;

	for( unsigned int i = 0; i < passToPlayerNum.size(); i ++ )
	{
		for( unsigned int j = 0; j < mWorldModel->mOppPlayerNumOnField; j ++ )
		{
			float miniDistToOpp = mWorldModel->mOurTeamPlayer[ passToPlayerNum.at(i) ].DistXyTo( mWorldModel->mOppTeamPlayer[j].mPos );

			// 如果是自己，就不要传了
			if( passToPlayerNum.at(i) == 0 )
			{
				continue;
			}
				
			// 如果队友旁边有人，也不能传
			if( miniDistToOpp < passOppRadius )
			{
				continue;
			}
	
			Angle angToOppGoalLeft = mWorldModel->mOurTeamPlayer[ passToPlayerNum.at(i) ].ThetaTo( mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos );
			Angle angToOppGoalRight = mWorldModel->mOurTeamPlayer[ passToPlayerNum.at(i) ].ThetaTo( mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos );
			Angle shootAngle = Normalize( angToOppGoalLeft - angToOppGoalRight );

			// 如果队友射门角度太小，还是不能传
			if( fabs(shootAngle) < minPlayerShootAngle )
			{
				continue;
			}
			else
			{
				passble = true;
			}
		}
	}

	if( passble )
	{
		SitKickLog << "Pass Weight: " << "Companion In Position " << endl;

		return 6.1f;
	}
	else
	{
		SitKickLog << "Pass Weight: " << "Default -- Don't Pass " << endl;

		return 2.3f;
	}
}





