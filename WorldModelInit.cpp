#include "stdafx.h"
/*/////////////////copy right AmoiesisNQ ////////////////////
*
*        Robocup 3D Soccer Simulation Team AmoiesisNQ
*    the automation department of Xiamen University China
*
*		worldmodel,�ײ�,����update�������Ϣ�������ϲ����
*
*change log
*2007��8��22�ա���ɳ��ڿ��
*
*////////////////////////////////////////////////////////////
#include "WorldModel.h"

void WorldModel::WorldModelInit()
{
	mTeamName	= mBasicConfig->mMyTeamName;
	mMyPlayerNo = mBasicConfig->mMyPlayerNo;

/*	if( mMyPlayerNo == 9 )
	{
		mMyPlayerNo = 3;
	}
	else if( mMyPlayerNo == 10 )
	{
		mMyPlayerNo = 4;
	} */

	cout<< "WorldModel mMyPlayerNo " << mMyPlayerNo << endl;

	mSelf.mMyPlayerNo = mMyPlayerNo;

	mOppStrength = OS_Normal;

	mBallHistoryPos.resize(10);
	Vector3f iniBallPos(0.0f, 0.0f, 0.042f);
	for( int i = 0; i < 10; i ++ )
	{
		mBallHistoryPos.at(i) = iniBallPos;
	}
	mPredictBallPos.z = 0.042f;

	ReadWorldModelConf();

	InitMaps();
	InitMarkers();
	InitMatrixs();
	InitBodyRotation();
}
string WorldModel::GetAgentConfPath()
{
	return mBasicConfig->mMyAgentConf;
}

string WorldModel::GetFormationConfPath()
{
	return mBasicConfig->mMyFormation;
}
string WorldModel::GetWorldModelConfPath()
{
	return mBasicConfig->mWorldModel;
}

bool WorldModel::ReadWorldModelConf()
{
	ReadConf rC( GetWorldModelConfPath( ) ); 
	Predicate tempP;

	bool newServer;

	rC.Tranversal( "NewServer", tempP );
	tempP.GetValue( "NewServer", newServer );

	if( newServer )
	{
		mServerType = New_Server;
	}
	else
	{
		mServerType = Old_Server;
	}

	rC.Tranversal( "SimStepTime", tempP );
	tempP.GetValue( "SimStepTime", mSimStepTime );

	rC.Tranversal( "PenaltyWidth", tempP );
	tempP.GetValue( "PenaltyWidth", mPenaltyWidth );

	rC.Tranversal( "PenaltyLength", tempP );
	tempP.GetValue( "PenaltyLength", mPenaltyLength );

	rC.Tranversal( "GoalWidth", tempP );
	tempP.GetValue( "GoalWidth", mGoalWidth );

	rC.Tranversal( "GoalHeight", tempP );
	tempP.GetValue( "GoalHeight", mGoalHeight );

	rC.Tranversal( "GoalDepth", tempP );
	tempP.GetValue( "GoalDepth", mGoalDepth );

	rC.Tranversal( "FieldLength", tempP );
	tempP.GetValue( "FieldLength", mFieldLength );

	rC.Tranversal( "FieldWidth", tempP );
	tempP.GetValue( "FieldWidth", mFieldWidth );

	rC.Tranversal( "FlagCenterHeight", tempP );
	tempP.GetValue( "FlagCenterHeight", mFlagCenterHeight );

	rC.Tranversal( "BallRadius", tempP );
	tempP.GetValue( "BallRadius", mBallRadius );

	rC.Tranversal( "BodyRadius", tempP );
	tempP.GetValue( "BodyRadius", mBodyRadius );

	mOurGoalCenter.x = -mFieldLength / 2.0f;
	mOppGoalCenter.x =  mFieldLength / 2.0f;


	ReadConf rBeamConf( GetAgentConfPath() ); 
	Predicate tempPBeam;
	BeamPara tempBeam;

	mInitBeamPos.playerNo = -1;
	mDefenseBeamPos.playerNo = -1;

	rBeamConf.Tranversal( "Beam", tempPBeam );

	multimap<string,Predicate>::iterator cp = tempPBeam.child.begin();

	while( cp != tempP.child.end() )
	{
		if( (cp->second).attr.size() != 5 )
		{
			break;
		}

		tempBeam.playerNo = (unsigned int) atoi( ((cp->second)).attr[0].c_str() );

		tempBeam.beamPara[0] = (float) atof( (cp->second).attr[1].c_str() );
		tempBeam.beamPara[1] = (float) atof( (cp->second).attr[2].c_str() );
		tempBeam.beamPara[2] = (float) atof( (cp->second).attr[3].c_str() );

		if( tempBeam.playerNo == mMyPlayerNo )
		{
			mInitBeamPos = tempBeam;
			//break;
		}
		else if( tempBeam.playerNo == mMyPlayerNo + 10 )
		{
			mDefenseBeamPos = tempBeam;
		}

		cp ++;
	}

	if( mInitBeamPos.playerNo == -1 )
	{
		mInitBeamPos.playerNo = mMyPlayerNo;
		mInitBeamPos.beamPara[0] = -3.5f;
		mInitBeamPos.beamPara[1] = (float)mMyPlayerNo - 3.5f;
		mInitBeamPos.beamPara[2] = 0.0f;
	}

	if( mDefenseBeamPos.playerNo == -1 )
	{
		mDefenseBeamPos.playerNo = mMyPlayerNo;
		mDefenseBeamPos.beamPara[0] = -3.5f;
		mDefenseBeamPos.beamPara[1] = (float)mMyPlayerNo - 3.5f;
		mDefenseBeamPos.beamPara[2] = 0.0f;
	}

	return true;
}

void WorldModel::InitMaps()   
{
	mPlayModeMap.clear();
	mPlayModeMap["BeforeKickOff"]		= PM_BEFORE_KICK_OFF;			//��������ǰ״̬
	mPlayModeMap["KickOff_Left"]		= PM_KICK_OFF_LEFT;				//��߿���
	mPlayModeMap["KickOff_Right"]		= PM_KICK_OFF_RIGHT;			//�ұ߿���
	mPlayModeMap["PlayOn"]				= PM_PLAY_ON;					//��������
	mPlayModeMap["KickIn_Left"]			= PM_KICK_IN_LEFT;				//���������󷽿�����
	mPlayModeMap["KickIn_Right"]		= PM_KICK_IN_RIGHT;				//���������ҷ�������
	mPlayModeMap["corner_kick_left"]	= PM_CORNER_KICK_LEFT;			//�󷽽���
	mPlayModeMap["corner_kick_right"]	= PM_CORNER_KICK_RIGHT;			//�ҷ�����
	mPlayModeMap["goal_kick_left"]		= PM_GOAL_KICK_LEFT;			//������
	mPlayModeMap["goal_kick_right"]		= PM_GOAL_KICK_RIGHT;			//�ҷ�����
	mPlayModeMap["offside_left"]		= PM_OFFSIDE_LEFT;				//��Խλ
	mPlayModeMap["offside_right"]		= PM_OFFSIDE_RIGHT;				//�ҷ�Խλ
	mPlayModeMap["Goal_Left"]			= PM_GOAL_LEFT;					//��ߵ÷�
	mPlayModeMap["Goal_Right"]			= PM_GOAL_RIGHT;				//�ұߵ÷�
	mPlayModeMap["free_kick_left"]		= PM_FREE_KICK_LEFT;			//���������
	mPlayModeMap["free_kick_right"]		= PM_FREE_KICK_RIGHT;			//�ұ�������
	mPlayModeMap["GameOver"]			= PM_GAME_OVER;					//��������
	mPlayModeMap["unknown"]				= PM_UNKNOWN;					//δ֪����״̬
	
	mHjMap.clear();
	mHjMap["hj1"]	= Head_1;			//ͷ����һ�ؽ�
	mHjMap["hj2"]	= Head_2;			//ͷ���ڶ��ؽ�
	mHjMap["llj1"]	= LLEG_1;			//���ȵ�һ�ؽ�
	mHjMap["rlj1"]	= RLEG_1;			//���ȵ�һ�ؽ�
	mHjMap["llj2"]	= LLEG_2;
	mHjMap["rlj2"]	= RLEG_2;
	mHjMap["llj3"]	= LLEG_3;
	mHjMap["rlj3"]	= RLEG_3;
	mHjMap["llj4"]	= LLEG_4;          //���ȵ��Ĺؽ�
	mHjMap["rlj4"]	= RLEG_4;          //���ȵ��Ĺؽ�
	mHjMap["llj5"]	= LLEG_5;
	mHjMap["rlj5"]	= RLEG_5;
	mHjMap["llj6"]	= LLEG_6;
	mHjMap["rlj6"]	= RLEG_6;
	mHjMap["laj1"]	= LARM_1;
	mHjMap["raj1"]	= RARM_1;
	mHjMap["laj2"]	= LARM_2;
	mHjMap["raj2"]	= RARM_2;
	mHjMap["laj3"]	= LARM_3;          //���ֱ۵����ؽ�
	mHjMap["raj3"]	= RARM_3;          //���ֱ۵����ؽ�
	mHjMap["laj4"]	= LARM_4;          //���ֱ۵��Ĺؽ�
	mHjMap["raj4"]	= RARM_4;          //���ֱ۵��Ĺؽ�

	//ujMap.clear();
	//ujMap["llj2_3"] = LLEG_2_3;          //���ȵ�2_3�ؽ�
	//ujMap["rlj2_3"] = RLEG_2_3;          //���ȵ�2_3�ؽ�
	//ujMap["llj5_6"] = LLEG_5_6;          //���ȵ�5_6�ؽ�
	//ujMap["rlj5_6"] = RLEG_5_6;          //���ȵ�5_6�ؽ�
	//ujMap["laj1_2"] = LARM_1_2;          //���ֱ۵�1_2�ؽ�
	//ujMap["raj1_2"] = RARM_1_2;          //���ֱ۵�1_2�ؽ�
}

void WorldModel::InitMarkers()
{
	float semiFieldLength = mFieldLength / 2.0f;
	float semiFieldWidth  = mFieldWidth  / 2.0f;
	float semiGoalWidth	  = mGoalWidth   / 2.0f;

	mFieldFlag[FLAG_OUR_LEFT].mPos.x	= -semiFieldLength;
	mFieldFlag[FLAG_OUR_LEFT].mPos.y	= semiFieldWidth;
	mFieldFlag[FLAG_OUR_RIGHT].mPos.x	= -semiFieldLength;
	mFieldFlag[FLAG_OUR_RIGHT].mPos.y	= -semiFieldWidth;
	mFieldFlag[FLAG_OPP_LEFT].mPos.x	= semiFieldLength;
	mFieldFlag[FLAG_OPP_LEFT].mPos.y	= semiFieldWidth;
	mFieldFlag[FLAG_OPP_RIGHT].mPos.x	= semiFieldLength;
	mFieldFlag[FLAG_OPP_RIGHT].mPos.y	= -semiFieldWidth;

	mFieldGoal[GOAL_OUR_LEFT].mPos.x	= -semiFieldLength;
	mFieldGoal[GOAL_OUR_LEFT].mPos.y	= semiGoalWidth;
	mFieldGoal[GOAL_OUR_RIGHT].mPos.x	= -semiFieldLength;
	mFieldGoal[GOAL_OUR_RIGHT].mPos.y	= -semiGoalWidth;
	mFieldGoal[GOAL_OPP_LEFT].mPos.x	= semiFieldLength;
	mFieldGoal[GOAL_OPP_LEFT].mPos.y	= semiGoalWidth;
	mFieldGoal[GOAL_OPP_RIGHT].mPos.x	= semiFieldLength;
	mFieldGoal[GOAL_OPP_RIGHT].mPos.y	= -semiGoalWidth;

	mFieldFlag[FLAG_OUR_LEFT].mPos.z	= mFlagCenterHeight;
	mFieldFlag[FLAG_OUR_RIGHT].mPos.z	= mFlagCenterHeight;	
	mFieldFlag[FLAG_OPP_LEFT].mPos.z	= mFlagCenterHeight;
	mFieldFlag[FLAG_OPP_RIGHT].mPos.z	= mFlagCenterHeight;

// 	mFieldGoal[GOAL_OUR_LEFT].mPos.z	= 0.0f;
// 	mFieldGoal[GOAL_OUR_RIGHT].mPos.z	= 0.0f;	
// 	mFieldGoal[GOAL_OPP_LEFT].mPos.z	= 0.0f;
// 	mFieldGoal[GOAL_OPP_RIGHT].mPos.z	= 0.0f;

	mFieldGoal[GOAL_OUR_LEFT].mPos.z	= 0.8f;
	mFieldGoal[GOAL_OUR_RIGHT].mPos.z	= 0.8f;	
	mFieldGoal[GOAL_OPP_LEFT].mPos.z	= 0.8f;
	mFieldGoal[GOAL_OPP_RIGHT].mPos.z	= 0.8f;
}

void WorldModel::InitMatrixs()
{	
	rMatrix.Init(4, 4);
	tMatrix.Init(4, 4);
	pMatrix.Init(1, 4);
	invUmatrix.Init(4, 4);
	eqsMypos.Init(3);

	/////////////////////////////
	YMatrix.Init(8,1);
	HMatrix.Init(8,3);
	ProH.Init(3,8);
	TraH.Init(3,3);
	DeltaMatrix.Init(3,1);

	//FLAG_OUR_LEFT,  FLAG_OUR_RIGHT,  FLAG_OPP_LEFT, GOAL_OUR_LEFTȫ�����������ɾ��������
	//float invUmatrix1235[16] =  
	//{
	//	-0.0200f,	-0.0000f,    0.0200f,		0.0000f,
	//	0.0313f,		-0.0313f,	0.0f,			0.0f,
	//	1.7083f,		0.9583f,		0.0f,			-2.6667f,
	//	-0.6406f,	0.1406f,		0.5000f,		1.0000f
	//};
	//float invUmatrix1235[16] =  
	//{
	//	-0.08333,	0.0,    0.08333,		0.0,
	//	0.125,		-0.125,	0.0,			0.0,
	//	-58750,		-41250,		0.0,			100000,
	//	0.5875,	0.9125,		0.5,		-1.0
	////};

	// �ҷ�����������ҷ��Ҳ��������Է�����������Է��Ҳ��־��
	// 2008���籭�汾������
  	float invUmatrix1235[16] = 
  	{
  		-0.0833f,	0.0f,		0.0833f,	0.0f,
  		0.7143f,	-0.7143f,	0.0f,		0.0f,
  		4.1964f,	-2.9464f,	0.0f,		-1.25f,
  		-3.3571f,	2.8571f,    0.50f,		1.0f
  	};

	// �ҷ�����������ҷ��Ҳ��������Է�����������Է��Ҳ��־��
	// 2008ȫ�����汾������
   /* 	float invUmatrix1235[16] = 
    	{
    		-0.0417,   -0.0000,    0.0417,   -0.0000,
    		0.5000,   -0.5000,         0,         0,
    		5.6250,   -4.3750,         0,   -1.2500,
    		-4.5000,    4.0000,    0.5000,    1.0000,
    	};*/

	invUmatrix.SetData(invUmatrix1235);
}


void WorldModel::InitBodyRotation()
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
	
	mBodyRotation = Matrix::Rpy2Rot( 0.0f, 0.0f, mInitBeamPos.beamPara[2] );
	mBodyRotation = initMatrix * mBodyRotation;
	mBodyRotation.PrintMatrix();
}	
