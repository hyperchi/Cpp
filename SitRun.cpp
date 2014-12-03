#include "SitRun.h"
#define SitRunLog gLog<< "[sitRun] " 

SitRun::SitRun( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo )
{
	mWorldModel = wm;
	mFieldSquare = square;
	mAgentInfo = agentInfo;
}
SitRun::~SitRun()
{

}

Vector3f SitRun::AttackRunPos( AttDefkTrend attDefTrend )
{
	if( attDefTrend == ADT_FullAttack )
	{
		return FullAttackRunPos();
	}
	else if(  attDefTrend == ADT_TrendAttack )
	{
		return TrendAttackRunPos();
	}
	else if( attDefTrend == ADT_NormalAttack )
	{
		return NormalAttackRunPos();
	}
	else if( attDefTrend == ADT_NormalDefence )
	{
		return NormalDefenceRunPos();
	}
	else if( attDefTrend == ADT_TrendDefence )
	{
		return TrendDefenceRunPos();
	}
	else 
	{
		return FullDefenceRunPos();
	}
}

//******************************************************************
//	强进攻跑位
//		跑到队友可以传球的点
//******************************************************************
Vector3f SitRun::FullAttackRunPos()
{
	return NormalAttackRunPos();


	SitRunLog << "FullAttackRunPos" << endl;

	const float passDist = 5.5f;
	const float basicDeltaAngle = 30.0f;

	Angle basicAngle;
	Vector3f basicTarPos;

	Angle startAngle = Normalize(  ( mWorldModel->mOppGoalCenter - mWorldModel->mBall.mPos ).angTheta() );
	Ray basicRay_1 = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, startAngle + basicDeltaAngle );
	Ray basicRay_2 = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, startAngle -basicDeltaAngle );

	Vector3f basicTar_1 = basicRay_1.GetPoint( passDist );
	Vector3f basicTar_2 = basicRay_2.GetPoint( passDist );

	float minBasicDist_1 = mWorldModel->mSelf.DistXyTo( basicTar_1 );
	float minBasicDist_2 = mWorldModel->mSelf.DistXyTo( basicTar_2 );

	if( minBasicDist_1 <= minBasicDist_2 )
	{
		basicAngle = startAngle + basicDeltaAngle;
		basicTarPos = basicTar_1;
	}
	else
	{
		basicAngle = startAngle - basicDeltaAngle;
		basicTarPos = basicTar_2;
	}

	const float minDistObs = 1.0f;
	const Angle unitAngle = 2.0f;
	const Angle minShootAngle = 20.0f;

	float minDistToOppPlayer = 100.0f;
	float resultTarAngle;
	Vector3f resultTarPos;

	for( int i = 0; i < (int)40.0f / unitAngle; i ++ )
	{
		for( int j = 1; j > -2; j -= 2 )
		{
			Angle deltaAngle = unitAngle * j * i;

			Ray tempRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, basicAngle + deltaAngle );
			resultTarPos = tempRay.GetPoint( passDist );

			Angle tempAngToOppGoal = Normalize( ( mWorldModel->mOppGoalCenter - resultTarPos ).angTheta() );

			if( !mFieldSquare->IsInField( resultTarPos ) )
			{
				continue;
			}

			Angle angToOppGoalLeft = resultTarPos.angTheta2( mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos );
			Angle angToOppGoalRight = resultTarPos.angTheta2( mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos ); 
			Angle shootAngle = Normalize( angToOppGoalLeft - angToOppGoalRight );

			if( shootAngle < minShootAngle )
			{
				continue;
			}

			for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
			{
				float tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( basicTarPos );

				if( tempDist < minDistToOppPlayer )
				{
					minDistToOppPlayer = tempDist;
				}
			}	

			if( minDistToOppPlayer >= minDistObs )
			{
				SitRunLog << "Compute Run Pos Ready! " 
					<< " Dist To Ball: " << resultTarPos.distXY2( mWorldModel->mBall.mPos )
					<< " Angle to Ball: " << resultTarPos.angTheta2( mWorldModel->mBall.mPos )
					<< " Angle to Opp Goal " << resultTarPos.angTheta2( mWorldModel->mOppGoalCenter )
					<< endl;

				return resultTarPos;
			}
		}
	}

	//	计算不出合适的跑位点
	//		跑到离球门较近的区域
	//const float resultDist = 2.0f;
	float resultDist = mWorldModel->mBall.DistXyTo( mWorldModel->mOppGoalCenter ) / 2.0f;

	if( resultDist < 2.0f )
	{
		resultDist = 2.0f;
	}

	Ray resultTarRay_1 = Ray::MakeRayFromPositionAndAngle( mWorldModel->mOppGoalCenter, 135.0f );
	Ray resultTarRay_2 = Ray::MakeRayFromPositionAndAngle( mWorldModel->mOppGoalCenter, -135.0f );

	Vector3f resultTar_1 = resultTarRay_1.GetPoint( resultDist );
	Vector3f resultTar_2 = resultTarRay_2.GetPoint( resultDist );

	float resultDistToTar_1 = mWorldModel->mSelf.DistXyTo( resultTar_1 );
	float resultDistToTar_2 = mWorldModel->mSelf.DistXyTo( resultTar_2 );

	if( resultDistToTar_1 <= resultDistToTar_2 )
	{
		resultTarPos = resultTar_1;
	}
	else
	{
		resultTarPos = resultTar_2;
	}

	SitRunLog << "Goto Near Opp Goal " << resultTarPos.x << " " << resultTarPos.y << endl;

	return resultTarPos;
}

//******************************************************************
//	中进攻跑位
//		//平行跟随进攻队员
//		同 NormalAttackRunPos
//******************************************************************
Vector3f SitRun::TrendAttackRunPos()
{
	return NormalAttackRunPos();
	

	// 如果场上只有自己，则向球跑位
	//		正常情况下，如果场上只有自己，则会进入控球决策，不会进入这里
	//		只是防止代码的Bug，才这么写
	if( mWorldModel->mOurPlayerNumOnField == 1 )
	{
		return mWorldModel->mBall.mPos;
	}

	// 判断我方控球队员的位置
	float minDistToBall = 100.0f;
	unsigned int playerNum = 0;

	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		float distToBall = mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		if( distToBall < minDistToBall )
		{
			minDistToBall = distToBall;
			playerNum = i;
		}
	}

	const float paraDist = 1.0f;
	
	Angle angBallToOppGoal = Normalize( mWorldModel->mBall.ThetaTo( mWorldModel->mOppGoalCenter ) );
	Angle paraAng;

	if( angBallToOppGoal >= 0.0f )
	{
		paraAng = angBallToOppGoal + 90.0f;
	}
	else
	{
		paraAng = angBallToOppGoal - 90.0f;
	}

	Ray paraRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, paraAng );
	Vector3f runPos = paraRay.GetPoint( paraDist );

	SitRunLog << "TrendAttackRunPos: " << runPos.x << " " << runPos.y << endl;

	return runPos;
}

//******************************************************************
//	正常进攻跑位
//		跑位点为球的后面一定距离（followBallDist）
//******************************************************************
Vector3f SitRun::NormalAttackRunPos()
{
	SitRunLog << "NormalAttackRunPos" << endl;

	//const float followBallDist = 1.5f;
	//const float backBallDist = 0.5f;

	//Vector3f backBallPos = mWorldModel->mBall.mPos - ( mWorldModel->mOppGoalCenter - mWorldModel->mBall.mPos ).normalize( backBallDist );
	////Ray followBallRay = Ray::MakeRayFromPositionAndAngle( backBallPos, 180.0f );

	////Vector3f followBallPos = followBallRay.GetPoint( followBallDist );

	//Angle followBallAng = backBallPos.angTheta2( mWorldModel->mSelf.mPos );
	//Ray followBallRay = Ray::MakeRayFromPositionAndAngle( backBallPos, followBallAng );

	//Vector3f followBallPos = followBallRay.GetPoint( followBallDist );

	//return followBallPos;

	const float followBallDist = 1.5f;

	Vector3f posFollowBall;

	Angle angBallToSelf = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mSelf.mPos );
	Angle angSelfToBall = mWorldModel->mSelf.mPos.angTheta2( mWorldModel->mSelf.mPos );
	Angle angBallToOurGoal = Normalize( mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter ) );
	Angle angBallToOurGoalLeft = Normalize( angBallToOurGoal - 45.0f );
	Angle angBallToOurGoalRight = Normalize( angBallToOurGoal + 45.0f );

	Ray rayBallToSelf = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, angBallToSelf );
	Ray raySelfToBall = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, angSelfToBall );
	Ray rayBallToOurGoalLeft = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, angBallToOurGoalLeft );
	Ray rayBallToOurGoalRight = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, angBallToOurGoalRight );

	Vector3f followBallPos_1 = rayBallToSelf.GetPoint( followBallDist );
	Vector3f followBallPos_2 = raySelfToBall.GetPoint( followBallDist );
	Vector3f followBallPos_3 = rayBallToOurGoalLeft.GetPoint( followBallDist );
	Vector3f followBallPos_4 = rayBallToOurGoalRight.GetPoint( followBallDist );

	float distPos_1 = followBallPos_1.distXY2( mWorldModel->mOurGoalCenter );
	float distPos_2 = followBallPos_2.distXY2( mWorldModel->mOurGoalCenter );
	float distPos_3 = followBallPos_3.distXY2( mWorldModel->mOurGoalCenter );
	float distPos_4 = followBallPos_4.distXY2( mWorldModel->mOurGoalCenter );

	Vector3f basicFollowPos;

	if( distPos_1 <= distPos_2 )
	{
		basicFollowPos = distPos_1;
	}
	else
	{
		basicFollowPos = distPos_2;
	}

	const float ourPlayerCirRadius = 1.5f;
	float distBasicPos = basicFollowPos.distXY2( mWorldModel->mOurGoalCenter );

	if( distBasicPos <= distPos_3 && distBasicPos <= distPos_4 )
	{
		posFollowBall = basicFollowPos;
	}
	else if( distPos_3 < distBasicPos && distPos_3 <= distPos_4 )
	{
		posFollowBall = followBallPos_3;
	}
	else
	{
		posFollowBall = followBallPos_4;
	}
	
	return posFollowBall;
}

//******************************************************************
//	强防守跑位
//		不顾一切向球点跑
//******************************************************************
Vector3f SitRun::FullDefenceRunPos()
{
	const float gotoControlBallRaidus = 1.5f;
	const float controlBallRadius = 1.0f;
	const float outsideBallDist = 1.5f;

	const Vector3f basicDefPosMiddle( -( mWorldModel->mFieldLength / 2.0f - mWorldModel->mPenaltyLength ), 0.0f, 0.0f );
	const Vector3f basicDefPosLeft( -( mWorldModel->mFieldLength / 2.0f - mWorldModel->mPenaltyLength ), mWorldModel->mPenaltyWidth / 2.0f , 0.0f ); 
	const Vector3f basicDefPosRight( -( mWorldModel->mFieldLength / 2.0f - mWorldModel->mPenaltyLength ), -mWorldModel->mPenaltyWidth / 2.0f , 0.0f ); 

	float distBallToOurGoal = mWorldModel->mBall.DistXyTo( mWorldModel->mOurGoalCenter );

	Vector3f runPos;

	float myDistToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

	if( mWorldModel->mBall.mPos.x < mWorldModel->mSelf.mPos.x )
	{
		SitRunLog << "FullDefenceRunPos: " << "球在我的后面" << endl;

		if( mWorldModel->mBall.mPos.x > mWorldModel->mPenaltyLength * 1.5f )
		{
			if( mWorldModel->mBall.mPos.y > mWorldModel->mPenaltyWidth / 2.0f )
			{
				runPos = basicDefPosLeft;
			}
			else if( mWorldModel->mBall.mPos.y < -mWorldModel->mPenaltyWidth / 2.0f )
			{
				runPos = basicDefPosRight;
			}
			else
			{
				runPos = basicDefPosMiddle;
			}
		}
		else
		{
			Angle runPosAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter );
			Ray runPosRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, runPosAngle );

			runPos = runPosRay.GetPoint( controlBallRadius );
		}
	}
	else if( myDistToBall <= gotoControlBallRaidus )
	{
		SitRunLog << "FullDefenceRunPos: " << "我靠近球" << endl;

		//Angle runPosAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter );

		Angle tempBisect  = mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos) + 
			0.5 * Normalize(mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos)
			- mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos));
	
		Ray runPosRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, tempBisect );

		runPos = runPosRay.GetPoint( distBallToOurGoal * 0.4f );
	}
	else
	{
		SitRunLog << "FullDefenceRunPos: " << "我远离球" << endl;

		//Angle runPosAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter );
		
		Angle tempBisect  = mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos) + 
			0.5 * Normalize(mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos)
			- mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos));

		Ray runPosRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, tempBisect );

		runPos = runPosRay.GetPoint( distBallToOurGoal * 0.5f );
	}

	const float minDistToDefPos = 1.5f;
	const float minDefRadius = 1.0f;

	if( mWorldModel->mSelf.DistXyTo( runPos ) <= minDistToDefPos )
	{
		//Angle tempBisect  = mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos) + 
		//	0.5 * (mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos)
		//	- mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos));


		//Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, tempBisect );

		//Vector3f defencePos = defenceRay.GetPoint( minDefRadius );
		float minOppDistToOurGoal = 100.0f;
		Vector3f minOppPosToOurGoal(100.0f,100.0f,0.0f);

		for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
		{
			float tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mOurGoalCenter );

			if( tempDist < minOppDistToOurGoal )
			{
				minOppDistToOurGoal = tempDist;
				minOppPosToOurGoal = mWorldModel->mOppTeamPlayer[i].mPos;
			}
		}

		runPos = minOppPosToOurGoal;
		//runPos = defencePos;
	}

	SitRunLog << "FullDefenceRunPos: " 
			  << "MyDistToBall: " << myDistToBall << " "
			  << "RunPos: " << runPos.x << " " << runPos.y
			  << endl;

	return runPos;	
}

//******************************************************************
//	中防守跑位
//		跑到球门与球连线的防守半径上
//******************************************************************
Vector3f SitRun::TrendDefenceRunPos()
{
	const float nearBallDist = 1.0f;
	const float defenceRadius = mWorldModel->mFieldLength / 12.0f;
	
	const Vector3f basicDefPosMiddle( -( mWorldModel->mFieldLength / 2.0f - mWorldModel->mPenaltyLength ), 0.0f, 0.0f );
	const Vector3f basicDefPosLeft( -( mWorldModel->mFieldLength / 2.0f - mWorldModel->mPenaltyLength ), mWorldModel->mPenaltyWidth / 2.0f , 0.0f ); 
	const Vector3f basicDefPosRight( -( mWorldModel->mFieldLength / 2.0f - mWorldModel->mPenaltyLength ), -mWorldModel->mPenaltyWidth / 2.0f , 0.0f ); 

	Vector3f runPos;

	float distBallToOurGoal = mWorldModel->mBall.DistXyTo( mWorldModel->mOurGoalCenter );

	float myDistToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );
	float myDistToOurGoal = mWorldModel->mSelf.DistXyTo( mWorldModel->mOurGoalCenter );

	if( mWorldModel->mBall.mPos.x < mWorldModel->mSelf.mPos.x )
	{
		SitRunLog << "TrendDefenceRunPos: " << "球在我的后面" << endl;

		if( mWorldModel->mBall.mPos.x > mWorldModel->mPenaltyLength * 1.5f )
		{
			if( mWorldModel->mBall.mPos.y > mWorldModel->mPenaltyWidth / 2.0f )
			{
				runPos = basicDefPosLeft;
			}
			else if( mWorldModel->mBall.mPos.y < -mWorldModel->mPenaltyWidth / 2.0f )
			{
				runPos = basicDefPosRight;
			}
			else
			{
				runPos = basicDefPosMiddle;
			}
		}
		else
		{
			Angle runPosAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter );
			Ray runPosRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, runPosAngle );

			runPos = runPosRay.GetPoint( nearBallDist );
		}
	}
	else if( myDistToOurGoal <= defenceRadius )
	{
		SitRunLog << "TrendDefenceRunPos: " << "我靠近球" << endl;

		//Angle defenceAng = mWorldModel->mOurGoalCenter.angTheta2( mWorldModel->mBall.mPos );

		Angle tempBisect  = mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos) + 
			0.5 * Normalize(mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos)
			- mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos));

		Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, tempBisect );
		
		Vector3f defencePos = defenceRay.GetPoint( distBallToOurGoal * 0.3f );	
		
		runPos = defencePos;
	}
	else
	{
		SitRunLog << "TrendDefenceRunPos: " << "我远离球" << endl;

		//Angle defenceAng = mWorldModel->mOurGoalCenter.angTheta2( mWorldModel->mBall.mPos );
		
		Angle tempBisect = mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos) + 
			0.5 * Normalize(mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos)
			- mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos));

		
		Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, tempBisect );
		
		Vector3f defencePos = defenceRay.GetPoint( distBallToOurGoal * 0.4f );

		runPos = defencePos;
	}
	
	const float minDistToDefPos = 1.5f;
	const float minDefRadius = 1.0f;

	if( mWorldModel->mSelf.DistXyTo( runPos ) <= minDistToDefPos )
	{
		SitRunLog << "In Defence Position" << endl;

		//Angle tempBisect  = mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos) + 
		//	0.5 * (mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos)
		//	- mWorldModel->mBall.mPos.angTheta2(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos));


		//Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, tempBisect );

		//Vector3f defencePos = defenceRay.GetPoint( minDefRadius );
		float minOppDistToOurGoal = 100.0f;
		Vector3f minOppPosToOurGoal(100.0f,100.0f,0.0f);

		for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
		{
			float tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mOurGoalCenter );

			if( tempDist < minOppDistToOurGoal )
			{
				minOppDistToOurGoal = tempDist;
				minOppPosToOurGoal = mWorldModel->mOppTeamPlayer[i].mPos;
			}
		}

		runPos = minOppPosToOurGoal;
		//runPos = defencePos;
	}

	SitRunLog << "TrendDefenceRunPos: " << runPos.x << " " << runPos.y << endl;

	return runPos;
}

//******************************************************************
//	正常防守跑位
//		盯住对方前锋
//******************************************************************
Vector3f SitRun::NormalDefenceRunPos()
{
	float minOppDistToOurGoal = 100.0f;
	Vector3f mostNearOurGoalPos;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		float tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mOurGoalCenter );

		if( tempDist < minOppDistToOurGoal )
		{
			minOppDistToOurGoal = tempDist;
			mostNearOurGoalPos = mWorldModel->mOppTeamPlayer[i].mPos;
		}
	}

	Vector3f runPos;

	const float oppInBallControlRadius = 1.0f;
	float defenceRadius =  mWorldModel->mFieldLength * 0.3f;
	
	// 对方没有对我方形成威胁
	if( minOppDistToOurGoal > mWorldModel->mFieldLength * 0.45f )
	{
		SitRunLog << "NormalDefenceRunPos " << "对方没有对我方形成威胁" << endl;

		//Angle defenceAng = mWorldModel->mOurGoalCenter.angTheta2( mWorldModel->mBall.mPos );
		//Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mOurGoalCenter, 0.0f );
		
		//runPos = defenceRay.GetPoint( defenceRadius );
		runPos = NormalAttackRunPos();
	}
	else
	{
		float oppDistToBall = mostNearOurGoalPos.distXY2( mWorldModel->mBall.mPos );

		// 对方没有控球
		if( oppDistToBall > oppInBallControlRadius )
		{
			SitRunLog << "NormalDefenceRunPos " << "对方没有控球" << endl;

			Angle defenceAng = mWorldModel->mOurGoalCenter.angTheta2( mostNearOurGoalPos );
			Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mOurGoalCenter, defenceAng );
			Vector3f defencePos = defenceRay.GetPoint( minOppDistToOurGoal * 0.7f );

			runPos = defencePos;
		}
		else
		{
			SitRunLog << "NormalDefenceRunPos " << "对方控球" << endl;

			Angle defenceAng = mWorldModel->mOurGoalCenter.angTheta2( mostNearOurGoalPos );
			Ray defenceRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mOurGoalCenter, defenceAng );
			Vector3f defencePos = defenceRay.GetPoint( minOppDistToOurGoal * 0.5f );

			runPos = defencePos;
		}
	}

	SitRunLog << "NormalDefenceRunPos " 
			  << " MinOppDistToOurGoal: " << minOppDistToOurGoal 
			  << " MostNearOurGoalPos: " << mostNearOurGoalPos.x << " " << mostNearOurGoalPos.y
			  << " RunPos: " << runPos.x << " " << runPos.y
			  << endl;

	return runPos;
}
