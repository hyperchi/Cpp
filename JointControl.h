#ifndef __JOINTCONTROL_H__
#define __JOINTCONTROL_H__

#include <iostream>
#include <stdio.h>
#include <vector>

#include "EnumType.h"
#include "WorldModel.h"
#include "CommandQuene.h"
#include "Logger.h"
#include "FloatMath.h"

using namespace std;

namespace joints
{
	struct Joint
	{
		float joint[HJCOUNT];
	};
};
using namespace joints;

class JointControl
{
public:
	JointControl(  WorldModel * wm, CommandQuene *cmdQuene );
	~JointControl();

private:
	WorldModel   *mWorldModel;
	CommandQuene *mCmdQuene;
	CommandPriority mCmdPri;
	vector<Joint> mJoints;

	bool mJointEnd;

public:
	unsigned int mDelayFrameNum;

	void ClearJoint();
	void ClearDelayJoint();
	void SetJointAngle( CommandPriority cmdPri );
	void SetJointAngle( CommandPriority cmdPri, Joint jointVec );
	void SetJointAngle( CommandPriority cmdPri, HJointT jointType, float jointAng );
	void SetHeadJointAngle( Angle yawAng, Angle pitchAng );
	void GetCommand();
	bool IsJointVectorEnd();

private:
	string GetJointCommand( const Joint &jointVec );


private:
	vector<float> mLastJointAngle;
	vector<Joint> mDelayJointAngle;
	//vector<Joint> mDelayWorldModelJointAngle;

	bool mUsePID;
	float mPIDEps;
	float mAngleMax;
	int	mErrorJointNum;

	void InitPID( );
	bool PID( Joint initJoint, Joint &tarJoint );
	bool PIDError( const float &diffAngle, const float &currAng, const float &preAng, float &tarAngle );
	bool PIDError( const float &angle, unsigned int num, float &aFact );

private:
	bool IsAgentOutOfControl();
	Joint ControlAgentToInitialPos();

private:
	bool mIsBeamAndInitial;
	float mBeamValue[3];

public:
	void SetBeamAndInitial( bool isBeamAndInitial);
	void SetBeamValue( float xBeam, float yBeam, float angBeam );
};

#endif //__JOINTCONTROL_H__