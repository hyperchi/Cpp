#include "Action.h"

#define TransFrameNum 2

//加速度：0.001f
//最大速度：0.15f

bool Action::CrazyTrans( float transLen )
{
	ActLog << "Crazy Trans " << endl;

	mJoint->ClearJoint();

	int walkT = TransFrameNum;
	int frameNum = 0;
	int deltaN = walkT / 2;

	static float lastTransLen = 0.0f;

	bool leftTrans;
	if(transLen >= 0.0f )
	{
		leftTrans= true;
	}
	else
	{
		leftTrans = false;
	}

	const float thighLen = 0.14f;
	const float shankLen = 0.11f;
	const float footLen = 0.16f;

	const float standingHeight = 0.18f ;// v0.59 - 0.18f;	// v0.58 - 0.204
	float deltaH = 0.0083f;		// v0.59 - 0.0072f;	// v0.58 - 0.012f		 

	float heightLeft;
	float heightRight;
	float transLeft = 0.0f;
	float transRight = 0.0f;

	while( frameNum < walkT )
	{
		//计算前进时各关节的角度
		if( leftTrans )
		{
			if(	mRightWalk )		//右脚前进
			{	
				heightLeft  = standingHeight;
				heightRight = standingHeight - deltaH;

				transLeft = transLen * sin( PI * ( frameNum - deltaN ) / walkT );
				transRight = -transLen * sin( PI * ( frameNum - deltaN ) / walkT );
			}
			else				//左脚前进
			{
				heightLeft	= standingHeight - deltaH;
				heightRight = standingHeight;

				transLeft = -transLen * sin( PI * ( frameNum - deltaN ) / walkT );
				transRight = transLen * sin( PI * ( frameNum - deltaN ) / walkT );
			}
		}
		else
		{
			if(	!mRightWalk )		//右脚前进
			{	
				heightLeft  = standingHeight;
				heightRight = standingHeight - deltaH;
	
				transLeft = transLen * sin( PI * ( frameNum - deltaN ) / walkT );
				transRight = -transLen * sin( PI * ( frameNum - deltaN ) / walkT );
			}
			else				//左脚前进
			{
				heightLeft	= standingHeight - deltaH;
				heightRight = standingHeight;

				transLeft = -transLen * sin( PI * ( frameNum - deltaN ) / walkT );
				transRight = transLen * sin( PI * ( frameNum - deltaN ) / walkT );
			}
		}
		ComputeCrazyTrans(thighLen,shankLen,0.0f,0.0f,heightLeft,heightRight,transLeft, transRight,frameNum, mRightWalk, leftTrans );
		
		frameNum ++ ;
	}

	mRightWalk = !mRightWalk;
	lastTransLen = transLen;

	return true;
}

void Action::ComputeCrazyTrans(float l1,float l2,float m1,float m2,float h1,float h2, float transLeft, float transRight,  int num, bool leftWalk, bool leftTrans )
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

	if( leftTrans )
	{
		lLeg_2 = 180.0f * atan( transLeft / h1 ) + 10.0f;	
		rLeg_2 = 180.0f * atan( transRight / h2 ) + 10.0f;
	}
	else
	{
		lLeg_2 = 180.0f * atan( transLeft / h1 ) - 10.0f;
		rLeg_2 = 180.0f * atan( transRight / h2 ) - 10.0f;
	}

	lLeg_6 = - lLeg_2;
	rLeg_6 = - rLeg_2;

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

	mJoint->SetJointAngle( CP_Normal, tempJoints );
}

// 稳定值: 0.001f
void Action::SteadyTrans( float transLen )
{
	ActLog << "SteadyTrans " << endl;

	mJoint->ClearJoint();

	int walkT = 8;
	int frameNum = 0;
	int deltaN;
	int deltaT = walkT / 4;

	float forLen = 0.0f;
	float turnAng = 0.0f;

	if ( forLen >= 0.0f )
	{
		deltaN = walkT  / 4;
	}
	else
	{
		deltaN = walkT  * 3 / 4;
	}

	const float thighLen = 0.14f;
	const float shankLen = 0.11f;
	const float footLen = 0.16f;

	const float standingHeight = 0.18f ;// v0.59 - 0.18f;  // v0.58 - 0.204
	float stepLen = fabs(forLen);	//0.015f
	float tempLen = stepLen * 0.9f;	//0.9f

	float heightLeft;
	float heightRight;
	float stepLeft;
	float stepRight;
	float turnLeft;
	float turnRight;
	float transLeft;
	float transRight;
	float deltaH = 0.0072f;// v0.58 - 0.012f		// v0.59 - 0.0072f; //0.01f //0.012f //0.015f

	while( frameNum < walkT )
	{
		//计算前进时各关节的角度
		if( frameNum >= 0 && frameNum <= 0.5 * walkT - 1)
		{			
			heightLeft  = standingHeight;
			heightRight = standingHeight - deltaH;
			stepLeft  = stepLen + tempLen * sin( 2 * PI * ( frameNum - deltaN ) / walkT );
			stepRight = stepLen - tempLen * sin( 2 * PI * ( frameNum - deltaN ) / walkT );	
			if( turnAng > 0.0f )
			{
				turnLeft = 0.0f;
				turnRight = -turnAng + turnAng * sin( 2 * PI * ( frameNum - deltaN ) / walkT );
			}
			else
			{
				turnLeft = turnAng - turnAng * sin( 2 * PI * ( frameNum + deltaN ) / walkT );
				turnRight = 0.0f;
			}
		}
		else 
		{
			heightLeft	= standingHeight - deltaH;
			heightRight = standingHeight;
			stepLeft  = stepLen + tempLen * sin( 2 * PI * ( frameNum - deltaN ) / walkT );	
			stepRight = stepLen - tempLen * sin( 2 * PI * ( frameNum - deltaN ) / walkT );
			if( turnAng > 0.0f )
			{
				turnLeft = -turnAng + turnAng * sin( 2 * PI * ( frameNum - deltaN ) / walkT );
				turnRight = 0.0f;
			}
			else
			{
				turnLeft = 0.0f;
				turnRight = turnAng - turnAng * sin( 2 * PI * ( frameNum + deltaN ) / walkT );
			}
		}	

		transLeft = transLen * sin( 2 * PI * ( frameNum - deltaN ) / walkT );
		transRight = -transLen * sin( 2 * PI * ( frameNum - deltaN ) / walkT );

		ComputeTransAngle(thighLen,shankLen,stepLeft,stepRight,heightLeft,heightRight,turnLeft,turnRight,transLeft,transRight,frameNum);
		frameNum ++ ;
	}
}

void Action::ComputeTransAngle(float l1,float l2,float m1,float m2,float h1,float h2,float turnLeft,float turnRight,float transLeft,float transRight,int num)
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


	lArm_1 = -115.0f + 20 * sin( 2 * PI * num / 8 );
	rArm_1 = -115.0f - 20 * sin( 2 * PI * num / 8 );


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