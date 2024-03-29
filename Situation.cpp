#include "Situation.h"

#define SitLog gLog<< "[sition] " 
#define ProcessingLog gProcessingLog<<"[Motin] "

Situation::Situation( WorldModel *wm, Formation *formation  )
{
	mWorldModel = wm;
	mFormation = formation;

	mAgentInfo = new AgentInfo( mWorldModel );

	mFieldSquare = new FieldSquare( mWorldModel );
	mSitDribble = new SitDribble( mWorldModel, mFieldSquare, mAgentInfo );
	mSitKick = new SitKick( mWorldModel, mFieldSquare, mAgentInfo );
	mSitPass = new SitPass( mWorldModel, mFieldSquare, mAgentInfo );
	mSitRun = new SitRun( mWorldModel, mFieldSquare, mAgentInfo );

	mCoach = Coach::GetInstance( mWorldModel );

	mOurControlBallCycle = 0;
	mOppControlBallCycle = 0;
}
Situation::~Situation()
{
	if( mAgentInfo ) 
	{
		delete mAgentInfo;
		mAgentInfo = NULL;
	}
	if( mFieldSquare ) 
	{
		delete mFieldSquare;
		mFieldSquare = NULL;
	}
	if( mSitDribble ) 
	{
		delete mSitDribble;
		mSitDribble = NULL;
	}
	if( mSitKick ) 
	{
		delete mSitKick;
		mSitKick = NULL;
	}
	if( mSitPass ) 
	{
		delete mSitPass;
		mSitPass = NULL;
	}
	if( mSitRun ) 
	{
		delete mSitRun;
		mSitRun = NULL;
	}
}

//*******************************************************************
//	更新Situation
//*******************************************************************
void Situation::Update()
{
	static unsigned int statisticsTime = 0;

	//	因为比赛模式切换到 PM_PLAY_ON 后，机器人会被 Beam 回自己的半场，
	//		所以要等待一段周期再更新 AgentInfo
	if( mWorldModel->mPlayMode == PM_PLAY_ON )
	{
		if( statisticsTime > 10 )
		{
			mAgentInfo->Update();
		}

		if( WeControlBall() )
		{
			mOurControlBallCycle ++;
		}
		else
		{
			mOppControlBallCycle ++;
		}

		statisticsTime ++;
	}
	else
	{
		statisticsTime = 0;
	}


	//SitLog << "OurControlBallCycle: " << mOurControlBallCycle << " "
	//	   << "OppControlBallCycle: " << mOppControlBallCycle << endl;
}


float Situation::DistMostNearOurGoal()
{
	float tempDist = 0.0f;
	float minDist = 1000.0f;
	
	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mOurGoalCenter );
			
		if( tempDist < minDist )
		{
			minDist = tempDist;
		}
	}

	//SitLog << "Opp MostNearOurGoal " << minDist << endl;

	return minDist;
}
//*******************************************************************
// 判断对方哪个队员距离球最近
//*******************************************************************
void Situation::OppDistMostNearBall( float &minDist, unsigned int &playerNum )
{
	float tempDist = 0.0f;
	float oppMinDist = 100.0f;
	unsigned int oppMinNearPlayerNum = 0;


	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		if( tempDist < oppMinDist )
		{
			oppMinDist = tempDist;
			oppMinNearPlayerNum = mWorldModel->mOppTeamPlayer[i].mMyPlayerNo;
		}
	}

	minDist = oppMinDist;
	playerNum = oppMinNearPlayerNum;

	//SitLog << "oppMinDist " << oppMinDist << " playerNum " << playerNum << endl;
}
//*******************************************************************
// 判断对方哪个队员距离我方球门最近
//*******************************************************************
void Situation::OppDistMostNearOurGoal( float &minDist, unsigned int &playerNum )
{
	float tempDist = 0.0f;
	float oppMinDist = 100.0f;
	unsigned int oppMinNearPlayerNum = 0;


	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mOurGoalCenter );

		if( tempDist < oppMinDist )
		{
			oppMinDist = tempDist;
			oppMinNearPlayerNum = mWorldModel->mOppTeamPlayer[i].mMyPlayerNo;
		}
	}

	minDist = oppMinDist;
	playerNum = oppMinNearPlayerNum;

}

//*******************************************************************
// 判断我方哪个队员距离球最近//已经不能用了
//*******************************************************************
void Situation::OurDistMostNearBall( float &minDist, unsigned int &playerNum )
{
	const float basicProportion = 3.0f;

	float tempDist = 0.0f;
	float ourMinDist = 100.0f;
	
	unsigned int ourMinNearPlayerNum = 0;

	for( unsigned int i = 0; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		if( mWorldModel->mOurTeamPlayer[i].mPos.z < 0.25f )
		{
			continue;
		}

		tempDist = mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		Angle basicAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOppGoalCenter );
		Angle ballToPlayer = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurTeamPlayer[i].mPos );

		if( fabs(ballToPlayer - basicAngle) < 50.0f )
		{
			tempDist *= basicProportion;
		}
		else
		{
			tempDist *= -1.0f * (basicProportion - 1.0f) / 180.0f * fabs(ballToPlayer - basicAngle) + 3.0f;
		}

		if( tempDist < ourMinDist )
		{
			ourMinDist = tempDist;
			ourMinNearPlayerNum = mWorldModel->mOurTeamPlayer[i].mMyPlayerNo;
		}
	}

	minDist = ourMinDist;
	playerNum = ourMinNearPlayerNum;

	//SitLog << "ourMinDist " << ourMinDist << " playerNum " << playerNum << endl;
}

//*******************************************************************
// 判断我方哪个队员（除自己）距离球最近
//*******************************************************************
void Situation::OurOtherDistMostNearBall( float &minDist, unsigned int &playerNum )
{
	float behindBallTimeProportion = 3.0f;
	const float basicProportion = 3.0f;

	float tempDist = 0.0f;
	float ourMinDist = 100.0f;

	unsigned int ourMinNearPlayerNum = 0;

	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		if( mWorldModel->mOurTeamPlayer[i].mPos.z < 0.25f )
		{
			continue;
		}

		tempDist = mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		Angle basicAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOppGoalCenter );
		Angle ballToPlayer = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurTeamPlayer[i].mPos );

		if( fabs(ballToPlayer - basicAngle) < 50.0f )
		{
			tempDist *= basicProportion;
		}
		else
		{
			tempDist *= -1.0f * (basicProportion - 1.0f) / 180.0f * fabs(ballToPlayer - basicAngle) + 3.0f;
		}

		if( tempDist < ourMinDist )
		{
			ourMinDist = tempDist;
			ourMinNearPlayerNum = mWorldModel->mOurTeamPlayer[i].mMyPlayerNo;
		}
	}

	minDist = ourMinDist;
	playerNum = ourMinNearPlayerNum;

	//SitLog << "ourOtherMinDist " << ourMinDist << " playerNum " << playerNum << endl;
}

//*******************************************************************
// 判断当前是否我方控球
//
//		判断依据：自己与对方距离球的距离和双方速度的比较
//*******************************************************************
bool Situation::WeControlBall()
{
	const float minControlRadius = 0.5f;

	float ourMinDistToBall;
	float oppMinDistToBall;
	unsigned int ourPlayerMinToBall;
	unsigned int oppPlayerMinToBall;

	OurDistMostNearBall( ourMinDistToBall, ourPlayerMinToBall );
	OppDistMostNearBall( oppMinDistToBall, oppPlayerMinToBall );

	if( ourMinDistToBall <= minControlRadius )
	{
		//SitLog << "We Control Ball" << " -- Very Near "<< endl;
		
		return true;
	}
	else if( oppMinDistToBall <= ourMinDistToBall * 0.5f )
	{
		//SitLog << "We don't Control Ball" << " -- Farther" << endl;

		return false;
	}
	else if( ourMinDistToBall <= oppMinDistToBall * 0.5f )
	{
		//SitLog << "We Control Ball " << " -- Nearer" << endl;

		return true;
	}

		else
		{
			//SitLog << "We don't Control Ball" << " -- Weaker" << endl;

			return false;
		}
	
	//else if( ( ourMinDistToBall / mAgentInfo->GetOurMaxSpeed()  ) 
	//	<= (oppMinDistToBall /mAgentInfo->GetOppMaxSpeed()) )
	//{
	//	SitLog << "We Control Ball" << " -- Faster "<< endl;
	//	
	//	return true;
	//}
	//else
	//{
	//	SitLog << "We don't ControlBall" << " -- Slower " << endl;

	//	return false;
	//}
}

//*******************************************************************
// 判断自己是否应该上前控球
//*******************************************************************
bool Situation::IShouldGotoControlBall()
{
	const float myGotoTimeProportion = 1.3f;
	const float otherGotoTimeProportion = 1.5f;
	const float gotoControlBallEps = 0.5f;
	const float minControlBallEps = 0.4f;
	const float nearBallEps = 0.2f;

	float ourMinDistToBall;
	unsigned int ourPlayerMinToBall;

	float ourOtherMinDistToBall;
	unsigned int ourOtherPlayerMInToBall;
	
	float myDistToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

	OurDistMostNearBall( ourMinDistToBall, ourPlayerMinToBall );
	OurOtherDistMostNearBall( ourOtherMinDistToBall, ourOtherPlayerMInToBall );

	//SitLog << "myDistToBall " << myDistToBall << " " 
	//	   << "ourDistMostNearBall " << ourMinDistToBall << " No.: " << ourPlayerMinToBall << " "
	//	   << "ourOtherMinDistToBall " << ourOtherMinDistToBall << " No.: " << ourOtherPlayerMInToBall << " "
	//	   << endl;

	if( myDistToBall <= minControlBallEps 
		&& ourOtherMinDistToBall <= minControlBallEps
		)
	{
		if( mFormation->GetMyRole() > mFormation->GetRole(ourOtherPlayerMInToBall) )
		{
			//SitLog << "I Should Goto Control Ball" << " -- Nearer and Higher Priority " <<endl;

			return true;
		}
		else
		{
			//SitLog << "I Should Not Goto Control Ball" << " -- Nearer but Lower Priority " <<endl;

			return false;
		}
	}

	//if( myDistToBall <= minControlBallEps )
	//{
	//	SitLog << "I Should Goto Control Ball" << " -- I'm Very Near Ball " <<endl;

	//	return true;
	//}

	//if( ourOtherMinDistToBall <= minControlBallEps )
	//{
	//	SitLog << "I Should Not Goto Control Ball" << " -- Company Very Near Ball " <<endl;

	//	return false;
	//}

	// 当自己和队友都离球比较近时，根据角色（前锋或后卫等）判断是否应该上前控球
	if( fabs(myDistToBall - ourOtherMinDistToBall) <= gotoControlBallEps )
	{
		if( mFormation->GetMyRole() > mFormation->GetRole(ourOtherPlayerMInToBall) )
		{
			//SitLog << "I Should Goto Control Ball" << " -- Higher Priority " <<endl;

			return true;
		}
		else
		{
			//SitLog << "I Should Not Goto Control Ball" << " -- Lower Priority " <<endl;

			return false;
		}
	}
	
	// 自己是距离球最近的队员，则前去控球
	if( ourPlayerMinToBall == mWorldModel->mMyPlayerNo )
	{
		//SitLog << "I Should Goto Control Ball" << " -- Nearer " <<endl;

		return true;
	}
	//// 情况2：自己距离球比较远，考虑队友是否在球的前方，
	//// 如果队友在前方，转身回来控球势必用时较久，故需加入权重

	//if( mWorldModel->mSelf.mPos.x > mWorldModel->mBall.mPos.x )
	//{
	//	myDistToBall = myDistToBall * myGotoTimeProportion;
	//}

	//for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	//{
	//	float tempDist = mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );
	//	
	//	if( mWorldModel->mOurTeamPlayer[i].mPos.x > mWorldModel->mBall.mPos.x )
	//	{
	//		tempDist = tempDist * otherGotoTimeProportion;
	//	}

	//	if( tempDist < myDistToBall )
	//	{
	//		SitLog << "I Should Not Goto Control Ball" << endl;
	//		
	//		return false;
	//	}
	//}
	//
	//SitLog << "I Should Goto Control Ball" << " -- Default " <<endl;

	//return true;

	SitLog << "I Should Not Goto Control Ball " << " -- Default " << endl;

	return false;
}	
bool Situation::ShouldAttack()
{
	return true;
}

Vector3f Situation::InterceptPos()
{
	const float ballExceedMeDist = 1.5f;	
	const float distBeforeBallDist = 0.17f;
	const Vector3f basicInterceptPos( -mWorldModel->mFieldLength  / 2.0f * 11.0f/12.0f, 0.0f, 0.0f );

	Vector3f tarPosBeforeBall = mWorldModel->mBall.mPos - ( mWorldModel->mOppGoalCenter - mWorldModel->mBall.mPos ).normalize( distBeforeBallDist );
	
	float oppMinDistToBall = 100.0f;

	for( unsigned int i = 0; i < mWorldModel->mOppPlayerNumOnField; i ++ )
	{
		float tempDist = mWorldModel->mOppTeamPlayer[i].DistXyTo( mWorldModel->mSelf.mPos );

		if( tempDist < oppMinDistToBall )
		{
			oppMinDistToBall = tempDist;
		}
	}

	float selfDistToBall = mWorldModel->mSelf.DistXyTo( tarPosBeforeBall );

	if( selfDistToBall <= oppMinDistToBall )
	{
		return tarPosBeforeBall;
	}

	// 如果球在中前场
	if( mWorldModel->mBall.mPos.x > mWorldModel->mFieldLength / 4.0f )
	{
		// 自己没有控球
		if( mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos ) >= ballExceedMeDist )
		{
			Angle ballToOurGoalAng = InNormalize( mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter ) );
			Angle basicRelaAngLeft = InNormalize( ballToOurGoalAng - 30.0f );
			Angle basicRelaAngRight = InNormalize( ballToOurGoalAng + 30.0f );
			Angle ballToSelfAng = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mSelf.mPos );

			Angle diffAngle = InNormalize( basicRelaAngRight - basicRelaAngLeft );
			Angle diffAngleToSelf = InNormalize( basicRelaAngRight - ballToSelfAng );

			//SitLog<< "InterceptPos: " << ballToOurGoalAng << " "
			//	  << basicRelaAngLeft << " "
			//	  << basicRelaAngRight << " "
			//	  << ballToSelfAng 
			//	  << endl;

			if( mWorldModel->mSelf.mPos.x < mWorldModel->mBall.mPos.x - 2.0f )
			{
				return tarPosBeforeBall;
			}

			// 球在我的相对后面
			if( diffAngleToSelf > diffAngle )
			{
				//SitLog<< "InterceptPos: " << "Basic Intercept Pos " << endl;

				return basicInterceptPos;
			}
			else
			{
				//SitLog<< "InterceptPos: " << "Goto Ball Pos " << endl;

				return tarPosBeforeBall;
			}
		}
		else
		{
			//SitLog<< "InterceptPos: " << "I Goto Ball " << endl;

			return tarPosBeforeBall;
		}
	}
	else
	{
		Angle ballToOurGoalAng = InNormalize( mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter ) );
		Ray ballToOurGoalRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mBall.mPos, ballToOurGoalAng );
		Vector3f basicDefencePos = ballToOurGoalRay.GetPoint( ballExceedMeDist );
		float distBallToOurGoal = mWorldModel->mBall.DistXyTo( mWorldModel->mOurGoalCenter );

		if( distBallToOurGoal <= ballExceedMeDist )
		{
			//SitLog<< "InterceptPos: " << "Ball Near Our Goal" << endl;
			Vector3f blockPos = mWorldModel->mBall.mPos - ( mWorldModel->mBall.mPos - mWorldModel->mOurGoalCenter ).normalize( 0.1f );

			basicDefencePos = blockPos;
		}
		
		//if( mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos ) >= ballExceedMeDist )
		//{
		//{	
			//Angle ballToOurGoalAng = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurGoalCenter );
			Angle basicRelaAngLeft = InNormalize( ballToOurGoalAng - 25.0f );
			Angle basicRelaAngRight = InNormalize( ballToOurGoalAng + 25.0f );
			Angle ballToSelfAng = InNormalize( mWorldModel->mBall.mPos.angTheta2( mWorldModel->mSelf.mPos ) );

			Angle diffAngle = InNormalize( basicRelaAngRight - basicRelaAngLeft );
			Angle diffAngleToSelf = InNormalize( basicRelaAngRight - ballToSelfAng );

			//SitLog<< "InterceptPos: " << ballToOurGoalAng << " "
			//	<< basicRelaAngLeft << " "
			//	<< basicRelaAngRight << " "
			//	<< ballToSelfAng 
			//	<< endl;

			// 球在我的相对后面
			if( diffAngleToSelf > diffAngle )
			{
				SitLog<< "InterceptPos: " << "Defence " << "Basic Defence Pos " << endl;

				return basicDefencePos;
			}
			else
			{
				SitLog<< "InterceptPos: " << "Defence " << "Goto Ball Pos " << endl;

				return tarPosBeforeBall;
			}

		//}
		//}
		//else
		//{
		//	SitLog<< "InterceptPos: " << "Defence " << "I Goto Ball " << endl;

		//	return tarPosBeforeBall;
		//}
	}
}

//*******************************************************************
//	根据场上形势：
//			控球方
//			球的位置
//			自己位置
//			双方移动速度和控球时间对比
//			比赛模式和比赛时间
//			比分差距
//
//	判断进攻权重
//
//	
//	评判标准：
//			设定 attackWeight = 0.0f --- 60.0f
//			权值		进攻等级	防守等级	函数返回值
//		0.0f  --- 10.0f				  +++		ADT_FullDefence	
//		10.0f --- 20.0f				  ++		ADT_TrendDefence	
//		20.0f --- 30.0f				  +			ADT_Defence	
//		30.0f --- 40.0f	   +					ADT_Attack	
//		40.0f --- 50.0f	   ++					ADT_TrendAttack	
//		50.0f --- 60.0f    +++					ADT_FullAttack
//			
//	评判依据：
//
//			我方控球 ---	进攻 +	防守 -
//			对方控球 ---	防守 +	防守 -
//
//			领先比分数	进攻	防守
//			  0			 O		 O
//			  1			 O		 O
//			 >=2		 +		 -
//			  -1		 +		 -
//			 <=-2		 -		 +	
//*******************************************************************		
AttDefkTrend Situation::AttackWeight()
{
	//return ADT_FullAttack; 
	//return ADT_NormalAttack;
	//return ADT_TrendAttack;
	//return ADT_FullDefence;
	//return ADT_TrendDefence;
	//return ADT_NormalDefence;
	const float totleGameTime = 480.0f;
	const float basicAttackWeight = 30.0f;
	float attackWeight = basicAttackWeight;

	unsigned int ourNearerPlayerNum = OurNearPlayerToBall();

	float ourMinDistToBall;
	unsigned int ourPlayerMinToBall;

	OurDistMostNearBall( ourMinDistToBall, ourPlayerMinToBall );

	if( mFormation->GetRole( ourPlayerMinToBall ) == PR_Goalie )
	{
		return ADT_NormalDefence;
	}

	if( ourNearerPlayerNum == 0 )
	{
		SitLog << "AttackWeight " << "Strange! " << "-- I'm the nearest player " << "-- I'm in front of the ball? " << endl;
		SitLog << "My X: " << mWorldModel->mSelf.mPos.x << " Ball X: " << mWorldModel->mBall.mPos.x << endl;

		// 加强进攻
		attackWeight += 5.0f;
	}
	else if( ourNearerPlayerNum == 1 )
	{
		SitLog << "AttackWeight " << "Second Nearer! " << "-- Protect Ball" << endl; 
	
		// 不改变 attackWeight
	}
	else if( ourNearerPlayerNum == 2 )
	{
		SitLog << "AttackWeight " << "Third Nearer! " << "-- Defense Backyard! " << endl;

		// 加强防守
		attackWeight -= 10.0f;
	}
	else if( ourNearerPlayerNum == 3 )
	{
		SitLog << "AttackWeight " << "Forth Nearer! " << "-- Too Front / Back " << endl;

		// 加强防守
		attackWeight -= 20.0f;
	}
	else
	{
		SitLog << "AttackWeight " << " Error! " << " Code Error In Situation::AttackWeight() " << "-- Our Player Num > 4" << endl;
	}


	float gameTime = mWorldModel->mGameTime;
	int scoreLead = mWorldModel->mOurScore - mWorldModel->mOppScore;

	SitLog << "Our Score: " << mWorldModel->mOurScore
		   << " Opp Score: " << mWorldModel->mOppScore
		   << " Score Lead: " << scoreLead << endl;
	
	if( WeControlBall() )
	{
		attackWeight += 5.0f;
	}
	else
	{
		attackWeight -= 15.0f;
	}

	float distBallToOurGoal = mWorldModel->mBall.DistXyTo( mWorldModel->mOurGoalCenter );
	float halfFieldLength = mWorldModel->mFieldLength * 0.5f;
	float distBallFactor = ( ( basicAttackWeight / halfFieldLength ) * distBallToOurGoal - basicAttackWeight ) * 0.5f;

	if( distBallFactor > 0.0f )
	{
		distBallFactor = 0.0f;
	}

	attackWeight += distBallFactor;

	SitLog << "DistBallToOurGoal: " << distBallToOurGoal << " DistBallFactor: " << distBallFactor << endl;

	if( mWorldModel->mOppStrength == OS_Strong )
	{
		attackWeight /= 1.5f;
	}
	else if( mWorldModel->mOppStrength == OS_Weak )
	{
		attackWeight *= 1.5f;
	}

	if( mWorldModel->mBall.mPos.x < -mWorldModel->mFieldLength / 6.0f )
	{
		attackWeight -= 20.0f;
	}

	if( scoreLead == 0
		|| scoreLead == 1 
		|| scoreLead == 2 )
	{
		// Do Nothing
	}
	else if( scoreLead >= 3)
	{
		attackWeight *= 1.5f;
	}
	else if( scoreLead == 1 )
	{
		attackWeight *= 1.3f;
	}
	else
	{
		attackWeight /= 1.5f;
	}
	
	SitLog << "Attack / Defence Weight: " << attackWeight << endl;

	//			权值		进攻等级	防守等级	函数返回值
	//		0.0f  --- 10.0f				  +++		ADT_FullDefence	
	//		10.0f --- 20.0f				  ++		ADT_TrendDefence	
	//		20.0f --- 30.0f				  +			ADT_Defence	
	//		30.0f --- 40.0f	   +					ADT_Attack	
	//		40.0f --- 50.0f	   ++					ADT_TrendAttack	
	//		50.0f --- 60.0f    +++					ADT_FullAttack
	if( attackWeight <= 10.0f )
	{
		return ADT_FullDefence;
	}
	else if( attackWeight > 10.0f && attackWeight <= 20.0f )
	{
		return ADT_TrendDefence;
	}
	else if( attackWeight > 20.0f && attackWeight <= 30.0f )
	{
		return ADT_NormalDefence;
	}
	else if( attackWeight > 30.0f && attackWeight <= 40.0f )
	{
		return ADT_NormalAttack;
	}
	else if( attackWeight > 40.0f && attackWeight <= 50.0f )
	{
		return ADT_TrendAttack;
	}
	else
	{
		return ADT_FullAttack;
	}
}

Vector3f Situation::DribbleTo( Vector3f tarDribbleVector )
{
	Vector3f tempVector3f = mSitDribble->DribbleTo( tarDribbleVector );
	
	return tempVector3f;
}

Vector3f Situation::KickTo( Vector3f tarKickVector, float kickDist )
{
	Vector3f tempVector3f = mSitKick->KickTo( tarKickVector, kickDist );

	return tempVector3f;
}

Vector3f Situation::PassTo()
{
	Vector3f tempVector3f = mSitKick->PassTo();

	return tempVector3f;
}

Vector3f Situation::AttackRunPos( AttDefkTrend attDefTrend )
{
	return mSitRun->AttackRunPos( attDefTrend );
}


//******************************************************************
//			评估进攻途径
//		
//		综合衡量四种进攻途径的权重
//			包括：	射门（shoot）
//					传球（pass）
//					带球（dribble）
//					进攻跑位(runposition)
//		权重指标：
//				最高为 10.0f
//				最低为 0.0f
//		优先权：
//				优先权  途径		阈值（waited to be tested）
//				最高	射门		7.0f
//				次高	传球		5.0f
//				中		带球		3.0f
//				低		进攻跑位	1.0f
//******************************************************************
AttackApproach Situation::EvaluAttackApproach()
{
	const float shootThreshold = 7.0f;
	const float passThreshold = 5.0f;
	const float dribbleThreshold = 3.0f;
	const float runPositionThreshold = 1.0f;

	float shootWeight = mSitKick->ShootWeight();
	float passWeight = mSitKick->PassWeight();
	float dribbleWeight = mSitDribble->DribbleWeight();
	float runPositionWeight = 0.0;

	//float maxWeight = Max( Max(shootWeight, passWeight), dribbleWeight );
	SitLog << "ShootWeight " << shootWeight << " PassWeight " << passWeight << " DribbleWeight " << dribbleWeight << endl;

	/*if( shootWeight >= shootThreshold )
	{
		return AA_Shoot;
	}
	
	if( passWeight >= passThreshold )
	{
		if( shootWeight >= passWeight )
		{
			return AA_Shoot;
		}
		else
		{
			return AA_Pass;
		}
	}

	if( dribbleWeight >= dribbleThreshold )
	{
		if( shootWeight >= passWeight 
			&& passWeight >= dribbleWeight 
			)
		{
			return AA_Shoot;
		}
		else if( passWeight >shootWeight 
			  && passWeight >= dribbleWeight
			  )
		{
			return AA_Pass;
		}
		else
		{
			return AA_Dribble;
		}
	}*/
	
	if( shootWeight >= passWeight 
		&& shootWeight >= dribbleWeight )
	{
		return AA_Shoot;
	}

	if( passWeight >= shootWeight 
		&& passWeight >= dribbleWeight )
	{
		return AA_Pass;
	}

	if( dribbleWeight >= shootWeight 
		&& dribbleWeight >= passWeight )
	{
		return AA_Dribble;
	}

	if( runPositionWeight >= runPositionThreshold )
	{
		return AA_RunPosition;
	}

	return AA_Defense;
}

AttackApproach Situation::AttackOrDefense()
{
	if( EvaluAttackApproach() != AA_Defense )
	{
		return EvaluAttackApproach();
	}

	return AA_Defense;
}

void Situation::PrintApproach( AttackApproach approach )
{
	switch( approach )
	{
	case AA_Shoot:
		SitLog << "Attack Approach " << "Shoot" << endl;
		break;

	case AA_Pass:
		SitLog << "Attack Approach " << "Pass" << endl;
		break;
		
	case AA_Dribble:
		SitLog << "Attack Approach " << "Dribble" << endl;
		break;

	case AA_RunPosition:
		SitLog << "Attack Approach " << "RunPosition" << endl;
		break;

	default:
		SitLog << "Attack Approach " << "Defense" << endl;
	}
}

//******************************************************************
// 我方离球比我近的队员数目
//******************************************************************
unsigned int Situation::OurNearPlayerToBall()
{
	unsigned int playerNum = 0;
	float myDistToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

	for( unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField; i ++ )
	{
		float tempDist = mWorldModel->mOurTeamPlayer[i].DistXyTo( mWorldModel->mBall.mPos );

		if( tempDist < myDistToBall )
		{
			playerNum ++;
		}
	}

	return playerNum;
}

unsigned int Situation::GetOurControlBallCycle()
{
	return mOurControlBallCycle;
}

unsigned int Situation::GetOppControlBallCycle()
{
	return mOppControlBallCycle;
}


bool Situation::goalieLookSharp()
{
	Circle ballDefenceArea;
	ballDefenceArea.setCircle( mWorldModel->mOurGoalCenter, mWorldModel->mFieldLength / 2.0f );

	if (ballDefenceArea.isInsideBall(mWorldModel->mBall.mPos))
	{
		return true;
	}
	return false;
}

bool Situation::goalieCatchBall()
{
	Circle goalieCatchCircle;
	goalieCatchCircle.setCircle(mWorldModel->mOurGoalCenter,(mWorldModel->mGoalWidth)/2);

	if (goalieCatchCircle.isInsideBall(mWorldModel->mBall.mPos))
	{
		return true;
	}
	return false;
}
bool Situation::CaculatePlayerExp()
{

	bool JudgeExp[4];

	for (unsigned int i = 1; i < mWorldModel->mOurPlayerNumOnField;i++)
	{
		if (mWorldModel->mOurTeamPlayer[i].JudgeHistoryPosZ())// > 0.25
		{
			JudgeExp[i] = true;// > 0.25
		}
		else
			JudgeExp[i] = false;// < 0.25
	}
	for (unsigned int j = 0; j < 4; j++)
	{
		if (JudgeExp[j])
		{
			return false;// > 0.25
		}
	}
	return true;// < 0.25
}
bool Situation::goaliePlayerExp()
{
	//static errorCount = 0;
	//if (CaculatePlayerExp())
	//{
	//	errorCount ++;
	//}
	//if (errorCount == 5)
	//{
	//	return true;
	//}
	return false;
}
bool Situation::goalieDeadBall()
{
	if (mWorldModel->mPlayMode == PM_KICK_OFF_LEFT	|| mWorldModel->mPlayMode == PM_KICK_OFF_RIGHT 
			|| mWorldModel->mPlayMode == PM_KICK_IN_LEFT || mWorldModel->mPlayMode == PM_KICK_IN_RIGHT
			|| mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT || mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT
			|| (mWorldModel->mPlayMode == PM_GOAL_KICK_LEFT && mWorldModel->mTeamSide == SD_RIGHT)
			|| (mWorldModel->mPlayMode == PM_GOAL_KICK_RIGHT && mWorldModel->mTeamSide == SD_LEFT))
	{
		return true;
	}
	return false;
}
bool Situation::NotGoalKick()
{
	if (mWorldModel->mOppScore - mWorldModel->mOurScore >= 3)
	{
		return true;
	}
	return false;
}
bool Situation::goalieBack()
{
	Circle goalieCircle;
	goalieCircle.setCircle(mWorldModel->mOurGoalCenter,(mWorldModel->mGoalWidth)/2);

	if (goalieCircle.isInsideBall(mWorldModel->mSelf.mPos))
	{
		return false;
	}
	return true;
}

bool Situation::IsTarInField( Vector3f tarVector )
{
	return mFieldSquare->IsInField( tarVector );
}
void Situation::OurMinDistToBall( float &minDist, unsigned int &playerNum )
{
	const float basicProportion = 3.0f;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	float minDistToBall = 100.0f;
	unsigned int minDistPlayerNum = 0;

	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		float tempDist = mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos);
		if( mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 1 )
 		{
			continue;
		}
		Angle basicAngle = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOppGoalCenter );
		Angle ballToPlayer = mWorldModel->mBall.mPos.angTheta2( mWorldModel->mOurPlayers[i].mPos );
// 		if( fabs(ballToPlayer - basicAngle) < 50.0f )
// 		{
// 			tempDist *= basicProportion;
// 		}
// 		else
// 		{
// 			tempDist *= -1.0f * (basicProportion - 1.0f) / 180.0f * fabs(ballToPlayer - basicAngle) + 3.0f;
// 		}
		if(  tempDist < minDistToBall )
		{
			minDistToBall = tempDist;
			minDistPlayerNum = mWorldModel->mOurPlayers.at(i).mMyPlayerNo;
		}
	}

	minDist = minDistToBall; 
	playerNum = minDistPlayerNum;
}
void Situation::OppMinDistToBall( float &minDist, unsigned int &playerNum )
{
	Vector3f ballPos = mWorldModel->mBall.mPos;
	float minDistToBall = 100.0f;
	unsigned int minDistPlayerNum = 0;

	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		float tempDist = mWorldModel->mOppPlayers.at(i).DistXyTo(ballPos);
		if(  tempDist < minDistToBall )
		{
			minDistToBall = tempDist;
			minDistPlayerNum = mWorldModel->mOppPlayers.at(i).mMyPlayerNo;
		}
	}

	minDist = minDistToBall; 
	playerNum = minDistPlayerNum;
}
void Situation::OppMinDistToBall( Vector3f &oppMostNearPos)
{
	Vector3f ballPos = mWorldModel->mBall.mPos;
	float minDistToBall = 100.0f;
	unsigned int minDistPlayerNum = 0;

	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		float tempDist = mWorldModel->mOppPlayers.at(i).DistXyTo(ballPos);
		if(  tempDist < minDistToBall )
		{
			minDistToBall = tempDist;
			oppMostNearPos = mWorldModel->mOppPlayers.at(i).mPos;
		}
	}


}
bool Situation::IControlingBall()
{
	const float minControlRadius = 0.3f;
	float myDistToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

	SitLog << "IControlingBall ?" << myDistToBall << endl;

	if( myDistToBall <= minControlRadius )
	{
		SitLog << "Yes  " << myDistToBall << endl;
		return true;
	}

	return false;
}
bool Situation::WeControlingBall()
{
	const float minControlRadius = 0.5f;

	float ourMinDistToBall;
	float oppMinDistToBall;
	unsigned int ourPlayerMinToBall;
	unsigned int oppPlayerMinToBall;

	OurMinDistToBall( ourMinDistToBall, ourPlayerMinToBall );
	OppMinDistToBall( oppMinDistToBall, oppPlayerMinToBall );

	SitLog << " ourMinDistToBall " << ourMinDistToBall << " " << " oppMinDistToBall " << oppMinDistToBall << endl;

	if( ourMinDistToBall <= minControlRadius )
	{
		SitLog << "We Control Ball" << " -- Very Near "<< endl;

		return true;
	}
	else if( oppMinDistToBall <= ourMinDistToBall * 0.7f )
	{
		SitLog << "We don't Control Ball" << " -- Farther" << endl;

		return false;
	}
	else if( ourMinDistToBall <= oppMinDistToBall * 0.7f )
	{
		SitLog << "We Control Ball " << " -- Nearer" << endl;

		return true;
	}
	else if( ourMinDistToBall > 1.0f && oppMinDistToBall > 1.0f )
	{
		if( mCoach->GetOppStrength() == OS_Weak )
		{
			if( ourMinDistToBall < oppMinDistToBall * 1.5f )
			{
				SitLog << "We Control Ball " << " -- Stronger and Nearer" << endl;
				return true;
			}
			else 
			{
				SitLog << "We don't Control Ball " << " -- Stronger but Farther" << endl;
				return true;
			}
		}
		else
		{
			if( ourMinDistToBall < oppMinDistToBall * 0.8f )
			{
				SitLog << "We Control Ball " << " -- Weaker but Nearer" << endl;
				return true;
			}
			else
			{
				SitLog << "We don't Control Ball " << " -- Weaker and Farther" << endl;
				return true;
			}
		}
	}
	else
	{
		SitLog << "Need Coach " << endl;
		if( mCoach->GetOppStrength() == OS_Strong )
		{
			SitLog << "We Control Ball" << " -- Stronger" << endl;

			return true;
		}
		else
		{
			SitLog << "We don't Control Ball" << " -- Weaker" << endl;

			return false;
		}
		return true;
	}
}
bool Situation::SelfDistToBallMin()
{
	float ourMinDistToBall;
	unsigned int ourPlayerMinToBall;

	OurMinDistToBall( ourMinDistToBall, ourPlayerMinToBall );

	return ( ourPlayerMinToBall == mWorldModel->mMyPlayerNo );
}
BasicStrategy Situation::GetBasicStrategy()
{
	int inGuardDistNumS = 0;												//小的弹开距离为0.4
	int inGuardDistNumB = 0;												//大的弹开距离为1.0
	float tempDist = 1.25f;

	if(mWorldModel->mOurPlayers.size() > 0)
	{
		for(int i = 0;i < mWorldModel->mOurPlayers.size();i ++)
		{
			if (mWorldModel->mSelf.mMyPlayerNo==mWorldModel->mOurPlayers.at(i).mMyPlayerNo)
			{
				continue;

			}
			tempDist= mWorldModel->mOurPlayers.at(i).DistXyTo(mWorldModel->mBall.mPos);

			if(tempDist <= 0.45)
			{
				inGuardDistNumS ++;
			}
			else if(tempDist > 0.45 && tempDist <= 1.05)
			{
				inGuardDistNumB ++;
			}
		}		
	}
	
	BasicStrategy basicStrategy = BSA_Dribble;

	float guardShouldClearDist = 4.5f;

	if( mWorldModel->mGameTime < 10.0f || (mWorldModel->mGameTime > 299.0f && mWorldModel->mGameTime < 310.0f ) ) 
	{
		if( ( mWorldModel->mPlayMode == PM_KICK_OFF_LEFT && mWorldModel->mTeamSide == SD_LEFT )
			|| ( mWorldModel->mPlayMode == PM_KICK_OFF_RIGHT && mWorldModel->mTeamSide == SD_RIGHT ) )
		{
			if( mWorldModel->mMyPlayerNo == 7 )
			{
				return BSA_Dribble;
			}
			else if( mWorldModel->mMyPlayerNo != 1 )
			{
				return BSA_RunPosition;
			}
		}
		//else if (mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT)
		//{
		//	if( mWorldModel->mMyPlayerNo != 1 )
		//	{
		//		return BSD_CornerBall;
		//	}
		//	/*else if( mWorldModel->mMyPlayerNo != 1 )
		//	{
		//		return BSA_RunPosition;
		//	}*/
		//	
		//}
	}



	if( mWorldModel->mBall.mPos.x < 0.0f - mWorldModel->mFieldLength / 3.0f )
	{
		Vector3f ourOtherPlayerPos;
		Vector3f selfPos = mWorldModel->mSelf.mPos;
		Vector3f ballPos = mWorldModel->mBall.mPos;
		bool isIShouldGoUp = true;
		float tempMinDis=10.0f;
		for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
		{
			if( mWorldModel->mOurPlayers.at(i).mMyPlayerNo == mWorldModel->mMyPlayerNo 
				|| mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 1 ||mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 2)
			{
				continue;
			}

			Vector3f playerPos = mWorldModel->mOurPlayers.at(i).mPos;
			if (playerPos.distXY2(ballPos)<tempMinDis)
			{
				tempMinDis=playerPos.distXY2(ballPos);
			}
			
			if( selfPos.distXY2(ballPos) > playerPos.distXY2(ballPos) )
			{
			
				SitLog<<"Set false"<<mWorldModel->mGameTime<<endl;
				SitLog<<"tempMinDis==="<<tempMinDis<<"   selfPos===="<<selfPos.distXY2(ballPos)<<endl;
				
				isIShouldGoUp = false;
			}
		}
		if (mFormation->GetMyRole()==PR_Guard_1)
		{		
			if (IControlingBall())
			{
				basicStrategy = BSD_ClearBall;
			} 
			else
			{
			basicStrategy = BSA_RunPosition;
			}
			SitLog<<"I should Act now!"<< mWorldModel->mGameTime<<endl;
			return basicStrategy;
		}
		if (  (SecondNearToBall() && mFormation->GetMyRole()!=PR_Guard_1) || (NearoppPlayer() && !isIShouldGoUp) )
		{
			SitLog<<"Blocking!!!!!!!"<<mWorldModel->mGameTime<<endl;
			basicStrategy = BSD_Block;
		}

		

		if(isIShouldGoUp && mFormation->GetMyRole()!=PR_Guard_1 )
		{		
			
			
				//cout<<"selfPos.distXY2(ballPos) ===="<<selfPos.distXY2(ballPos) <<"  tempMinDis===="<<tempMinDis<<endl;
				//cout<<"inGuardNumS:::"<<inGuardDistNumS<<"  inGuardDistNumb:::  "<<inGuardDistNumB<<endl;
				SitLog<<"I should go uuuuuup"<<mWorldModel->mGameTime<<endl;
				float ourMinDistToball;
				unsigned int ourMinToballNum;
				OurMinDistToBall(ourMinDistToball,ourMinToballNum);
				basicStrategy = BSD_ClearBall;
		
				if (IControlingBall())
				{
					basicStrategy = BSD_ClearBall;
				
				}
				else if((inGuardDistNumS >= 1||inGuardDistNumB >= 2)
					&&(mFormation->GetMyRole()==PR_Guard_2||mFormation->GetMyRole()==PR_Guard_3))
				{
					if( mWorldModel->mMyPlayerNo != ourMinToballNum )
					{
						basicStrategy = BSA_RunPosition;
											
						SitLog<<"there are already ourplayer around ball"<<mWorldModel->mGameTime<<endl;

						
					}
					else
					{
						
						SitLog<<"ClearingBall~~~~~~~~~~~~~  "<<mWorldModel->mMyPlayerNo<<endl;
			
						basicStrategy = BSD_ClearBall;
					}
				}
				else if (mFormation->GetMyRole() != PR_Guard_2 && mFormation->GetMyRole() != PR_Guard_3)
				{
					SitLog<<"I don't know if I should goup "<<mWorldModel->mMyPlayerNo<<endl;
					basicStrategy = BSD_ClearBall;
				}
			
		}
		else
		{
			SitLog<<"the last situation"<<endl;
			basicStrategy = BSA_RunPosition;
		}
		return basicStrategy;
	}

	if( IControlingBall() )
	{
		// 球的位置：是否需要清球
		if( mFieldSquare->IsNearOurGoal( mWorldModel->mBall.mPos ) )
		{
			basicStrategy = BSD_ClearBall;
		}
		else
		{
			basicStrategy = BSA_Dribble;
		}
		//basicStrategy =  BSA_Shoot;//temp test
	/*	if( mWorldModel->mSelf.mMyPlayerNo == 2 )
		{
			cout<<"shoooooot!!!!!"<<endl;
			basicStrategy =  BSA_Shoot;
			//HMotionShoot();		
		}
		else if( mWorldModel->mSelf.mMyPlayerNo == 3 )

		{
			cout<<"shoooooot!!!!!"<<endl;
			basicStrategy =  BSA_Shoot;
		}*/
// 		basicStrategy =  BSA_Pass;
// 		basicStrategy =  BSA_Shoot;
	}
	else
	{
		if( WeControlingBall() )
		{
			if( SelfDistToBallMin() )
			{
				basicStrategy =  BSA_Dribble;
			}
		/*	else if ((SecondNearToBall() && mWorldModel->mMyPlayerNo >  4) || NearoppPlayer())
			{
				basicStrategy = BSD_Block;
			}*/
			else
			{
				basicStrategy =  BSA_RunPosition;
			}
		}
		else
		{
			basicStrategy =  BSD_Intercept;
		}
	}

	return basicStrategy;
}
GoalieState Situation::GetGoalieState()
{
	GoalieState goalieState;
	int sizeofQue = 0;

	float ballSpeed = 0.0;

	vector<float> que;
	
	
	
	sizeofQue = que.size();

	if (mWorldModel->mBall.mPos.x < -5.5)
	{
		if (que.size() == 10)
		{
			vector<float>::iterator que_it = que.begin();

			que.erase(que_it);
		}		

		if (sizeofQue == 0)
		{
			que.push_back(0.2);
		}
		else
		{
			float ad = 0.0;

			ad = mWorldModel->mBall.DistXyTo(mWorldModel->mOurGoalCenter);  

			/*cout << "ball2 < " << ad <<" "<<que.size()<< endl;*/

			ad = ad -que[que.size()-1];			

			que.push_back(ad);			
		}		
	}

	sizeofQue = que.size();

	for (int i = 0;i < sizeofQue;i ++)
	{	
		ballSpeed += que.at(i);
	}
	if (!que.empty())
	{		
		ballSpeed = ballSpeed / sizeofQue;
	}
	

	//if (mWorldModel->mBall.mPos.x < 0)
	//{
	//	goalieState = GoaS_DefendPos;
	//	Circle kickCircle;
	//	float kickRange = 2.2f;//mWorldModel->mPenaltyWidth;//2.2fmWorldModel->mPenaltyWidth;////2.0f;2.3f;; //mWorldModel->mFieldLength / 4;
	//	kickCircle.setCircle(mWorldModel->mOurGoalCenter,kickRange);
	//	Circle defendCircle;
	//	float defendRange = 3.0f;
	//	defendCircle.setCircle(mWorldModel->mOurGoalCenter,defendRange);
	//	if (GoalieDefendSuper())// || OppKickBall()
	//	{
	//		SitLog << "GoalieDefendSuper" << endl;
	//		goalieState = GoaS_DefendSuper;
	//	}
	//	/*else if (OppKickBall())
	//	{
	//	SitLog << "OppKickBall" << endl;
	//	goalieState = GoaS_DefendSuper;
	//	}*/
	//	else if (kickCircle.isInsideCircle(mWorldModel->mBall.mPos))//DefinePenlty(mWorldModel->mBall.mPos))
	//	{
	//		SitLog << "ball dist 2 goal center"<< mWorldModel->mBall.DistXyTo(mWorldModel->mOurGoalCenter)<< endl;
	//		if(IControlingBall())
	//		{
	//			goalieState = GoaS_ClearBall;
	//		}
	//		else if (WeControlBallExpGoalie())
	//		{
	//			SitLog << "we control ball and I not" << endl;
	//			goalieState = GoaS_DefendPos;
	//		}
	//		else
	//		{
	//			/*if (DefinePenlty(mWorldModel->mBall.mPos))
	//			{*/
	//			SitLog << "Ball in Penlty " << endl;
	//			cout << "ball in penlty!" << endl;
	//			goalieState = GoaS_DefendBall;	
	//			/*}*/		
	//		}
	//	}
	//	else
	//	{					
	//		if (defendCircle.isInsideCircle(mWorldModel->mBall.mPos))
	//		{
	//			SitLog << "ball in defendCircle" << endl;
	//			if (!WeControlingBall() && OppNotControlBall())
	//			{
	//				SitLog << "no Opp and us, goalie go to ball" << endl;
	//				goalieState = GoaS_DefendBall;		
	//			}		
	//		}	
	//	}
	//}
	//else 
	//{
	//	goalieState = GoaS_Other;
	//}
	//if (mWorldModel->mBall.mPos.x > /*mWorldModel->mFieldLength /*/ -10.5)
	//{
	//	goalieState = GoaS_Other;
	//}
	//else 
	//{
		/*if (mWorldModel->mBall.mPos.x / mWorldModel->mBall.mPos.y > 1.8)
		{
			goalieState = GoaS_DefendPos;
		}
		else if (mWorldModel->mBall.mPos.x / mWorldModel->mBall.mPos.y < -1.8)
		{
			goalieState = GoaS_DefendPos;
		}*/
		/*else*/ 
	Vector3f standPos = mWorldModel->mOurGoalCenter;

	standPos.x = -10.1;

	/*cout << "myPos" << mWorldModel->mSelf.mPos.x << " " << mWorldModel->mSelf.mPos.y << endl;*/

	/*if ( (mWorldModel->mPlayMode ==PM_GOAL_KICK_LEFT && mWorldModel->mTeamSide == SD_LEFT) 
		|| (mWorldModel->mPlayMode ==PM_GOAL_KICK_RIGHT && mWorldModel->mTeamSide == SD_RIGHT) )
	{
		cout<<"shoot"<<endl;
		goalieState = GoaS_GoalKick;
	}
	else*/ if (mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT)
	{
		goalieState = GoaS_Other;
	}
	else
	{
		//if (mWorldModel->mSelf.mPos.x > 10.1 || fabs(mWorldModel->mSelf.mPos.y) > 0.1)
		if(mWorldModel->mSelf.mPos.distXY2(standPos) > 0.4)
		{
			/*cout << "dist1" << mWorldModel->mSelf.mPos.distXY2(standPos) << endl;*/
			goalieState = GoaS_DefendPos;
		}
		else if ((mWorldModel->mBodyAngle > 30 && mWorldModel->mBodyAngle < 150) || (mWorldModel->mBodyAngle < -30 && mWorldModel->mBodyAngle > -150))
		{
			goalieState = GoaS_DefendPos;
		}
		/*else if (fabs(mWorldModel->mSelf.mPos.y) > 2.0)
		{
			goalieState = GoaS_DefendPos;
		}*/
		
		else
		{
			goalieState = GoaS_Other;
		}		

		if (mWorldModel->mBall.mPos.x < -9.1 &&  ballSpeed > 0.0 && fabs(mWorldModel->mBall.mPos.y) < 2.0)
		{
			goalieState = GoaS_DefendSuper;
		}
		else if (ballSpeed > 0.25)
		{
			goalieState = GoaS_DefendSuper;
		}
	}
	
		
		/*else
		{
			goalieState = GoaS_DefendPos;
		}
		
	}*/
	/*if (mWorldModel->mSelf.mPos.distXY2(mWorldModel->mBall.mPos) > 2.0f)
	{
		SitLog << "GoalieDefendhere" << endl;

		goalieState = GoaS_DefendPos;
	}*/
	
	return goalieState;
}
bool Situation::WeControlBallExpGoalie()
{
	if (WeControlingBall())
	{
		float ourMinDistToBall;
		unsigned int ourPlayerMinToBall;
		OurMinDistToBall( ourMinDistToBall, ourPlayerMinToBall);
		if (ourPlayerMinToBall == mWorldModel->mSelf.mMyPlayerNo)
		{
			return false;
		}
		return true;
	}
	return false;
}
bool Situation::OppNotControlBall()
{
	Circle ballCir;
	float ballBlankRadius = 1.5f;
	ballCir.setCircle(mWorldModel->mBall.mPos,ballBlankRadius);
	
	for(int i = 0; i < mWorldModel->mOppPlayers.size(); ++i)
	{
		if (ballCir.isInsideCircle(mWorldModel->mOppPlayers.at(i).mPos))
		{
			return false;
		}
	}
	return true;
}
bool Situation::DefinePenlty(Vector3f pos)
{
	Vector3f pos1(-(mWorldModel->mFieldLength/2 - mWorldModel->mPenaltyLength),mWorldModel->mPenaltyWidth/2,0.0f);
	Vector3f pos2(-mWorldModel->mFieldLength/2,-mWorldModel->mPenaltyWidth/2,0.0f);
	Rectangle defendTangle(pos1,pos2);
	if (defendTangle.isInside(pos))
	{
		SitLog << "Pos :" << pos.x << " " << pos.y << " " << pos.z << endl;
		return true;
	}
	return false;
}
bool Situation::DefinePenltySmall(Vector3f pos)
{
	//SitLog << "Define Penlty : " << endl;
	Vector3f pos1(-(mWorldModel->mFieldLength/2 - 1),mWorldModel->mGoalWidth/2,0.0f);
	Vector3f pos2(-mWorldModel->mFieldLength/2,-mWorldModel->mGoalWidth/2,0.0f);
	Rectangle smalldefendTangle(pos1,pos2);

	//SitLog << "Pos1 :" << pos1.x << " " << pos1.y << " " << pos1.z << endl;
	//SitLog << "Pos2 :" << pos2.x << " " << pos2.y << " " << pos2.z << endl;

	if (smalldefendTangle.isInside(pos))
	{
		SitLog << "Pos :" << pos.x << " " << pos.y << " " << pos.z << endl;
		return true;
	}
	return false;
}
bool Situation::GoalieDefendSuper()
{	
	/*float mClearRadius = mWorldModel->mGoalWidth / 2;
	Circle m_ClearCir;
	m_ClearCir.setCircle(mWorldModel->mOurGoalCenter,mClearRadius);

	if (m_ClearCir.isInsideCircle(mWorldModel->mBall.mPos))
	{
		SitLog << "ball in Goalie Defend super Area!" << endl;
		float temp = CacHistoryBallSpeed();
		if (temp > 0.4)
		{
		return true;
	}
	}*/
	if (DefinePenltySmall(mWorldModel->mBall.mPos))
	{
		SitLog << "ball in Goalie Defend super Area!" << endl;
		SitLog << "ball Pos :" << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.y << endl;
		float temp = CacHistoryBallSpeed();
		//if (temp > 0.4)
		//{
			SitLog << "ball is rolling with avarage speed = " <<temp <<  endl;
			return true;
		//}
	}
	return false;
}
float Situation::CacHistoryBallSpeed()
{
	float ballPossibleVec = 0.0f;
	list<Vector3f>::iterator temp;
	if (mWorldModel->mBall.mHistorySpeed.empty())
	{
		SitLog<<"mHistroy Speed is empty !"<<endl;
	}
	else
	{
		for (temp = mWorldModel->mBall.mHistorySpeed.begin();temp != mWorldModel->mBall.mHistorySpeed.end();++temp)
		{
			ballPossibleVec += (*temp).modXY();
		}

		ballPossibleVec /= (int)mWorldModel->mBall.mHistorySpeed.size();
		SitLog << "ballPossibleVec = " <<ballPossibleVec << endl;
	}
	return ballPossibleVec;
}
bool Situation::OppKickBall()
{
	/*Circle ballCircle;
	float ballKick = 0.2f;
	ballCircle.setCircle(mWorldModel->mBall.mPos,ballKick);
	static bool oppKick = false;
	static float oppMayKickTime = 0.0f;

	static float ball2Goalie = 0.0f;
	int oppNo;
	for (int i = 0; i < mWorldModel->mOppPlayers.size(); ++i)
	{
		if (ballCircle.isInsideCircle(mWorldModel->mOppPlayers.at(i).mPos) && (!DefinePenlty(mWorldModel->mBall.mPos)))
		{
			oppKick = true;
			oppNo = i;
			break;
		}
	}
	if (oppKick)
	{
		if (mWorldModel->mOppPlayers.at(oppNo).DistXyTo(mWorldModel->mBall.mPos) > 0.4)
{
			oppMayKickTime = mWorldModel->mGameTime;
			ball2Goalie = mWorldModel->mBall.DistXyTo(mWorldModel->mSelf.mPos);
		}
	}*/
	//float ballInCircleTime = mWorldModel->mGameTime;
	Circle myCircle;
	float myCirus = 4.0f;
	myCircle.setCircle(mWorldModel->mSelf.mPos,myCirus);

	if (mWorldModel->mBall.mPos.x < 0)//(myCircle.isInsideCircle(mWorldModel->mBall.mPos))
	{
		SitLog << "inside circle!\n";
		float temp = CacHistoryBallSpeed();
		if (temp >= 4)
	{
			SitLog << "ballPossibleVec = " <<temp <<" Larger than 4!\n";
			SitLog << "ballDist2goalie = " << mWorldModel->mSelf.DistXyTo(mWorldModel->mBall.mPos)<<endl;
		return true;
	}	
	}
	return false;
}
void Situation::GetGoalieDefendBall(Vector3f& pos, Angle& ang)
{
	SitLog << "GetGoalieDefendBall" << endl;
	//cout << "defend ball" << endl;
	pos = mWorldModel->mBall.mPos;

	Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
		+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
	ang  = Normalize(angballTrack + 180);

	SitLog << "Angle : " << ang << endl;
}
int Situation::CaculateDropDownSide()
{
	SitLog << "Caculate Drop Down side \n" << endl;
	Line GoalTrack;
	Line balltrack;
	int sizeofQue = 0;
	
	float ballSpeed = 0.0;
	
	vector<float> que;

	sizeofQue = que.size();
	
	if (mWorldModel->mBall.mPos.x < -6.5)
	{
		if (que.size() == 10)
		{
			vector<float>::iterator que_it = que.begin();

			que.erase(que_it);
		}
		if (sizeofQue == 0)
		{
			que.push_back(0.2);
		}
		else
		{
			float ad = 0.0;

			ad = mWorldModel->mBall.DistXyTo(mWorldModel->mOurGoalCenter);  		

			ad = ad -que[que.size()-1];			

			que.push_back(ad);

		}		
	}

	sizeofQue = que.size();

	for (int i = 0;i < sizeofQue;i ++)
	{
		ballSpeed += que.at(i);
	}
	if (!que.empty())
	{
		ballSpeed = ballSpeed / sizeofQue;
	}
	

	Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
		+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
	balltrack = Line::makeLineFromPositionAndAngle(mWorldModel->mBall.mPos,angballTrack);

	GoalTrack.setA(0);
	GoalTrack.setB(1);
	GoalTrack.setC(-mWorldModel->mSelf.mPos.x);

	Vector3f TempTargetPos = GoalTrack.getIntersection(balltrack);
	int left;
	int dir;
	if (BallAfterGoalie())
		{
		SitLog << "ball is after goalie"<<endl;
		return left = 4;
		}
	if (ballSpeed > 0.25 )
	{
		Angle  bodyAngle = mWorldModel->mBodyAngle;

		/*if (bodyAngle < 0)
		{
			bodyAngle += 360;
		}*/
		if (mWorldModel->mBall.mPos.y > mWorldModel->mSelf.mPos.y 
			&& ((bodyAngle > 0 && bodyAngle < 90) || bodyAngle > -90))
		{
			return left = 0;
		}
		else if(mWorldModel->mBall.mPos.y > mWorldModel->mSelf.mPos.y 
			&& bodyAngle > 90 && bodyAngle < -90)
		{
			return left = 1;
		}
		else if (mWorldModel->mBall.mPos.y < mWorldModel->mSelf.mPos.y 
			&& ((bodyAngle > 0 && bodyAngle < 90) || bodyAngle > -90))
		{
			return left = 1;
		}
		else if (mWorldModel->mBall.mPos.y < mWorldModel->mSelf.mPos.y 
			&& bodyAngle > 90 && bodyAngle < -90)
		{
			return left = 0;
		}
	}
	else if (ballSpeed > 0.0 && mWorldModel->mBall.mPos.x < -9.0)
	{
		Angle  bodyAngle = mWorldModel->mBodyAngle;

		/*if (bodyAngle < 0)
		{
		bodyAngle += 360;
		}*/
		if (mWorldModel->mBall.mPos.y > mWorldModel->mSelf.mPos.y 
			&& ((bodyAngle > 0 && bodyAngle < 90) || bodyAngle > -90))
		{
			return left = 0;
		}
		else if(mWorldModel->mBall.mPos.y > mWorldModel->mSelf.mPos.y 
			&& bodyAngle > 90 && bodyAngle < -90)
		{
			return left = 1;
		}
		else if (mWorldModel->mBall.mPos.y < mWorldModel->mSelf.mPos.y 
			&& ((bodyAngle > 0 && bodyAngle < 90) || bodyAngle > -90))
		{
			return left = 1;
		}
		else if (mWorldModel->mBall.mPos.y < mWorldModel->mSelf.mPos.y 
			&& bodyAngle > 90 && bodyAngle < -90)
		{
			return left = 0;
		}
	}
	if (GoalieCanCatchBall(dir))
	{
		if (dir == 2)
		{
			return left = 5;
		}
		/*if (GoalieFace2Ball())
		{
			SitLog << "Goalie is face to Ball!" << endl;
			left = dir;
	}
		else
	{
			SitLog << "Goalie is not face to Ball!" << endl;
			left = 1 - dir;
		}*/
		left = dir;
	}
	else
	{
		if (GoalieTurnOnly())
		{
			SitLog<<"Goalie turn to drop"<<endl;
			left = 2;
		}
		else
		{
			SitLog << "Goalie go to tar and drop" << endl;
			left = 3;
		}
	}
	SitLog << "left = " << left << endl;
	return left;
}
void Situation::GetGoalieSuperTarget(Vector3f& pos,Angle& ang)
	{
	Angle turAng;
	Line balltrack;
	Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
		+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
	balltrack = Line::makeLineFromPositionAndAngle(mWorldModel->mBall.mPos,angballTrack);
	
	pos = balltrack.getPointOnLineClosestTo(mWorldModel->mSelf.mPos);
	if ((fabs(pos.x) > (mWorldModel->mFieldLength / 2)) || (fabs(pos.y) >(mWorldModel->mFieldWidth/2)))
	{
		Line GoalTrack;
		GoalTrack.setA(0);
		GoalTrack.setB(1);
		GoalTrack.setC(-mWorldModel->mOurGoalCenter.x - 0.1);
		pos = balltrack.getIntersection(GoalTrack);
		SitLog << "interPos is out of goal = " << pos.x << " " << pos.y << endl;
	}
	if (GoalieFace2Ball())
	{
		ang = pos.angTheta2(mWorldModel->mBall.mPos);
}
	else
		ang = mWorldModel->mBall.mPos.angTheta2(pos);
}
Angle Situation::GoalieTurnAngle()
{
	Angle turAng;
	Line balltrack;
	Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
		+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
	balltrack = Line::makeLineFromPositionAndAngle(mWorldModel->mBall.mPos,angballTrack);

	Vector3f tangenPoint = balltrack.getPointOnLineClosestTo(mWorldModel->mSelf.mPos);
	if (GoalieFace2Ball())
	{
		turAng = tangenPoint.angTheta2(mWorldModel->mBall.mPos);
	}
	else
		turAng = mWorldModel->mBall.mPos.angTheta2(tangenPoint);
	return turAng;
}
bool Situation::GoalieTurnOnly()
		{
	Line balltrack;
	Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
		+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
	balltrack = Line::makeLineFromPositionAndAngle(mWorldModel->mBall.mPos,angballTrack);

	float dist = balltrack.getDistanceWithPoint(mWorldModel->mSelf.mPos);
	Vector3f tangenPoint = balltrack.getPointOnLineClosestTo(mWorldModel->mSelf.mPos);
	if ((dist <= 0.4) && (fabs(tangenPoint.x) > (mWorldModel->mFieldLength / 2)) || (fabs(tangenPoint.y) >(mWorldModel->mFieldWidth/2)))
	{
		return true;
	}
	return false;
}
bool Situation::BallAfterGoalie()
{
	if ((!GoalieFace2Ball()) && (mWorldModel->mBall.mPos.x < mWorldModel->mSelf.mPos.x))
	{
		return true;
		}
	else if ((GoalieFace2Ball()) && (mWorldModel->mBall.mPos.x < mWorldModel->mSelf.mPos.x) && (fabs(Normalize(mWorldModel->mBodyAngle)) > 90))
		{
		return true;
		}
	else
		return false;
	}
bool Situation::GoalieFace2Ball()
{
	Angle goalie2ball = Normalize(mWorldModel->mSelf.ThetaTo(mWorldModel->mBall.mPos));
	Angle goalie = Normalize(mWorldModel->mBodyAngle);

	Angle err = fabs(Normalize(goalie - goalie2ball));
	if (err > 90)
	{
		return false;
	}	
	return true;
}
bool Situation::GoalieCanCatchBall(int& direction)
{
	
	Line balltrack;
	Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
		+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
	balltrack = Line::makeLineFromPositionAndAngle(mWorldModel->mBall.mPos,angballTrack);

	Line goalieTrack;
	Angle temp = Normalize(mWorldModel->mBodyAngle - 90);
	goalieTrack = Line::makeLineFromPositionAndAngle(mWorldModel->mSelf.mPos,temp);

	Vector3f interPos = goalieTrack.getIntersection(balltrack);

	SitLog << "interPos = " << interPos.x << " " << interPos.y << endl;
	if ((fabs(interPos.x) > (mWorldModel->mFieldLength / 2)) || (fabs(interPos.y) >(mWorldModel->mFieldWidth/2))
		 || (interPos.x > mWorldModel->mBall.mPos.x))
	{
		/*Line GoalTrack;
		GoalTrack.setA(0);
		GoalTrack.setB(1);
		GoalTrack.setC(-mWorldModel->mOurGoalCenter.x - 0.3);
		interPos = balltrack.getIntersection(GoalTrack);
		SitLog << "interPos is out of goal = " << interPos.x << " " << interPos.y << endl;*/
		return false;
	}
	SitLog << "myPos = " << mWorldModel->mSelf.mPos.x << " " << mWorldModel->mSelf.mPos.y << endl;
	SitLog << "Ball Pos = " << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.y << endl;
	if (interPos.distXY2(mWorldModel->mSelf.mPos) > 0.4)
	{
		return false;
	}	
	else
	{
		float body = Normalize(mWorldModel->mBodyAngle);
		SitLog <<"My Body Angle = " <<body << endl;
		if (fabs(mWorldModel->mSelf.mPos.y - interPos.y) < 0.1)
		{
			direction = 2;
			return true;
		}
		if (fabs(angballTrack - body) > 70)
		{
			SitLog <<"The angle is too small!" <<endl;
			return false;
		}
		if (fabs(Normalize(mWorldModel->mBodyAngle)) > 90)//(GoalieFace2Ball())//
		{
			SitLog << "body angle > 90" << endl;
			if (mWorldModel->mSelf.mPos.y > interPos.y)
		{
				direction = 1; //left
		}
		else
				direction = 0;//right
		}
		else
		{
			SitLog << "body angle < 90"<< endl;
			if (mWorldModel->mSelf.mPos.y > interPos.y)
		{
				direction = 1; //right
		}
			else
				direction = 0;//left
		}		
		return true;
	}	
}
int Situation::GetGoalieDefendPos(Vector3f& pos, Angle& ang)
{
	SitLog << "GetGoalieDefend" << endl;
	/*if (IControlingBall())
	{
		return 0;
	}
	else
	{*/
	Vector3f ourGoalCenter = mWorldModel->mOurGoalCenter;



	ourGoalCenter.x -= 1.0f;

	Vector3f ballPos = mWorldModel->mBall.mPos;

	Angle ourGoalToBallAngle = ourGoalCenter.angTheta2( ballPos );

	Angle selfAngle = mWorldModel->mSelf.mPos.angTheta2(mWorldModel->mOppGoalCenter);

	Ray ourGoalToBallRay = Ray::MakeRayFromPositionAndAngle( ourGoalCenter, ourGoalToBallAngle );

	float defineDist = 1.5;
		//在球门前守着
		/*Line balltrack,GoalTrack;
		Angle angballTrack = Normalize(mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)
			+ 0.5 * (mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos) - mWorldModel->mBall.ThetaTo(mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos)));
		balltrack = Line::makeLineFromPositionAndAngle(mWorldModel->mBall.mPos,angballTrack);

		GoalTrack.setA(0);
		GoalTrack.setB(1);
		GoalTrack.setC(-mWorldModel->mOurGoalCenter.x - 0.35);

		Circle tempCir;
		tempCir.setCircle(mWorldModel->mOurGoalCenter,2.0f);
		pos = balltrack.getIntersection(GoalTrack);
		if (!tempCir.isInsideCircle(pos))
		{
			SitLog << "Defend target pos is illegal" << endl;
			pos.x = mWorldModel->mOurGoalCenter.x + 0.35;
			if (mWorldModel->mBall.mPos.y > 0)
			{
				pos.y = mWorldModel->mGoalWidth / 2;
			}
			else
			{
				pos.y =-mWorldModel->mGoalWidth /2;
			}
			pos.z = 0;
		}*/
		

		/*SitLog << "GoalieDefendAng" << selfAngle << endl;
		
		SitLog << "GoalieDefendAng" << ang << endl;*/
	Vector3f standPos = mWorldModel->mOurGoalCenter;	

	standPos.x = -10.1;
		
	/*if (mWorldModel->mBall.mPos.x / mWorldModel->mBall.mPos.y > 1.8 && mWorldModel->mSelf.mPos.y > -0.2)
	{
		pos = mWorldModel->mSelf.mPos;

		pos.y = mWorldModel->mSelf.mPos.y - 0.05;
		
	}
	else if (mWorldModel->mBall.mPos.x / mWorldModel->mBall.mPos.y < -1.8 && mWorldModel->mSelf.mPos.y < 0.2)
	{
		pos = mWorldModel->mSelf.mPos;

		pos.y = mWorldModel->mSelf.mPos.y + 0.05;
		
	}
	else*/ 
	float canStandDist = 0.6;

	if (mWorldModel->mSelf.mPos.distXY2(standPos) > 0.4)
	{
		/*cout << "dist2" << mWorldModel->mSelf.mPos.distXY2(standPos) << endl;*/
		pos = standPos;
	}	
	else if (mWorldModel->mSelf.mPos.distXY2(standPos) <= canStandDist)
	{
		if((mWorldModel->mBodyAngle > 30 && mWorldModel->mBodyAngle < 150) || (mWorldModel->mBodyAngle < -30 && mWorldModel->mBodyAngle > -150))
			/*if (mWorldModel->mBodyAngle > 60 && mWorldModel->mBodyAngle < 120)*/
		{
			pos = mWorldModel->mSelf.mPos;		

			ang = -mWorldModel->mBodyAngle;			
		}
	}


		//	pos = ourGoalToBallRay.GetPoint(defineDist);

		//	ang = ourGoalCenter.angTheta2(mWorldModel->mBall.mPos);		

		//if (pos.x < -mWorldModel->mFieldLength / 2.0)
		//{
		//	pos.x = -mWorldModel->mFieldLength / 2.0 + 0.2;
		//}

		/*pos.x = -10.5;

		pos.y = (ballPos.y / mWorldModel->mFieldWidth) *  0.5;		*/
		
		//cout << "GoaliePos" << endl;
		return 1;
	//}
}
void Situation::LookOppGoal(Vector3f& pos,Angle& ang)
		{
	Line GoalTrack;

	GoalTrack.setA(0);
	GoalTrack.setB(1);
	GoalTrack.setC(-mWorldModel->mOurGoalCenter.x - 0.35);

	Line oppGoal;
	oppGoal = Line::makeLineFromTwoPoints(mWorldModel->mOppGoalCenter,mWorldModel->mOurGoalCenter);

	pos = oppGoal.getIntersection(GoalTrack);
			ang = pos.angTheta2(mWorldModel->mOppGoalCenter);
		}
int Situation::RealPlayerNo(int num,ObjectType obj)
{
	if (obj == Say_Ball)
	{
		return 0;
	}
	else if (obj == Say_OurTeam)
	{
		vector<int> ourNum;
		for (size_t i = 0; i < mWorldModel->mOurPlayers.size();++i)
		{
			ourNum.push_back(mWorldModel->mOurPlayers[i].mMyPlayerNo);
		}
		sort(ourNum.begin(),ourNum.end());
		int temp = ourNum[num];
		return temp;
	}
	else if (obj == Say_OppTeam)
	{
		vector<int> oppNum;
		for (size_t i = 0; i < mWorldModel->mOppPlayers.size();++i)
		{
			oppNum.push_back(mWorldModel->mOppPlayers[i].mMyPlayerNo);
		}
		sort(oppNum.begin(),oppNum.end());
		int temp = oppNum[num];
		return temp;
	}
}
bool Situation::NearoppPlayer()
{
	float NearDist = 0.2f;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f oppMostNearBall;
	OppMinDistToBall( oppMostNearBall );
	float mDistTooppplayer = selfPos.distXY2(oppMostNearBall);
	if (mDistTooppplayer<NearDist)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Situation::SecondNearToBall()
{
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	float mDistToBall = selfPos.distXY2(ballPos);
	unsigned int CountMoreNearPlayer = 0;

	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		if (mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 1|| mWorldModel->mOurPlayers.at(i).mMyPlayerNo == 2)
		{
			continue;
		}
		float tempDist = mWorldModel->mOurPlayers.at(i).DistXyTo(ballPos);
		
		if(  tempDist < mDistToBall )
		{
			CountMoreNearPlayer++;
		}
	}
	
	if ( CountMoreNearPlayer == 1 )
	{
		return true;
	} 
	else
	{
		return false;
	}
}
