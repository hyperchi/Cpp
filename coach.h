#ifndef __COACH_H__
#define __COACH_H__

#include "WorldModel.h"
#include "Logger.h"
#include <deque>

class Coach
{
private:
	Coach( WorldModel *wm );
	~Coach();

private:
	WorldModel *mWorldModel;

private: 
	static Coach *mInstance;
public: 
	static Coach *GetInstance( WorldModel *wm )
	{
		if( mInstance == NULL )
		{
			mInstance = new Coach( wm );
		}
		return mInstance;
	}

private:
	deque<Vector3f> mOppPos; 
	deque<Vector3f> mSelfPos; 

public:
	float mOppAverSpeed;
	float mSelfAverSpeed;
	float mOppMaxAverSpeed;
	float mSelfMaxAverSpeed;
	float mBallAverPos;
	OppStrength mOppStrength;

	void Update();
	float SelfAverSpeed();
	float OppAverSpeed();
	void BallAverPos();
	OppStrength GetOppStrength();
};

#endif // __COACH_H__