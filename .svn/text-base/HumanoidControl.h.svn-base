#ifndef __HUMANOIDCONTROL_H__
#define __HUMANOIDCONTROL_H__

#include <vector>

#include "Matrix.h"
#include "JointControl.h"
#include "Logger.h"
#define LeftStep	true
#define RightStep	false

class Humanoid
{
public:
	Humanoid();
	~Humanoid();

private:
	Matrix Rot2Omega( Matrix R );
	Matrix Rpy2Rot( AngRad a, AngRad b, AngRad c);
	Matrix CalcVWerr( Matrix pTar, Matrix pNow, Matrix RTar, Matrix RNow );
	Matrix Rodrigues( Matrix ang, float theta );
	Matrix CrossMulti( Matrix w, Matrix p );
	Matrix CalcLegJacobian( bool isLeftLeg, const Matrix &pTar );

private:
	struct JointPara 
	{
		Matrix a;
		Matrix b;
		AngRad q;
		Matrix p;
		Matrix R;
	};

	vector<JointPara> mLeftLeg;
	vector<JointPara> mRightLeg;
	vector<JointPara> mUpperJoints;

	void InitUpperJoitnAngle();

	void InitLegPara( bool isLeftLeg );
	void InitLegAngle( bool isLeftLeg, int iPlan );
	void UpdateLegPosAndR( bool isLeftLeg );
	void UpdateLegAngle( AngRad &initQ, AngRad deltaQ );
	bool InverseKinmatics( bool isLeftLeg, const Matrix &pTar, const Matrix &RTar );
	bool IfLegJointLegal( bool isLeftLeg );	

	void IllegalJointLog( float forLength, float transLengh, float turnAng );

	bool SetTarFoot( bool isLeftLeg, float posX, float posY, float posZ, Angle yawAng, Angle bodyAng, unsigned int frameNum );
	bool GetTarFoot( bool isLeftLeg, float posX, float posY, float posZ, Angle angX, Angle angY, Angle angZ );
	
	Angle GetUpperJoint( unsigned int legJointNum );
	Angle GetLegJoint( bool isLeftLeg, unsigned int legJointNum );

public:
	bool mFootStep;
	void GetJoints( Joint &joints );
	bool Walk( float forLength, float transLengh, float turnAng, vector<Joint> &tempjointsV );
	bool TurnAndTrans( float forLength, float transLengh, float turnAng, vector<Joint> &tempjointsV );
	bool QuickTurn( float turnAng, vector<Joint> &tempjointsV );
	bool SteadyAdjust( float forLength, float transLengh, float turnAng, vector<Joint> &tempjointsV );
	bool CheckWalkPara( float &forLength, float &transLengh, float &turnAng );
	bool BufferAction( vector<Joint> &tempjointsV );

private:
	const float cInitLeftTransLen;
	const float cInitRightTransLen;
	const float cInitForLen;
	const float cInitHeight;
	const Angle cBodyAngle;

	float mUltiLeftForLen;
	float mUltiLeftTransLen;
	float mUltiLeftHeight;
	float mUltiLeftTurn;
	float mUltiRightForLen;
	float mUltiRightTransLen;
	float mUltiRightHeight;
	float mUltiRightTurn;
	
	float mWalkFrameNum;
	float mTurnAndTransFrameNum;
	float mQuickTurnFrameNum;
	float mSteadyAdjustFrameNum;
public:
	void ResetFrameNum();
	void ResetFrameNum( float forLen );
	void SetFootStep();
};

#endif	//__HUMANOIDCONTROL_H__