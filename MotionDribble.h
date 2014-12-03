#ifndef __MOTIONDRIBBLE_H__
#define __MOTIONDRIBBLE_H__

#include "WorldModel.h"
#include "Situation.h"
#include "MotionGoto.h"
#include "CommandQuene.h"
#include "Action.h"
#include "Logger.h"
#include "Geometry.h"

class MotionDribble
{
public:
	MotionDribble( WorldModel *wm, Situation *situ, MotionGoto *mtGoto, CommandQuene *cmdQuene, Action *act );
	~MotionDribble();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	MotionGoto *mGoto;
	Action *mAct;

private:
	void InitDribble();

public:
	bool Dribble();

private:
	bool GotoDribbleArea( Vector3f tarVector3f );
	bool DribbleTo( Vector3f tarVector3f );
	
private:
	float mDribbleRadius;
	Angle mDribbleAngle;
	Angle mDribbleAngleEps;

	bool InDribbleRadius();
	bool InDribbleAngle( Vector3f tarVector3f );
	bool InDribbleAngleAllowBack( Vector3f tarVector3f );
	bool InDribbleAngleAllowTrans( Vector3f tarVector3f );
	bool InDribbleArea( Vector3f tarVector3f );

	bool EvaluCurrDribbleTar();

};

#endif //__MOTIONDRIBBLE_H__
