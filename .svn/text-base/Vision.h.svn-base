#ifndef __VISION_H__
#define __VISION_H__

#include "WorldModel.h"
#include "Matrix.h"
#include "FloatMath.h"
#include "Geometry.h"

class Vision
{
public:
	Vision( WorldModel *wm );
	~Vision();

private:
	WorldModel *mWorldModel;

	Player			mSelf;
	MobileObject	mBall;						//球
	vector<Player>	mOurPlayers;
	vector<Player>	mOppPlayers;

	Angle			mBodyAngle;					//身体朝向			
	bool			mIsFalled;					//身体已经摔倒
	bool			mIsFaceUpFalled;			//身体仰面摔倒
	bool			mIsSideFalled;				//身体侧倒

	deque<Vector3f> mBallHistoryPos;
	Vector3f		mPredictBallPos;

	Matrix mBodyRotation;

	void UpdateInitial();
	void InitGYR();
	void UpdateGYR();
	void ModifyGYR();
	void LocateSelfPos();
	void LocateBall();
	void LocatePlayer();
	void UpdateBodyState();
	void UpdateWorldModel();

public:	
	float lastSeeBallTime;
	Angle mNeckYawAng;    //
	Angle mNeckPitchAng;  //
	int FlagNumISee();
	void UpdatePos();
	void TurnNeck();

private:
	void LocateSelf_1();
	int LocateSelf_3();
	int Get_3_SpereInterception( float &posX1, float &posY1, float &posZ1, float &posX2, float &posY2, float &posZ2 );
	//int Get_3_SpereInterceptionDebug( float &posX1, float &posY1, float &posZ1, float &posX2, float &posY2, float &posZ2 );
	bool LocateSelf_4_Ideal();
	void LocateWithNoVisionRestrict();

	void GetFlagPos( FlagAndGoalT flagT, float &flagX, float &flagY, float &flagZ);
	void GetFlagPos( FlagAgentSee flagISee, float &flagX, float &flagY, float &flagZ);
	//ball_location
	
	void GetBallPosFromGYRAndBallPol(  Polar3f ballRelPol, float &bPosX, float &bPosY, float &bPosZ );
	void GetOthersPosFromGYRAndRel(  Polar3f otherRelPol, float &aPosX, float &aPosY, float &aPosZ );
	void LocateOtherAgent_4_Ideal();
public:
	void SetTurnNeckAng( Angle &yawAng, Angle &pitchAng );
	bool AngleDiffLth120( Angle angle1,Angle angle2,Angle &diffAng);
	void AddHeadRotation( Matrix &mBodyRot);
	void SubHeadRotation( Matrix &mBodyRot);

private:
	void UpdateVisibleObject();
	bool IsVisibleObject( Vector3f objPos );

private:
	bool mNeedToLocateBall;
public:
	bool NeedToLocateBall();
};

#endif //__VISION_H__