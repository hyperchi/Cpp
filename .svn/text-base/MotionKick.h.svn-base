#ifndef __MOTIONKICK_H__
#define __MOTIONKICK_H__

#include "WorldModel.h"
#include "Situation.h"
#include "MotionGoto.h"
#include "CommandQuene.h"
#include "Action.h"
#include "Logger.h"
#include "Geometry.h"

class MotionKick
{
public:
	MotionKick( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act );
	~MotionKick();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	MotionGoto *mGoto;
	Action *mAct;

public:
	float GetKickDist();
	bool Kick();
	bool Pass();
	bool KickToTar( Vector3f tarVector3f );

private:
	bool GotoKickArea( Vector3f tarVector3f );
	bool KickTo( Vector3f tarVector3f );
	bool SoftKick();
	bool PowerKick();

private:
	float mKickRadius;
	//Angle mKickAngle;
	Angle mKickAngleEps;

	bool InKickAngle( Vector3f tarVector3f );
	bool InKickAngleAllowBack( Vector3f tarVector3f );
	bool InKickDist();
	bool InKickArea( Vector3f tarVector3f );
};
#endif //__MOTIONKICK_H__