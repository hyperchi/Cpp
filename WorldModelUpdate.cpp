#include "WorldModel.h"
#include "Logger.h"
#define WorldLog gLog << "[world ] "

bool WorldModel::WorldModelUpdate()
{
	mCurrentSimCycle ++;
// 	if( mFlagVec.size() < 8 )
// 	{
		return true;
	//}

	SetBodyRotationFromGYR();

	UpdateMyRelPos();
	UpdateMyUniversalPos();
	UpdateBodyState();

	PushBallPos();
	Vector3f preBallPos = PredictBallPos(10);

	//WorldLog << " OurPlayerNumOnField " << mOurPlayerNumOnField 
	//		 <<	" OppPlayerNumOnField " << mOppPlayerNumOnField
	//		 << endl;

	WorldLog << "My Position " << mSelf.mPos.x << " " << mSelf.mPos.y 
			 << " Ball Position " << mBall.mPos.x << " " << mBall.mPos.y
			 << " Ball Real Position " << mBallRealPosFromServer.x << " " << mBallRealPosFromServer.y
			 << endl;

	float bPosX;
	float bPosY;
	float bPosZ;
	GetBallPosFromGYRAndFlag( mBall.mRelPol, bPosX, bPosY, bPosZ );
	//WorldLog << " Ball GYR  Position " << bPosX << " " << bPosY << " " << bPosZ
	//		 << " Ball Real Position " << mBallRealPosFromServer.x << " " << mBallRealPosFromServer.y
	//		 << endl;
	
	Player selfPlayer;
	selfPlayer.mMyPlayerNo = mMyPlayerNo;
	selfPlayer.mPos = mSelf.mPos;

	if( mOurPlayers.size() == 0 )
	{
		mOurPlayers.push_back( selfPlayer );
	}
	else
	{
		for( int i = 0; i < mOurPlayers.size(); i ++ )
		{
			if( mOurPlayers[i].mMyPlayerNo == mMyPlayerNo )
			{
				mOurPlayers[i] = selfPlayer;
				break;
			}
			if( i == mOurPlayers.size() - 1 )
			{
				mOurPlayers.push_back( selfPlayer );
				break;
			}
		}
	}

// 	for( int i = 0; i < mOurPlayers.size(); i ++ )
// 	{
// 		WorldLog << " Our " << mOurPlayers[i].mMyPlayerNo << " " << mOurPlayers[i].mPos.x << " " << mOurPlayers[i].mPos.y << endl;
// 	}
// 	for( int i = 0; i < mOppPlayers.size(); i ++ )
// 	{
// 		WorldLog << " Opp " << mOppPlayers[i].mMyPlayerNo << " " << mOppPlayers[i].mPos.x << " " << mOppPlayers[i].mPos.y << endl;
// 	}
	Angle rollX,pitchY,yawZ;
	mBodyRotation.InvertAngles( rollX, pitchY, yawZ );

	WorldLog << " Roll X: "  << rollX + 90.0f  << " "
		<< " Pitch Y: " << pitchY << " "
		<< " Yaw Z: "   << yawZ << endl;

	//WorldLog << "mBodyAngle " << mBodyAngle << endl;

	if( fabs(pitchY) > 30.0f /*&& !mIsFalled*/ )
	{
		mIsSideFalled = true;
	}
	else
	{
		mIsSideFalled = false;
	}
// 	// 与y轴夹角
// 	WorldLog << " body angle Roll X: "  << rollX + 90.0f << " "
// 			 << " bodyangle "<< mBodyAngle << endl;

// 	WorldLog << "my real pos " << mMyRealPosFromServer.x << " " << mMyRealPosFromServer.y << " " << mMyRealPosFromServer.z << endl;
//  	float myRealX, myRealY, myRealZ;
//  	GetPosFromGYRAndFlag( mFieldFlag[FLAG_OUR_LEFT],myRealX, myRealY, myRealZ );
//  	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldFlag[FLAG_OUR_RIGHT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldFlag[FLAG_OPP_LEFT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldFlag[FLAG_OPP_RIGHT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldGoal[GOAL_OUR_LEFT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldGoal[GOAL_OUR_RIGHT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldGoal[GOAL_OPP_LEFT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
// 
// 	GetPosFromGYRAndFlag( mFieldGoal[GOAL_OPP_RIGHT],myRealX, myRealY, myRealZ );
// 	WorldLog << "my real pos " << myRealX << " " << myRealY << " " << myRealZ << endl;
	//WorldLog << "OurPlayerPosition " << endl;

	//for( unsigned int i = 1; i < mOurPlayerNumOnField; i ++ )
	//{
	//	WorldLog <<  mOurTeamPlayer[i].mMyPlayerNo << " " << mOurTeamPlayer[i].mPos.x << " " << mOurTeamPlayer[i].mPos.y << endl;
	//}
	//
	//WorldLog << "OppPlayerPosition " << endl;

	//for( unsigned int i = 0; i < mOppPlayerNumOnField; i ++ )
	//{
	//	WorldLog << mOppTeamPlayer[i].mMyPlayerNo << " " << mOppTeamPlayer[i].mPos.x << " " << mOppTeamPlayer[i].mPos.y << endl;
	//}
	return true;
}

void WorldModel::UpdateMyRelPos()
{
	int i;	
	for (i = 0; i < FLAG_COUNT; i++)
	{
		mFieldFlag[i].mRelPos.fromPolar3f(mFieldFlag[i].mRelPol);
	}
	for (i = 0; i < GOAL_COUNT; i++)
	{
		mFieldGoal[i].mRelPos.fromPolar3f(mFieldGoal[i].mRelPol);
	}
	for (i = 1; i < mPlayerTotleNum; i++)
	{
		mOurTeamPlayer[i].mRelPos.fromPolar3f(mOurTeamPlayer[i].mRelPol);
	}
	for (i = 0; i < mPlayerTotleNum; i++)
	{
		mOppTeamPlayer[i].mRelPos.fromPolar3f(mOppTeamPlayer[i].mRelPol);
	}

	for( i = 0; i < mOurPlayers.size(); i ++ )
	{
		mOurPlayers[i].mRelPos.fromPolar3f(mOurPlayers[i].mRelPol);
	}

	for( i = 0; i < mOppPlayers.size(); i ++ )
	{
		mOppPlayers[i].mRelPos.fromPolar3f(mOppPlayers[i].mRelPol);
	}
	if (bSeeBall)
	{
		mBall.mRelPos.fromPolar3f(mBall.mRelPol);
	}
}

void WorldModel::UpdateMyUniversalPos()
{
	int i, j;	
	//update tMatrix
	for (i = 0; i < 3; i++)
	{		
		rMatrix[i * 4]		= mFieldGoal[i].mRelPos.x;		
		rMatrix[i * 4 + 1]	= mFieldGoal[i].mRelPos.y;		
		rMatrix[i * 4 + 2]	= mFieldGoal[i].mRelPos.z;		
		rMatrix[i * 4 + 3]	= 1;
	}
	rMatrix[12] = mFieldFlag[0].mRelPos.x;
	rMatrix[13] = mFieldFlag[0].mRelPos.y;
	rMatrix[14] = mFieldFlag[0].mRelPos.z;
	rMatrix[15] = 1;	
	tMatrix = invUmatrix * rMatrix;

	//update my pos
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			eqsMypos.mCoef.SetElement(i, j, -tMatrix.GetElement(j, i));
		}
		eqsMypos.mConst[i] = tMatrix[i + 12];
	}

	if (eqsMypos.GetRoot())
	{
		mSelf.SaveHistoryPos();
		mSelf.SaveHistorySpeed( mSimStepTime );
		mSelf.SaveHistoryAccSpeed( mSimStepTime );
		
		mSelf.mPos.x = eqsMypos.mRoot[0];
		mSelf.mPos.y = eqsMypos.mRoot[1];
		mSelf.mPos.z = eqsMypos.mRoot[2];		
	}

	//Log_Logger<<"[update] "<< "my universal pos: " << mSelf.mPos.x << " " << mSelf.mPos.y
	//	<< " " << mSelf.mPos.z << END;


	//if (fabs(mMyRealPosFromServer.x - mSelf.mPos.x) > 0.3 || fabs(mMyRealPosFromServer.y - mSelf.mPos.y) > 0.3
	//	|| fabs(mMyRealPosFromServer.z - mSelf.mPos.z) > 0.3)
	//{
	//	//	Log_Logger<< "mypos update false" << END;
	//}

	if (tMatrix.Invert())
	{
		//pMatrix[0] = 50;
		pMatrix[0] = mFieldLength;
		pMatrix[1] = 0;
		pMatrix[2] = 0;
		pMatrix[3] = 1;
		pMatrix = pMatrix * tMatrix;
		mBodyFacePoint.x = pMatrix[0];
		mBodyFacePoint.y = pMatrix[1];
		mBodyFacePoint.z = pMatrix[2];

		//update ball
		pMatrix[0] = mBall.mRelPos.x;
		pMatrix[1] = mBall.mRelPos.y;
		pMatrix[2] = mBall.mRelPos.z;
		pMatrix[3] = 1;

		pMatrix = pMatrix * tMatrix;
		
		mBall.SaveHistoryPos();
		mBall.SaveHistorySpeed( mSimStepTime );
		mBall.SaveHistoryAccSpeed( mSimStepTime );
		
		mBall.mPos.x = pMatrix[0];
		mBall.mPos.y = pMatrix[1];
		mBall.mPos.z = pMatrix[2];

		//Log_Logger << "ball pos: " << mBall.mPos.x << " " << mBall.mPos.y
		//	<< " " << mBall.mPos.z << END;


		mBallToSelfAng = Normalize(mBall.mPos.angTheta2(mSelf.mPos));

		bool testRoll = true;
		int countNum;
		int num = mBall.mHistorySpeed.size();
		WorldLog << " num = " << num << endl;
		for (int i = 0; i < num; ++i)
		{
			Vector3f lastBallvec = mBall.mHistorySpeed.back();
			if (lastBallvec.modXY() < EPS)
			{
				testRoll = false;
				countNum++;
			}
		}
		isBallRolling = testRoll;
		if (countNum > 7 && countNum < 10)
		{
			ballStateChange = true;
		}
		
		//	Log_Logger <<"first 0: " << ourTeam[0].mNo<<" :(" << ourTeam[0].mPos.x << ", " << ourTeam[0].mPos.y << ", " << ourTeam[0].mPos.z << ")\n";

		//update my teammates
		for(i = 1; i < mPlayerTotleNum; i++)
		{
			pMatrix[0] = mOurTeamPlayer[i].mRelPos.x;
			pMatrix[1] = mOurTeamPlayer[i].mRelPos.y;
			pMatrix[2] = mOurTeamPlayer[i].mRelPos.z;
			pMatrix[3] = 1;

			pMatrix = pMatrix * tMatrix;
			
			mOurTeamPlayer[i].SaveHistoryPos();
			mOurTeamPlayer[i].SaveHistorySpeed( mSimStepTime );
			mOurTeamPlayer[i].SaveHistoryAccSpeed( mSimStepTime );
			
			mOurTeamPlayer[i].mPos.x = pMatrix[0];
			mOurTeamPlayer[i].mPos.y = pMatrix[1];
			mOurTeamPlayer[i].mPos.z = pMatrix[2];

			//	Log_Logger << "first ourTeam[" << i <<"]: mNo=" <<ourTeam[i].mNo<<" :(" << ourTeam[i].mPos.x << ", " << ourTeam[i].mPos.y << ", " << ourTeam[i].mPos.z << ")\n";
		}

		//update oppteam
		for(i = 0; i < mPlayerTotleNum; i++)
		{
			pMatrix[0] = mOppTeamPlayer[i].mRelPos.x;
			pMatrix[1] = mOppTeamPlayer[i].mRelPos.y;
			pMatrix[2] = mOppTeamPlayer[i].mRelPos.z;
			pMatrix[3] = 1;

			pMatrix = pMatrix * tMatrix;
			mOppTeamPlayer[i].SaveHistoryPos();
			mOppTeamPlayer[i].SaveHistorySpeed( mSimStepTime );
			mOppTeamPlayer[i].SaveHistoryAccSpeed( mSimStepTime );
			mOppTeamPlayer[i].mPos.x = pMatrix[0];
			mOppTeamPlayer[i].mPos.y = pMatrix[1];
			mOppTeamPlayer[i].mPos.z = pMatrix[2];
		}

		for(i = 0; i < mOurPlayers.size(); i++)
		{
			pMatrix[0] = mOurPlayers[i].mRelPos.x;
			pMatrix[1] = mOurPlayers[i].mRelPos.y;
			pMatrix[2] = mOurPlayers[i].mRelPos.z;
			pMatrix[3] = 1;

			pMatrix = pMatrix * tMatrix;
			mOurPlayers[i].SaveHistoryPos();
			mOurPlayers[i].SaveHistorySpeed( mSimStepTime );
			mOurPlayers[i].SaveHistoryAccSpeed( mSimStepTime );
			mOurPlayers[i].mPos.x = pMatrix[0];
			mOurPlayers[i].mPos.y = pMatrix[1];
			mOurPlayers[i].mPos.z = pMatrix[2];
			WorldLog <<" teamPlayer : "<<mOurPlayers[i].mMyPlayerNo <<"  :"<< mOurPlayers[i].mPos.x
					<<" "<<mOurPlayers[i].mPos.y<<
					" "<<mOurPlayers[i].mPos.z<<endl;
		}

		for(i = 0; i < mOppPlayers.size(); i++)
		{
			pMatrix[0] = mOppPlayers[i].mRelPos.x;
			pMatrix[1] = mOppPlayers[i].mRelPos.y;
			pMatrix[2] = mOppPlayers[i].mRelPos.z;
			pMatrix[3] = 1;

			pMatrix = pMatrix * tMatrix;
			mOppPlayers[i].SaveHistoryPos();
			mOppPlayers[i].SaveHistorySpeed( mSimStepTime );
			mOppPlayers[i].SaveHistoryAccSpeed( mSimStepTime );
			mOppPlayers[i].mPos.x = pMatrix[0];
			mOppPlayers[i].mPos.y = pMatrix[1];
			mOppPlayers[i].mPos.z = pMatrix[2];
			WorldLog <<" teamPlayer : "
				<< mOppPlayers[i].mPos.x
				<<" "<<mOppPlayers[i].mPos.y
				<<" "<<mOppPlayers[i].mPos.z<<endl;
		}
	}
}

void WorldModel::UpdateBodyState()
{
	int i;	
	Vector3f  bodyFaceTo;
	mBodyAngle = 0;

	for (i = 0; i < FLAG_COUNT; i++)
	{
		mBodyAngle += Normalize(mSelf.ThetaTo(mFieldFlag[i].mPos)-mFieldFlag[i].mRelPol.theta);	
	}
	for (i = 0; i < GOAL_COUNT; i++)
	{
		mBodyAngle += Normalize(mSelf.ThetaTo(mFieldGoal[i].mPos)-mFieldGoal[i].mRelPol.theta);
	}

	mBodyAngle /= ( FLAG_COUNT + GOAL_COUNT );

	bodyFaceTo = mBodyFacePoint - mSelf.mPos;

	mBodyFaceTo = bodyFaceTo;

	static float lastCycleDipAngle = 0.0f;

	WorldLog << "Body Dip Angle: " << bodyFaceTo.angPhi() << endl;

	if( fabs(bodyFaceTo.angPhi()) > 20.0f )
	{
		WorldLog << "Waring Code: Begin To Fall ! " << endl;

		mBeginToFall = true;
		if( bodyFaceTo.z < EPS )
		{
			mBeginToFowardFall = true;
		}
		else
		{
			mBeginToFowardFall = false;
		}
	}
	else
	{
		mBeginToFall = false;
	}

	if( fabs(bodyFaceTo.angPhi() - lastCycleDipAngle ) > 2.0f )
	{
		WorldLog << " Warining Code: NotStable ! " << endl;
		mIsStable = false;
	}
	else
	{
		mIsStable = true;
	}

	lastCycleDipAngle = bodyFaceTo.angPhi();

	/******modified by gqq*********/

	//cout<< " angle " 
	//	<< bodyFaceTo.angPhi() << endl;
	if ( fabs(bodyFaceTo.angPhi())> 40.0f || mSelf.mPos.z < 0.18 )
	{
		mIsFalled = true;

		//Log_Logger << "[update] " << "Agent fall " <<END;
		if (bodyFaceTo.z > EPS)
		{
			mIsFaceUpFalled = true;

			//Log_Logger << "[update] "<< "face up fall" << END;
		}
		else if(bodyFaceTo.z < EPS)
		{
			mIsFaceUpFalled = false;

			//Log_Logger << "[update] "<< "face down fall" << END;
		}
	}
	else
	{
		mIsFalled = false;
	}	
}

void WorldModel::UpdateGPS()
{
	//LOG_UPDATE << "*****----- ini pos: -----*****" << iniPos.x << " " << iniPos.y
	//	<< " " << iniPos.z << END;
	int i;
	for (i = 0; i < 10; i++)
	{
		UpdateByGPS();
	}

	double errx = iniPos.x - mMyRealPosFromServer.x;
	double erry = iniPos.y - mMyRealPosFromServer.y;
	double errz = iniPos.z - mMyRealPosFromServer.z;

	if (fabs(errx) < 0.01 && fabs(erry) <0.01)
	{		
		if (fabs(errz) > 0.1)
		{
			//Log_Logger << "[Gpsz pos is not usible] "  << END;
		}
	}
	mSelf.SaveHistoryPos();
	mSelf.mPos.x = iniPos.x;
	mSelf.mPos.y = iniPos.y;
	mSelf.mPos.z = iniPos.z;


	//Log_Logger << "My GPS Pos: " << mSelf.mPos.x << " " << mSelf.mPos.y << " " << mSelf.mPos.z << END;
}
void WorldModel::UpdateByGPS()
{

	//标志物与人的初值，即绝对坐标下开场时刻的值。可由BEAM的坐标求得
	int i,j;	
	for (i = 0; i < FLAG_COUNT; i++)
	{
		YMatrix[i] = mFieldFlag[i].mRelPol.dist - mFieldFlag[i].mPos.dist2(iniPos);
		YMatrix[i + 4] = mFieldGoal[i].mRelPol.dist - mFieldGoal[i].mPos.dist2(iniPos);
	}
	for (i = 0; i < FLAG_COUNT; i++)
	{
		HMatrix[i * 3]			= - (mFieldFlag[i].mPos.x - iniPos.x) / mFieldFlag[i].mPos.dist2(iniPos);
		HMatrix[i * 3 + 1]		= - (mFieldFlag[i].mPos.y - iniPos.y) / mFieldFlag[i].mPos.dist2(iniPos);
		HMatrix[i * 3 + 2]		= - (mFieldFlag[i].mPos.z - iniPos.z) / mFieldFlag[i].mPos.dist2(iniPos);		

		HMatrix[(i+4) * 3]		= - (mFieldGoal[i].mPos.x - iniPos.x) / mFieldGoal[i].mPos.dist2(iniPos);
		HMatrix[(i+4) * 3 + 1]	= - (mFieldGoal[i].mPos.y - iniPos.y) / mFieldGoal[i].mPos.dist2(iniPos);
		HMatrix[(i+4) * 3 + 2]	= - (mFieldGoal[i].mPos.z - iniPos.z) / mFieldGoal[i].mPos.dist2(iniPos);
	}
	TraH = HMatrix.Transpose();
	ProH = TraH * HMatrix;
	if (ProH.Invert())
	{
		DeltaMatrix = ProH * TraH * YMatrix;		
	}
	iniPos.x = iniPos.x + DeltaMatrix[0];
	iniPos.y = iniPos.y + DeltaMatrix[1];
	iniPos.z = iniPos.z + DeltaMatrix[2];	
}

void WorldModel::SetBodyRotationFromGYR()
{
	Matrix gyrToRot;
	gyrToRot = gyrToRot.Rpy2Rot( mSensor.mTorsoGYR.x * 0.02f, mSensor.mTorsoGYR.y * 0.02f, mSensor.mTorsoGYR.z * 0.02f );

	mBodyRotation = mBodyRotation * gyrToRot;
// 	WorldLog << endl;
// 	WorldLog << "BodyRotationFromGYR " << mBodyRotation.GetElement(0,0) << " " << mBodyRotation.GetElement(0,1) << " " << mBodyRotation.GetElement(0,2) << endl;
// 	WorldLog << "BodyRotationFromGYR " << mBodyRotation.GetElement(1,0) << " " << mBodyRotation.GetElement(1,1) << " " << mBodyRotation.GetElement(1,2) << endl;
// 	WorldLog << "BodyRotationFromGYR " << mBodyRotation.GetElement(2,0) << " " << mBodyRotation.GetElement(2,1) << " " << mBodyRotation.GetElement(2,2) << endl;
// 	WorldLog << endl;
}

void WorldModel::GetPosFromGYRAndFlag( Object flag, float &myPosX, float &myPosY, float &myPosZ )
{
	Polar3f flagPol = flag.mRelPol;
	float x = flagPol.dist * cosDeg(flagPol.theta) * cosDeg(flagPol.phi);
	float y = flagPol.dist * cosDeg(flagPol.theta) * sinDeg(flagPol.phi);
	float z = flagPol.dist * sinDeg(flagPol.theta);

	float fx = flag.mPos.x;
	float fy = flag.mPos.y;
	float fz = flag.mPos.z;

	Matrix bodyR = mBodyRotation;
	bodyR.Invert();

	Matrix invBodyR(4,4);
	invBodyR.SetElement(0,0,bodyR.GetElement(0,0));
	invBodyR.SetElement(0,1,bodyR.GetElement(0,1));
	invBodyR.SetElement(0,2,bodyR.GetElement(0,2));
	invBodyR.SetElement(0,3,-z);
	invBodyR.SetElement(1,0,bodyR.GetElement(1,0));
	invBodyR.SetElement(1,1,bodyR.GetElement(1,1));
	invBodyR.SetElement(1,2,bodyR.GetElement(1,2));
	invBodyR.SetElement(1,3,x);
	invBodyR.SetElement(2,0,bodyR.GetElement(2,0));
	invBodyR.SetElement(2,1,bodyR.GetElement(2,1));
	invBodyR.SetElement(2,2,bodyR.GetElement(2,2));
	invBodyR.SetElement(2,3,-y);
	invBodyR.SetElement(3,3,1.0f);

	Matrix flagR;
	flagR.MakeUnitMatrix(4);
	flagR.SetElement(0,3,fx);
	flagR.SetElement(1,3,fy);
	flagR.SetElement(2,3,fz);
	flagR.Invert();

	Matrix myRealR;
	myRealR = invBodyR * flagR;
	myRealR.Invert();

	myPosX = myRealR.GetElement(0,3);
	myPosY = myRealR.GetElement(1,3);
	myPosZ = myRealR.GetElement(2,3);	
}

void WorldModel::GetBallPosFromGYRAndFlag(  Polar3f ballRelPol, float &bPosX, float &bPosY, float &bPosZ )
{
	Polar3f ballPol = ballRelPol;
	float x = ballPol.dist * cosDeg(ballPol.phi) * cosDeg( ballPol.theta);
	float y = ballPol.dist * cosDeg(ballPol.phi) * sinDeg( ballPol.theta);
	float z = ballPol.dist * sinDeg(ballPol.phi);

	Matrix bodyR1 = mBodyRotation;

	Matrix bodyR=bodyR1;

	Matrix myPosMatrix(4,4);
	myPosMatrix.SetElement(0,0,bodyR.GetElement(0,0));
	myPosMatrix.SetElement(0,1,bodyR.GetElement(0,1));
	myPosMatrix.SetElement(0,2,bodyR.GetElement(0,2));
	myPosMatrix.SetElement(0,3,mSelf.mPos.x);
	myPosMatrix.SetElement(1,0,bodyR.GetElement(1,0));
	myPosMatrix.SetElement(1,1,bodyR.GetElement(1,1));
	myPosMatrix.SetElement(1,2,bodyR.GetElement(1,2));
	myPosMatrix.SetElement(1,3,mSelf.mPos.y);
	myPosMatrix.SetElement(2,0,bodyR.GetElement(2,0));
	myPosMatrix.SetElement(2,1,bodyR.GetElement(2,1));
	myPosMatrix.SetElement(2,2,bodyR.GetElement(2,2));
	myPosMatrix.SetElement(2,3,mSelf.mPos.z);
	myPosMatrix.SetElement(3,0,0.0f);
	myPosMatrix.SetElement(3,1,0.0f);
	myPosMatrix.SetElement(3,2,0.0f);
	myPosMatrix.SetElement(3,3,1.0f);

	bodyR.Invert();

	Matrix ballRelMatrix(4,4);
	ballRelMatrix.SetElement(0,0,bodyR.GetElement(0,0));
	ballRelMatrix.SetElement(0,1,bodyR.GetElement(0,1));
	ballRelMatrix.SetElement(0,2,bodyR.GetElement(0,2));
	ballRelMatrix.SetElement(0,3,-y);
	ballRelMatrix.SetElement(1,0,bodyR.GetElement(1,0));
	ballRelMatrix.SetElement(1,1,bodyR.GetElement(1,1));
	ballRelMatrix.SetElement(1,2,bodyR.GetElement(1,2));
	ballRelMatrix.SetElement(1,3,x);
	ballRelMatrix.SetElement(2,0,bodyR.GetElement(2,0));
	ballRelMatrix.SetElement(2,1,bodyR.GetElement(2,1));
	ballRelMatrix.SetElement(2,2,bodyR.GetElement(2,2));
	ballRelMatrix.SetElement(2,3,z);
	ballRelMatrix.SetElement(3,0,0.0f);
	ballRelMatrix.SetElement(3,1,0.0f);
	ballRelMatrix.SetElement(3,2,0.0f);
	ballRelMatrix.SetElement(3,3,1.0f);

	Matrix ballPosMatrix(4,4);
	ballPosMatrix = myPosMatrix*ballRelMatrix;

	bPosX = ballPosMatrix.GetElement(0,3);
	bPosY = ballPosMatrix.GetElement(1,3);
	bPosZ = ballPosMatrix.GetElement(2,3);	
}

void WorldModel::PushBallPos()
{
	if( mBall.mPos.distXY2( mBallHistoryPos.at(0) ) > 0.05f )
	{
		mBallHistoryPos.push_front( mBall.mPos );
		mBallHistoryPos.pop_back();
	}
}
Vector3f WorldModel::PredictBallPos( unsigned int frameNum )
{
	const double para = -0.014;
	double dealtT = mSimStepTime;
	double ballR = mBodyRadius;
	double k = exp( para );

	double currX = mBall.mPos.x;
	double currY = mBall.mPos.y;

	double Vx0 = ( currX - mBallHistoryPos.at(1).x ) / dealtT;
	double Vy0 = ( currY - mBallHistoryPos.at(1).y ) / dealtT;

	double preX = currX;
	double preY = currY;
	double sumX = 0.0;
	double sumY = 0.0;

	for( unsigned int i = 0; i < frameNum; i ++ )
	{
		sumX += Vx0 * pow(k, (int)i) * dealtT;
		sumY += Vy0 * pow(k, (int)i) * dealtT;
		preX += sumX;
		preY += sumY;
	}
	
	Vector3f res( preX, preY, ballR );

	//WorldLog << " PreBall Pos " << res.x << " " << Vx0 << " " << mBallHistoryPos.at(1).x << endl;

	//WorldLog << " CurrBall Pos " << currX << endl;
	return res;
}


