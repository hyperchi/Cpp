#include "WorldModel.h"
#include "Predicate.h"
#include "Logger.h"
#define ParseLog gLog<< "[parse ] "

bool WorldModel::WorldModelParse( const string &msg )
{
	mPlayerNumOnField = 1;
	mOurPlayerNumOnField = 1;
	mOppPlayerNumOnField = 0;

	//mOurPlayers.clear();
	//mOppPlayers.clear();

	mOurPlayerNoISee.clear();
	mOppPlayerNoISee.clear();

	mFlagUse.clear();
	mFlagVec.clear();

	bSeeBall = false;

	static PlayModeT lastPlayMode;
	vector <Predicate> predList;		
	int head =(int) msg.find("(");					//解析'('
	if ( head == -1)
	{
		return false;
	}
	if (!Parser::Parse(msg.substr(head), predList))
	{
		return false;
	}
	if (predList.size() < 1)
	{
		return false;
	}

	for (int i = 0; i < (int)predList.size(); ++ i)  
	{
		if (predList[i].name == "time")			//解析'time',比赛时间
		{
			mLastSimTime = mSimTime;			
			
			predList[i].GetValue("now", mSimTime);
			
			float dTime = mSimTime - mLastSimTime;
			
			if ( dTime > 0.021f  )
			{
				ParseLog << "Lost Package at: " << mSimTime << END;
			}
		}
		else if(predList[i].name == "GS")		//解析比赛状态
		{
			string pMode;
			string side;
			
			if (mTeamSide == SD_UNKNOWN)
			{
				if (predList[i].GetValue("team", side))
				{
					if (side == "right")
					{
						mTeamSide = SD_RIGHT;
					}
					else
					{
						mTeamSide = SD_LEFT;
					}
				}
			}			
			
			predList[i].GetValue("t", mGameTime);
			predList[i].GetValue("pm", pMode);	
			
			PlayModeMap::iterator iter = mPlayModeMap.find(pMode);
			mPlayMode = (PlayModeT)(*iter).second;
			
			if( ( lastPlayMode == PM_GOAL_LEFT && mTeamSide == SD_LEFT ) 
				|| ( lastPlayMode == PM_GOAL_RIGHT && mTeamSide == SD_RIGHT )
				)
			{

				if( mPlayMode == PM_KICK_OFF_RIGHT && mTeamSide == SD_LEFT 
					||  mPlayMode == PM_KICK_OFF_LEFT && mTeamSide == SD_RIGHT )
				{
					mOurScore++;
				}
			}
			else if( ( lastPlayMode == PM_GOAL_LEFT && mTeamSide == SD_RIGHT ) 
					|| ( lastPlayMode == PM_GOAL_RIGHT && mTeamSide == SD_LEFT )
					)
			{

				if( mPlayMode == PM_KICK_OFF_RIGHT && mTeamSide == SD_RIGHT 
					||  mPlayMode == PM_KICK_OFF_LEFT && mTeamSide == SD_LEFT )
				{
					mOppScore++;
				}
			}	

			lastPlayMode = mPlayMode;
		}
		else if (predList[i].name == "hear")
		{
			predList[i].GetValue("hear",mHearMsg);
			ParseLog << " Hear " << mHearMsg.mHearTime << " " << mHearMsg.mAngle << " mHeardMessage : " << mHearMsg.mHeardMessage << endl;
		}
		else if(predList[i].name == "GYR")		//解析GYR
		{
			string name;
			predList[i].GetValue("n", name);			
			if (name == "arm")
			{
				predList[i].GetValue("rt", mSensor.mArmGYR);
			}
			else if (name == "torso")
			{
				predList[i].GetValue("rt", mSensor.mTorsoGYR);
				predList[i].GetValue("R", mBodyRotationRight);
				predList[i].GetValue("U", mBodyRotationUp);
				predList[i].GetValue("F", mBodyRotationForward);
				predList[i].GetValue("P", mBodyRotationPos);
				predList[i].GetValue("velocity", mBodyVelocity);
// 				ParseLog<< " torso GYR " 
// 						<< mSensor.mTorsoGYR.x << " "
// 						<< mSensor.mTorsoGYR.y << " "
// 						<< mSensor.mTorsoGYR.z << endl << endl;
// 
// 				ParseLog<< " torso rot "
// 						<< mBodyRotationRight.x << " "
// 						<< mBodyRotationRight.y << " "
// 						<< mBodyRotationRight.z << " "
// 						<< endl;
// 				ParseLog<< " torso rot "		
// 						<< mBodyRotationUp.x << " "
// 						<< mBodyRotationUp.y << " "
// 						<< mBodyRotationUp.z << " "
// 						<< endl;
// 				ParseLog<< " torso rot "
// 						<< mBodyRotationForward.x << " "
// 						<< mBodyRotationForward.y << " "
// 						<< mBodyRotationForward.z << " "
// 						<< endl
// 						<< endl;

				//ParseLog<< " torso vel " 
				//	<< mBodyVelocity.x << " "
				//	<< mBodyVelocity.y << " "
				//	<< mBodyVelocity.z << endl;
			}
		}
		else if(predList[i].name == "See")		//解析视觉信息
		{
			ParseVision(predList[i]);
		}
		else if(predList[i].name == "HJ")		//一自由度关节信息
		{
			string HJName;
			HJointT hjID;
			
			predList[i].GetValue("n", HJName);
			
			HJMap::iterator iter = mHjMap.find(HJName);
			hjID = (HJointT)(*iter).second;
			
			predList[i].GetValue("ax", mSensor.mHJ[hjID].mAxis);	//对应关节轴

		}
		//else if(predList[i].name == "UJ")		//二自由度关节信息
		//{

		//	string UJName;
		//	UJointT ujId;
		//	predList[i].GetValue("n", UJName);
		//	UJMap::iterator iter = ujMap.find(UJName);
		//	ujId = (UJointT)(*iter).second;
		//	predList[i].GetValue("ax1", sensor.mUJ[ujId].mAxis1);
		//	predList[i].GetValue("ax2", sensor.mUJ[ujId].mAxis2);

		//}
		else if(predList[i].name == "FRP")		//FRP信息
		{
			string FRPName;
			
			predList[i].GetValue("n", FRPName);
			
			if (FRPName == "lf")				//左足
			{
				predList[i].GetValue("c", mSensor.mLeftFRP.mFRP_C);
				predList[i].GetValue("f", mSensor.mLeftFRP.mFRP_F);
 			//	cout<< " lf " << mSensor.mLeftFRP.mFRP_C.x << " " 
 			//				  << mSensor.mLeftFRP.mFRP_C.y << " "
 			//				  << mSensor.mLeftFRP.mFRP_C.z << " "
 			//				  << mSensor.mLeftFRP.mFRP_F.x << " "
 			//				  << mSensor.mLeftFRP.mFRP_F.y << " "
 			//				  << mSensor.mLeftFRP.mFRP_F.z << " ";

				//float fx = mSensor.mLeftFRP.mFRP_F.x;
				//float fy = mSensor.mLeftFRP.mFRP_F.y;
				//float fz = mSensor.mLeftFRP.mFRP_F.z;

				//cout<< " ---- " << sqrt( fx * fx + fy * fy + fz * fz ) << endl;

			} 
			else //右足
			{
				predList[i].GetValue("c", mSensor.mRightFRP.mFRP_C);
				predList[i].GetValue("f", mSensor.mRightFRP.mFRP_F);

 			//	cout<< " rf " << mSensor.mRightFRP.mFRP_C.x << " " 
 			//		<< mSensor.mRightFRP.mFRP_C.y << " "
 			//		<< mSensor.mRightFRP.mFRP_C.z << " "
 			//		<< mSensor.mRightFRP.mFRP_F.x << " "
 			//		<< mSensor.mRightFRP.mFRP_F.y << " "
 			//		<< mSensor.mRightFRP.mFRP_F.z << " ";
				//float fx = mSensor.mRightFRP.mFRP_F.x;
				//float fy = mSensor.mRightFRP.mFRP_F.y;
				//float fz = mSensor.mRightFRP.mFRP_F.z;

				//cout<< " ---- " << sqrt( fx * fx + fy * fy + fz * fz ) << endl;
			}
		}
	}

	return true;
}
bool WorldModel::ParseVision( Predicate &pred )
{
	if (pred.GetValue("mypos", mMyRealPosFromServer))
	{
		// /usr/local/share/rcssserver3d/rsg/agent/nao/nao.rsg
		ParseLog << "mypos " << mMyRealPosFromServer.x << " " << mMyRealPosFromServer.y << " " << mMyRealPosFromServer.z << END;
	}

	if (pred.GetValue("ballpos", mBallRealPosFromServer))
	{
		// /usr/local/share/rcssserver3d/rsg/agent/nao/nao.rsg
		ParseLog << "ballpos " << mBallRealPosFromServer.x << " " << mBallRealPosFromServer.y << " " << mBallRealPosFromServer.z << END;
	}
	////////////////////////////
	//临时代码,当前版本视角没有限制
	//!!!!!!!!注意!!!!!!!!!!!!
	//init.cpp Initialize（）做相应修改
	//2008-7-2 By Leo
	///////////////////////////
	for(int i = 0; i < mPlayerTotleNum; i++ )
	{
		mOppTeamPlayer[i].mMyPlayerNo = -1;

		mOppTeamPlayer[i].mRelPol.dist = 100.0f;
		mOppTeamPlayer[i].mRelPol.phi = 0.0f;
		mOppTeamPlayer[i].mRelPol.theta = 0.0f;
		
		mOppTeamPlayer[i].mPos.x = 0.0f;
		mOppTeamPlayer[i].mPos.y = 0.0f;
		mOppTeamPlayer[i].mPos.z = 0.0f;

		mOurTeamPlayer[i].mMyPlayerNo = -1;
		
		mOurTeamPlayer[i].mRelPol.dist = 100.0f;
		mOurTeamPlayer[i].mRelPol.phi = 0.0f;
		mOurTeamPlayer[i].mRelPol.theta = 0.0f;
		
		mOurTeamPlayer[i].mPos.x = 100.0f;
		mOurTeamPlayer[i].mPos.y = 100.0f;
		mOurTeamPlayer[i].mPos.z = 100.0f;
	}

	////////////////////////////////
	////////////////////////////////

	for (multimap<string, Predicate>::iterator iter = pred.child.begin();
		iter != pred.child.end(); ++iter) 
	{
		Predicate& childPred = iter->second;

		if (childPred.child.size() < 1) 
		{
			continue;
		}


		string name = childPred.name;			
		if (name == "F1L")						//左标志物1
		{
			FlagAgentSee tempFlagAgentSee;
			
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OPP_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OPP_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OPP_RIGHT].mRelPol;
			}
			else
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OUR_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OUR_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OUR_LEFT].mRelPol;
			}	

			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "F2L")					//左标志物2
		{
			FlagAgentSee tempFlagAgentSee;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OPP_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OPP_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OPP_LEFT].mRelPol;
			} 
			else
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OUR_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OUR_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OUR_RIGHT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "F1R")					//右标志物1
		{
			FlagAgentSee tempFlagAgentSee;
			//flagcount[2]=1;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OUR_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OUR_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OUR_RIGHT].mRelPol;
				
			} 
			else
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OPP_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OPP_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OPP_LEFT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "F2R")					//右标志物２
		{
			FlagAgentSee tempFlagAgentSee;
			//flagcount[3]=1;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OUR_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OUR_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OUR_LEFT].mRelPol;
			} 
			else
			{
				childPred.GetValue("pol", mFieldFlag[FLAG_OPP_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_FLAG_OPP_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_FLAG_OPP_RIGHT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "G1L")					//左门1
		{
			FlagAgentSee tempFlagAgentSee;
			//flagcount[4]=1;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OPP_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OPP_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OPP_RIGHT].mRelPol;
			} 
			else
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OUR_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OUR_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OUR_LEFT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "G2L")					//左门2
		{
			FlagAgentSee tempFlagAgentSee;			
			//flagcount[5]=1;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OPP_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OPP_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OPP_LEFT].mRelPol;
			} 
			else
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OUR_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OUR_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OUR_RIGHT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "G1R")					//右门１
		{
			
			FlagAgentSee tempFlagAgentSee;
			//flagcount[6]=1;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OUR_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OUR_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OUR_RIGHT].mRelPol;
			} 
			else
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OPP_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OPP_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OPP_LEFT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );
		}
		else if (name == "G2R")					//右门2
		{
			FlagAgentSee tempFlagAgentSee;
			//flagcount[7]=1;
			if (mTeamSide == SD_RIGHT)
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OUR_LEFT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OUR_LEFT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OUR_LEFT].mRelPol;
			} 
			else
			{
				childPred.GetValue("pol", mFieldGoal[GOAL_OPP_RIGHT].mRelPol);
				tempFlagAgentSee.flagT = FAG_GOAL_OPP_RIGHT;
				tempFlagAgentSee.flagRelPol = mFieldFlag[FAG_GOAL_OPP_RIGHT].mRelPol;
			}
			mFlagVec.push_back( tempFlagAgentSee );

		}
		else if (name == "B")					//球
		{			
			childPred.GetValue("pol", mBall.mRelPol);
			bSeeBall = true;
		}		
		else if (name == "P")					//球员
		{
			mPlayerNumOnField ++;
			string pTeamName;
			int pId;
			
			childPred.GetValue("team", pTeamName);//所属球队名
			childPred.GetValue("id", pId);        //号码

			//ofstream testI("testParse.log",ios::app);
			//string name = childPred.name;
			//testI << name.c_str()<<endl;
			Predicate headChild;

			if (childPred.GetChild("head",headChild))
			{
				string strT =  headChild.name;
				Player tempOurPlayer;
				headChild.GetValue("pol",tempOurPlayer.mRelPol);
// 				testI << strT.c_str()<< "  Pol :"<<tempOurPlayer.mRelPol.dist
// 					<< " " <<tempOurPlayer.mRelPol.phi
// 					<< " " << tempOurPlayer.mRelPol.theta 
// 					<< endl;
			}
			
			if (pTeamName == mTeamName)
			{
				if( pId == 9 )
				{
					pId = 3;
				}
				else if( pId == 10 )
				{
					pId = 4;
				}

				mOurPlayerNumOnField ++;
				mOurPlayerNoISee.push_back(pId);

				// *********************************************
				// 添加视角限制
				Player tempOurPlayer;

				tempOurPlayer.mMyPlayerNo = pId;
				//ofstream testI("tst.log",ios::app);
				//testI << childPred.GetValue("pol", tempOurPlayer.mRelPol);
				
				if (childPred.GetChild("head",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOurPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOurPlayer.mRelPol.dist
						<< " " <<tempOurPlayer.mRelPol.phi
						<< " " << tempOurPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("rlowerarm",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOurPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOurPlayer.mRelPol.dist
						<< " " <<tempOurPlayer.mRelPol.phi
						<< " " << tempOurPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("llowerarm",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOurPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOurPlayer.mRelPol.dist
						<< " " <<tempOurPlayer.mRelPol.phi
						<< " " << tempOurPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("rfoot",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOurPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOurPlayer.mRelPol.dist
						<< " " <<tempOurPlayer.mRelPol.phi
						<< " " << tempOurPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("lfoot",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOurPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOurPlayer.mRelPol.dist
						<< " " <<tempOurPlayer.mRelPol.phi
						<< " " << tempOurPlayer.mRelPol.theta 
						<< endl;
				}
				//else 
				//{
				//	childPred.GetValue("pol",tempOurPlayer.mRelPol);
				//}
				
				if( mOurPlayers.size() == 0 )
				{
					mOurPlayers.push_back( tempOurPlayer );
				}
				else
				{
					for( int i = 0; i < mOurPlayers.size(); i ++ )
					{
						if( mOurPlayers[i].mMyPlayerNo == pId )
						{
							mOurPlayers[i] = tempOurPlayer;
							break;
						}

						if( i == mOurPlayers.size() - 1 )
						{
							mOurPlayers.push_back( tempOurPlayer );
							break;
						}
					}
				}

				// *********************************************

				for (int i = 1; i < mPlayerTotleNum; i++)
				{
					if (mOurTeamPlayer[i].mMyPlayerNo < 0 || mOurTeamPlayer[i].mMyPlayerNo == pId)
					{
						mOurTeamPlayer[i].mMyPlayerNo = pId;
						childPred.GetValue("pol", mOurTeamPlayer[i].mRelPol);
						break;
					}
				}			
			}
			else
			{
				mOppPlayerNoISee.push_back(pId);

				mOppTeamName = pTeamName;

				mOppPlayerNumOnField ++;

				// *********************************************
				// 添加视角限制
				Player tempOppPlayer;
				tempOppPlayer.mMyPlayerNo = pId;
				childPred.GetValue("pol", tempOppPlayer.mRelPol);

				if (childPred.GetChild("head",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOppPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOppPlayer.mRelPol.dist
						<< " " <<tempOppPlayer.mRelPol.phi
						<< " " << tempOppPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("rlowerarm",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOppPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOppPlayer.mRelPol.dist
						<< " " <<tempOppPlayer.mRelPol.phi
						<< " " << tempOppPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("llowerarm",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOppPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOppPlayer.mRelPol.dist
						<< " " <<tempOppPlayer.mRelPol.phi
						<< " " << tempOppPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("rfoot",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOppPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOppPlayer.mRelPol.dist
						<< " " <<tempOppPlayer.mRelPol.phi
						<< " " << tempOppPlayer.mRelPol.theta 
						<< endl;
				}
				else if(childPred.GetChild("lfoot",headChild))
				{
					string strT =  headChild.name;
					headChild.GetValue("pol",tempOppPlayer.mRelPol);
					ParseLog << strT.c_str()<< "  Pol :"<<tempOppPlayer.mRelPol.dist
						<< " " <<tempOppPlayer.mRelPol.phi
						<< " " << tempOppPlayer.mRelPol.theta 
						<< endl;
				}

				if( mOppPlayers.size() == 0 )
				{
					mOppPlayers.push_back( tempOppPlayer );
				}
				else
				{
					for( int i = 0; i < mOppPlayers.size(); i ++ )
					{
						if( mOppPlayers[i].mMyPlayerNo == pId )
						{
							mOppPlayers[i] = tempOppPlayer;
							break;
						}

						if( i == mOppPlayers.size() - 1 )
						{
							mOppPlayers.push_back( tempOppPlayer );
							break;
						}
					}
				}
				// *********************************************

				for (int i = 0; i < mPlayerTotleNum; i++)
				{
					if (mOppTeamPlayer[i].mMyPlayerNo < 0 || mOppTeamPlayer[i].mMyPlayerNo == (pId + 11))
					{
						mOppTeamPlayer[i].mMyPlayerNo = pId + 11;
						childPred.GetValue("pol", mOppTeamPlayer[i].mRelPol);
						break;
					}
				}	
			}
		}
		else
		{
			// for unknown object
		}		
	}

	mOurTeamPlayer[0].mMyPlayerNo = mSelf.mMyPlayerNo;
	mOurTeamPlayer[0].mPos = mSelf.mPos;

	return true;

}