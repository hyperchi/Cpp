#ifndef __SAY_H__
#define __SAY_H__

#include "WorldModel.h"
#include "CommandQuene.h"
#include "Encryption.h"
#include "EnumType.h"
#include "Logger.h"
#include <string>
//#define SayLog gLog << "[Say ] "

class Say
{
public:
	Say(WorldModel *wm,CommandQuene *cq);
	~Say();

	string sayMsg;
	vector<float> sayInf;
	//bool sayPos;
	//bool sayChar;
	//bool sayWithFlag;
	unsigned char controlHead;

private:
	WorldModel *mWorldModel;
	CommandQuene *mCmdQuene;

public:	
	bool SayObjectPos(float x,float y);
	//bool SayObjectPosWithFlag(float x,float y, ObjectType obj);
	bool SayOBjectPosWithNo(float x,float y, int number);
	bool SayChar(string& sMsg);
	bool SendSay();
	bool AddValid();
	char SetControl(ControlType ct,SayType st);
	char CheckNum(char num);
};
#endif