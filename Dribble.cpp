#include "Dribble.h"
#define HMDribbleLog gDribbleLog<< "[hmDrib] "

Dribble::Dribble( WorldModel *wm, Situation *situ, HumanGoto *hGoto, CommandQuene *cmdQuene, Action *act )
{
	mWorldModel = wm;
	mSituation = situ;
	mHGoto = hGoto;
	mCmdQuene = cmdQuene;
	mAct = act;

	IsneedTurn = true;

	mObstacle = Obstacle::GetInstance( mWorldModel );
}
Dribble::~Dribble()
{

}
bool Dribble::BasicDribbleAttackViability( Vector3f tarDribbleTo )
{
	Vector3f currBallPos = mWorldModel->mBall.mPos;
	Vector3f predictBallPos = tarDribbleTo;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f ourGoalCenter = mWorldModel->mOurGoalCenter;
	Vector3f oppGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	Vector3f oppGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos;
	//把球门缩小一点以提高射门精度
	oppGoalLeft.z = 0.0f;
	oppGoalRight.z = 0.0f;
	oppGoalCenter.x -= 0.2f;
	oppGoalLeft.x -= 0.2f;
	oppGoalLeft.y *= 0.6f;
	oppGoalRight.x -= 0.2f;
	oppGoalRight.y *= 0.6f;

	//if( currBallPos.x < 0.0f - mWorldModel->mFieldLength / 3.0f )
	//{
	//	//球在我方半场
	//	if( predictBallPos.distXY2(ourGoalCenter) > currBallPos.distXY2(ourGoalCenter)
	//		|| !mSituation->mFieldSquare->IsInerField(predictBallPos) )
	//	{
	//		HMDribbleLog << "Dribble Defense " << endl;
	//		return true;
	//	}
	//}

	float currBallToOppGoalDist = currBallPos.distXY2( oppGoalCenter );
	Angle currBalltoOppGoalAng = Normalize( currBallPos.angTheta2(oppGoalLeft) - currBallPos.angTheta2(oppGoalRight) );

	float predictBallToOppGoalDist = predictBallPos.distXY2( oppGoalCenter );
	Angle predictBallToOppGoalAng = Normalize( predictBallPos.angTheta2(oppGoalLeft) - predictBallPos.angTheta2(oppGoalRight) );

	// 距离对方球门角度更大
	Angle deltaAngle = 10.0f;
	if( currBallPos.distXY2(oppGoalCenter) < 1.0f )
	{
		deltaAngle = 30.0f;
	}
	if( fabs(predictBallToOppGoalAng) >= fabs(currBalltoOppGoalAng) + deltaAngle 
		//&& predictBallToOppGoalAng >= 0.0f 
		&& mSituation->mFieldSquare->IsInField(predictBallPos) )
	{
		HMDribbleLog << " Larger Angle " << endl;
		return true;
	}

	//球会穿入对方球门
	Line dribbleLine = Line::makeLineFromTwoPoints( currBallPos, predictBallPos );
	Line oppBaseLine = Line::makeLineFromPositionAndAngle( oppGoalCenter, 90.0f );
	Vector3f intersectionVec = dribbleLine.getIntersection( oppBaseLine );
	Vector3f currOppGoalCenterToBall = oppGoalCenter - currBallPos;
	Vector3f predicBallToCurrBall = predictBallPos - currBallPos;

	if( intersectionVec.distXY2(oppGoalLeft) <= mWorldModel->mGoalWidth * 0.8f 
		&& intersectionVec.distXY2(oppGoalRight) <= mWorldModel->mGoalWidth  * 0.8f 
		&& predicBallToCurrBall.x * currOppGoalCenterToBall.x > 0.0f
		&& predicBallToCurrBall.y * currOppGoalCenterToBall.y > 0.0f 
		)
	{
		HMDribbleLog << " currBallPos " << currBallPos.x << " " << currBallPos.y << endl;
		HMDribbleLog << " predictBallPos " << predictBallPos.x << " " << predictBallPos.y << endl;
		HMDribbleLog << " intersectionVec " << intersectionVec.x << " " << intersectionVec.y << endl;
		HMDribbleLog << " leftDist " << intersectionVec.distXY2(oppGoalLeft) << " rightDist " << intersectionVec.distXY2(oppGoalRight) << endl;
		HMDribbleLog << " Into Goal " << endl;
		return true;
	}

	//距离对方球门更近
	float nearerMinDist = 1.8f;
	//for( unsigned int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	//{
	//	Vector3f oppPlayerPos = mWorldModel->mOppPlayers.at(i).mPos;
	//	if( oppPlayerPos.distXY2(currBallPos) < 0.3f 
	//		&& predictBallPos.x > 0.0f + mWorldModel->mFieldLength * 0.5f * 0.2f 
	//		&& predictBallPos.x < 0.0f + mWorldModel->mFieldWidth * 0.5f * 0.8f 
	//		/*&& predictBallPos.x > 0.0f - mWorldModel->mFieldWidth * 0.5f * 0.8f */
	//		&& currBallPos.distXY2(oppGoalCenter) > 3.0f )
	//	{
	//		HMDribbleLog << " Avoid OppPlayer " << endl;
	//		//nearerMinDist = 0.5f;
	//		nearerMinDist = -2.0f;
	//		break;
	//	}
	//}
	if( predictBallToOppGoalDist <= currBallToOppGoalDist - nearerMinDist 
		&& mSituation->mFieldSquare->IsInerField(predictBallPos) )

	{
		HMDribbleLog << " Nearer " << predictBallToOppGoalDist << " " << currBallToOppGoalDist << endl;
		return true;
	}
	
	//在对方前半场离边线较远且带球方向靠近对方底线
	if(predictBallPos.x>currBallPos.x&&currBallPos.x<(oppGoalCenter.x-4.6f)&&mSituation->mFieldSquare->IsInerField(predictBallPos))
	{
		HMDribbleLog << " Nearer oppGoalline " << predictBallPos.x << " " << currBallPos.x << endl;
		return true;
	}
	//在禁区外及对方后半场且带球方向靠近中间
	if((fabs(predictBallPos.y)<fabs(currBallPos.y)||fabs(predictBallPos.y)<fabs(oppGoalCenter.y-mWorldModel->mGoalWidth))&&predictBallPos.x>currBallPos.x
		&&currBallPos.x>(oppGoalCenter.x-mWorldModel->mGoalWidth*2.0f)&&currBallPos.x<(oppGoalCenter.x-mWorldModel->mGoalWidth))
	{
		HMDribbleLog << " Adapting " << predictBallPos.x << " " << currBallPos.x << endl;
		return true;
	}
	
	//在对方禁区且带球方向指向球门以内
	if(predictBallPos.x>currBallPos.x&&currBallPos.x>(oppGoalCenter.x-mWorldModel->mGoalWidth)&&predictBallPos.y>(oppGoalCenter.y-mWorldModel->mGoalWidth*1.4f)
		&&predictBallPos.y<(oppGoalCenter.y+mWorldModel->mGoalWidth*1.4f)
		&&currBallPos.angTheta2(predictBallPos)>currBallPos.angTheta2(oppGoalRight)&&currBallPos.angTheta2(predictBallPos)<currBallPos.angTheta2(oppGoalLeft))
		{
			HMDribbleLog << " In PenaltyArea " << "My gangle" <<currBallPos.angTheta2(predictBallPos)<< " LeftAngle " << currBallPos.angTheta2(oppGoalLeft)<<" RightAngle "<<currBallPos.angTheta2(oppGoalRight)<<endl;
			return true;
		}
	
	return false;
}
bool Dribble::GetDribbleAttackViability( Vector3f tarDribbleTo )
{
	return BasicDribbleAttackViability(tarDribbleTo);

}
bool Dribble::GetDribblePassViability( Vector3f tarDribbleTo )
{
	Vector3f currBallPos = mWorldModel->mBall.mPos;
	Vector3f predictBallPos = tarDribbleTo;

	//float currBallToPartner = currBallPos.distXY2( mWorldModel->mOppGoalCenter );
	return false;
}

bool Dribble::GetDribbleDefenseViability( Vector3f tarDribbleTo )
{
	Vector3f currBallPos = mWorldModel->mBall.mPos;
	Vector3f predictBallPos = tarDribbleTo;

	float currBallToOurGoalDist = currBallPos.distXY2( mWorldModel->mOurGoalCenter );

	return false;
}

Vector3f Dribble::GetDribbleAttackTar()
{
	const float dribbleRadius = 0.095f * 2.0f * 0.6f;   // 0.95f * 2.0f 脚前进时覆盖的宽度
	const float dribbleRunDist = 1.5f;

	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;

	return ballPos;
}
float Dribble::GetDribleDist( Vector3f tarDribbleTo )
{
	const float longRunDist = 3.0f;
	//const float shortRunDist = 0.5f;
	const float shortRunDist = 2.0f;
	const float agentRadius = 1.0f;

	Vector3f ballPos = mWorldModel->mBall.mPos;
	
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		Vector3f oppPos = mWorldModel->mOppPlayers.at(i).mPos;

		if( oppPos.distXY2(tarDribbleTo) < agentRadius )
		{
			HMDribbleLog<< " ------------ shortRunDist 1 " << shortRunDist << endl;
			return shortRunDist;
		}

		if( oppPos.distXY2(ballPos) < agentRadius )
		{
			HMDribbleLog<< " ------------ shortRunDist: near ball " << longRunDist << endl;
			return shortRunDist;
		}

		Line ballToTarLine = Line::makeLineFromTwoPoints( ballPos, tarDribbleTo );
		Vector3f nearestPoint = ballToTarLine.getPointOnLineClosestTo( oppPos );
		
		if( nearestPoint.distXY2( oppPos ) < agentRadius )
		{
			if( ballToTarLine.isInBetween(nearestPoint, ballPos, tarDribbleTo ) )
			{
				HMDribbleLog<< " ------------ shortRunDist 2 " << shortRunDist << endl;
				return shortRunDist;
			}
		}
	}
	HMDribbleLog<< " ------------ longRunDist " << longRunDist << endl;
	return longRunDist;
}
bool Dribble::IsInDribbleArea()
{
	const float dribbleDistEps = 0.4f;
	Vector3f currBallPos = mWorldModel->mBall.mPos;
	Vector3f currMyPos = mWorldModel->mSelf.mPos;
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f oppGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos;
	Vector3f oppGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos;
	//把球门缩小一点以提高射门精度
	oppGoalLeft.z = 0.0f;
	oppGoalRight.z = 0.0f;
	oppGoalLeft.y *= 0.85f;
	oppGoalRight.y *= 0.85f;

	Vector3f ballToOppGoalCenter	= oppGoalCenter - currBallPos;
	Vector3f ballToOppGoalLeft		= oppGoalLeft - currBallPos;
	Vector3f ballToOppGoalRight		= oppGoalRight - currBallPos;

	Vector3f beforeDribble1 = currBallPos - (ballToOppGoalLeft.normalize(dribbleDistEps));
	Vector3f beforeDribble2 = currBallPos - (ballToOppGoalRight.normalize(dribbleDistEps));

	HMDribbleLog << " IsInDribbleArea " << " Before Dribble Point" 
				 << beforeDribble1.x <<" "  << beforeDribble1.y  << " " 
				 << beforeDribble2.x <<" "  << beforeDribble2.y  << endl;

	Triangle beforeDribbleTriangle(beforeDribble1,beforeDribble2,currBallPos);
	return beforeDribbleTriangle.IsInTriangle( currMyPos );
}

bool Dribble::DribbleAttack()
{
	HMDribbleLog << endl << endl << " -------- Game Time " << mWorldModel->mGameTime << endl;
	HMDribbleLog << " Self Pos " << mWorldModel->mSelf.mPos.x << " " << mWorldModel->mSelf.mPos.y << " " << mWorldModel->mSelf.mPos.z << endl;
	HMDribbleLog << " Ball Pos " << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.y << " " << mWorldModel->mBall.mPos.z << endl;

	const float dribbleRadius = 0.095f * 2.0f * 0.6f;   // 0.095f * 2.0f 脚前进时覆盖的宽度
	const float dribbleRunDist = 3.0f;
	const float distBeforeDribble = -0.18f;

	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Vector3f ourGoalCenter = mWorldModel->mOurGoalCenter;
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Vector3f ballPos = mWorldModel->mBall.mPos;
	Angle bodyAng = mWorldModel->mBodyAngle;
	Angle selfToBallAng = selfPos.angTheta2( ballPos );
	Angle BallToGoalAng = ballPos.angTheta2( oppGoalCenter );
	Ray bodyToBallRay = Ray::MakeRayFromPositionAndAngle( ballPos, selfToBallAng );
	Ray ballToBodyRay = Ray::MakeRayFromPositionAndAngle( ballPos, ballPos.angTheta2( selfPos ) );
	Vector3f tempBodyToBallLineDribbleTar = bodyToBallRay.GetPoint( dribbleRunDist );
	const Angle unitAngle = 10.0f;
	//测试
	/*Vector3f Transtar = selfPos;
	Transtar.y=selfPos.y+0.2f;
	
	return DoTranAction( Transtar);*/	
	//测试结束
	
	if (fabs(selfPos.x - ballPos.x) < 0.2f && fabs(selfPos.y - ballPos.y)< 0.2f &&!(mSituation->WeControlBall()))
	{
		Vector3f tarTrans = ballPos;
		tarTrans.y += (ballPos.y - selfPos.y)*3.0f; 
		return DoTranAction(tarTrans);
	}




	if( GetDribbleAttackViability(tempBodyToBallLineDribbleTar) 
		/*	&&  selfPos.distXY2(ballPos) < 1.0f*/
		//&& fabs(bodyAng - selfToBallAng) > 20.0f
		)
	{
		HMDribbleLog << " ----- Dribble Code 1" << endl;
		float distToBall=selfPos.distXY2(ballPos);
		float gotoDist = 1.0f; /*gotoDist = GetDribleDist( tempBodyToBallLineDribbleTar )*/;
	
		Vector3f gotoPos = bodyToBallRay.GetPoint( gotoDist );

		if (distToBall < 0.35f)
		{
			return DoTranAction(ballPos);
		}
		else if (distToBall < 0.7f)
		{
			return DoTranAction(ballPos);
		}
		else 
		{
			return DoGotoAction(ballPos);
		}

		//return DoGotoAction( gotoPos/*, selfToBallAng*/ );
	}

	



	Ray bodyFacingRay = Ray::MakeRayFromPositionAndAngle( selfPos, bodyAng );
	float bodyFacingRayToBallDist = bodyFacingRay.getDistanceWithPoint( ballPos );	
	Vector3f tempDribbleTar = bodyFacingRay.GetPoint( dribbleRunDist );

	if( bodyFacingRayToBallDist <= dribbleRadius && fabs(selfToBallAng) < 90.0f )
	{
		HMDribbleLog << " ----- Dribble Code 2" << endl;
		if( GetDribbleAttackViability(tempDribbleTar) )
		{
			float gotoDist = GetDribleDist( tempDribbleTar );
			Vector3f gotoPos = bodyFacingRay.GetPoint( gotoDist );

			//return DoDribbleAction( tempDribbleTar );
			return DoDribbleAction( gotoPos );
		}
	}

	if( selfPos.x > ballPos.x - 0.1f )//&& ballPos.x < - 0.5f )
	{
		HMDribbleLog << " ----- Dribble Code 0-0" << endl;
		Vector3f beforeDribblePos_1(ballPos.x-0.8f, ballPos.y + 0.2f, 0.0f);
		Vector3f beforeDribblePos_2(ballPos.x-0.8f, ballPos.y - 0.2f, 0.0f);
		Vector3f gotoBeforeDribblePos_1 = beforeDribblePos_1;
		Vector3f gotoBeforeDribblePos_2 = beforeDribblePos_2;
		Vector3f beforeDribblePos;

		if( selfPos.distXY2(gotoBeforeDribblePos_1) < selfPos.distXY2(gotoBeforeDribblePos_2) )
		{
			beforeDribblePos = gotoBeforeDribblePos_1;
		}
		else
		{
			beforeDribblePos = gotoBeforeDribblePos_2;
		}
		return DoGotoAction( beforeDribblePos/*, selfToBallAng*/ );
	}



	//在球门的两侧且带球方向倾向于水平靠近禁区
	if ((ballPos.y<oppGoalCenter.y-mWorldModel->mGoalWidth*0.5f||ballPos.y>oppGoalCenter.y+mWorldModel->mGoalWidth*0.5f)
		&&ballPos.x>oppGoalCenter.x-mWorldModel->mGoalWidth)
	{
		HMDribbleLog << " In Corner " << endl;
		float distToBall=selfPos.distXY2(ballPos);
		Ray gotoRay = Ray::MakeRayFromPositionAndAngle(ballPos,BallToGoalAng);
		Vector3f gotoTar = gotoRay.GetPoint( dribbleRunDist );
		Vector3f beforeDribbleTar = gotoRay.GetPoint(distBeforeDribble*2.0f );
		
		//if( GetDribbleAttackViability(gotoTar) )
		{
			HMDribbleLog << " ----- Dribble Code 3 " <<endl;
			HMDribbleLog << " gotoTar " << gotoTar.x << " " << gotoTar.y << endl;
			HMDribbleLog << " beforeDribbleTar " << beforeDribbleTar.x << " " << beforeDribbleTar.y << endl;

			float distToBeforeDribbleTar = selfPos.distXY2( beforeDribbleTar );
			if (fabs(selfPos.x - beforeDribbleTar.x)<0.1f && fabs(selfPos.y - beforeDribbleTar.y)<0.1f)
			{
				return DoTranAction(gotoTar);
			} 
			else
			{
				return DoTranAction(beforeDribbleTar);
			}

			
		}
	}


	for( int i = 0; i < (int)(360.0f / unitAngle); i ++ )
	{
		for( int j = -1; j < 2; j += 2)
		{
			Angle deltaAngle = (float)(i * j) * unitAngle;
			//Ray gotoRay = Ray::MakeRayFromPositionAndAngle( ballPos, selfToBallAng + deltaAngle );
			Ray gotoRay = Ray::MakeRayFromPositionAndAngle(ballPos,BallToGoalAng);
			Vector3f gotoTar = gotoRay.GetPoint( dribbleRunDist*0.3f );
			float distToBall=selfPos.distXY2(ballPos);
			Vector3f beforeDribbleTar = gotoRay.GetPoint(distBeforeDribble*2.0f );
			//if( GetDribbleAttackViability(gotoTar) )
			{
				HMDribbleLog << " ----- Dribble Code 4 " << i << " " << j << endl;
				HMDribbleLog << " gotoTar " << gotoTar.x << " " << gotoTar.y << endl;
				HMDribbleLog << " beforeDribbleTar " << beforeDribbleTar.x << " " << beforeDribbleTar.y << endl;
				
				float distToBeforeDribbleTar = selfPos.distXY2( beforeDribbleTar );
				/*if (distToBall<0.1f)
				{
					Vector3f beforeDribbleTarNear = gotoRay.GetPoint(distBeforeDribble*10.0f );
                    return DoTranAction( beforeDribbleTarNear);
				}
				else*/ 
				
				if (distToBall < 0.35f)
				{
					return DoTranAction(beforeDribbleTar);
				}
				else if (distToBall < 0.7f)
				{
					return DoTranAction(beforeDribbleTar);
				}
				else 
				{
					return DoGotoAction(beforeDribbleTar);
				}
/*
				if( distToBeforeDribbleTar < 0.1f )
				{
					HMDribbleLog << "In position" << endl;
					return DoDribbleAction( gotoTar);
				}
				else
				{
					HMDribbleLog << "Goto position" << endl;
					return DoGotoAction( beforeDribbleTar );
				}
*/

				//return DoTranAction( selfPos.y-1.0f);
			}
		}
	}

	if( ( mWorldModel->mPlayMode == PM_CORNER_KICK_RIGHT && mWorldModel->mTeamSide == SD_RIGHT )
		|| ( mWorldModel->mPlayMode == PM_CORNER_KICK_LEFT && mWorldModel->mTeamSide == SD_LEFT ) )
	{
		HMDribbleLog << " ----- Dribble Code 5 " << endl;
		Ray kickOffPosRay = Ray::MakeRayFromPositionAndAngle( ballPos, ballPos.angTheta2(oppGoalCenter) );
		Vector3f preKickOffPos = kickOffPosRay.GetPoint( distBeforeDribble );
		Vector3f kickOffPos = kickOffPosRay.GetPoint( dribbleRunDist );
		if( (selfPos.y < ballPos.y + fabs(distBeforeDribble) * 0.5f && selfPos.y > oppGoalCenter.y)
			|| (selfPos.y > ballPos.y - fabs(distBeforeDribble) * 0.5f && selfPos.y < oppGoalCenter.y) )
		{
			return DoGotoAction( preKickOffPos/*, selfToBallAng + deltaAngle*/ );
		}
		else
		{
			return DoDribbleAction( kickOffPos/*, selfToBallAng + deltaAngle*/ );
		}
	}

	HMDribbleLog << " Error: No Position suitable" << endl;

	return DoDribbleAction( ballPos );
}

bool Dribble::DribbleDefense()
{
	return DribbleAttack();
}
bool Dribble::DoDribbleAction( Vector3f tarGoto )
{	
	HMDribbleLog << " Final tarGoto DoDribbleAction " << tarGoto.x << " " << tarGoto.y << endl;

	return mHGoto->GotoTar( tarGoto );
}
bool Dribble::DoDribbleAction( Vector3f tarGoto, Angle tarAng )
{
	HMDribbleLog << " Final tarGoto DoDribbleAction " << tarGoto.x << " " << tarGoto.y << " Angle " << tarAng << endl;
	
	return mHGoto->GotoTar( tarGoto );
}
bool Dribble::DoGotoAction( Vector3f tarGoto )
{
	HMDribbleLog << " Final tarGoto DoGotoAction " << tarGoto.x << " " << tarGoto.y << endl;
	return mHGoto->GotoTar( tarGoto );
	Vector3f tarVec = mObstacle->GetRidOfObstacle( tarGoto );
	HMDribbleLog << " GetRidOfObstacle tarGoto DoGotoAction " << tarGoto.x << " " << tarGoto.y << endl;
	Ray tarVecRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, mWorldModel->mSelf.ThetaTo( tarVec ) );
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Angle ballToOppGoalCenter = InNormalize( mWorldModel->mBall.mPos.angTheta2(oppGoalCenter) );
	Angle ballToSelf = InNormalize( mWorldModel->mBall.mPos.angTheta2(mWorldModel->mSelf.mPos) );
	//float tarGotoLengh = 0.5f;
	const float tarGotoLengh = 0.4f;
	if( mObstacle->IsBallObstacle(tarVec) )
	{
		float distToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

		if( distToBall > tarGotoLengh )
		{
			tarVec = tarVecRay.GetPoint( tarGotoLengh );
			HMDribbleLog << " tarVec changed" << tarVec.x << " " << tarVec.y << endl;
		}
	}
	else if( fabs(Normalize(ballToSelf - ballToOppGoalCenter) ) < 100.0f && mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos ) < 0.2f )
	{
		tarVec = tarVecRay.GetPoint( tarGotoLengh );
		HMDribbleLog << " tarVec changed" << tarVec.x << " " << tarVec.y << endl;
	}

	return mHGoto->GotoTar( tarVec );
}
bool Dribble::DoGotoAction( Vector3f tarGoto, Angle tarAng )
{
	HMDribbleLog << " Final tarGoto DoGotoAction " << tarGoto.x << " " << tarGoto.y << " Angle " << tarAng << endl;
	return mHGoto->GotoTar( tarGoto, tarAng );
	Vector3f tarVec = mObstacle->GetRidOfObstacle( tarGoto );
	HMDribbleLog << " GetRidOfObstacle tarGoto DoGotoAction " << tarGoto.x << " " << tarGoto.y << endl;
	Ray tarVecRay = Ray::MakeRayFromPositionAndAngle( mWorldModel->mSelf.mPos, mWorldModel->mSelf.ThetaTo( tarVec ) );
	Vector3f oppGoalCenter = mWorldModel->mOppGoalCenter;
	Angle ballToOppGoalCenter = InNormalize( mWorldModel->mBall.mPos.angTheta2(oppGoalCenter) );
	Angle ballToSelf = InNormalize( mWorldModel->mBall.mPos.angTheta2(mWorldModel->mSelf.mPos) );
	const float tarGotoLengh = 0.2f;
	if( mObstacle->IsBallObstacle(tarVec) )
	{
		float distToBall = mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos );

		if( distToBall > tarGotoLengh )
		{
			tarVec = tarVecRay.GetPoint( tarGotoLengh );
		}
	}
	else if( fabs(Normalize(ballToSelf - ballToOppGoalCenter) ) < 100.0f && mWorldModel->mSelf.DistXyTo( mWorldModel->mBall.mPos ) < 0.2f )
	{
		tarVec = tarVecRay.GetPoint( tarGotoLengh );
	}

	return mHGoto->GotoTar( tarVec, tarAng );
}
bool Dribble::DoTranAction( Vector3f tarGoto )
{
	HMDribbleLog << " Final tarGoto DoTranAction " << tarGoto.x << " " << tarGoto.y << endl;

	return mHGoto->TranstoTar( tarGoto );
}