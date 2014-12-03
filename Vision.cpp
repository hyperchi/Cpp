#include "Vision.h"
#include "Logger.h"
#define VisionLog gVisionInfoLog<< "[vision] "
#define VisionGLog gLog<< "[vision] "


Vision::Vision( WorldModel *wm )
{
	lastSeeBallTime = 0.0f;
	mWorldModel = wm;
	InitGYR();
	mSelf.mPos.x = mWorldModel->mInitBeamPos.beamPara[0];
	mSelf.mPos.y = mWorldModel->mInitBeamPos.beamPara[1];
	mSelf.mPos.z = 0.40f;

	mPredictBallPos = mWorldModel->mPredictBallPos;
	mNeedToLocateBall = false;

	mOurPlayers.resize(0);
	mOppPlayers.resize(0);
}
Vision::~Vision()
{

}
int Vision::FlagNumISee()
{
	return mWorldModel->mFlagVec.size();
}
void Vision::UpdatePos()
{
	static PlayModeT lastPlayModeT = mWorldModel->mPlayMode;
	if( mWorldModel->mPlayMode == PM_GOAL_LEFT || mWorldModel->mPlayMode == PM_GOAL_RIGHT )
	{
		if( lastPlayModeT != mWorldModel->mPlayMode )
		{
			InitGYR();
		}
	}
	lastPlayModeT = mWorldModel->mPlayMode;
	UpdateInitial();
	UpdateGYR();
	LocateSelfPos();
    
	LocateBall();

	LocatePlayer(); //

	UpdateBodyState();
	UpdateWorldModel();

	UpdateVisibleObject();
}
void Vision::UpdateInitial()
{
	for (int i = 0; i < mWorldModel->mFlagVec.size(); i++)
	{
		mWorldModel->mFlagVec[i].mRelPos.fromPolar3f(mWorldModel->mFlagVec[i].flagRelPol);
	}

	for( int n = 0; n < mWorldModel->mFlagVec.size(); n ++ )
	{
		switch (mWorldModel->mFlagVec[n].flagT)
		{
		case FAG_FLAG_OUR_LEFT :  
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_FLAG_OUR_LEFT];
			break;

		case FAG_FLAG_OUR_RIGHT :
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_FLAG_OUR_RIGHT];
			break;

		case FAG_FLAG_OPP_LEFT:
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_FLAG_OPP_LEFT];
			break; 
		case FAG_FLAG_OPP_RIGHT:
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_FLAG_OPP_RIGHT];
			break;
		}

		switch(mWorldModel->mFlagVec[n].flagT)
		{
		case FAG_GOAL_OUR_LEFT:
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_GOAL_OUR_LEFT];
			break;

		case FAG_GOAL_OUR_RIGHT:
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_GOAL_OUR_RIGHT];
			break;

		case FAG_GOAL_OPP_LEFT:
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_GOAL_OPP_LEFT];
			break;

		case FAG_GOAL_OPP_RIGHT:
			mWorldModel->mFlagVec[n].flagInfo = mWorldModel->mFieldFlag[FAG_GOAL_OPP_RIGHT];
			break;
		}
	}

	//ballrelpos !!! transfer or not  //NO
    if (mWorldModel->bSeeBall)
	{
		mWorldModel->mBall.mRelPos.fromPolar3f(mWorldModel->mBall.mRelPol); 
    }
}

void Vision::InitGYR()
{
	Matrix initMatrix(3,3);
	initMatrix.SetElement(0,0,0.0f);
	initMatrix.SetElement(0,1,1.0f);
	initMatrix.SetElement(0,2,0.0f);
	initMatrix.SetElement(1,0,-1.0f);
	initMatrix.SetElement(1,1,0.0f);
	initMatrix.SetElement(1,2,0.0f);
	initMatrix.SetElement(2,0,0.0f);
	initMatrix.SetElement(2,1,0.0f);
	initMatrix.SetElement(2,2,1.0f);

	mBodyRotation = Matrix::Rpy2Rot( 0.0f, 0.0f, mWorldModel->mInitBeamPos.beamPara[2] );
	mBodyRotation = initMatrix * mBodyRotation;
	mBodyRotation.PrintMatrix();
}
//iterator to update gyr
void Vision::UpdateGYR()
{
	Matrix gyrToRot;
	gyrToRot = gyrToRot.Rpy2Rot( mWorldModel->mSensor.mTorsoGYR.x * 0.02f, mWorldModel->mSensor.mTorsoGYR.y * 0.02f, mWorldModel->mSensor.mTorsoGYR.z * 0.02f );

	mBodyRotation = mBodyRotation * gyrToRot;
}
void Vision::ModifyGYR()
{
	Matrix gyrToRot;

	float a1,a2,a3;
	a1= mSelf.mPos.x;
	a2= mSelf.mPos.y;
	a3= mSelf.mPos.z;
	float fx1;
	float fy1;
	float fz1;
	float fx2;
	float fy2;
	float fz2;
	float fx3;
	float fy3;
	float fz3;

	GetFlagPos( mWorldModel->mFlagVec[0].flagT, fx1, fy1, fz1 );
	GetFlagPos( mWorldModel->mFlagVec[1].flagT, fx2, fy2, fz2 );
	GetFlagPos( mWorldModel->mFlagVec[2].flagT, fx3, fy3, fz3 );

	Matrix flag(3,3);
	flag.SetElement(0,0,fx1-a1);
	flag.SetElement(0,1,fx2-a1);
	flag.SetElement(0,2,fx3-a1);
	flag.SetElement(1,0,fy1-a2);
	flag.SetElement(1,1,fy2-a2);
	flag.SetElement(1,2,fy3-a2);
	flag.SetElement(2,0,fz1-a3);
	flag.SetElement(2,1,fz2-a3);
	flag.SetElement(2,2,fz3-a3);

	Matrix flagRel(3,3);
	flagRel.SetElement(0,0,-mWorldModel->mFlagVec[0].mRelPos.y);
	flagRel.SetElement(0,1,-mWorldModel->mFlagVec[1].mRelPos.y);
	flagRel.SetElement(0,2,-mWorldModel->mFlagVec[2].mRelPos.y);
	flagRel.SetElement(1,0,mWorldModel->mFlagVec[0].mRelPos.x);
	flagRel.SetElement(1,1,mWorldModel->mFlagVec[1].mRelPos.x);
	flagRel.SetElement(1,2,mWorldModel->mFlagVec[2].mRelPos.x);
	flagRel.SetElement(2,0,mWorldModel->mFlagVec[0].mRelPos.z);
	flagRel.SetElement(2,1,mWorldModel->mFlagVec[1].mRelPos.z);
	flagRel.SetElement(2,2,mWorldModel->mFlagVec[2].mRelPos.z);
// 	VisionLog << "flag " << flag.GetElement(0,0) << " " << flag.GetElement(0,1) << " " << flag.GetElement(0,2) << endl;
// 	VisionLog << "flag " << flag.GetElement(1,0) << " " << flag.GetElement(1,1) << " " << flag.GetElement(1,2) << endl;
// 	VisionLog << "flag " << flag.GetElement(2,0) << " " << flag.GetElement(2,1) << " " << flag.GetElement(2,2) << endl;
// 	VisionLog << endl;
// 
// 	VisionLog << "flagrel " << flagRel.GetElement(0,0) << " " << flagRel.GetElement(0,1) << " " << flagRel.GetElement(0,2) << endl;
// 	VisionLog << "flagrel " << flagRel.GetElement(1,0) << " " << flagRel.GetElement(1,1) << " " << flagRel.GetElement(1,2) << endl;
// 	VisionLog << "flagrel " << flagRel.GetElement(2,0) << " " << flagRel.GetElement(2,1) << " " << flagRel.GetElement(2,2) << endl;
// 	VisionLog << endl;
	VisionLog << " flagRel detvalue: "<<flagRel.Det()<<endl;
	if (fabs(flagRel.Det())< 0.15) 
	{
		//bFallByZ = true;
		VisionLog << "biaoji:! "<<endl;
		return ;  //illegal
	}

	flagRel.Invert();
	Matrix BodyRotationinit;
	BodyRotationinit=flag*flagRel;

// 	VisionLog << "BodyRotationchange " << BodyRotationinit.GetElement(0,0) << " " << BodyRotationinit.GetElement(0,1) << " " << BodyRotationinit.GetElement(0,2) << endl;
// 	VisionLog << "BodyRotationchange " << BodyRotationinit.GetElement(1,0) << " " << BodyRotationinit.GetElement(1,1) << " " << BodyRotationinit.GetElement(1,2) << endl;
// 	VisionLog << "BodyRotationchange " << BodyRotationinit.GetElement(2,0) << " " << BodyRotationinit.GetElement(2,1) << " " << BodyRotationinit.GetElement(2,2) << endl;
// 	VisionLog << endl;
// 
// 	VisionLog << "BodyRotationchange " << mBodyRotation.GetElement(0,0) << " " << mBodyRotation.GetElement(0,1) << " " << mBodyRotation.GetElement(0,2) << endl;
// 	VisionLog << "BodyRotationchange " << mBodyRotation.GetElement(1,0) << " " << mBodyRotation.GetElement(1,1) << " " << mBodyRotation.GetElement(1,2) << endl;
// 	VisionLog << "BodyRotationchange " << mBodyRotation.GetElement(2,0) << " " << mBodyRotation.GetElement(2,1) << " " << mBodyRotation.GetElement(2,2) << endl;
// 	VisionLog << endl;
	if (mWorldModel->mPlayMode != PM_BEFORE_KICK_OFF)
	{
		mBodyRotation=BodyRotationinit;
		SubHeadRotation(mBodyRotation); //1	
	}	
}
void Vision::LocateSelfPos()
{
	int flagISeeNum = FlagNumISee();
	VisionLog << " FlagNumISee " << flagISeeNum << endl;

	bool bModify = true; 
	
	if( flagISeeNum <= 2&&flagISeeNum >=1 )
	{
		LocateSelf_1();
	}
	else if( flagISeeNum == 3 )
	{
		bModify = (LocateSelf_3() == 2)?true:false ;
	}
	else if( flagISeeNum == 4 )
	{
		int leftFlagNum = 0;
		int rightFlagNum = 0;

		for( int i = 0; i < 4; i ++ )
		{
			if( mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_LEFT
				|| mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_RIGHT
				|| mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_LEFT
				|| mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_RIGHT )
			{
				leftFlagNum ++;
			}
			else
			{
				rightFlagNum ++;
			}
		}
		if( leftFlagNum == 4 || rightFlagNum == 4 )
		{
			bModify = (LocateSelf_3() == 2)?true:false ;
		}
		else
		{
			char cFlag[10];
			sprintf(cFlag,"%d%d%d%d",mWorldModel->mFlagVec[0].flagT,mWorldModel->mFlagVec[1].flagT,mWorldModel->mFlagVec[2].flagT,mWorldModel->mFlagVec[3].flagT);
			string sFlag = string(cFlag);
			VisionLog<<"sFlags: "<< sFlag.c_str()<<END;
			if ( sFlag.find("1")!=-1&&sFlag.find("3")!=-1&&sFlag.find("5")!=-1&&sFlag.find("7")!=-1
				|| sFlag.find("0")!=-1&&sFlag.find("2")!=-1&&sFlag.find("4")!=-1&&sFlag.find("6")!=-1)
			{
				bModify = (LocateSelf_3() == 2)?true:false ;
			}
			else LocateSelf_4_Ideal();
		}
	}
	else if( flagISeeNum == 8 )
	{
		LocateWithNoVisionRestrict();
	}
	else if( flagISeeNum > 4 )
	{
		LocateSelf_4_Ideal();
	}

	if (!bModify)
	{
		VisionLog <<" bmodify: no!"<<endl;
		//cout<<" bmodify: no!"<<endl;
	}

	if( flagISeeNum >= 3 && bModify  )
	{
		ModifyGYR();
	}
}

void Vision::LocateBall()
{
	if (mWorldModel->bSeeBall)
	{	
		//if (!mWorldModel->mIsFalled)
		VisionLog << "I see ball " << endl;
		{
			float tX,tY,tZ;
			GetBallPosFromGYRAndBallPol(mWorldModel->mBall.mRelPol,tX,tY,tZ);

			VisionLog<< "mBallrelpol : "<<mWorldModel->mBall.mRelPol.dist << " " << mWorldModel->mBall.mRelPol.phi << " " <<mWorldModel->mBall.mRelPol.theta<< endl;

			mBall.mPos.x = tX;
			mBall.mPos.y = tY;
			mBall.mPos.z = tZ;

			lastSeeBallTime = mWorldModel->mSimTime;

			Angle rollX,pitchY,yawZ;
			mBodyRotation.InvertAngles( rollX, pitchY, yawZ );
			VisionLog << "lastSeeBallTime: " << lastSeeBallTime <<endl;
			VisionLog << "ballPosTest(GYR):  " << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.z 
				<< " head " << mWorldModel->mSensor.mHJ[Head_1].mAxis << " " << mWorldModel->mSensor.mHJ[Head_2].mAxis 
				<< " ballpol " <<mWorldModel->mBall.mRelPol.dist << " " << mWorldModel->mBall.mRelPol.phi << " " <<mWorldModel->mBall.mRelPol.theta
				<< " gyr:" <<  rollX << " " << pitchY << " "  << yawZ 
				<< endl;
		}
	}
	else 
	{
		VisionLog << "I don't see ball " << endl;
		if( mWorldModel->mSimTime - lastSeeBallTime > 2.0f )
		{
			VisionLog << "2S no see ball! : " << endl;
			if( mWorldModel->mPlayMode != PM_BEFORE_KICK_OFF )
			{
				mNeedToLocateBall = true;
			}
		}
		else
		{
			mNeedToLocateBall = false;
		}
		VisionLog <<mWorldModel->mSimTime <<" ballPosTest(GYR) no see ball:  " << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.x << " " << mWorldModel->mBall.mPos.z << " "<<endl;
	}
}
//!!move to updateModel
void Vision::LocatePlayer()
{
	//LocateOtherAgent_4_Ideal();
	if( mWorldModel->mOurPlayerNoISee.size() == 0 )
	{
		//当前周期无视觉
		return;
	}
	mOurPlayers = mWorldModel->mOurPlayers;
	mOppPlayers = mWorldModel->mOppPlayers;

	for(int i = 0; i < mOurPlayers.size(); i++)
	{
		bool bISee = false;
		for(int j = 0; j < mWorldModel->mOurPlayerNoISee.size(); j ++ )
		{
			if( mOurPlayers.at(i).mMyPlayerNo == mWorldModel->mOurPlayerNoISee.at(j) )
			{
				bISee = true;
				break;
			}
		}
		if( bISee )
		{
			float tX,tY,tZ;
			if( mOurPlayers[i].mMyPlayerNo != mWorldModel->mMyPlayerNo )
			{
				GetOthersPosFromGYRAndRel(mOurPlayers[i].mRelPol,tX,tY,tZ );
				mOurPlayers[i].mPos.x = tX;
				mOurPlayers[i].mPos.y = tY;
				mOurPlayers[i].mPos.z = tZ;
			}
		}
	}

	for(int i = 0; i < mOurPlayers.size(); i++)
	{
		if( mOurPlayers[i].mMyPlayerNo == mWorldModel->mMyPlayerNo )
		{
			mOurPlayers[i].mPos.x = mSelf.mPos.x;
			mOurPlayers[i].mPos.y = mSelf.mPos.y;
			mOurPlayers[i].mPos.z = mSelf.mPos.z;
			break;
		}
	}

	for(int i = 0; i < mOppPlayers.size(); i++)
	{
		bool bISee = false;
		for(int j = 0; j < mWorldModel->mOppPlayerNoISee.size(); j ++ )
		{
			if( mOppPlayers.at(i).mMyPlayerNo == mWorldModel->mOppPlayerNoISee.at(j) )
			{
				bISee = true;
				break;
			}
		}
		if( bISee )
		{
			float tX,tY,tZ;
			GetOthersPosFromGYRAndRel(mOppPlayers[i].mRelPol,tX,tY,tZ );
			mOppPlayers[i].mPos.x = tX;
			mOppPlayers[i].mPos.y = tY;
			mOppPlayers[i].mPos.z = tZ;
		}
	}
}
// use flag 1 2 3 5 to locate self
void Vision::LocateWithNoVisionRestrict()
{
	for (int i = 0; i < FLAG_COUNT; i++)
	{
		mWorldModel->mFieldFlag[i].mRelPos.fromPolar3f(mWorldModel->mFieldFlag[i].mRelPol);
	}
	for (int i = 0; i < GOAL_COUNT; i++)
	{
		mWorldModel->mFieldGoal[i].mRelPos.fromPolar3f(mWorldModel->mFieldGoal[i].mRelPol);
	}

	Matrix worldFlag(4,4);
	worldFlag.SetElement( 0, 0, mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos.x );
	worldFlag.SetElement( 0, 1, mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos.y );
	worldFlag.SetElement( 0, 2, mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos.z );
	worldFlag.SetElement( 0, 3, 1.0f );

	worldFlag.SetElement( 1, 0, mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos.x );
	worldFlag.SetElement( 1, 1, mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos.y );
	worldFlag.SetElement( 1, 2, mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos.z );
	worldFlag.SetElement( 1, 3, 1.0f );

	worldFlag.SetElement( 2, 0, mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.x );
	worldFlag.SetElement( 2, 1, mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.y );
	worldFlag.SetElement( 2, 2, mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.z );
	worldFlag.SetElement( 2, 3, 1.0f );

	worldFlag.SetElement( 3, 0, mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.x );
	worldFlag.SetElement( 3, 1, mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.y );
	worldFlag.SetElement( 3, 2, mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.z );
	worldFlag.SetElement( 3, 3, 1.0f );

	Matrix localFlag(4,4);
	for (int i = 0; i < 3; i++)
	{		
		localFlag[i * 4]		= mWorldModel->mFieldGoal[i].mRelPos.x;		
		localFlag[i * 4 + 1]	= mWorldModel->mFieldGoal[i].mRelPos.y;		
		localFlag[i * 4 + 2]	= mWorldModel->mFieldGoal[i].mRelPos.z;		
		localFlag[i * 4 + 3]	= 1;
	}
	localFlag[12] = mWorldModel->mFieldFlag[0].mRelPos.x;
	localFlag[13] = mWorldModel->mFieldFlag[0].mRelPos.y;
	localFlag[14] = mWorldModel->mFieldFlag[0].mRelPos.z;
	localFlag[15] = 1.0f;	

	Matrix translate;
	worldFlag.Invert();
	translate = worldFlag * localFlag;

	LEquations	eqsMypos;
	eqsMypos.Init(3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			eqsMypos.mCoef.SetElement(i, j, -translate.GetElement(j, i));
		}
		eqsMypos.mConst[i] = translate[i + 12];
	}

	if (eqsMypos.GetRoot())
	{
		mSelf.mPos.x = eqsMypos.mRoot[0];
		mSelf.mPos.y = eqsMypos.mRoot[1];
		mSelf.mPos.z = eqsMypos.mRoot[2];		
		VisionLog << "NoVisionRestrict my pos: " <<  mSelf.mPos.x  << " " << mSelf.mPos.y  << " " << mSelf.mPos.z << endl;
	}
}
void Vision::LocateSelf_1()
{
	for ( int i = 0;i<mWorldModel->mFlagVec.size();i++)
	{
		VisionLog << "I See flag " << mWorldModel->mFlagVec[i].flagT <<"   " ;
	}
	int usedFlag = 0;

	if (mWorldModel->mSelf.mPos.x > mWorldModel->mFieldLength/3)
	{
		for (int i = 0;i<mWorldModel->mFlagVec.size();i++)
		{
			if (mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OPP_LEFT
				||mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OPP_RIGHT
				||mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OPP_LEFT
				||mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OPP_RIGHT )
			{
				usedFlag = i;
				break;
			}
		}
	}

	if (mWorldModel->mSelf.mPos.x < -mWorldModel->mFieldLength/3)
	{
		for (int i = 0;i<mWorldModel->mFlagVec.size();i++)
		{
			if (mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_LEFT
				||mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_RIGHT
				||mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_LEFT
				||mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_RIGHT )
			{
				usedFlag = i;
				break;
			}
		}
	}
	VisionLog << "i use !: "<<mWorldModel->mFlagVec[usedFlag].flagT<<endl;
	Polar3f flagPol = mWorldModel->mFlagVec[usedFlag].flagRelPol;
	float x = flagPol.dist * cosDeg(flagPol.phi) * cosDeg(flagPol.theta);
	float y = flagPol.dist * cosDeg(flagPol.phi) * sinDeg(flagPol.theta);
	float z = flagPol.dist * sinDeg(flagPol.phi);

	float fx;
	float fy;
	float fz;

	GetFlagPos( mWorldModel->mFlagVec[usedFlag].flagT, fx, fy, fz );

	Matrix bodyR = mBodyRotation;

	AddHeadRotation(bodyR);
	bodyR.Invert();

	VisionLog << "flagPol : " << fx << " "<< fy << " "<< fz << " flagPos "<< x << " "<< y << " " << z <<endl;

	Matrix invBodyR(4,4);
	invBodyR.SetElement(0,0,bodyR.GetElement(0,0));
	invBodyR.SetElement(0,1,bodyR.GetElement(0,1));
	invBodyR.SetElement(0,2,bodyR.GetElement(0,2));
	invBodyR.SetElement(0,3,-y);
	invBodyR.SetElement(1,0,bodyR.GetElement(1,0));
	invBodyR.SetElement(1,1,bodyR.GetElement(1,1));
	invBodyR.SetElement(1,2,bodyR.GetElement(1,2));
	invBodyR.SetElement(1,3,x);
	invBodyR.SetElement(2,0,bodyR.GetElement(2,0));
	invBodyR.SetElement(2,1,bodyR.GetElement(2,1));
	invBodyR.SetElement(2,2,bodyR.GetElement(2,2));
	invBodyR.SetElement(2,3,z);
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

	mSelf.mPos.x = myRealR.GetElement(0,3);
	mSelf.mPos.y = myRealR.GetElement(1,3);
	mSelf.mPos.z = myRealR.GetElement(2,3);	

	VisionLog << "my 1 vision pos: " <<  myRealR.GetElement(0,3)  << " " << myRealR.GetElement(1,3)  << " " << myRealR.GetElement(2,3) << endl;
}
bool Vision::LocateSelf_4_Ideal()
{
	vector<FlagAgentSee> flagUse;
	vector<unsigned int> flagSeeLeft;
	vector<unsigned int> flagSeeRight;

	for( int i = 0; i < FlagNumISee(); i ++ )
	{
		if( mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_LEFT
			|| mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_RIGHT
			|| mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_LEFT
			|| mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_RIGHT )
		{
			flagSeeLeft.push_back( i );
		}
		else
		{
			flagSeeRight.push_back( i );
		}
	}
	if (FlagNumISee()==4)
	{
	for( int i = 0; i < ( flagSeeLeft.size() <= 3 ? flagSeeLeft.size(): 3 ); i ++ )
	{
		flagUse.push_back( mWorldModel->mFlagVec[ flagSeeLeft[i] ] );
	}
		int flagNum = flagUse.size();
		for( int i = 0; i < ( 4 - flagNum ); i ++ )
	{
		flagUse.push_back( mWorldModel->mFlagVec[ flagSeeRight[i] ] );
	}
	}
	else if (FlagNumISee()>4)
	{
		VisionLog<<"flag all i see! :  ";
		for (int i = 0;i<mWorldModel->mFlagVec.size();i++)
		{
			VisionLog<<mWorldModel->mFlagVec[i].flagT<<" ";
		}
		VisionLog<<endl;
		for( int i = 0; i < ( flagSeeLeft.size() <= 3 ? flagSeeLeft.size(): 3 ); i ++ )
		{
			flagUse.push_back( mWorldModel->mFlagVec[ flagSeeLeft[i] ] );
		}
		int flagNum = flagUse.size();
		string sFlag;
		for (int i = 0;i<flagNum ;i++)
		{
			char temp[2];
			sprintf(temp,"%d",flagUse[i].flagT);
			sFlag +=string(temp);
		}
		VisionLog << "before: "<<sFlag.c_str()<<" !    ";
		for( int i = 0; i < ( 4 - flagNum ); i ++ )
		{
			string preStr = sFlag;
			char temp[2];
			sprintf(temp,"%d",mWorldModel->mFlagVec[ flagSeeRight[i] ].flagT);
			preStr += string(temp);
			if (preStr.find("1")!=-1&&preStr.find("3")!=-1&&preStr.find("5")!=-1&&preStr.find("7")!=-1
			 || preStr.find("0")!=-1&&preStr.find("2")!=-1&&preStr.find("4")!=-1&&preStr.find("6")!=-1)
			{
				flagNum --;
				continue;
			}
			sFlag = preStr;
			VisionLog << "loop: "<<sFlag.c_str()<<" !    ";
			flagUse.push_back( mWorldModel->mFlagVec[ flagSeeRight[i] ] );
		}
	}

	
	VisionLog << "LocateSelf_4_Ideal " << "Flags I use " 
			  << flagUse[0].flagT << " "
			  << flagUse[1].flagT << " "
			  << flagUse[2].flagT << " "
			  << flagUse[3].flagT << endl;

	float x1,y1,z1;
	GetFlagPos( flagUse[0].flagT, x1,y1,z1 );
	float x2,y2,z2;
	GetFlagPos( flagUse[1].flagT, x2,y2,z2 );
	float x3,y3,z3;
	GetFlagPos( flagUse[2].flagT, x3,y3,z3 );
	float x4,y4,z4;
	GetFlagPos( flagUse[3].flagT, x4,y4,z4 );
	
	Matrix wFlag(4,4);
	wFlag[0] = x1;	wFlag[1] = y1;	wFlag[2] = z1;	wFlag[3] = 1.0f;
	wFlag[4] = x2;	wFlag[5] = y2;	wFlag[6] = z2;	wFlag[7] = 1.0f;
	wFlag[8] = x3;	wFlag[9] = y3;	wFlag[10] = z3;	wFlag[11] = 1.0f;
	wFlag[12] = x4;	wFlag[13] = y4;	wFlag[14] = z4;	wFlag[15] = 1.0f;

	Matrix lFlag(4,4);
	for(int i = 0; i < 4; i ++ )
	{
		flagUse[i].mRelPos.fromPolar3f( flagUse[i].flagRelPol );
	}

	float fx1,fy1,fz1;
	GetFlagPos( flagUse[0], fx1,fy1,fz1 );
	float fx2,fy2,fz2;
	GetFlagPos( flagUse[1], fx2,fy2,fz2 );
	float fx3,fy3,fz3;
	GetFlagPos( flagUse[2], fx3,fy3,fz3 );
	float fx4,fy4,fz4;
	GetFlagPos( flagUse[3], fx4,fy4,fz4 );

	lFlag[0] = fx1;	lFlag[1] = fy1;	lFlag[2] = fz1;	lFlag[3] = 1.0f;
	lFlag[4] = fx2;	lFlag[5] = fy2;	lFlag[6] = fz2;	lFlag[7] = 1.0f;
	lFlag[8] = fx3;	lFlag[9] = fy3;	lFlag[10] = fz3;lFlag[11] = 1.0f;
	lFlag[12] = fx4;lFlag[13] = fy4;lFlag[14] = fz4;lFlag[15] = 1.0f;

	wFlag.Invert();
// 	VisionLog << wFlag[0] << " " <<  wFlag[1] << " " <<  wFlag[2] << " " <<  wFlag[3] << endl;
// 	VisionLog << wFlag[4] << " " <<  wFlag[5] << " " <<  wFlag[6] << " " <<  wFlag[7] << endl;
// 	VisionLog << wFlag[8] << " " <<  wFlag[9] << " " <<  wFlag[10] << " " << wFlag[11] << endl;
// 	VisionLog << wFlag[12] << " "<<  wFlag[13] << " "<<  wFlag[14] << " "<<  wFlag[15] << endl << endl;
// 
// 	VisionLog << lFlag[0] << " " << lFlag[1] << " " << lFlag[2] << " " << lFlag[3] << endl;
// 	VisionLog << lFlag[4] << " " << lFlag[5] << " " << lFlag[6] << " " << lFlag[7] << endl;
// 	VisionLog << lFlag[8] << " " << lFlag[9] << " " << lFlag[10] << " " << lFlag[11] << endl;
// 	VisionLog << lFlag[12] << " " << lFlag[13] << " " << lFlag[14] << " " << lFlag[15] << endl << endl;
	Matrix transBody;
	transBody = wFlag;
	transBody = transBody * lFlag;
// 	VisionLog << transBody[0] << " " << transBody[1] << " " << transBody[2] << " " << transBody[3] << endl;
// 	VisionLog << transBody[4] << " " << transBody[5] << " " << transBody[6] << " " << transBody[7] << endl;
// 	VisionLog << transBody[8] << " " << transBody[9] << " " << transBody[10] << " " <<transBody[11] << endl;
// 	VisionLog << transBody[12] << " "<< transBody[13] << " "<< transBody[14] << " "<< transBody[15] << endl << endl;	
	Matrix rotBody(3,3);
	rotBody[0] = transBody[0];		rotBody[1] = transBody[1];		rotBody[2] = transBody[2];
	rotBody[3] = transBody[4];		rotBody[4] = transBody[5];		rotBody[5] = transBody[6];
	rotBody[6] = transBody[8];		rotBody[7] = transBody[9];		rotBody[8] = transBody[10];
	
	Matrix  posBody(1,3);
	posBody[0] = transBody[12];		posBody[1] = transBody[13];		posBody[2] = transBody[14];	
// 	VisionLog << rotBody[0] << " " << rotBody[1] << " " << rotBody[2] << endl;
// 	VisionLog << rotBody[3] << " " << rotBody[4] << " " << rotBody[5] << endl;
// 	VisionLog << rotBody[6] << " " << rotBody[7] << " " << rotBody[8] << endl << endl;
// 	
// 	VisionLog << posBody[0] << " " << posBody[1] << " " << posBody[2] << endl << endl;
	rotBody = rotBody.Transpose();
	rotBody.Invert();
	posBody = posBody.Transpose();

	Matrix bodyPos; 
	bodyPos = rotBody * (-1.0f);
	bodyPos = bodyPos * posBody;
	
	mSelf.mPos.x = bodyPos[0];
	mSelf.mPos.y = bodyPos[1];
	mSelf.mPos.z = bodyPos[2];

	VisionLog << "LocateSelf_4_Ideal " << bodyPos[0] << " " << bodyPos[1] << " " << bodyPos[2] << endl;
}
//!!
int Vision::LocateSelf_3()
{
	float posX1,posY1,posZ1;
	float posX2,posY2,posZ2;
	int returnValue;
	if( (returnValue = Get_3_SpereInterception( posX1,posY1,posZ1,posX2,posY2,posZ2 )) != 2 )
	{
		if ( returnValue == 8 )
	{
			VisionLog << "use local 1: "<<endl;
			LocateSelf_1();
		}
		return returnValue;
	}

	Vector3f pos1(posX1,posY1,posZ1);
	Vector3f pos2(posX2,posY2,posZ2);

	float distT1,distT2;
	distT1 = sqrt((posX1 - mSelf.mPos.x)*(posX1 - mSelf.mPos.x)+(posY1- mSelf.mPos.y)*(posY1 - mSelf.mPos.y));
	distT2 = sqrt((posX2 - mSelf.mPos.x)*(posX2 - mSelf.mPos.x)+(posY2- mSelf.mPos.y)*(posY2 - mSelf.mPos.y));
	
	float dist1 = pos1.distXY2( mSelf.mPos );
	float dist2 = pos2.distXY2( mSelf.mPos );
	VisionLog << "first " << posX1 << " " << posY1 << " " << posZ1 << " second " << posX2 << " " << posY2 << " " << posZ2 << " dist " << dist1 << " " << dist2 << "distT1" <<distT1 <<" "<<distT2<< endl;

	if  ( ( posX1 == posX2 ) && ( posY1 == posY2 ) && ( posZ1 == posZ2 ) ) 
	{
		mSelf.mPos.x = posX1;
		mSelf.mPos.y = posY1;
		mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
	}
	else if (( posX1 != posX2 ) && ( posY1 == posY2 ) && ( posZ1 == posZ2 ))
	{	
		if ( fabs(posX1) > fabs(posX2) )
		{

			if( fabs(posX1) > mWorldModel->mFieldLength * 0.6f )
			{
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
			}
			else if ( dist1 < dist2 )
		{
			mSelf.mPos.x = posX1;
			mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
		}
		else 
		{
 		mSelf.mPos.x = posX2;
 		mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
	}
		}
		else
		{
			if( fabs(posX2) > mWorldModel->mFieldLength * 0.6f )
			{
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;

	}
			else if ( dist2 < dist1 )
	{
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
			}
			else
			{
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
			}

		}

	}
	else if (( posX1 == posX2 ) && ( posY1 != posY2 ) && ( posZ1 == posZ2 ))
	{	
		if ( fabs(posY1) > fabs(posY2) )
		{

			if( fabs(posY1) > mWorldModel->mFieldWidth * 0.6f )
			{
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
			
			}
			else if ( dist1 < dist2 )
			{	
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
			}
			else
			{
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;

			}
		}
		else
		{
			if( fabs(posY2) > mWorldModel->mFieldWidth * 0.6f )
			{
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
			
			}
			else if ( dist2 < dist1 )
			{	
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
			}
			else
			{
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;

			}

		}

	}
	else if (( posX1 == posX2 ) && ( posY1 == posY2 ) && ( posZ1 != posZ2 ))
	{	
		if ( fabs(posZ1) > fabs(posZ2) )
		{

			if( fabs(posZ1) >1.0f )
			{
				if (posZ2>0.8f)
				{
					mSelf.mPos.x = posX2;
					mSelf.mPos.y = posY2;
					mSelf.mPos.z = 0.5f;
				}
				else
		{
			mSelf.mPos.x = posX2;
			mSelf.mPos.y = posY2;
			mSelf.mPos.z = posZ2;
		}
			}
			else if ( dist1 < dist2 )
			{	
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;

			}
		else
		{
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;

			}
		}

		else
		{
			if( fabs(posZ2) > 1.0f )
			{
				if (posZ1>0.8f)
				{
					mSelf.mPos.x = posX1;
					mSelf.mPos.y = posY1;
					mSelf.mPos.z = 0.5f;
				}
				else
				{

 		mSelf.mPos.x = posX1;
 		mSelf.mPos.y = posY1;
 		mSelf.mPos.z = posZ1;
	}
	}
			else if ( dist2 < dist1 )
			{	
				mSelf.mPos.x = posX2;
				mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;

			}
			else
			{
				mSelf.mPos.x = posX1;
				mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;

			}

		}

	}
	/*if ((( posX1 != posX2 ) && ( posY1 != posY2 ) && ( posZ1 == posZ2 ))
	||(( posX1 != posX2 ) && ( posY1 == posY2 ) && ( posZ1 != posZ2 ))
	(( posX1 == posX2 ) && ( posY1 != posY2 ) && ( posZ1 != posZ2 ))
	)*/
	else 
	{
		if( fabs(posX1) > mWorldModel->mFieldLength * 0.6f 
			|| fabs(posY1) > mWorldModel->mFieldWidth *0.6f
			|| fabs(posZ1) > 1.0f
			)
		{	
			mSelf.mPos.x = posX2;
			mSelf.mPos.y = posY2;
			mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
			
		}
		else if( fabs(posX2) > mWorldModel->mFieldLength * 0.6f 
			|| fabs(posY2) > mWorldModel->mFieldWidth * 0.6f
			|| fabs(posZ2) > 1.0f
			)
		{	
			mSelf.mPos.x = posX1;
			mSelf.mPos.y = posY1;
			mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
			
		}
	else if( posZ2 > 0.0f && fabs(posZ2) < 1.0f && posZ1 < 0.0f )
	{
			mSelf.mPos.x = posX2;
			mSelf.mPos.y = posY2;
			mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;

	}
	else if( posZ1 > 0.0f && fabs(posZ1) < 1.0f && posZ2 < 0.0f )
	{
			mSelf.mPos.x = posX1;
			mSelf.mPos.y = posY1;
			mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
	}
	else
	{
		if( dist1 < dist2 )
		{
			 	mSelf.mPos.x = posX1;
			 	mSelf.mPos.y = posY1;
				mSelf.mPos.z = fabs(posZ1) > 0.8f?0.5f:posZ1;
		}
		else
		{
		 		mSelf.mPos.x = posX2;
		 		mSelf.mPos.y = posY2;
				mSelf.mPos.z = fabs(posZ2) > 0.8f?0.5f:posZ2;
		}
	}
	}
	///*if( fabs(posX1) > mWorldModel->mFieldLength * 0.6f 
	//	|| fabs(posY1) > mWorldModel->mFieldWidth *0.6f
	//	|| fabs(posZ1) > 1.0f
	//	)
	//{		
	//	if (fabs(posX2)*fabs(posY2)*fabs(posZ2) > fabs(posX1)*fabs(posY1)*fabs(posZ1))
	//	{
	//		mSelf.mPos.x = posX1;
	//		mSelf.mPos.y = posY1;
	//		mSelf.mPos.z = posZ1;
	//	}
	//	else 
	//	{
	//		mSelf.mPos.x = posX2;
	//		mSelf.mPos.y = posY2;
	//		mSelf.mPos.z = posZ2;
	//	}

	//}
	//else if( fabs(posX2) > mWorldModel->mFieldLength * 0.6f 
	//	|| fabs(posY2) > mWorldModel->mFieldWidth * 0.6f
	//	|| fabs(posZ2) > 1.0f
	//	)
	//{	
	//	if(  fabs(posX1)*fabs(posY1)*fabs(posZ1) > fabs(posX2)*fabs(posY2)*fabs(posZ2)
	//		)
	//	{
	//		mSelf.mPos.x = posX2;
	//		mSelf.mPos.y = posY2;
	//		mSelf.mPos.z = posZ2;
	//	}
	//	else
	//	{
	//		mSelf.mPos.x = posX1;
	//		mSelf.mPos.y = posY1;
	//		mSelf.mPos.z = posZ1;
	//	}
	//}
	//else if( posZ2 > 0.0f && fabs(posZ2) < 1.0f && posZ1 < 0.0f )
	//{
	//	
	//}
	//else if( posZ1 > 0.0f && fabs(posZ1) < 1.0f && posZ2 < 0.0f )
	//{

	//}
	//else
	//{
	//	if( dist1 < dist2 )
	//	{
	//	 	mSelf.mPos.x = posX1;
	//	 	mSelf.mPos.y = posY1;
	//	 	mSelf.mPos.z = posZ1;
	//	}
	//	else
	//	{
	// 		mSelf.mPos.x = posX2;
	// 		mSelf.mPos.y = posY2;
	// 		mSelf.mPos.z = posZ2;
	//	}
	//}*/

	/*mSelf.mPos.x = posX1;
	mSelf.mPos.y = posY1;
	mSelf.mPos.z = posZ1;*/
	VisionLog << "myPos(2point): " <<mSelf.mPos.x << " "<<mSelf.mPos.y << " "<<mSelf.mPos.z <<endl;
	return returnValue;
}
int Vision::Get_3_SpereInterception( float &posX1, float &posY1, float &posZ1, float &posX2, float &posY2, float &posZ2 )
{
	// 求解方程组：
	// (x-x1)^2 + (y-y1)^2 + (z-z1)^2 = r1^2
	// (x-x2)^2 + (y-y2)^2 + (z-z2)^2 = r2^2
	// (x-x3)^2 + (y-y3)^2 + (z-z3)^2 = r3^2
	// 即三个球的交点
	// 理论上，交点有两个，需要通过worldmodel信息舍去其中一个
	// 
	// 将方程变形为：
	// x^2 + y^2 + z^2 - 2*x1*x - 2*y1*y - 2*z1*z = r1^2 - x1^2 - y1^2 - z1^2 = m1		……（1）
	// x^2 + y^2 + z^2 - 2*x2*x - 2*y2*y - 2*z2*z = r2^2 - x2^2 - y2^2 - z2^2 = m2		……（2）
	// x^2 + y^2 + z^2 - 2*x3*x - 2*y3*y - 2*z3*z = r3^2 - x3^2 - y3^2 - z3^2 = m3		……（3）
	// 然后（1）-（2）、（1）-（3），消去二次项
	// 得到 x y z的线性方程组，再消元得到结果
	float x1,y1,z1;
	GetFlagPos( mWorldModel->mFlagVec[0].flagT, x1,y1,z1 );
	float x2,y2,z2;
	GetFlagPos( mWorldModel->mFlagVec[1].flagT, x2,y2,z2 );	
	float x3,y3,z3;
	GetFlagPos( mWorldModel->mFlagVec[2].flagT, x3,y3,z3 );

	float r1 = mWorldModel->mFlagVec[0].flagRelPol.dist;
	float r2 = mWorldModel->mFlagVec[1].flagRelPol.dist;
	float r3 = mWorldModel->mFlagVec[2].flagRelPol.dist;

	float point_z1 = 0.0f;
	float point_z2 = 0.0f;
	float point_x1 = 0.0f;
	float point_x2 = 0.0f;
	float point_y1 = 0.0f;
	float point_y2 = 0.0f;

	float m1 = r1*r1 - x1*x1 - y1*y1 - z1*z1;
	float m2 = r2*r2 - x2*x2 - y2*y2 - z2*z2;
	float m3 = r3*r3 - x3*x3 - y3*y3 - z3*z3;

	// x = a1 + b1*z
	// y = a2 + b2*z
	float a1 = 0.0f;
	float b1 = 0.0f;
	float a2 = 0.0f;
	float b2 = 0.0f;

	if( fabs(x2-x1) < EPS && fabs(x3-x1) < EPS 
		&& fabs(y2-y1) < EPS && fabs(y3-y1) < EPS
		)
	{
		return -1;//两球的球心相同 或  两球的球心x-y坐标相同，z不同
	}

	if( fabs(x2-x1) < EPS )
	{
		a2 = (m1-m2)/(y2-y1)*0.5f;
		b2 = 0.0f;
		//b2 = -(z2-z1)/(y2-y1);
	}
	else if( fabs(x3-x1) < EPS )
	{
		a2 = (m1-m3)/(y3-y1)*0.5f;
		b2 = 0.0f;
		//b2 = -(z3-z1)/(y3-y1);
	}
	else 
	{
		if( fabs(y2-y1) > EPS || fabs(y3-y1) > EPS )
		{
			float numerator_1;	//分子 a2
			float numerator_2;	//分子 b2
			float denominator;	//分母

			numerator_1 = (m1-m2)/(x2-x1)*0.5f - (m1-m3)/(x3-x1)*0.5f;
			numerator_2 = -(z2-z1)/(x2-x1)+(z3-z1)/(x3-x1);
			denominator = (y2-y1)/(x2-x1)-(y3-y1)/(x3-x1);

			a2 = numerator_1 / denominator;
			b2 = numerator_2 / denominator;
		}
		else
		{
			point_z1 = point_z2 = 0.5f*( (m1-m2)*(x3-x1)-(m1-m3)*(x2-x1) ) / ( (z2-z1)*(x3-x1) - (z3-z1)*(x2-x1) );
			point_x1 = point_x2 = (0.5f*(m1-m2)-(z2-z1)*point_z1)/(x2-x1);
			point_y1 = sqrt( r1*r1 - (point_z1-z1)*(point_z1-z1) - (point_x1-x1)*(point_x1-x1) ) + y1;
			point_y2 = -sqrt( r1*r1 - (point_z1-z1)*(point_z1-z1) - (point_x1-x1)*(point_x1-x1) ) + y1;
	
			posX1 = point_x1;
			posY1 = point_y1;
			posZ1 = point_z1;
			posX2 = point_x2;
			posY2 = point_y2;
			posZ2 = point_z2;

			return 2;
		}
	}

	if( fabs(y2-y1) < EPS )
	{
		a1 = (m1-m2)/(x2-x1)*0.5f;
		b1 = 0.0f;
	}
	else if( fabs(y3-y1) < EPS )
	{
		a1 = (m1-m3)/(x3-x1)*0.5f;
		b1 = 0.0f;
	}
	else
	{
		if( fabs(x2-x1) > EPS || fabs(x3-x1) > EPS )
		{
			float numerator_1;	//分子 a1
			float numerator_2;	//分子 b1
			float denominator;	//分母

			numerator_1 = (m1-m2)/(y2-y1)*0.5f - (m1-m3)/(y3-y1)*0.5f;
			numerator_2 = -(z2-z1)/(y2-y1)+(z3-z1)/(y3-y1);
			denominator = (x2-x1)/(y2-y1)-(x3-x1)/(y3-y1);

			a1 = numerator_1 / denominator;
			b1 = numerator_2 / denominator;
		}
		else
		{
			point_z1 = point_z2 = 0.5f*( (m1-m2)*(y3-y1)-(m1-m3)*(y2-y1) ) / ( (z2-z1)*(y3-y1) - (z3-z1)*(y2-y1) );
			point_y1 = point_y2 = (0.5f*(m1-m2)-(z2-z1)*point_z1)/(y2-y1);
			point_x1 = sqrt(fabs(r1*r1 - (point_z1-z1)*(point_z1-z1) - (point_y1-y1)*(point_y1-y1))  ) + x1;
			point_x2 = -sqrt( fabs(r1*r1 - (point_z1-z1)*(point_z1-z1) - (point_y1-y1)*(point_y1-y1)) ) + x1;
			
			posX1 = point_x1;
			posY1 = point_y1;
			posZ1 = point_z1;
			posX2 = point_x2;
			posY2 = point_y2;
			posZ2 = point_z2;

			return 2;
		}
	}

	// 将方程组归一化为：
	// az^2 + bz -c = 0;
	float a = b1*b1+b2*b2+1.0f;
	float b = 2*a1*b1+2*a2*b2-2*x1*b1-2*y1*b2-2*z1;
	float c = m1-a1*a1-a2*a2+2*x1*a1+2*y1*a2;

	if (b*b+4*a*c <0)
	{
		return 8;
	}
	point_z1 = ( -b + sqrt((b*b+4*a*c)) )/ a * 0.5f;
	point_z2 = ( -b - sqrt((b*b+4*a*c)) )/ a * 0.5f;

	point_x1 = a1 + b1 * point_z1;
	point_x2 = a1 + b1 * point_z2;
	point_y1 = a2 + b2 * point_z1;
	point_y2 = a2 + b2 * point_z2;

	posX1 = point_x1;
	posY1 = point_y1;
	posZ1 = point_z1;
	posX2 = point_x2;
	posY2 = point_y2;
	posZ2 = point_z2;

	return 2;
}
//falled or not
void Vision::UpdateBodyState()
{
	Angle rollX,pitchY,yawZ;
	mBodyRotation.InvertAngles( rollX, pitchY, yawZ );
	rollX += 90.0f;
	VisionLog << " Roll X: "  << rollX << " " << " Pitch Y: " << pitchY << " " << " Yaw Z: "   << yawZ << endl;
	
	mBodyAngle = rollX;

	mIsFalled = false;			
	mIsFaceUpFalled = false;	
	mIsSideFalled = false;

	if( fabs(yawZ) > 50.0f )
	{
		mIsFalled = true;
		if( yawZ < 0.0f )
		{
			mIsFaceUpFalled = false;
		}
		else
		{
			mIsFaceUpFalled = true;
		}
	}	

	if( fabs(pitchY) > 50.0f )
	{
		mIsFalled = true;
		mIsSideFalled = true;
	}
}
//!!
void Vision::UpdateWorldModel()
{
	mWorldModel->mSelf.mPos.x = mSelf.mPos.x;
	mWorldModel->mSelf.mPos.y = mSelf.mPos.y;
	mWorldModel->mSelf.mPos.z = mSelf.mPos.z;
	mWorldModel->mBall.mPos.x = mBall.mPos.x;
	mWorldModel->mBall.mPos.y = mBall.mPos.y;
	mWorldModel->mBall.mPos.z = mBall.mPos.z;
	mWorldModel->mOurPlayers = mOurPlayers;
	mWorldModel->mOppPlayers = mOppPlayers;
	mWorldModel->mBodyAngle = Normalize( mBodyAngle );
	mWorldModel->mIsFalled = mIsFalled;
	mWorldModel->mIsFaceUpFalled = mIsFaceUpFalled;
	mWorldModel->mIsSideFalled = mIsSideFalled;

	mWorldModel->mBall.SaveHistoryPos();
	mWorldModel->mBall.SaveHistorySpeed(mWorldModel->mSimStepTime);
	VisionLog<<"bodyR: "<<endl;
	for (int i = 0;i<3;i++)
	{
		for (int j = 0;j<3;j++)
		{
			VisionLog << mBodyRotation.GetElement(i,j) <<" ";
		}
		VisionLog << endl;
	}
}
//absolute flag positon
void Vision::GetFlagPos( FlagAndGoalT flagT, float &flagX, float &flagY, float &flagZ)
{
	if( flagT == FAG_FLAG_OUR_LEFT )
	{
		flagX = mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.x;
		flagY = mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.y;
		flagZ = mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.z;
	}
	else if( flagT == FAG_FLAG_OUR_RIGHT )
	{
		flagX = mWorldModel->mFieldFlag[FLAG_OUR_RIGHT].mPos.x;
		flagY = mWorldModel->mFieldFlag[FLAG_OUR_RIGHT].mPos.y;
		flagZ = mWorldModel->mFieldFlag[FLAG_OUR_RIGHT].mPos.z;
	}
	else if( flagT == FAG_FLAG_OPP_LEFT )
	{
		flagX = mWorldModel->mFieldFlag[FLAG_OPP_LEFT].mPos.x;
		flagY = mWorldModel->mFieldFlag[FLAG_OPP_LEFT].mPos.y;
		flagZ = mWorldModel->mFieldFlag[FLAG_OPP_LEFT].mPos.z;
	}
	else if( flagT == FAG_FLAG_OPP_RIGHT )
	{
		flagX = mWorldModel->mFieldFlag[FLAG_OPP_RIGHT].mPos.x;
		flagY = mWorldModel->mFieldFlag[FLAG_OPP_RIGHT].mPos.y;
		flagZ = mWorldModel->mFieldFlag[FLAG_OPP_RIGHT].mPos.z;
	}
	else if( flagT == FAG_GOAL_OUR_LEFT )
	{
		flagX = mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos.x;
		flagY = mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos.y;
		flagZ = mWorldModel->mFieldGoal[GOAL_OUR_LEFT].mPos.z;
	}
	else if( flagT == FAG_GOAL_OUR_RIGHT )
	{
		flagX = mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos.x;
		flagY = mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos.y;
		flagZ = mWorldModel->mFieldGoal[GOAL_OUR_RIGHT].mPos.z;
	}
	else if( flagT == FAG_GOAL_OPP_LEFT )
	{
		flagX = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.x;
		flagY = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.y;
		flagZ = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos.z;
	}
	else if( flagT == FAG_GOAL_OPP_RIGHT )
	{
		flagX = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos.x;
		flagY = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos.y;
		flagZ = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos.z;
	}
	else
	{
		VisionLog << "Error: " << " GetFlagPos() " << flagT << endl;
		//cout << "Error: " << " GetFlagPos() " << flagT << endl;
		flagX = mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.x;
		flagY = mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.y;
		flagZ = mWorldModel->mFieldFlag[FLAG_OUR_LEFT].mPos.z;
	}
}
//!!
void Vision::GetFlagPos( FlagAgentSee flagISee, float &flagX, float &flagY, float &flagZ)
{
	flagX = flagISee.mRelPos.x;
	flagY = flagISee.mRelPos.y;
	flagZ = flagISee.mRelPos.z;
}

//location_ball
void Vision::GetBallPosFromGYRAndBallPol(  Polar3f ballRelPol, float &bPosX, float &bPosY, float &bPosZ )
{
	Polar3f ballPol = ballRelPol;
	float x = ballPol.dist * cosDeg(ballPol.phi) * cosDeg( ballPol.theta);
	float y = ballPol.dist * cosDeg(ballPol.phi) * sinDeg( ballPol.theta);
	float z = ballPol.dist * sinDeg(ballPol.phi);

	Matrix bodyR1 = mBodyRotation;

	AddHeadRotation(bodyR1);

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

void Vision::LocateOtherAgent_4_Ideal()
{
	//absolute pos
	vector<FlagAgentSee> flagUse;
	vector<unsigned int> flagSeeLeft;
	vector<unsigned int> flagSeeRight;

	for( int i = 0; i < FlagNumISee(); i ++ )
	{
		if( mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_LEFT
			|| mWorldModel->mFlagVec[i].flagT == FAG_FLAG_OUR_RIGHT
			|| mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_LEFT
			|| mWorldModel->mFlagVec[i].flagT == FAG_GOAL_OUR_RIGHT )
		{
			flagSeeLeft.push_back( i );
		}
		else
		{
			flagSeeRight.push_back( i );
		}
	}

	for( int i = 0; i < ( flagSeeLeft.size() <= 3 ? flagSeeLeft.size(): 3 ); i ++ )
	{
		flagUse.push_back( mWorldModel->mFlagVec[ flagSeeLeft[i] ] );
	}
	unsigned int flagSize = flagUse.size();
	for( int i = 0; i < ( 4 - flagSize ); i ++ )
	{
		flagUse.push_back( mWorldModel->mFlagVec[ flagSeeRight[i] ] );
	}

	for(int i = 0; i < 4; i ++ )
	{
		flagUse[i].mRelPos.fromPolar3f( flagUse[i].flagRelPol );
	}

	float x1,y1,z1;
	GetFlagPos( flagUse[0].flagT, x1,y1,z1 );
	float x2,y2,z2;
	GetFlagPos( flagUse[1].flagT, x2,y2,z2 );
	float x3,y3,z3;
	GetFlagPos( flagUse[2].flagT, x3,y3,z3 );
	float x4,y4,z4;
	GetFlagPos( flagUse[3].flagT, x4,y4,z4 );

	Matrix wFlag(4,4);
	wFlag[0] = x1;	wFlag[1] = y1;	wFlag[2] = z1;	wFlag[3] = 1.0f;
	wFlag[4] = x2;	wFlag[5] = y2;	wFlag[6] = z2;	wFlag[7] = 1.0f;
	wFlag[8] = x3;	wFlag[9] = y3;	wFlag[10] = z3;	wFlag[11] = 1.0f;
	wFlag[12] = x4;	wFlag[13] = y4;	wFlag[14] = z4;	wFlag[15] = 1.0f;

	Matrix	rMatrix;
	Matrix  tMatrix;
	Matrix	pMatrix;
	rMatrix.Init(4,4);
	tMatrix.Init(4,4);
	pMatrix.Init(1, 4);
	wFlag.Invert();

	for (int i = 0; i <4; i++)
	{		
		rMatrix[i * 4]		= flagUse[i].mRelPos.x;		
		rMatrix[i * 4 + 1]	= flagUse[i].mRelPos.y;		
		rMatrix[i * 4 + 2]	= flagUse[i].mRelPos.z;		
		rMatrix[i * 4 + 3]	= 1;
	}
	tMatrix = wFlag * rMatrix;

	if (tMatrix.Invert())	
	{
		//update my teammates
		for(int i = 0; i < mWorldModel->mOurPlayers.size(); i++)
		{
			pMatrix[0] = mWorldModel->mOurPlayers[i].mRelPos.x;
			pMatrix[1] = mWorldModel->mOurPlayers[i].mRelPos.y;
			pMatrix[2] = mWorldModel->mOurPlayers[i].mRelPos.z;
			pMatrix[3] = 1;

			pMatrix = pMatrix * tMatrix;

			/*mOurPlayers[i].SaveHistoryPos();
			mOurPlayers[i].SaveHistorySpeed( mWorldModel->mSimStepTime );
			mOurPlayers[i].SaveHistoryAccSpeed( mWorldModel->mSimStepTime );*/

			/*mOurPlayers[i].mPos.x = pMatrix[0];
			mOurPlayers[i].mPos.y = pMatrix[1];
			mOurPlayers[i].mPos.z = pMatrix[2];*/
			float tX,tY,tZ;
			tX =  pMatrix[0];
			tY =  pMatrix[1];
			tZ =  pMatrix[2];
			VisionLog << "pol: "<<mWorldModel->mOurPlayers[i].mRelPol.dist<<" "
				<<mWorldModel->mOurPlayers[i].mRelPol.phi<<" "
				<<mWorldModel->mOurPlayers[i].mRelPol.theta<<endl;
			VisionLog << "ourPlayer(4):: " << mWorldModel->mOurPlayers[i].mMyPlayerNo<<": " <<tX<<" " << tY<< " "<< tZ<<endl;
		}

		//update oppteam
		for(int i = 0; i < mWorldModel->mOppPlayers.size(); i++)
		{
			pMatrix[0] = mOppPlayers[i].mRelPos.x;
			pMatrix[1] = mOppPlayers[i].mRelPos.y;
			pMatrix[2] = mOppPlayers[i].mRelPos.z;
			pMatrix[3] = 1;

			pMatrix = pMatrix * tMatrix;
			mOppPlayers[i].SaveHistoryPos();
			mOppPlayers[i].SaveHistorySpeed( mWorldModel->mSimStepTime );
			mOppPlayers[i].SaveHistoryAccSpeed( mWorldModel->mSimStepTime );
			/*mOppPlayers[i].mPos.x = pMatrix[0];
			mOppPlayers[i].mPos.y = pMatrix[1];
			mOppPlayers[i].mPos.z = pMatrix[2];*/
			float tX,tY,tZ;
			tX =  pMatrix[0];
			tY =  pMatrix[1];
			tZ =  pMatrix[2];
			VisionLog << "oppPlayer" << mOppPlayers[i].mMyPlayerNo << ": "<<pMatrix[0] <<" " << pMatrix[1]<< " "<< pMatrix[2] <<endl;
		}
	}
}

void Vision::GetOthersPosFromGYRAndRel(  Polar3f otherRelPol, float &aPosX, float &aPosY, float &aPosZ )
{
	Polar3f otherPol = otherRelPol;
	float x = otherPol.dist * cosDeg(otherRelPol.phi) * cosDeg( otherRelPol.theta);
	float y = otherPol.dist * cosDeg(otherRelPol.phi) * sinDeg( otherRelPol.theta);
	float z = otherPol.dist * sinDeg(otherRelPol.phi);

	Matrix bodyR1 = mBodyRotation;

	AddHeadRotation(bodyR1);
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

	Matrix otherRelMatrix(4,4);
	otherRelMatrix.SetElement(0,0,bodyR.GetElement(0,0));
	otherRelMatrix.SetElement(0,1,bodyR.GetElement(0,1));
	otherRelMatrix.SetElement(0,2,bodyR.GetElement(0,2));
	otherRelMatrix.SetElement(0,3,-y);
	otherRelMatrix.SetElement(1,0,bodyR.GetElement(1,0));
	otherRelMatrix.SetElement(1,1,bodyR.GetElement(1,1));
	otherRelMatrix.SetElement(1,2,bodyR.GetElement(1,2));
	otherRelMatrix.SetElement(1,3,x);
	otherRelMatrix.SetElement(2,0,bodyR.GetElement(2,0));
	otherRelMatrix.SetElement(2,1,bodyR.GetElement(2,1));
	otherRelMatrix.SetElement(2,2,bodyR.GetElement(2,2));
	otherRelMatrix.SetElement(2,3,z);
	otherRelMatrix.SetElement(3,0,0.0f);
	otherRelMatrix.SetElement(3,1,0.0f);
	otherRelMatrix.SetElement(3,2,0.0f);
	otherRelMatrix.SetElement(3,3,1.0f);

	Matrix otherPosMatrix(4,4);
	otherPosMatrix = myPosMatrix*otherRelMatrix;

	aPosX = otherPosMatrix .GetElement(0,3);
	aPosY = otherPosMatrix .GetElement(1,3);
	aPosZ = otherPosMatrix .GetElement(2,3);	
}
//calculate the angle to turn the neck
void Vision::SetTurnNeckAng( Angle& yawAng, Angle& pitchAng )
{
	Angle bodyAngle = mWorldModel->mBodyAngle;
	Angle selfToFlagsAng[8];
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	int flagNo[8] = {0,4,5,1,3,7,6,2};

	for (int i = 0;i<FLAG_COUNT; i++)
	{
		selfToFlagsAng[i] = Normalize( selfPos.angTheta2(mWorldModel->mFieldFlag[i].mPos ) );
	}

	for (int i = 0;i<GOAL_COUNT; i++)
	{
		selfToFlagsAng[i+4] = Normalize( selfPos.angTheta2(mWorldModel->mFieldGoal[i].mPos ) );
	}

	VisionLog<<"bodyA: "<<bodyAngle<<"  mypos: "<<selfPos.x <<" "<<selfPos.y <<" "<<selfPos.z<<endl<<"8angles:  ";
	
	for( int i = 0; i < 8; i ++ )
	{
		VisionLog << selfToFlagsAng[i] << " ";
	}
	
	Angle selfToBallAngle = Normalize( selfPos.angTheta2( mWorldModel->mBall.mPos ) );
	VisionLog << endl;
	VisionLog <<"selfToball: "<<selfToBallAngle<<endl;

	if (mWorldModel->bSeeBall)
	{
		Angle minAverToBall = 1000;

		for( int i = 0; i < 8; i ++ )
		{
			int flag_num_1 = flagNo[i];
			int flag_num_3 = flagNo[(i+2)%8];
			Angle diff1,diff2,diff3;
			Angle maxiDiff,minAngle;

			if (AngleDiffLth120( selfToFlagsAng[flag_num_1] ,selfToFlagsAng[flag_num_3],diff1 )
				&&AngleDiffLth120( selfToFlagsAng[flag_num_1] ,selfToBallAngle ,diff2 )
				&&AngleDiffLth120( selfToFlagsAng[flag_num_3] ,selfToBallAngle ,diff3 ))
			{
				maxiDiff = diff1 > diff2?diff1:diff2;
				maxiDiff = maxiDiff > diff3?maxiDiff:diff3;

				minAngle = selfToFlagsAng[flag_num_1] < selfToFlagsAng[flag_num_3]?selfToFlagsAng[flag_num_1]:selfToFlagsAng[flag_num_3] ;
				minAngle = minAngle < selfToBallAngle?minAngle:selfToBallAngle;

				Angle minTAverToBall = fabs( selfToBallAngle - minAngle - maxiDiff/2);
				if (minAverToBall>minTAverToBall)
				{
					minAverToBall = minTAverToBall;
					yawAng = ( minAngle + maxiDiff/2 - bodyAngle );
				}

				VisionLog << "maxi: " << maxiDiff << " minA: " << minAngle <<" yawAngle: " << yawAng<<endl;
				//break;
			}
		}
		if( minAverToBall == 1000 )
		{
			yawAng = pitchAng = 0;
		}
	}
	else 
	{
// 		if (mWorldModel->mIsFalled)
// 		{
// 			yawAng = pitchAng = 0;
// 		}
// 		else 
// 		{
			int t = 35;
			int gameCycle = int(mWorldModel->mGameTime/0.02);
			yawAng = 35.0f*cos(2*PI*1.0f*(gameCycle%t)/t);
			pitchAng = -35.0f;
//		}
	}
	static bool down = false;
			
	if (down!= mWorldModel->mIsFalled)
	{
			down = mWorldModel->mIsFalled;
			int t = 35;
			int gameCycle = int(mWorldModel->mGameTime/0.02);
			if (!mWorldModel->mIsFalled&&FlagNumISee()<=2)
			{
				VisionLog << "turn 120"<<endl;
				yawAng = 120*cos(2*PI*1.0f*(gameCycle%t)/t);
				pitchAng = -35;
			}
	}
	//in the opp Penalty area!!! change the pitch!
	
	mWorldModel->mPenaltyLength = 1.2;
	mWorldModel->mPenaltyWidth = 2.6;
	if (mWorldModel->mSelf.mPos.x > mWorldModel->mFieldLength/2 - mWorldModel->mPenaltyLength
		&& mWorldModel->mSelf.mPos.x < mWorldModel->mFieldLength/2 + 0.5
		&& fabs(mWorldModel->mSelf.mPos.y)<mWorldModel->mPenaltyWidth/2 
		&& !mWorldModel->mIsFalled)
	{
		//cout<<"IN the area!"<<endl;
		
		Angle upAngleL,upAngleR,downAngle,upAngleMax;
		Vector3f selfToGoalLeft,selfToGoalRight,selfToBallVector;
		selfToGoalLeft = mWorldModel->mFieldGoal[GOAL_OPP_LEFT].mPos - selfPos;
		selfToGoalRight = mWorldModel->mFieldGoal[GOAL_OPP_RIGHT].mPos - selfPos;

		upAngleL = Normalize(selfToGoalLeft.angPhi());
		upAngleR = Normalize(selfToGoalRight.angPhi());
		upAngleMax = upAngleL > upAngleR ? upAngleL : upAngleR;
		selfToBallVector = mWorldModel->mBall.mPos - selfPos;
		downAngle = Normalize(selfToBallVector.angPhi());
		downAngle -= 13;                                         //bug!yuliang
		if (fabs(upAngleMax - downAngle)<120)
		{
			pitchAng = downAngle + fabs(upAngleMax - downAngle)/2;
		}
		VisionLog << "upAngleL: "<<upAngleL<<" upAngleR: "<<upAngleR <<" upAngleMax: "
			<<upAngleMax<<" downAngle: "<<downAngle << " PITCH: " <<  pitchAng<<endl;
		VisionLog <<" IN THE AREA!(see ball: )  " 
			<< mWorldModel->bSeeBall <<" iseeNum:  "
			<<FlagNumISee() <<" yawA: "<<yawAng<<" pitch: "<<pitchAng<<endl;
	}
	
	//pitchAng

	//如果太久没有看到标志物的话就转头
/*	static float lastTimeSeeFlag;

	if (FlagNumISee() >0)
	{
		lastTimeSeeFlag = mWorldModel->mGameTime;
	}

	if (mWorldModel->mGameTime - lastTimeSeeFlag >=2)
	{
		if (!mWorldModel->mIsFalled)
		{
			int t = 35;
			int gameCycle = int(mWorldModel->mGameTime/0.02);
			yawAng = 120*cos(2*PI*1.0f*(gameCycle%t)/t);
			pitchAng = -35;
		}
	}*/

	//yawAng = 120*sin(mWorldModel->mSimTime);
	/*if (mWorldModel->mSimTime > 10)
	{
		VisionLog << "wow!"<<endl;
		yawAng = 70;
		pitchAng = 35;
	
	}
	else yawAng = pitchAng = 0;*/
	/*if (mWorldModel->bSeeBall )
	{
		yawAng = mWorldModel->mBall.mRelPol.theta;
		pitchAng = mWorldModel->mBall.mRelPol.phi;
	}
	else {
		int t = 35;
		int gameCycle = int(mWorldModel->mGameTime/0.02);
		yawAng = 120*cos(2*PI*1.0f*(gameCycle%t)/t);
		pitchAng = -35;
	}*/
	
	//test
/*
	int t = 35;
	int gameCycle = int(mWorldModel->mGameTime/0.02);
	yawAng = 120*sin(mWorldModel->mSimTime);
	pitchAng = 40*sin(mWorldModel->mSimTime);
	VisionLog << "head: "<<mWorldModel->mSensor.mHJ[Head_1].mAxis<<" "<<mWorldModel->mSensor.mHJ[Head_2].mAxis<<endl;
	*/
}

bool Vision::AngleDiffLth120( Angle angle1,Angle angle2,Angle &diffAng)
{
	diffAng = fabs( angle2 - angle1 );
	return diffAng < 120;
}

void Vision::AddHeadRotation( Matrix &mBodyRot )
{
	Matrix gyrToRot;
	Angle head1 = mWorldModel->mSensor.mHJ[Head_1].mAxis;
	Angle head2 = mWorldModel->mSensor.mHJ[Head_2].mAxis;
	
	gyrToRot = gyrToRot.Rpy2Rot( head2, 0, head1 );
	mBodyRot = mBodyRot * gyrToRot;
}
void Vision::SubHeadRotation( Matrix &mBodyRot )
{
	Matrix gyrToRot;
	Angle head1 = mWorldModel->mSensor.mHJ[Head_1].mAxis; 
	Angle head2 = mWorldModel->mSensor.mHJ[Head_2].mAxis;

	gyrToRot = gyrToRot.Rpy2Rot( head2, 0, head1 );
	gyrToRot.Invert();
	mBodyRot = mBodyRot *gyrToRot;
}
void Vision::UpdateVisibleObject()
{
	if( mWorldModel->mOurPlayerNoISee.size() == 0 )
	{
		//当前周期无视觉
		return;
	}
	VisionLog << "mOurPlayerTotleNoISee " << mWorldModel->mOurPlayerNoISee.size() << endl;
	for( int i = 0; i < mWorldModel->mOurPlayerNoISee.size(); i ++ )
	{
		VisionLog << "mOurPlayerNoISee " << mWorldModel->mOurPlayerNoISee.at(i) << endl;
	}
	VisionLog << "mOppPlayerTotleNoISee " << mWorldModel->mOppPlayerNoISee.size() << endl;
	for( int i = 0; i < mWorldModel->mOppPlayerNoISee.size(); i ++ )
	{
		VisionLog << "mOppPlayerNoISee " << mWorldModel->mOppPlayerNoISee.at(i) << endl;
	}

	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		VisionLog << "OurPlayer " << mWorldModel->mOurPlayers.at(i).mMyPlayerNo << " " << mWorldModel->mOurPlayers.at(i).mPos.x << " " << mWorldModel->mOurPlayers.at(i).mPos.y << endl;
	}
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		VisionLog << "OppPlayer " << mWorldModel->mOppPlayers.at(i).mMyPlayerNo << " " << mWorldModel->mOppPlayers.at(i).mPos.x << " " << mWorldModel->mOppPlayers.at(i).mPos.y << endl;
	}

	vector<int> eraseOurNum;
	vector<int> eraseOppNum;
	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		bool bISee = false;
		if( mWorldModel->mOurPlayers.at(i).mMyPlayerNo == mWorldModel->mMyPlayerNo )
		{
			continue;
		}
		for( int j = 0; j < mWorldModel->mOurPlayerNoISee.size(); j ++ )
		{
			if( mWorldModel->mOurPlayerNoISee.at(j) == mWorldModel->mOurPlayers.at(i).mMyPlayerNo )
			{
				bISee = true;
				break;
			}
		}
		if( !bISee && IsVisibleObject(mWorldModel->mOurPlayers.at(i).mPos) )
		{
			eraseOurNum.push_back(mWorldModel->mOurPlayers.at(i).mMyPlayerNo);
		}
	}
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		bool bISee = false;
		for( int j = 0; j < mWorldModel->mOppPlayerNoISee.size(); j ++ )
		{
			if( mWorldModel->mOppPlayerNoISee.at(j) == mWorldModel->mOppPlayers.at(i).mMyPlayerNo )
			{
				bISee = true;
				break;
			}
		}
		//当前视角内没有看到该物体，并且该物体在当前区域可见，则需要将其删除
		if( !bISee && IsVisibleObject(mWorldModel->mOppPlayers.at(i).mPos) )
		{
			eraseOppNum.push_back(mWorldModel->mOppPlayers.at(i).mMyPlayerNo);
		}
	}

	vector<Player> tempOur;
	vector<Player> tempOpp;
	for( int i = 0; i < mWorldModel->mOurPlayers.size(); i ++ )
	{
		bool add = true;
		for( int j = 0; j < eraseOurNum.size(); j ++ )
		{
			if( eraseOurNum.at(j) == mWorldModel->mOurPlayers.at(i).mMyPlayerNo )
			{
				add = false;
				break;
			}
		}
		if( add )
		{
			tempOur.push_back(mWorldModel->mOurPlayers.at(i));
		}
	}
	for( int i = 0; i < mWorldModel->mOppPlayers.size(); i ++ )
	{
		bool add = true;
		for( int j = 0; j < eraseOppNum.size(); j ++ )
		{
			if( eraseOppNum.at(j) == mWorldModel->mOppPlayers.at(i).mMyPlayerNo )
			{
				add = false;
				break;
			}
		}
		if( add )
		{
			tempOpp.push_back(mWorldModel->mOppPlayers.at(i));
		}
	}

	mWorldModel->mOurPlayers = tempOur;
	mWorldModel->mOppPlayers = tempOpp;

	VisionLog << "mOurPlayers " << mWorldModel->mOurPlayers.size() << endl;
	VisionLog << "mOppPlayers " << mWorldModel->mOppPlayers.size() << endl;
}
bool Vision::IsVisibleObject( Vector3f objPos )
{
	//只进行水平检测
	Vector3f selfPos = mWorldModel->mSelf.mPos;
	Angle angToObj = InNormalize( selfPos.angTheta2( objPos ) );
	Angle bodyAng = InNormalize( mWorldModel->mBodyAngle );
	Angle headPitchAng = InNormalize( mWorldModel->mSensor.mHJ[Head_1].mAxis );
	Angle headWorldAng = InNormalize( bodyAng + headPitchAng );
	const Angle pitchAngLimit = 120.0f;
	const Angle pitchAngUpLimit = headWorldAng + pitchAngLimit * 0.5f;
	const Angle pitchAngDownLimit = headWorldAng - pitchAngLimit * 0.5f;
	
	if( angToObj > pitchAngDownLimit && angToObj < pitchAngUpLimit )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Vision::NeedToLocateBall()
{
	return mNeedToLocateBall;
}
