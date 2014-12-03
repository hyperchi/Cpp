#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "WorldModel.h"
#include "Logger.h"

class Obstacle
{
private:
	Obstacle( WorldModel *wm );
	~Obstacle();

private: 
	static Obstacle *mInstance;
public: 
	static Obstacle *GetInstance( WorldModel *wm )
	{
		if( mInstance == NULL )
		{
			mInstance = new Obstacle( wm );
		}
		return mInstance;
	}

private:
	WorldModel *mWorldModel;
	
public:
	bool IsObstacle( Vector3f tarGoto, Vector3f obs, float radius );
	bool IsPlayerObstacle( Vector3f tarGoto, Vector3f playerVector3f );
	bool IsBallObstacle( Vector3f tarGoto );
	bool IsOurPlayerObstacle( Vector3f tarGoto );
	bool IsOppPlayerObstacle( Vector3f tarGoto );
public:
	Vector3f GetRidOfObstacle( Vector3f tarGoto );
	Vector3f AvoidBall( Vector3f tarGoto );
};


#endif //__OBSTACLE_H__