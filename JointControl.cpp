#include "JointControl.h"

#define JointLog gLog<< "[Joint ] "

JointControl::JointControl(  WorldModel * wm, CommandQuene *cmdQuene )
{
	mCmdPri = CP_Normal;
	mJoints.clear();
	mWorldModel =  wm;
	mCmdQuene = cmdQuene;

	mJointEnd = true;

	mDelayFrameNum = 1;
	mDelayJointAngle.resize( 10 );	//预留出10个周期的延迟
	//mDelayWorldModelJointAngle.resize( 10 );

	mLastJointAngle.resize( HJCOUNT );

	for( unsigned int i = 0; i < HJCOUNT; i ++ )
	{
		mLastJointAngle[i] = 0.0f;
	}

	mUsePID = true;

	mPIDEps = 0.5f;
	mAngleMax = 7.02f;
	
	mErrorJointNum = 0;
	InitPID( );

	mIsBeamAndInitial = false;
}
JointControl::~JointControl()
{

}

void JointControl::ClearJoint()
{
	mCmdPri = CP_Normal;
	mJoints.clear();
	mJointEnd = true;
}

void JointControl::ClearDelayJoint()
{
	for( unsigned int i = 0; i < mDelayJointAngle.size(); i ++ )
	{
		for( unsigned int j = 0; j < HJCOUNT; j ++ )
		{
			mDelayJointAngle[i].joint[j] = 0.0f;
		}
	}
}

void JointControl::InitPID( )
{

	ReadConf rC( mWorldModel->GetAgentConfPath() ); 
	Predicate tempP;

	rC.Tranversal( "PID_Use", tempP );
	tempP.GetValue( "PID_Use", mUsePID ); 

	rC.Tranversal( "PID_Eps", tempP );
	tempP.GetValue( "PID_Eps", mPIDEps );	

	rC.Tranversal( "PID_AngleMax", tempP );
	tempP.GetValue( "PID_AngleMax", mAngleMax );
}

void JointControl::SetJointAngle( CommandPriority cmdPri )
{
	mCmdPri = cmdPri;

	Joint tempJoint;

	ClearDelayJoint( );

	for( unsigned int i = 0; i < HJCOUNT; i ++ )
	{
		tempJoint.joint[i] = mWorldModel->mSensor.mHJ[i].mAxis;
	}

	mJoints.push_back( tempJoint );
}

void JointControl::SetJointAngle( CommandPriority cmdPri, Joint jointVec )
{
	mCmdPri = cmdPri;

	mJoints.push_back( jointVec );
}

void JointControl::SetJointAngle( CommandPriority cmdPri, HJointT jointType, float jointAng )
{
	Joint tempJoint;
	
	mCmdPri = cmdPri;

	ClearDelayJoint( );
	
	for( unsigned int i = 0; i < HJCOUNT; i ++ )
	{
		if( i == jointType )
		{
			tempJoint.joint[i] = jointAng;
		}
		else
		{
			tempJoint.joint[i] = mWorldModel->mSensor.mHJ[i].mAxis;
		}
	}

	mJoints.push_back( tempJoint );
}

void JointControl::SetHeadJointAngle( Angle yawAng, Angle pitchAng )
{
	if( mJoints.size() == 0 )
	{
		Joint tempJoint;
		tempJoint.joint[Head_1] = yawAng;
		tempJoint.joint[Head_2] = pitchAng;

		mJoints.push_back( tempJoint );
	}
	else
	{
		for( int i = 0; i < mJoints.size(); i ++ )
		{
			mJoints[i].joint[Head_1] = yawAng;
			mJoints[i].joint[Head_2] = pitchAng;
		}
	}
}

void JointControl::GetCommand()
{	
	if( mJoints.empty() )
	{
		JointLog << "mJoints.empty()" << endl;
		return;
	}
	JointLog << "mJoints.size() " << mJoints.size() << endl;

	Joint tarJoint;
	Joint resultJoint;

	static unsigned int frameNum = 0;	
	
	static unsigned int outCycle = 0;
	if( IsAgentOutOfControl( ) || ( outCycle > 0 && outCycle < 10 ) )
	{
		ClearDelayJoint();
		outCycle ++;
		tarJoint = ControlAgentToInitialPos( );	
		frameNum = 0;
	}
	else
	{
		outCycle = 0;
		tarJoint = mJoints[frameNum];
	}
	//PID( mJoints[i], tempJoint );
	PID( tarJoint, resultJoint );
	
	if( frameNum == mJoints.size() - 1 )
	{
		mJointEnd = true;
	}
	else
	{
		mJointEnd = false;
	}

	frameNum = ( frameNum + 1 ) % mJoints.size();

	string cmdString = GetJointCommand( resultJoint );

	if( !mIsBeamAndInitial )
	{
		mCmdQuene->InsertCommand( mCmdPri, cmdString );
	}
	else
	{
		char cmd[128];

		sprintf( cmd, "(beam %0.2f %0.2f %0.2f)", mBeamValue[0], mBeamValue[1], mBeamValue[2] );

		string beamInitialString = string(cmd) + cmdString;
		
		mCmdQuene->InsertCommand( mCmdPri, beamInitialString );

		SetBeamAndInitial( false );
	}
}

bool JointControl::IsJointVectorEnd()
{
	return mJointEnd;
}

string JointControl::GetJointCommand( const Joint &joint )
{
	char tempJoint[HJCOUNT][64];
	string tarString = "";

	sprintf( tempJoint[Head_1], "(he1 %0.2f)",  joint.joint[Head_1] );
	sprintf( tempJoint[Head_2], "(he2 %0.2f)",  joint.joint[Head_2] );
	sprintf( tempJoint[LARM_1], "(lae1 %0.2f)", joint.joint[LARM_1] );
	sprintf( tempJoint[RARM_1], "(rae1 %0.2f)", joint.joint[RARM_1] );
	sprintf( tempJoint[LARM_2], "(lae2 %0.2f)", joint.joint[LARM_2] );
	sprintf( tempJoint[RARM_2], "(rae2 %0.2f)", joint.joint[RARM_2] );
	sprintf( tempJoint[LARM_3], "(lae3 %0.2f)", joint.joint[LARM_3] );
	sprintf( tempJoint[RARM_3], "(rae3 %0.2f)", joint.joint[RARM_3] );
	sprintf( tempJoint[LARM_4], "(lae4 %0.2f)", joint.joint[LARM_4] );
	sprintf( tempJoint[RARM_4], "(rae4 %0.2f)", joint.joint[RARM_4] );
	sprintf( tempJoint[LLEG_1], "(lle1 %0.2f)", joint.joint[LLEG_1] );
	sprintf( tempJoint[RLEG_1], "(rle1 %0.2f)", joint.joint[RLEG_1] );
	sprintf( tempJoint[LLEG_2], "(lle2 %0.2f)", joint.joint[LLEG_2] );
	sprintf( tempJoint[RLEG_2], "(rle2 %0.2f)", joint.joint[RLEG_2] );
	sprintf( tempJoint[LLEG_3], "(lle3 %0.2f)", joint.joint[LLEG_3] );
	sprintf( tempJoint[RLEG_3], "(rle3 %0.2f)", joint.joint[RLEG_3] );
	sprintf( tempJoint[LLEG_4], "(lle4 %0.2f)", joint.joint[LLEG_4] );
	sprintf( tempJoint[RLEG_4], "(rle4 %0.2f)", joint.joint[RLEG_4] );
	sprintf( tempJoint[LLEG_5], "(lle5 %0.2f)", joint.joint[LLEG_5] );
	sprintf( tempJoint[RLEG_5], "(rle5 %0.2f)", joint.joint[RLEG_5] );
	sprintf( tempJoint[LLEG_6], "(lle6 %0.2f)", joint.joint[LLEG_6] );
	sprintf( tempJoint[RLEG_6], "(rle6 %0.2f)", joint.joint[RLEG_6] );

	for( unsigned int i = 0; i < HJCOUNT; i ++)
	{
		tarString += string(tempJoint[i]);
	}

	return tarString;

}



bool JointControl::PID( Joint initJoint, Joint &tarJoint )
{
	for( unsigned int i = mDelayJointAngle.size() - 1; i > 0; i -- )
	{
		mDelayJointAngle[i] = mDelayJointAngle[i - 1];
	}
	// 1.145f 是一个经过测试产生的 Magic Numbers
	// 当给 Server 发送变化角度为 5.0f时，实际执行效果是 5.72f
	// 当给 Server 发送变化角度为 2.0f时，实际执行效果是 2.29f
	// 所以得到该 Magic Number: 2.29f / 2.0f == 5.72f / 5.0f == 1.145f

	// 补充说明：2008国内赛版本去掉了1.145f的误差控制（为了使动作执行效果更好）
	for( unsigned int i = 0; i < HJCOUNT; i ++ )
	{	
		float diffAng = Normalize( initJoint.joint[i] - mWorldModel->mSensor.mHJ[i].mAxis - mDelayJointAngle[mDelayFrameNum].joint[i] );
		tarJoint.joint[i] = diffAng;
		mDelayJointAngle[0].joint[i] = tarJoint.joint[i];
	}

	return true;
}

bool JointControl::IsAgentOutOfControl()
{
	//const float controlEps = 100.0f;		// 控制误差，防止机器人乱动

	//for( unsigned int i = 0; i < mDelayJointAngle.size(); i ++ )
	//{
	//	for( unsigned int j = 0; j < HJCOUNT; j ++ )
	//	{
	//		if( fabs(mDelayJointAngle[i].joint[j]) >= controlEps )
	//		{

	//			JointLog << "AgentOutOfControl " << j << " " << mDelayJointAngle[i].joint[j] << endl;

	//			return true;
	//		}
	//	}
	//}

	return false;
}

Joint JointControl::ControlAgentToInitialPos()
{
	Joint tempJoint;

	//0.0f, 0.0f, -115, 0, -85, -85,0.0f, 0, 37.6584, -88.6979, 51.0395, 0.0f, -115, 0, 85, 85, 0.0f, 0, 37.6584, -88.6979, 51.0395, 0.0f,
	tempJoint.joint[Head_1] = 0.0f;
	tempJoint.joint[Head_2] = 0.0f;
	tempJoint.joint[LARM_1] = -115.0f;
	tempJoint.joint[LARM_2] = 0.0f;
	tempJoint.joint[LARM_3] = -85.0f;
	tempJoint.joint[LARM_4] = -85.0f;
	tempJoint.joint[LLEG_1] = 0.0f;
	tempJoint.joint[LLEG_2] = 0.0f;
	tempJoint.joint[LLEG_3] = 37.6584f;
	tempJoint.joint[LLEG_4] = -88.6979f;
	tempJoint.joint[LLEG_5] = 51.0395f;
	tempJoint.joint[LLEG_6] = 0.0f;
	tempJoint.joint[RARM_1] = -115.0f;
	tempJoint.joint[RARM_2] = 0.0f;
	tempJoint.joint[RARM_3] = 85.0f;
	tempJoint.joint[RARM_4] = 85.0f;
	tempJoint.joint[RLEG_1] = 0.0f;
	tempJoint.joint[RLEG_2] = 0.0f;
	tempJoint.joint[RLEG_3] = 37.6584f;
	tempJoint.joint[RLEG_4] = -88.6979f;
	tempJoint.joint[RLEG_5] = 51.0395f;
	tempJoint.joint[RLEG_6] = 0.0f;

	return tempJoint;
}

void JointControl::SetBeamAndInitial( bool isBeamAndInitial)
{
	mIsBeamAndInitial = isBeamAndInitial;
}

void JointControl::SetBeamValue( float xBeam, float yBeam, float angBeam )
{
	mBeamValue[0] = xBeam;
	mBeamValue[1] = yBeam;
	mBeamValue[2] = angBeam;
}



//bool JointControl::PIDError( const float &diffAngle, const float &currAng, const float &preAng, float &tarAngle )
//{
//
//	if( fabs( currAng - preAng ) > mPIDEps )
//	{
//		tarAngle = mKP * diffAngle;
//
//		return false;
//	}
//	else
//	{
//		tarAngle = diffAngle;
//	}
//
//	return true;;
//}
