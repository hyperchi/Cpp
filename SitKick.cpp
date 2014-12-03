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
	
	// ������������򣬱�������С
	Vector3f oppGoalLeftKickTo;		
	Vector3f oppGoalRightKickTo;
	oppGoalLeftKickTo.x = mWorldModel->mFieldLength / 2.0f;
	oppGoalLeftKickTo.y = mWorldModel->mGoalWidth / 2.2f;		//��������С
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

	// ��������·�� ����Ҫ�ܿ��ϰ��
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

	// û�п�����·��
	return ultimateTarget;
}

//*******************************************************************
//	�ж����Ž�����(���������)
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

	// ��������·��ʱ��ֻҪ����û��ˤ�����Ͳ�������Ϊ�ϰ���
	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		// ���ĸ߶ȣ�0.17f  wait to be tested
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

	// ������������
	if( shootDist <= shootableRadius )		
	{
		// �������ŽǶ�
		if( fabs(shootAngle) >= shootableAngle )
		{
			// û���ϰ���
			if( !IsObstacle( mWorldModel->mOppGoalCenter) )
			{
				// ������������Ȩ
				//		�ȴ�����������Ȩ�Ե�
				//		�μ� SitDribble.cpp�� DribbleWeight()
				return 9.0f;
			}
			else // ���ϰ����赲
			{
				return 6.1f;	// ���Ǵ���,���ܸ���������ֵ
			}
		}
		else // û�����ŽǶ�
		{
				return 2.1f;	// ���Ǵ������򣬲��ܸ��ڴ�����ֵ
		}
	}
	else // û�н�����������
	{
		return 6.0f * shootableRadius / shootDist; // ����ԽԶ��ȨֵԽ��
	}
}

float SitKick::PassWeight()
{
	const float passableRadius = 5.5f;		//waited to be tested
	const float agentMoveRadius = 2.0f;
	const float passRadiusEps = 2.0f;
	bool passble = false;

	vector<unsigned int> passToPlayerNum;   // �洢��������˳�򣬶�����Ա����
	passToPlayerNum.resize( 4 );			// ��Ա���������һ����ΪԤ����

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
	
	// ���ж��Ѷ����ڴ���Χ��
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
		// ���Ǵ�������
		//	�Լ��ȶԷ��ߵ�Խ�죬ԽӦ�ü�ǿ����
	}
	
	// �жϿɴ����Ա����Է�����С����
	const float passOppRadius = 1.0f;	// �����뾶��Χ�ڲ����жԷ���Ա
	const float minPlayerShootAngle = 40.0f;
	
	passble = false;

	for( unsigned int i = 0; i < passToPlayerNum.size(); i ++ )
	{
		for( unsigned int j = 0; j < mWorldModel->mOppPlayerNumOnField; j ++ )
		{
			float miniDistToOpp = mWorldModel->mOurTeamPlayer[ passToPlayerNum.at(i) ].DistXyTo( mWorldModel->mOppTeamPlayer[j].mPos );

			// ������Լ����Ͳ�Ҫ����
			if( passToPlayerNum.at(i) == 0 )
			{
				continue;
			}
				
			// ��������Ա����ˣ�Ҳ���ܴ�
			if( miniDistToOpp < passOppRadius )
			{
				continue;
			}
	
			Angle angToOppGoalLeft = mWorldModel->mOurTeamPlayer[ passToPlayerNum.at(i) ].ThetaTo( mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos );
			Angle angToOppGoalRight = mWorldModel->mOurTeamPlayer[ passToPlayerNum.at(i) ].ThetaTo( mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos );
			Angle shootAngle = Normalize( angToOppGoalLeft - angToOppGoalRight );

			// ����������ŽǶ�̫С�����ǲ��ܴ�
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





