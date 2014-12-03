//******************************************************************
//						Action  类  ( Server 0.6 ）
//											By:	Leo		2008-9-10
//																
//					计算Agent完成每一个动作时各关节（Joint）的角度
//
//******************************************************************

#ifndef __ACTION_H__
#define __ACTION_H__

#include <vector>

#include "ConfFileRead.h"
#include "EnumType.h"
#include "WorldModel.h"
#include "CommandQuene.h"
#include "JointControl.h"
#include "ActionData.h"
#include "ActionKickData.h"
#include "ActionKickNew.h"
#include "ActionGetUpData.h"
#include "HumanoidControl.h"
#include "BasicWalk.h"

#define ActLog gLog<< "[Action] "

class Action
{
public:
	Action( WorldModel *wm, CommandQuene *cmdQuene );
	~Action();

private:
	WorldModel *mWorldModel;
	CommandQuene *mCmdQuene;
	JointControl *mJoint;

public:
	bool IsActionDone();			// 判断当前动作是否完成
	bool Do();						// 向指令队列压入一帧动作

private:
	unsigned int mJointFrameNow;
	unsigned int mKeyFrameNum;
	const float (*mKeyFrames)[HJCOUNT];

	unsigned int TestActionNum;
	float TestActionFrames[2000][HJCOUNT];

	void InitAction();
	void ReadActionDataFromFile();
	void ReadActionData();
	void ReadActionData( const float frame[] );
	void ReadReverseActionData();
	void ReadReverseActionData( const float frame[] );
	float SetActionData( float joint );

	Humanoid mHuman;

	BasicWalk mBasicWalk;

private:
	enum ActionType
	{
		AT_Walk,
		AT_TurnAndTrans,
		AT_QuickTurn,
		AT_SteadyAdjust,
		AT_CrazyTurn,
		AT_Other,
	};
	float mForLen;
	float mTransLen;
	float mTurnAng;
public:	
	ActionType mActionType;
	bool IsLastActAdj;
	bool IsLastActQTurn;

	void ClearJoint();
	bool Beam( float beamX, float beamY, float beamAng );		// 将Agent Beam到指定位置
	bool InitialStand();										// 让Agent 从初始姿势（各关节角度为0）过渡到站立姿势
	bool BeamInitial( float beamX, float beamY, float beamAng );
	bool StandBy();												// Agent 原地待命
	bool TestNetState();										// 测试命令延迟的帧数
	bool Test();												// 测试动作（调试用）
	bool FaceUpGetUp();
	bool FaceDownGetUp();
	bool Stand();
	bool Walk( float forLen, float transLen,float turnAng );		// 走路
	
	bool GetFootStep();
	bool SetFootStep();
	int GetFrameNum();

	bool HumanWalk( float forLen, float transLen,float turnAng );
	bool HumanTurnAndTrans( float forLen, float transLen,float turnAng );		//  转身
	bool HumanQuickTurn( float turnAng );
	bool HumanCrazyTurn( float TurnAng );
	bool HumanSteadyAdjust( float forLen, float transLen,float turnAng );
	bool ResetFrameNum();

	int GetCycle();

	bool HumanBufferAction();
	
	void SetTurnNeckAng( Angle yawAng, Angle pitchAng );
	Angle mNeckYawAng;
	Angle mNeckPitchAng;
	bool TurnNeck();
	bool SwingArm();	//防止侧倒

	bool WeKickLeft();
	bool WeKickRight();
	bool NewKickLeft();
	bool NewKickRight();

	bool SwingHead();

	bool DropDownLeft();		//守门员向左扑到
	bool DropDownRight();		//守门员向右扑到

	bool LeftTurnAroundBall();
	bool RightTurnAroundBall();

	bool CrazyTurn( float turnAng );
	bool CrazyWalk( float forLen );
	bool CrazyTrans( float transLen );

	void SteadyTrans( float transLen );


	bool LeftStraightKick();
	bool RightStraightKick();
	bool LeftSoftKick();
	bool RightSlowPowerKick();

	bool QuickLeftKick();
	bool QuickRightKick();

private:
	unsigned int mWalkFrameNum;									// 完成一步走路所需要的帧数
	float mTestWalkForlen;
	float mTestWalkTurnAng;
	float mTestWalkTransLen;

	bool mRightWalk;

	void ComputeWalkAngle( float l1,float l2,float m1,float m2,float h1,float h2,float turnLeft,float turnRight,float transLeft,float transRight,int num, bool leftWalk );
																// 走路所需要的辅助计算函数
	void ComputeCrazyTurn(float l1,float l2,float m1,float m2,float h1,float h2, float turnAng, int num, bool leftWalk );
	void ComputeCrazyTrans(float l1,float l2,float m1,float m2,float h1,float h2, float transLeft, float transRight, int num, bool leftWalk, bool leftTrans );

	void ComputeTransAngle(float l1,float l2,float m1,float m2,float h1,float h2,float turnLeft,float turnRight,float transLeft,float transRight,int num);

	void TransAngle( Angle preAngX, Angle preAngY, Angle preAngZ, Angle &curAngX, Angle &curAngY, Angle &curAngZ );
																// 将旧模型（v 0.56）的角度转换到新模型（v 0.60）
};

#endif //__ACTION_H__