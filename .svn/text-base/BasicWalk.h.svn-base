/*
按manual定义的坐标体系，P[a1,a2,a3]分别代表
a1:侧向
a2:前进方向
a3:垂直方向

*/
#ifndef __BASICWALK_H__
#define __BASICWALK_H__

#include <vector>
#include "Kinematics.h"
#include <math.h>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include "JointControl.h"


#define LeftLegStay true
#define RightLegStay false

#define Cycle_Normal 10
#define Cycle_QuickTrans 4
#define Cycle_QuickTurn 4
class BasicWalk
{
public:
	BasicWalk();
	~BasicWalk();
	void BasicWalkInit();
    void CalWalk(float forLength, float transLengh, float turnAngle, vector<Joint> &tempjointsV);
	bool ResetFrameNum();
	bool SetCycle(int newCycle);
	void PrintDat();


private:
    void UpdateTarFoot(Kinematics *mLegS,Kinematics *mLegM,float xMove,float yMove,int i,float per,float NowPosS[],float  NowPosM[],float NowRS[],float NowRM[], vector<Joint> &tempjointsV);
	float CalNextMove(float t,float x,float v);
	
	void CalXY();
	void ChangeVtest();
	void RLegS(vector<Joint> &tempjointsV);
	void LLegS(vector<Joint> &tempjointsV);
	void Jumptest();
	void InverInit();//逆向运动学之前先将两腿初始的角度调整成一样，减少计算误差
	void StateInit();
	void InitCenterofM_X();
	void InitCenterofM_Y();
	
	void SetJoints(Joint &tempjoints);
	void Turnangle(Kinematics *tLeg,float NowR[],float tAngle);
	void KeepState(int i);

public:
	bool IsLeftLegStay;
	int FrameNum;
	int Cycle;

private:

	Kinematics* mLLeg;
	Kinematics* mRLeg;

	
	float mAngle[22];
	float x[20+1];
	float y[20+1];
	float detCenteOfMx;
	float detCenteOfMy_multi;
	float StepLenX;
	float StepLenY;
	float TurnAng; //radian
	float mZ;
	float Tc;
	float g;
	float T;
	float InitR[9];
	//float NowR[9];
	float NowR_L[9];
	float NowR_R[9];
	//InitP为初始状态下双脚与质心相对位置
	float InitP_L[3];
	float InitP_R[3];
	//NowP为一步之后(10帧)双脚与质心相对位置
	float NowP_L[3];
    float NowP_R[3];
	bool IsyMoveLeft;
	bool IsTurnLeft;
	bool Is2LegsTurn;
	//std::ofstream fop;


};
#endif