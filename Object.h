/*/////////////////copy right AmoiesisNQ ////////////////////
*
*        Robocup 3D Soccer Simulation Team AmoiesisNQ
*    the automation department of Xiamen University China
*
*change log
*2007年8月22日　完成初期框架
*
*////////////////////////////////////////////////////////////
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "stdinc.h"
#include "BasicConfigure.h"
#include "EnumType.h"
#include "Geometry.h"

//////////////////////////////////////////////////////////////////////////
//球场上所有物体的基类
class Object
{
public:  
	Vector3f mPos;						//当前时刻的绝对直角坐标
	Vector3f mRelPos;					//该物体与我的相对直角坐标
    Polar3f  mRelPol;					//该物体与我的相对极坐标   	
	
    inline float DistXyTo(Vector3f& pos){ return this->mPos.distXY2(pos);}	//返回我与pos的水平距离   
	inline Angle ThetaTo(Vector3f& pos){ return this->mPos.angTheta2(pos);}	//返回我与pos在水平面与X轴的角度
  
};

//////////////////////////////////////////////////////////////////////////
//球场上移动物体的基类
class MobileObject : public Object
{
public:	
	Vector3f mVel;						//当前时刻在球场上的速度	
    //Polar3f  mVelPol;	
	//Vector3f mNextPos;
	//Polar3f mNextPol;
	
	list<Vector3f> mHistoryPos;			//存放10个位置历史信息
	list<Vector3f> mHistorySpeed;		//存放10个速度历史信息	
	list<Vector3f> mHistoryAccSpeed;	//存放10个加速度历史信息
	  					
	inline void SaveHistoryPos()
	{
		mHistoryPos.push_back(mPos);
		if (mHistoryPos.size() > 10)
		{
			mHistoryPos.pop_front();
		}
	}

	inline bool JudgeHistoryPosZ()
	{
		list<Vector3f>::iterator it;
		
		for (it = mHistoryPos.begin(); it != mHistoryPos.end(); it++)
		{
			if((*it).z > 0.25)
			{
				return true;// > 0.25
			}
		}
		return false;
	}
	inline void SaveHistorySpeed( const float simStepTime )
	{
		list<Vector3f>::iterator it, it_next;
		Vector3f mySpeed;

		for (it = mHistoryPos.begin(), it_next = ++(mHistoryPos.begin()); it_next != mHistoryPos.end(); it++, it_next++ )
		{
			
			mySpeed =  (*it_next - *it) / simStepTime;
			mHistorySpeed.push_back(mySpeed);
			
			if (mHistorySpeed.size() > 9)
			{
				mHistorySpeed.pop_front();
			}
		}
	}

	inline void SaveHistoryAccSpeed( const float simStepTime )
	{
		list<Vector3f>::iterator acc,acc_next;
		Vector3f myAccSpeed;
		
		for (acc = mHistorySpeed.begin(), acc_next = (mHistorySpeed.begin())++; acc_next != mHistorySpeed.end(); acc++,acc_next++ )
		{
			myAccSpeed = (*acc_next - *acc) / simStepTime;
			mHistoryAccSpeed.push_back(myAccSpeed);
			
			if(mHistoryAccSpeed.size() > 8)
			{
				mHistoryAccSpeed.pop_front();
			}
		}
	}
};

class Player : public MobileObject       //球员继承了移动物体类
{
public:	
	int      mMyPlayerNo;			     //队员号码	
	//Polar3f  mRelPol2Ball;		
	Player()
	{
		mMyPlayerNo = -1;
		mRelPol.dist = 100.0f;
		mRelPol.phi = 0.0f;
		mRelPol.theta = 0.0f;
	}						//未初始化时的号码
};

class HingeJoint                            //一自由度关节类
{
public:	
	HJointT mID;							//关节名称
	float mAxis;							//关节轴
	HingeJoint(){ mAxis = 0.0f;}	
};

//class UniversalJoint						//二自由度关节类
//{
//public:	
//	UJointT mID;							//关节名称
//	float mAxis1;							//关节轴1
//	float mAxis2;							//关节轴2
//	UniversalJoint(){mAxis1 = mAxis2 = 0.0;}		
//};

class FRP                                  //FRP类
{
public:
	Vector3f mFRP_C;                       //FRP作用点坐标
	Vector3f mFRP_F;                       //FRP作用力矢量
};

class HearMsg
{
public:
	float	mHearTime;
	int		mFromPlayerId;		                //0：自己
	float	mAngle;			                //Message传来的角度
	string	mHeardMessage;
};

class SensorData              
{
public:	
	HingeJoint		mHJ[HJCOUNT];		    //解析出来的一自由度关节信息
	//UniversalJoint	mUJ[UJCOUNT];		//解析出来的二自由度关节信息

	Vector3f		mArmGYR;
	Vector3f		mTorsoGYR;

	FRP				mLeftFRP;               //左足FRP值
	FRP				mRightFRP;              //右足FRP值

	SensorData()
	{
		int i;
		for (i = 0; i < HJCOUNT; i++)
		{ 
			mHJ[i].mID = (HJointT)i;
		}
		/*for (i = 0; i < UJCOUNT; i++)
		{
			mUJ[i].mID = (UJointT)i;
		}*/
	}

	HearMsg mHearMessage;
};


#endif
