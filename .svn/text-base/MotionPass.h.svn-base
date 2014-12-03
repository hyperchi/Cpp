#ifndef __MOTIONPASS_H__
#define __MOTIONPASS_H__

#include "WorldModel.h"
#include "Situation.h"
#include "MotionGoto.h"
#include "CommandQuene.h"
#include "Action.h"
#include "Logger.h"
#include "Geometry.h"

class MotionPass
{
public:
	MotionPass( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act );
	~MotionPass();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	MotionGoto *mGoto;
	Action *mAct;

public:
	bool Pass();

private:
	bool GotoPassArea();
	bool PassTo();

private:
	float mKickRadius;
	//Angle mKickAngle;
	Angle mKickAngleEps;

	bool InPassAngle( Vector3f tarVector3f );
	bool InPassDist();
	bool InPassArea( Vector3f tarVector3f );
};

#endif //__MOTIONPASS_H__