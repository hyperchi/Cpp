#ifndef __WORLDMODEL_H__
#define __WORLDMODEL_H__

#include "BasicConfigure.h"
#include "ConfFileRead.h"
#include "EnumType.h"
#include "Object.h"
#include "Predicate.h"
#include "Matrix.h"
#include "Logger.h"
#include "Hear.h"
#include <vector>
#include <deque>

struct FlagAgentSee
{
	FlagAndGoalT flagT;
	Vector3f mRelPos;	
	Object flagInfo;

	Polar3f  flagRelPol;
} ;

class WorldModel
{
public:
	WorldModel( BasicConfiguration * basicConf );
	~WorldModel();

public:
	
	enum ServerType
	{
		Old_Server,
		New_Server,
	};
	ServerType		mServerType;	

	/*!<Dynamic WorldModel Information>!*/
	float			mSimTime;					//Simulation time in seconds
	unsigned int	mCurrentSimCycle;			//Current cycle of simulation
	float			mLastSimTime;				//Last Simulation time in seconds
	float			mGameTime;					//Game time in seconds

	string			mTeamName;					//Team name of the agent
	string			mOppTeamName;				//Opp Team name of the agent
	SideT			mTeamSide;					//Side which agent plays for	
	int				mMyPlayerNo;				//The Number of myself
	PlayModeT		mPlayMode;					//Current play mode
	PlayModeMap		mPlayModeMap;				//比赛模式的Map
	HJMap			mHjMap;						//HingeJoin的Map
	int				mOurScore;					//Score of our side
	int				mOppScore;					//Score of opp side
	int				mPlayerTotleNum;			//Player number on field
	OppStrength		mOppStrength;

	Hear			mHearMsg;

	Player			mSelf;
	SensorData		mSensor;					//传感器信息
	Vector3f		mBodyFacePoint;				//身体面对的点
	Angle			mBodyAngle;					//身体朝向
	Angle			mBallToSelfAng;				
	bool			mBeginToFall;				//身体即将摔倒
	bool			mBeginToFowardFall;
	bool			mIsFalled;					//身体已经摔倒
	bool			mIsFaceUpFalled;			//身体仰面摔倒
	bool			mIsSideFalled;				//身体侧倒
	bool			mIsStable;
	Vector3f		mBodyFaceTo;

	unsigned int	mPlayerNumOnField;
	unsigned int	mOurPlayerNumOnField;
	unsigned int	mOppPlayerNumOnField;
	Player			mOurTeamPlayer[16];			//我方全部队员的数组  16 == mAgentTotleNum	预留6个
	Player			mOppTeamPlayer[16];			//对方全部队员的数组  16 == mAgentTotleNum	预留6个

	vector<Player> mOurPlayers;
	vector<Player> mOppPlayers;
	vector<int>	   mOurPlayerNoISee;
	vector<int>	   mOppPlayerNoISee;

	/*!<Static WorldModel Information>!*/
	float			mSimStepTime;				//Simulation Step in seconds

	float			mPenaltyLength;
	float			mPenaltyWidth;

	float			mGoalWidth;					//Goal width total             
	float			mGoalHeight;				//Goal height total  
	float			mGoalDepth;					//Goal depth total
	float			mFieldLength;				//Field length total             
	float			mFieldWidth;				//Field width total
	float			mFlagCenterHeight;			//Flag center height total
	float			mBallRadius;				//Ball radius total
	float			mBodyRadius;
	Object			mFieldFlag[FLAG_COUNT];		//标志
	Object			mFieldGoal[GOAL_COUNT];		//球门标志
	MobileObject	mBall;						//球
	bool			isBallRolling;				//判断球时候正在移动
	bool			ballStateChange;
	Vector3f		mOurGoalCenter;				//我方球门中心
	Vector3f		mOppGoalCenter;				//对方球门中心

	deque<Vector3f> mBallHistoryPos;
	Vector3f		mPredictBallPos;
	void			PushBallPos();
	Vector3f		PredictBallPos( unsigned int frameNum );

	void			WorldModelInit();
	bool			WorldModelParse( const string &msg );
	bool			WorldModelUpdate();

	Vector3f		mMyRealPosFromServer;		//服务器返回的自己的绝对直角坐标
	//需打开服务器中对应的开关
	Vector3f		mBallRealPosFromServer;		//服务器返回的球的绝对直角坐标

private:
	Matrix			rMatrix;					//标志物相对坐标矩阵
	Matrix			tMatrix;					//转换矩阵
	Matrix			pMatrix;					//球，其他球员的位置向量
	Matrix			invUmatrix;					//标志物绝对坐标矩阵的逆阵
	LEquations		eqsMypos;					//求自己绝对坐标的线性方程组

	//初始化
	void			InitMaps();
	void			InitMarkers();
	void			InitMatrixs();	

	bool			ParseVision( Predicate &pred );	//解析视觉信息

	//Update My Pos
	void			UpdateMyRelPos();	
	void			UpdateMyUniversalPos();
	void			UpdateOurTeamPos();
	void			UpdateBodyState();

	//新算法测试用变量
	Matrix			YMatrix;
	Matrix			HMatrix;
	Matrix			ProH;
	Matrix			TraH;
	Matrix			DeltaMatrix;
	Vector3f		iniPos;
	
	//新算法测试用函数
	void			UpdateGPS();
	void			UpdateByGPS();

private:
	BasicConfiguration * mBasicConfig;

public:
	string GetAgentConfPath( );
	string GetFormationConfPath( );
	string GetWorldModelConfPath( );

private:
	bool ReadWorldModelConf();

private:
	struct BeamPara
	{
		unsigned int playerNo;
		float beamPara[3];
	};
public:
	BeamPara mInitBeamPos;
	BeamPara mDefenseBeamPos;

//	2009世界杯增加视角限制和噪音
	Matrix mBodyRotation;

	vector<FlagAgentSee> mFlagVec;
	vector<FlagAgentSee> mFlagUse;
	bool bSeeBall;

public:
	void InitBodyRotation();
	void SetBodyRotationFromGYR();

	void GetPosFromGYRAndFlag( Object flag, float &myPosX, float &myPosY, float &myPosZ );
	void GetBallPosFromGYRAndFlag(  Polar3f ballRelPol, float &bPosX, float &bPosY, float &bPosZ );
//修改服务器，输出关于gyr的信息
	Vector3f mBodyRotationRight;
	Vector3f mBodyRotationUp;
	Vector3f mBodyRotationForward;
	Vector3f mBodyRotationPos;
	Vector3f mBodyVelocity;
};

#endif __WORLDMODEL_H__