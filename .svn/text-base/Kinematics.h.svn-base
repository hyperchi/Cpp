#ifndef __KINEMATICS_H__
#define __KINEMATICS_H__

#include <string>
#include <vector>
#include "Matrix.h"
#include "FloatMath.h"

enum Kinematics_Type
{
	Kinematics_Left,
	Kinematics_Right
};

class Kinematics 
{
public:
	//Kinematics();
	Kinematics(Kinematics_Type type);
	Kinematics(std::string str);
	void ForwardKine(int starJ);
	void InverseKine(int toj);
	void InitialAngle(float qAngle[]);
	void TestPrint();
	void SetTarget(float p[],float r[]);
	void SetTarget(float p[]);
	void SetmJP(int i,float p[]);
	void SetmJR(int i,float r[]);
	float* GetmJP(int i);
	float* GetmJR(int i);
	float* GetAngle();
	float GetAngle(int i);
	float* GetTargetP();
	float* GetTargetR();
	void PrintJP(int i);
	void PrintJR(int i);

private:
	struct JointUnit
	{
		//以下变量的意义请参考书本
		float R[9];
		float P[3];
		float Ax[3];
		float b[3];
		float q;
	};

	void InitL();
	void InitR();
   	void CalErr(int to,Matrix &err);
    Matrix CalLnr(const Matrix &rerr);
    void CalJacobian(Matrix &Jacobian);


	
	std::vector<JointUnit> mJointU;
	
	JointUnit mTarget;

	float tem_angle[6];

};
#endif

