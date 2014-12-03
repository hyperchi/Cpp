#include "Action.h"
#define ActLog gLog<< "[Action] "
#define ProcessingLog  gProcessingLog<<"[Action] "
Action::Action( WorldModel *wm, CommandQuene *cmdQuene )
{
	mWorldModel = wm;
	mCmdQuene = cmdQuene;

	mJoint = new JointControl( mWorldModel, cmdQuene );
	mWalkFrameNum = 4;

	mJointFrameNow = 0;

	InitAction( );

	mActionType = AT_Other;
	IsLastActAdj = false;
	IsLastActQTurn = false;


	mForLen = 0.0f;
	mTransLen = 0.0f;
	mTurnAng = 0.0f;
}
Action::~Action()
{

}

//******************************************************************
//		判断当前动作是否做完
//				(根据Joint队列是否到达尾部判断）
//
//		返回值：true	--	当前动作已完成
//				false	--	当前动作未完成
//******************************************************************
bool Action::IsActionDone()
{
	if( mJoint->IsJointVectorEnd() )
	{
		ActLog << "Is Action Done " << endl;
	}
	else
	{
		ActLog << "Action Not Done " << endl;
	}

	return mJoint->IsJointVectorEnd();
}

//******************************************************************
//		完成一帧动作
//					从关节（Joint）队列中得到当前命令
//					由 Joint类 向指令队列中压入一条指令
//******************************************************************
bool Action::Do()
{
	ProcessingLog <<"Do "<< " SimTime: "<<mWorldModel->mSimTime<<" GameTime: "<<mWorldModel->mGameTime<<"\n";

	if( mActionType == AT_Other )
	{
	}
 	else 
 	{	
 		mJoint->ClearJoint();
 
 		vector<Joint> tempJointV;

		if (mActionType ==AT_Walk)
		{
			mBasicWalk.SetCycle(Cycle_Normal);
			ProcessingLog<<"mTransLen====== "<<mTransLen<<endl;
			mBasicWalk.CalWalk(mForLen, mTransLen, mTurnAng * PI/180.0f, tempJointV);

			for( unsigned int i = 0; i < tempJointV.size(); i ++ )
			{				
				mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
			}

		} 
		else if( mActionType == AT_QuickTurn )
		{
			/*
			mHuman.QuickTurn( mTurnAng, tempJointV );

			for( unsigned int i = 0; i < tempJointV.size(); i ++ )
			{
				mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
			}
			*/
			mBasicWalk.SetCycle(Cycle_Normal);
			mBasicWalk.CalWalk( 0.0f,0.0f,mTurnAng * PI/180.0f, tempJointV );

			for( unsigned int i = 0; i < tempJointV.size(); i ++ )
			{
				mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
			}
			
		}
		else if (mActionType == AT_SteadyAdjust)
		{
			
			mBasicWalk.SetCycle(Cycle_QuickTrans);
			mBasicWalk.CalWalk(mForLen, mTransLen, mTurnAng * PI/180.0f, tempJointV);
			
			for( unsigned int i = 0; i < tempJointV.size(); i ++ )
			{
				mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
			}
			

		}
		else if (mActionType == AT_CrazyTurn)
		{
			//std::cout <<"AT_CrazyTurn: " << mWorldModel->mBodyAngle <<endl;
			mHuman.QuickTurn( mTurnAng, tempJointV );

			for( unsigned int i = 0; i < tempJointV.size(); i ++ )
			{
				mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
			}

		}
	
 	}
	
	TurnNeck();

	mJoint->GetCommand();
	
	return true;
}

//******************************************************************
//		初始化Action类所需要的参数
//			从Agent配置文件中读取
//******************************************************************
void Action::InitAction()
{
	ReadConf rC( mWorldModel->GetAgentConfPath() ); 
	Predicate tempP;

	rC.Tranversal( "Test_Walk_Forlen", tempP );
	tempP.GetValue( "Test_Walk_Forlen", mTestWalkForlen );

	rC.Tranversal( "Test_Walk_TurnAng", tempP );
	tempP.GetValue( "Test_Walk_TurnAng", mTestWalkTurnAng );

	rC.Tranversal( "Test_Walk_TransLen", tempP );
	tempP.GetValue( "Test_Walk_TransLen", mTestWalkTransLen );

	ReadActionDataFromFile( );

	mRightWalk = true;

	mNeckYawAng = 0.0f;
	mNeckPitchAng = 0.0f;
}

void Action::ReadActionDataFromFile()
{
	FILE *actionFile;

	if( (actionFile = fopen( "action.dat", "r" ) ) == NULL )
	{
		ActLog << "Can't open command.dat" << END;	
		
		return;
	}

	char buff[500];
	unsigned int i = 0;

	while( fgets( buff,500,actionFile ) != NULL )
	{
		if ( buff[0] == '#' || buff[0] == '\n' || buff[0] == '\r' )
		{	
			continue ;
		}

		sscanf( buff,"%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t%f,\t", 
			&TestActionFrames[i][Head_1],
			&TestActionFrames[i][Head_2],
			&TestActionFrames[i][LARM_1], 
			&TestActionFrames[i][LARM_2], 
			&TestActionFrames[i][LARM_3], 
			&TestActionFrames[i][LARM_4], 
			&TestActionFrames[i][LLEG_1], 
			&TestActionFrames[i][LLEG_2], 
			&TestActionFrames[i][LLEG_3], 
			&TestActionFrames[i][LLEG_4], 
			&TestActionFrames[i][LLEG_5], 
			&TestActionFrames[i][LLEG_6], 
			&TestActionFrames[i][RARM_1], 
			&TestActionFrames[i][RARM_2], 
			&TestActionFrames[i][RARM_3], 
			&TestActionFrames[i][RARM_4], 
			&TestActionFrames[i][RLEG_1], 
			&TestActionFrames[i][RLEG_2], 
			&TestActionFrames[i][RLEG_3], 
			&TestActionFrames[i][RLEG_4], 
			&TestActionFrames[i][RLEG_5], 
			&TestActionFrames[i][RLEG_6] );
		i++;
	}  

	TestActionNum = i;

	ActLog << "Read " << TestActionNum << " Commands " << endl;

	//if( TestActionNum >= 100 )
	//{
	//	ActLog << "Too Long Commands ! " << endl;
	//	exit(1);
	//}

	fclose( actionFile );
}

//******************************************************************
//		将命令数组中的数据导入Joint类
//			@(*keyFrame)[HJCOUNT]:	命令数组的指针
//			@keyFrameNum:			命令数组的大小
//******************************************************************

void Action::ReadActionData()
{
	for( unsigned int i = 0; i < mKeyFrameNum; i ++ )
	{
		ReadActionData( mKeyFrames[i] );
	}
}

void Action::ReadActionData( const float frame[] )
{
	Joint tempJoints;

	tempJoints.joint[Head_1] = frame[Head_1];
	tempJoints.joint[Head_2] = frame[Head_2];
	tempJoints.joint[LARM_1] = frame[LARM_1];
	tempJoints.joint[RARM_1] = frame[RARM_1];
	tempJoints.joint[LARM_2] = frame[LARM_2];
	tempJoints.joint[RARM_2] = frame[RARM_2];
	tempJoints.joint[LARM_3] = frame[LARM_3];
	tempJoints.joint[RARM_3] = frame[RARM_3];
	tempJoints.joint[LARM_4] = frame[LARM_4];
	tempJoints.joint[RARM_4] = frame[RARM_4];
	tempJoints.joint[LLEG_1] = frame[LLEG_1];
	tempJoints.joint[RLEG_1] = frame[RLEG_1];
	tempJoints.joint[LLEG_2] = frame[LLEG_2];
	tempJoints.joint[RLEG_2] = frame[RLEG_2];
	tempJoints.joint[LLEG_3] = frame[LLEG_3];
	tempJoints.joint[RLEG_3] = frame[RLEG_3];
	tempJoints.joint[LLEG_4] = frame[LLEG_4];
	tempJoints.joint[RLEG_4] = frame[RLEG_4];
	tempJoints.joint[LLEG_5] = frame[LLEG_5];
	tempJoints.joint[RLEG_5] = frame[RLEG_5];
	tempJoints.joint[LLEG_6] = frame[LLEG_6];
	tempJoints.joint[RLEG_6] = frame[RLEG_6];
								   
	mJoint->SetJointAngle( CP_Normal, tempJoints );
}
void Action::ReadReverseActionData()
{
	for( unsigned int i = 0; i < mKeyFrameNum; i ++ )
	{
		ReadReverseActionData( mKeyFrames[i] );
	}
}
void Action::ReadReverseActionData( const float frame[] )
{
	Joint tempJoints;

	tempJoints.joint[Head_1] = frame[Head_1];		
	tempJoints.joint[Head_2] = frame[Head_2];		
	tempJoints.joint[LARM_1] = -frame[RARM_1];		
	tempJoints.joint[RARM_1] = -frame[LARM_1];		
	tempJoints.joint[LARM_2] = frame[RARM_2];		
	tempJoints.joint[RARM_2] = frame[LARM_2];		
	tempJoints.joint[LARM_3] = frame[RARM_3];		
	tempJoints.joint[RARM_3] = frame[LARM_3];		
	tempJoints.joint[LARM_4] = frame[RARM_4];		
	tempJoints.joint[RARM_4] = frame[LARM_4];		
	tempJoints.joint[LLEG_1] = frame[RLEG_1];		
	tempJoints.joint[RLEG_1] = frame[LLEG_1];		
	tempJoints.joint[LLEG_2] = -frame[RLEG_2];		
	tempJoints.joint[RLEG_2] = -frame[LLEG_2];		
	tempJoints.joint[LLEG_3] = frame[RLEG_3];		
	tempJoints.joint[RLEG_3] = frame[LLEG_3];		
	tempJoints.joint[LLEG_4] = frame[RLEG_4];		
	tempJoints.joint[RLEG_4] = frame[LLEG_4];		
	tempJoints.joint[LLEG_5] = frame[RLEG_5];		
	tempJoints.joint[RLEG_5] = frame[LLEG_5];		
	tempJoints.joint[LLEG_6] = -frame[RLEG_6];		
	tempJoints.joint[RLEG_6] = -frame[LLEG_6];		

	mJoint->SetJointAngle( CP_Normal, tempJoints );
}
float Action::SetActionData( float joint )
{
	return joint;
}


void Action::ClearJoint()
{
	mJoint->ClearDelayJoint();
	mJoint->ClearJoint();
}

//******************************************************************
//		Agent 的 Beam 命令
//			@beamX		Beam 目标点的X坐标
//			@beamY:		Beam 目标点的Y坐标
//			@beamAng:	Beam 目标点的角度
//******************************************************************
bool Action::Beam( float beamX, float beamY, float beamAng )
{
	ActLog << "Beam " << beamX << " " << beamY << " " << beamAng << endl;
	mActionType = AT_Other;
	char cmd[128];

	sprintf( cmd, "(beam %0.2f %0.2f %0.2f)", beamX, beamY, beamAng );

	mCmdQuene->InsertCommand( CP_Beam, string(cmd) );

	return true;
}

//******************************************************************
//		让Agent 从初始姿势（各关节角度为0）过渡到站立姿势
//******************************************************************
bool Action::InitialStand()
{
	ActLog << "InitialStand" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = InitialStandFrameNum;
	mKeyFrames = InitialStandFrames;

	ReadActionData( );

	return true;
}

//******************************************************************
//		将 Agent Beam 到指定位置，并且关节回归待命状态
//******************************************************************
bool Action::BeamInitial( float beamX, float beamY, float beamAng )
{
	ActLog << "BeamInitial " << endl;
	mActionType = AT_Other;

	mJoint->SetBeamValue( beamX, beamY, beamAng );

	mJoint->SetBeamAndInitial( true );

	mJoint->ClearJoint();

	mKeyFrameNum = BeamIntialFrameNum;
	mKeyFrames = BeamInitialFrames;

	ReadActionData( );

	return true;
}

//******************************************************************
//		Agent 原地待命
//******************************************************************
bool Action::StandBy()
{
	ActLog << "StandBy" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mJoint->SetJointAngle( CP_Normal );

	return true;
}

bool Action::SwingHead()
{
	ActLog << "SwingHead" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = SwingHeadNum;
	mKeyFrames = SwingHeadFrames;

	ReadActionData( );

	return true;
}


//******************************************************************
//		测试命令延迟的帧数
//			1、头部摆动一个目标角度
//			2、记录WorldModel中头部关节的角度达到目标角度所需要的周期数
//			3、将周期数传给Joint类，用于延迟命令发送的周期
//******************************************************************
bool Action::TestNetState()
{
	ActLog << "TestNetState" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();
	
	static bool ifSendAng = false;
	static int delayFrameNum = -1;
	float testHeadAng = 2.0f;

	if( !ifSendAng )
	{
		mJoint->SetJointAngle( CP_Normal, Head_1, testHeadAng );
		ifSendAng = true;
	}
	else
	{
		StandBy();
	}

	float angEps = 1.0f;

	ActLog << " EPs " << mWorldModel->mSensor.mHJ[Head_1].mAxis << " " << testHeadAng << endl;

	if( fabs( mWorldModel->mSensor.mHJ[Head_1].mAxis - testHeadAng ) > angEps )
	{
		delayFrameNum ++;

		if( delayFrameNum > 3 )
		{
			ActLog << " Bad Net Condition ! " << endl;		

			ifSendAng = false;
			delayFrameNum = -1;
		}

		return false;
	}
	else
	{
		ActLog << "Delay Frame Number: " << delayFrameNum << endl;

		mJoint->mDelayFrameNum = delayFrameNum; 

		return true;
	}
}

//******************************************************************
//		测试动作（调试用）
//******************************************************************
bool Action::Test()
{
	ActLog << "Test" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();
	//Walk( mTestWalkForlen, mTestWalkTurnAng, mTestWalkTransLen );

	mKeyFrameNum = TestActionNum;
	mKeyFrames = TestActionFrames;

	//mKeyFrameNum = SwingHeadNum;
	//mKeyFrames = SwingHeadFrames;

	ReadActionData( );

	return true;
}

bool Action::FaceUpGetUp()
{
	ActLog << "Face Up Get Up " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();
	mKeyFrameNum = FaceUpGetUpNum;
	mKeyFrames = FaceUpGetUpFrames;
	ResetFrameNum();

	ReadActionData( );

	return true;
}

bool Action::FaceDownGetUp()
{
	ActLog << "Face Down Get Up " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = FaceDownGetUpNum;
	mKeyFrames = FaceDownGetUpFrames;

	ResetFrameNum();

	ReadActionData( );

	return true;
}

bool Action::Stand()
{
	ActLog << "Stand " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = StandFrameNum;
	mKeyFrames = StandFrames;

	ReadActionData( );
	//Walk( 0.0f, 0.0f, 0.0f );

	return true;
}

//******************************************************************
//		走路
//******************************************************************
bool Action::Walk( float forLen,float turnAng,float transLen )
{
	ActLog << "Walk" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	int walkT = mWalkFrameNum;
	int frameNum = 0;
	int deltaN;

	if( forLen >= 0.0f )
	{
		deltaN = walkT / 2;
	}
	else
	{
		deltaN = walkT * 3 / 2;
	}
	

	const float thighLen = 0.14f;
	const float shankLen = 0.11f;
	const float footLen = 0.16f;

	const float standingHeight = 0.18f ;// v0.59 - 0.18f;	// v0.58 - 0.204
	const float deltaH = 0.0072f;		// v0.59 - 0.0072f;	// v0.58 - 0.012f		 

	float stepLen = fabs(forLen);		//0.015f
	float tempLen = stepLen * 0.9f;		//0.9f

	float heightLeft;
	float heightRight;
	float stepLeft;
	float stepRight;
	float turnLeft;
	float turnRight;
	float transLeft = 0.0f;
	float transRight = 0.0f;
	
	while( frameNum < walkT )
	{
		//计算前进时各关节的角度
		if( mRightWalk )		//右脚前进
		{	
			heightLeft  = standingHeight;
			heightRight = standingHeight - deltaH;
			stepLeft  = stepLen + tempLen * sin( PI * ( frameNum - deltaN ) / walkT );
			stepRight = stepLen - tempLen * sin( PI * ( frameNum - deltaN ) / walkT );	

			if( turnAng > 0.0f )
			{
				turnLeft = 0.0f;
				turnRight = -turnAng + turnAng * sin( PI * ( frameNum - deltaN ) / walkT );
			}
			else
			{
				turnLeft = turnAng - turnAng * sin( PI * ( frameNum + deltaN ) / walkT );
				turnRight = 0.0f;
			}

			//transLeft = transLen * sin( PI * ( frameNum - deltaN ) / walkT );
			//transRight = -transLen * sin( PI * ( frameNum - deltaN ) / walkT );
		}
		else				//左脚前进
		{
			heightLeft	= standingHeight - deltaH;
			heightRight = standingHeight;
			stepLeft  = stepLen - tempLen * sin( PI * ( frameNum - deltaN ) / walkT );	
			stepRight = stepLen + tempLen * sin( PI * ( frameNum - deltaN ) / walkT );

			if( turnAng > 0.0f )
			{
				turnLeft = -turnAng - turnAng * sin( PI * ( frameNum - deltaN ) / walkT );
				turnRight = 0.0f;
			}
			else
			{
				turnLeft = 0.0f;
				turnRight = turnAng + turnAng * sin( PI * ( frameNum + deltaN ) / walkT );
			}

			//transLeft = -transLen * sin( PI * ( frameNum - deltaN ) / walkT );
			//transRight = transLen * sin( PI * ( frameNum - deltaN ) / walkT );
		}
	
		ComputeWalkAngle(thighLen,shankLen,stepLeft,stepRight,heightLeft,heightRight,turnLeft,turnRight,transLeft,transRight,frameNum, mRightWalk );
		frameNum ++ ;
	}

	mRightWalk = !mRightWalk;

	return true;
}

bool Action::GetFootStep()
{
	return mBasicWalk.IsLeftLegStay;
}

bool Action::SetFootStep()
{
	mBasicWalk.IsLeftLegStay = LeftLegStay;
	mHuman.mFootStep = LeftStep;
}

bool Action::HumanWalk( float forLen, float transLen,float turnAng )
{
	gProcessingLog << " HumanWalk   time:"<<mWorldModel->mSimTime<<"\n";

	ActLog << "Human Walk " << forLen << " " << transLen << " " << turnAng << endl;
	mActionType = AT_Walk;
	//cout << forLen << " " << transLen << " " << turnAng << endl;
 	
	mForLen = forLen;
	mTransLen = transLen;
	mTurnAng = turnAng;

	mJoint->ClearJoint();

		
	//mHuman.ResetFrameNum( forLen );
	//mHuman.SetFootStep();


	//vector<Joint> tempJointV;
	////Humanoid human;
	//mHuman.Walk( forLen, transLen, turnAng, tempJointV );

	//for( unsigned int i = 0; i < tempJointV.size(); i ++ )
	//{
	//	mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
	//}
}

bool Action::HumanTurnAndTrans( float forLen, float transLen,float turnAng )
{
	ActLog << "Human HumanTurnAndTrans " << forLen << " " << transLen << " " << turnAng << endl;
	//cout << forLen << " " << transLen << " " << turnAng << endl;
	mActionType = AT_Walk;

	mJoint->ClearJoint();

	mForLen = forLen;
	//mTransLen = transLen;
	mTurnAng = turnAng;

	//mHuman.ResetFrameNum();
	//vector<Joint> tempJointV;
	////Humanoid human;
	//mHuman.TurnAndTrans( forLen, transLen, turnAng, tempJointV );

	//for( unsigned int i = 0; i < tempJointV.size(); i ++ )
	//{
	//	mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
	//}
}
bool Action::HumanQuickTurn( float turnAng )
{
	/*
	ActLog << "Human HumanQuickTurn " << turnAng << endl;
	mActionType = AT_QuickTurn;

	mJoint->ClearJoint();

	mTurnAng = turnAng;
*/
	ActLog << "Human HumanQuickTurn " << turnAng << endl;
	mActionType = AT_QuickTurn;

	mJoint->ClearJoint();

	mTurnAng = turnAng;

	mHuman.ResetFrameNum();

	//mHuman.ResetFrameNum();
// 	vector<Joint> tempJointV;
// 	//Humanoid human;
// 	mHuman.QuickTurn( turnAng, tempJointV );
// 
// 	for( unsigned int i = 0; i < tempJointV.size(); i ++ )
// 	{
// 		mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
// 	}
}
bool Action::HumanCrazyTurn( float turnAng )
{
	mActionType = AT_CrazyTurn;

	mJoint->ClearJoint();

	mTurnAng = turnAng;

	mHuman.ResetFrameNum();

}
bool Action::HumanSteadyAdjust( float forLen, float transLen,float turnAng )
{
	ActLog << "Human AT_SteadyAdjust " <<forLen<< transLen<<turnAng << endl;
	mActionType = AT_SteadyAdjust;

	mJoint->ClearJoint();

	mForLen = forLen;
	//mTransLen = transLen;
	mTurnAng = turnAng;

 	if( forLen > 0.01f )
 	{
 		mForLen = 0.01f;
 	}
 	else if( forLen < -0.01f )
 	{
 		mForLen = -0.01f;
 	}
 	if( mTransLen > 0.01f )
 	{
 		mTransLen = 0.01f;
 	}
 	else if( mTransLen < -0.01f )
 	{
 		mTransLen = -0.01f;
 	}
	
	if( mTurnAng > 1.0f )
	{
		mTurnAng = 1.0f;
	}
	else if( mTurnAng < -1.0f )
	{
		mTurnAng = -1.0f;
	}
	//mHuman.ResetFrameNum();
}
bool Action::ResetFrameNum()
{
	ActLog << "ResetFrameNum " << endl;
	mBasicWalk.ResetFrameNum();
}
int Action::GetFrameNum()
{
	return mBasicWalk.FrameNum;
}
/*bool Action::HumanBufferAction()
{
	ActLog << "Human HumanBufferAction " << endl;

	mJoint->ClearJoint();

	vector<Joint> tempJointV;

	mHuman.BufferAction( tempJointV );

	for( unsigned int i = 0; i < tempJointV.size(); i ++ )
	{
		mJoint->SetJointAngle( CP_Normal, tempJointV.at(i) );
	}
}
*/
void Action::SetTurnNeckAng( Angle yawAng, Angle pitchAng )
{
	mNeckYawAng = yawAng;
	mNeckPitchAng = pitchAng;
}

bool Action::TurnNeck()
{
	ActLog << "TurnNeck " << endl;
	//mActionType = AT_Other;

	const Angle neckYawMin = -119.5f;
	const Angle neckYawMax = 119.5f;
	const Angle neckPitchMin = -44.5f;
	const Angle neckPitchMax = 44.5f;

	if( mNeckYawAng < neckYawMin )
	{
		mNeckYawAng = neckYawMin;
	}
	else if( mNeckYawAng > neckYawMax )
	{
		mNeckYawAng = neckYawMax;
	}

	if( mNeckPitchAng < neckPitchMin )
	{
		mNeckPitchAng = neckPitchMin;
	}
	else if( mNeckPitchAng > neckPitchMax )
	{
		mNeckPitchAng = neckPitchMax;
	}

	mJoint->SetHeadJointAngle( mNeckYawAng, mNeckPitchAng );
}

bool Action::SwingArm()
{
	ActLog << "SwingArm " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = SwingArmFrameNum;
	mKeyFrames = SwingArmFrames;

	ReadActionData( );

	return true;
}
bool Action::WeKickLeft()
{
	ActLog << "WeKickLeft " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = WeKickLeftFrameNum;
	mKeyFrames = WeKickLeftFrames;

	ReadActionData( );

	return true;

}
bool Action::WeKickRight()
{
	ActLog << "WeKickRight " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = WeKickRightFrameNum;
	mKeyFrames = WeKickRightFrames;

	ReadActionData( );

	return true;

}
bool Action::NewKickLeft()
{
	ActLog << "NewKickLeft "  << NewKickLeftFrameNum << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = NewKickLeftFrameNum;
	mKeyFrames = NewKickLeftFrames;

	ReadActionData( );

	return true;
}
bool Action::NewKickRight()
{
	ActLog << "NewKickRight " << NewKickLeftFrameNum << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = NewKickLeftFrameNum;
	mKeyFrames = NewKickLeftFrames;
	//NewKickRightFrameNum;
	//NewKickRightFrames

	ReadReverseActionData( );

	return true;
}
bool Action::LeftTurnAroundBall()
{
	ActLog << "Left Turn Around Ball " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = LeftTurnAroundBallNum;
	mKeyFrames = LeftTurnAroundBallFrames;

	ReadActionData( );

	return true;
}

bool Action::RightTurnAroundBall()
{
	ActLog << "Right Turn Around Ball " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = RightTurnAroundBallNum;
	mKeyFrames = RightTurnAroundBallFrames;

	ReadActionData( );

	return true;
}
bool Action::DropDownLeft()
{
	ActLog << "Drop Down Left " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = DropLeftDownNum;
	mKeyFrames = DropLeftDownNumFrames;

	ReadActionData( );

	return true;
}
bool Action::DropDownRight()
{
	ActLog << "Drop Down Right" << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = DropRightDownNum;
	mKeyFrames = DropRightDownFrames;

	ReadActionData( );

	return true;
}

//******************************************************************
//		左脚大力直踢
//		范围：	x			y
//				-0.19		-0.06
//				-0.19		-0.03
//				-0.18		-0.1
//				-0.18		-0.02
//				-0.17		-0.1
//				-0.17		-0.1
//				-0.16		-0.09
//				-0.16		-0.02
//				-0.15		-0.09
//				-0.15		-0.02
//		踢球距离：中场---大禁区
//		角度偏差：很小
//******************************************************************
bool Action::LeftStraightKick()
{
	ActLog << "Left Straight Kick " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = LeftStraightKickNum;
	mKeyFrames = LeftStraightKickFrames;

	ReadActionData( );

	return true;
}

//******************************************************************
//		右脚大力直踢
//		范围：	x			y
//				-0.19		0.03
//				-0.19		0.02
//				-0.18		0.09
//				-0.18		0.0
//				-0.17		0.09
//				-0.17		0.01
//				-0.16		0.08
//				-0.16		0.01
//				-0.15		0.08
//				-0.15		0.01
//		踢球距离：中场---大禁区
//		角度偏差：很小
//******************************************************************
bool Action::RightStraightKick()
{
	ActLog << "Right Straight Kick " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = RightStraightKickNum;
	mKeyFrames = RightStraightKickFrames;

	ReadActionData( );

	return true;
}

bool Action::QuickLeftKick()
{
	ActLog << "Quick Left Kick " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = QuickLeftKickFrameNum;
	mKeyFrames = QuickLeftKickFrames;

	ReadActionData( );

	return true;

}

bool Action::QuickRightKick()
{
	ActLog << "Quick Right Kick " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = QuickRightKickFrameNum;
	mKeyFrames = QuickRightKickFrames;

	ReadActionData( );

	return true;
}

bool Action::LeftSoftKick()
{
	ActLog << "Left Soft Kick " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = LeftSoftKickNum;
	mKeyFrames = LeftSoftKickFrames;

	ReadActionData( );

	return true;
}

bool Action::RightSlowPowerKick()
{
	ActLog << "Right Slow Power Kick " << endl;
	mActionType = AT_Other;

	mJoint->ClearJoint();

	mKeyFrameNum = RightSlowPowerKickNum;
	mKeyFrames = RightSlowPowerKickFrames;

	ReadActionData( );

	return true;
}

//******************************************************************
//		走路所需要的辅助计算函数
//
//			@l1：			Agent大腿长度
//			@l2:			Agent小腿长度
//			@m1:			Agent左脚步长
//			@m2:			Agent右脚步长
//			@h1:			Agent左脚抬脚高度
//			@h2:			Agent右脚抬脚高度

//			@turnLeft:		Agent向左旋转的角度
//			@turnRight:		Agent向右旋转的角度
//			@transLeft:		Agent向左平移的距离
//			@transRight：	Agent向右平移的距离
//			@num:			Agent当前的走路帧
//			@leftWalk:		Agent当前是否为迈左脚	
//							true：	左脚
//							false:	右脚
//******************************************************************
void Action::ComputeWalkAngle(float l1,float l2,float m1,float m2,float h1,float h2,float turnLeft,float turnRight,float transLeft,float transRight,int num, bool leftWalk )
{
	float l_1_2 = l1 * l1;
	float l_2_2 = l2 * l2;
	float h_1_2 = h1 * h1;
	float h_2_2 = h2 * h2;
	float m_1_2 = m1 * m1;
	float m_2_2 = m2 * m2; 

	float lLeg_1 = 0.0f;
	float lLeg_2 = 0.0f;
	float lLeg_3 = 0.0f;
	float lLeg_4 = 0.0f;
	float lLeg_5 = 0.0f;
	float lLeg_6 = 0.0f;
	float lArm_1 = -115.0f;	//-115.0f;
	float lArm_2 = 0.0f;	//0.0f;
	float lArm_3 = -85.0f;	//-85.0f;
	float lArm_4 = -85.0f;	//-85.0f;
	float rLeg_1 = 0.0f;
	float rLeg_2 = 0.0f;
	float rLeg_3 = 0.0f;
	float rLeg_4 = 0.0f;
	float rLeg_5 = 0.0f;
	float rLeg_6 = 0.0f;
	float rArm_1 = -115.0f;		//-115.0f;	
	float rArm_2 = 0.0f;		//0.0f;	
	float rArm_3 = 85.0f;		//85.0f;	
	float rArm_4 = 85.0f;		//85.0f;	

	//0.59版机器人 腿部第二、三关节有交换
	lLeg_3 = 180.0f * (asin((l_2_2-l_1_2-h_1_2-m_1_2)/(2*l1*sqrt(h_1_2+m_1_2)))+atan(h1/m1))/PI;	
	lLeg_5 = 180.0f * (PI-asin((l_2_2-l_1_2+h_1_2+m_1_2)/(2*l2*sqrt(h_1_2+m_1_2)))-atan(h1/m1))/PI;
	lLeg_4 = -1.0f * ( lLeg_5 + lLeg_3 );					
	
	rLeg_3 = 180.0f * (asin((l_2_2-l_1_2-h_2_2-m_2_2)/(2*l1*sqrt(h_2_2+m_2_2)))+atan(h2/m2))/PI;	
	rLeg_5 = 180.0f * (PI-asin((l_2_2-l_1_2+h_2_2+m_2_2)/(2*l2*sqrt(h_2_2+m_2_2)))-atan(h2/m2))/PI;
	rLeg_4 = -1.0f * ( rLeg_5 + rLeg_3 );	

	lLeg_1 = turnRight;
	rLeg_1 = turnRight;

	lLeg_2 = 180.0f * atan( transLeft / h1 );
	lLeg_6 = - lLeg_2;
	rLeg_2 = 180.0f * atan( transRight / h2 );
	rLeg_6 = - rLeg_2;

	//0.58版本机器人 
	//lLeg_2 = 180.0f * (asin((l_2_2-l_1_2-h_1_2-m_1_2)/(2*l1*sqrt(h_1_2+m_1_2)))+atan(h1/m1))/PI;	
	//lLeg_5 = 180.0f * (PI-asin((l_2_2-l_1_2+h_1_2+m_1_2)/(2*l2*sqrt(h_1_2+m_1_2)))-atan(h1/m1))/PI;
	//lLeg_4 = -1.0f * ( lLeg_5 + lLeg_2 );					
	//rLeg_2 = 180.0f * (asin((l_2_2-l_1_2-h_2_2-m_2_2)/(2*l1*sqrt(h_2_2+m_2_2)))+atan(h2/m2))/PI;	
	//rLeg_5 = 180.0f * (PI-asin((l_2_2-l_1_2+h_2_2+m_2_2)/(2*l2*sqrt(h_2_2+m_2_2)))-atan(h2/m2))/PI;
	//rLeg_4 = -1.0f * ( rLeg_5 + rLeg_2 );	

	//lLeg_1 = turnRight;
	//rLeg_1 = turnRight;
	//
	//lLeg_3 = 180.0f * atan( transLeft / h1 );
	//lLeg_6 = - lLeg_3;
	//rLeg_3 = 180.0f * atan( transRight / h2 );
	//rLeg_6 = - rLeg_3;

	if( leftWalk )
	{	
		lArm_1 = -115.0f + 20 * sin( PI * num / mWalkFrameNum );
		rArm_1 = -115.0f - 20 * sin( PI * num / mWalkFrameNum );
	}
	else
	{
		lArm_1 = -115.0f - 20 * sin( PI * num / mWalkFrameNum );
		rArm_1 = -115.0f + 20 * sin( PI * num / mWalkFrameNum );
	}
	
	Joint tempJoints;
	
	tempJoints.joint[Head_1] = 0.0f;
	tempJoints.joint[Head_2] = 0.0f;
	tempJoints.joint[LARM_1] = lArm_1;
	tempJoints.joint[RARM_1] = rArm_1;
	tempJoints.joint[LARM_2] = lArm_2;
	tempJoints.joint[RARM_2] = rArm_2;
	tempJoints.joint[LARM_3] = lArm_3;
	tempJoints.joint[RARM_3] = rArm_3;
	tempJoints.joint[LARM_4] = lArm_4;
	tempJoints.joint[RARM_4] = rArm_4;
	tempJoints.joint[LLEG_1] = lLeg_1;
	tempJoints.joint[RLEG_1] = rLeg_1;
	tempJoints.joint[LLEG_2] = lLeg_2;
	tempJoints.joint[RLEG_2] = rLeg_2;
	tempJoints.joint[LLEG_3] = lLeg_3;
	tempJoints.joint[RLEG_3] = rLeg_3;
	tempJoints.joint[LLEG_4] = lLeg_4;
	tempJoints.joint[RLEG_4] = rLeg_4;
	tempJoints.joint[LLEG_5] = lLeg_5;
	tempJoints.joint[RLEG_5] = rLeg_5;
	tempJoints.joint[LLEG_6] = lLeg_6;
	tempJoints.joint[RLEG_6] = rLeg_6;

	//tempJoints.joint[Head_1] = 107.03f;
	//tempJoints.joint[Head_2] = 0.0f;
	//tempJoints.joint[LARM_1] = 0.0f;
	//tempJoints.joint[RARM_1] = 0.0f;
	//tempJoints.joint[LARM_2] = 0.0f;
	//tempJoints.joint[RARM_2] = 0.0f;
	//tempJoints.joint[LARM_3] = 0.0f;
	//tempJoints.joint[RARM_3] = 0.0f;
	//tempJoints.joint[LARM_4] = 0.0f;
	//tempJoints.joint[RARM_4] = 0.0f;
	//tempJoints.joint[LLEG_1] = 0.0f;
	//tempJoints.joint[RLEG_1] = 0.0f;
	//tempJoints.joint[LLEG_2] = 0.0f; 
	//tempJoints.joint[RLEG_2] = 0.0f;
	//tempJoints.joint[LLEG_3] = 0.0f; 
	//tempJoints.joint[RLEG_3] = 0.0f;
	//tempJoints.joint[LLEG_4] = 0.0f;
	//tempJoints.joint[RLEG_4] = 0.0f;
	//tempJoints.joint[LLEG_5] = 0.0f;
	//tempJoints.joint[RLEG_5] = 0.0f;
	//tempJoints.joint[LLEG_6] = 0.0f;
	//tempJoints.joint[RLEG_6] = 0.0f;

	mJoint->SetJointAngle( CP_Normal, tempJoints );
}

//******************************************************************
//		将旧模型下的角度转换到新模型
//		Ps：新旧模型的区别
//				旧模型下大腿的三个自由度为标准坐标系下的三个轴（X、Y、Z轴）
//				新模型下
//
//			@l1：			Agent大腿长度
//			@l2:			Agent小腿长度
//			@m1:			Agent左脚步长
//			@m2:			Agent右脚步长
//			@h1:			Agent左脚抬脚高度
//			@h2:			Agent右脚抬脚高度
//			@turnLeft:		Agent向左旋转的角度
//			@turnRight:		Agent向右旋转的角度
//			@transLeft:		Agent向左平移的距离
//			@transRight：	Agent向右平移的距离 
//			@num:			Agent当前的走路帧
//			@leftWalk:		Agent当前是否为迈左脚	
//							true：	左脚
//							false:	右脚
//******************************************************************
void Action::TransAngle( Angle preAngX, Angle preAngY, Angle preAngZ, Angle &curAngX, Angle &curAngY, Angle &curAngZ )
{

}
int Action::GetCycle()
{
	return mBasicWalk.Cycle;
}