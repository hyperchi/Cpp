//******************************************************************
//						Action  ��  ( Server 0.6 ��
//											By:	Leo		2008-9-10
//																
//					����Agent���ÿһ������ʱ���ؽڣ�Joint���ĽǶ�
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
	bool IsActionDone();			// �жϵ�ǰ�����Ƿ����
	bool Do();						// ��ָ�����ѹ��һ֡����

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
	bool Beam( float beamX, float beamY, float beamAng );		// ��Agent Beam��ָ��λ��
	bool InitialStand();										// ��Agent �ӳ�ʼ���ƣ����ؽڽǶ�Ϊ0�����ɵ�վ������
	bool BeamInitial( float beamX, float beamY, float beamAng );
	bool StandBy();												// Agent ԭ�ش���
	bool TestNetState();										// ���������ӳٵ�֡��
	bool Test();												// ���Զ����������ã�
	bool FaceUpGetUp();
	bool FaceDownGetUp();
	bool Stand();
	bool Walk( float forLen, float transLen,float turnAng );		// ��·
	
	bool GetFootStep();
	bool SetFootStep();
	int GetFrameNum();

	bool HumanWalk( float forLen, float transLen,float turnAng );
	bool HumanTurnAndTrans( float forLen, float transLen,float turnAng );		//  ת��
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
	bool SwingArm();	//��ֹ�൹

	bool WeKickLeft();
	bool WeKickRight();
	bool NewKickLeft();
	bool NewKickRight();

	bool SwingHead();

	bool DropDownLeft();		//����Ա�����˵�
	bool DropDownRight();		//����Ա�����˵�

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
	unsigned int mWalkFrameNum;									// ���һ����·����Ҫ��֡��
	float mTestWalkForlen;
	float mTestWalkTurnAng;
	float mTestWalkTransLen;

	bool mRightWalk;

	void ComputeWalkAngle( float l1,float l2,float m1,float m2,float h1,float h2,float turnLeft,float turnRight,float transLeft,float transRight,int num, bool leftWalk );
																// ��·����Ҫ�ĸ������㺯��
	void ComputeCrazyTurn(float l1,float l2,float m1,float m2,float h1,float h2, float turnAng, int num, bool leftWalk );
	void ComputeCrazyTrans(float l1,float l2,float m1,float m2,float h1,float h2, float transLeft, float transRight, int num, bool leftWalk, bool leftTrans );

	void ComputeTransAngle(float l1,float l2,float m1,float m2,float h1,float h2,float turnLeft,float turnRight,float transLeft,float transRight,int num);

	void TransAngle( Angle preAngX, Angle preAngY, Angle preAngZ, Angle &curAngX, Angle &curAngY, Angle &curAngZ );
																// ����ģ�ͣ�v 0.56���ĽǶ�ת������ģ�ͣ�v 0.60��
};

#endif //__ACTION_H__