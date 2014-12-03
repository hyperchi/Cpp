#ifndef __FORMATION_H__
#define __FORMATION_H__

#include "WorldModel.h"

class Formation
{
public:
	Formation( WorldModel *wm );
	~Formation();

private:
	WorldModel *mWorldModel;
	void Initial();

private:
	PlayerRole mMyRole;

	float mBasicPositionX[FR_Count];
	float mBasicPositionY[FR_Count];

public:
	PlayerRole GetRole( unsigned int num );
	PlayerRole GetMyRole();
	float GetMyBasicPosX();
	float GetMyBasicPosY();
};

#endif //__FORMATION_H__
