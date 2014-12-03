#ifndef __RUNPOSITION_H__
#define __RUNPOSITION_H__

#include "WorldModel.h"
#include "Situation.h"
#include "MotionGoto.h"
#include "CommandQuene.h"
#include "Action.h"
#include "Logger.h"
#include "Geometry.h"


class RunPosition
{
public:
	RunPosition( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act );
	~RunPosition();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	MotionGoto *mGoto;
	Action *mAct;

public:
	bool ToPosition();
	
	bool DeadBallToPosition( bool ourKick );
};

#endif //__RUNPOSITION_H__