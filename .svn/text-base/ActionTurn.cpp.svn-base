#include "Action.h"

#define TurnFrameNum 2

bool Action::CrazyTurn( float turnAng )
{
	ActLog << "Crazy Turn " << endl;

	mJoint->ClearJoint();

	int walkT = TurnFrameNum;
	int frameNum = 0;
	int deltaN = walkT / 2;

	const float thighLen = 0.14f;
	const float shankLen = 0.11f;
	const float footLen = 0.16f;

	const float standingHeight = 0.18f ;// v0.59 - 0.18f;	// v0.58 - 0.204
	const float deltaH = 0.008f;		// v0.59 - 0.0072f;	// v0.58 - 0.012f		 

	float heightLeft;
	float heightRight;
	float angToTurn = turnAng;

	while( frameNum < walkT )
	{
		//计算前进时各关节的角度
		if( mRightWalk )		//右脚前进
		{	
			heightLeft  = standingHeight;
			heightRight = standingHeight - deltaH;

			if( turnAng > 0.0f )
			{
				angToTurn = -turnAng + turnAng * sin( PI * ( frameNum - deltaN ) / walkT );
			}
			else
			{
				angToTurn = 0.0f;
			}
		}
		else				//左脚前进
		{
			heightLeft	= standingHeight - deltaH;
			heightRight = standingHeight;

			if( turnAng > 0.0f )
			{
				angToTurn = 0.0f;
			}
			else
			{
				angToTurn = turnAng + turnAng * sin( PI * ( frameNum + deltaN ) / walkT );
			}
		}

		ComputeCrazyTurn(thighLen,shankLen,0.0f,0.0f,heightLeft,heightRight,angToTurn, frameNum, mRightWalk );
	
		frameNum ++ ;
	}

	mRightWalk = !mRightWalk;
	
	return true;
}

void Action::ComputeCrazyTurn(float l1,float l2,float m1,float m2,float h1,float h2,float turnAng, int num, bool leftWalk )
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

	lLeg_1 = turnAng;
	rLeg_1 = turnAng;

	if( leftWalk )
	{	
		lArm_1 = -115.0f + 20 * sin( PI * num / TurnFrameNum );
		rArm_1 = -115.0f - 20 * sin( PI * num / TurnFrameNum );
	}
	else
	{
		lArm_1 = -115.0f - 20 * sin( PI * num / TurnFrameNum );
		rArm_1 = -115.0f + 20 * sin( PI * num / TurnFrameNum );
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

	mJoint->SetJointAngle( CP_Normal, tempJoints );
}

