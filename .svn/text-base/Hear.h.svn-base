#ifndef __HEAR_H__
#define __HEAR_H__

#include "Object.h"
#include "Encryption.h"
#include "EnumType.h"
#include <string>
#include <vector>
//#include "Logger.h"
//#define HearLog cout << "[Hear ] "

class Hear
{
public:
	float	mHearTime;
	bool	mMsg;		                //true：自己
	float	mAngle;			            //Message传来的角度
	string mHeardMessage;
	int		playerHeardFrom;
	ControlType controlMode;
	SayType sayMode;
	//bool	sayerFalled;
	//bool	sayWithFlag;
	vector<float> posParsed;

public:
	bool ExamMsg();
	bool ParseHearMsg(float validFormX,float validFormY);
	void ParsePosMsg(float formX,float formY);
	void ParsePosWithFlag(float formX,float formY);
	string ParseCharMsg();
	int ParseControlMode();
	void PrintVector(vector<float>& vf);

public:
	vector<float> ballPos;
	vector<float> OurPos;
	vector<float> OppPos;
};
#endif