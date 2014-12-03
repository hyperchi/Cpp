#ifndef __SITDRIBBLE_H__
#define __SITDRIBBLE_H__

#include "WorldModel.h"
#include "AgentInfo.h"
#include "SitUnitSquare.h"
#include "ConfFileRead.h"
#include "Logger.h"

class SitDribble
{
public:
	SitDribble( WorldModel *wm, FieldSquare *square, AgentInfo *agentInfo );
	~SitDribble();

private:
	WorldModel *mWorldModel;
	FieldSquare *mFieldSquare;
	AgentInfo *mAgentInfo;

	void InitialDribble();

public:
	bool DribbleSquare( Vector3f &tarDribbleVector );

	Vector3f DribbleTo( const Vector3f &tarDribbleVector );

private:
	float mDribbleThreshold;
	Angle mDribbleUnitAng;
	float mDribbleDist;
	
	float DribbleAngleImpactFactor( float tarTurnAngle );
	bool  IsDribbleToSquareOk( Angle angleToTurn, Vector3f &tarDribbleVector, unsigned int &rowNum, unsigned int &colNum, float &maxWeight );
	float ComputeDribbleWeight( Angle angleToTurn, UnitSquare square );
	bool  LastDribbleWeightOK( Vector3f &tarDribbleVector );
	float ComputeCurrDribbleWeight( Vector3f &tarDribbleVector );

	//obstacle
	bool IsObstacle( const Vector3f &tarDribbleVector );

public:
	float DribbleWeight();
};

#endif //__SITDRIBBLE_H__