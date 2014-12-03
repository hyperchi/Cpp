#ifndef __DRIBBLE_H__
#define __DRIBBLE_H__

#include "stdafx.h"
#include "WorldModel.h"
#include "CommandQuene.h"
#include "Situation.h"
#include "Logger.h"
#include "HumanGoto.h"
#include "Obstacle.h"

class Dribble
{
public:
	Dribble( WorldModel *wm, Situation *situ, HumanGoto *hGoto, CommandQuene *cmdQuene, Action *act );
	~Dribble();

private:
	WorldModel *mWorldModel;
	Situation *mSituation;
	CommandQuene *mCmdQuene;
	HumanGoto *mHGoto;
	Action *mAct;
	Obstacle *mObstacle;

private:
	bool IsneedTurn;

private:
	bool BasicDribbleAttackViability( Vector3f tarDribbleTo );
	bool GetDribbleAttackViability( Vector3f tarDribbleTo );
	bool GetDribblePassViability( Vector3f tarDribbleTo );
	bool GetDribbleDefenseViability( Vector3f tarDribbleTo );

	Vector3f GetDribbleAttackTar();
	float GetDribleDist( Vector3f tarDribbleTo );

public:
	//bool DribbleTo( Vector3f tarDribbleTo );
	bool IsInDribbleArea();
	
	bool DribbleAttack();
	bool DribblePass();
	bool DribbleDefense();

private:
	bool DoDribbleAction( Vector3f tarGoto );
	bool DoDribbleAction( Vector3f tarGoto, Angle tarAng );
 	bool DoGotoAction( Vector3f tarGoto );
	bool DoTranAction( Vector3f tarGoto );
 	bool DoGotoAction( Vector3f tarGoto, Angle tarAng );
};

#endif //__DRIBBLE_H__