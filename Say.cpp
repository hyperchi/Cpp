#include "Say.h"
#include <bitset>
#define SayLog gHearSayLog<< "[say    ] "

Say::Say(WorldModel *wm,CommandQuene *cq)
{
	mWorldModel = wm;
	mCmdQuene = cq;
	sayMsg.clear();
	sayInf.clear();
	//sayPos = false;
	//sayChar = false;
	//sayWithFlag = false;
}
Say::~Say()
{
}
char Say::CheckNum(char num)
{
	if (num & 128)
	{
		num -= 128;
	}
	if (num & 64)
	{
		num -= 64;
	}
	return num;
}
bool Say::SayObjectPos(float x,float y)
{
	x += mWorldModel->mFieldLength / 2;
	y += mWorldModel->mFieldWidth / 2;
	
	unsigned char result[4];
	Encryption *ep = new Encryption;
	//数据转char，加密
	unsigned char posX = (char)ep->Combine(x);
	unsigned char posY = (char)ep->Combine(y);
	//cout << "[Say]PosX : " << bitset<8>(posX) << END;
	//cout << "[Say]PosY : " << bitset<8>(posY) << END;
	unsigned char tempX = CheckNum(posX >> 2);
	//cout << "[Say]tempX : " << bitset<8>(tempX) << END;
	result[0] = ep->map_into_printablechar((int)tempX);
	//cout << "result[0]" << result[0] << endl;

	unsigned char tempO = posX << 6;
	tempO = tempO >> 2;
	unsigned char tempY = posY >> 4;
	tempO |= tempY;
	tempO = CheckNum(tempO);
	//cout << "[Say]tempO: " << bitset<8>(tempO) << END;
	result[1] = ep->map_into_printablechar((int)tempO);
	//cout << "result[1]" << result[1] << endl;

	tempY = posY << 4;
	tempY = CheckNum(tempY >> 4);
	//cout << "[Say]tempY: " << bitset<8>(tempY) << END;
	result[2] = ep->map_into_printablechar((int)tempY);
	//cout << "result[2]" << result[2] << endl;
	result[3] = 0;
	//cout << "PosMsg : "<< result<< END;
	
	sayMsg += ((char*)result);
	//cout << "sayMsg : " << sayMsg << END;
	//sayPos = true;
	return true;
}
bool Say::SayOBjectPosWithNo(float x,float y,int number)// ObjectType obj
{
	x += mWorldModel->mFieldLength / 2;
	y += mWorldModel->mFieldWidth / 2;
	
	/*if (obj == Say_OurTeam)
	{
		objType = 0;
	}
	else if (obj == Say_OppTeam)
	{
		objType = 1;
	}
	else if (obj == Say_Ball)
	{
		objType = 2;
	}
	else
	{
		objType = 3;
	}*/
	if (number > 3)
	{
		SayLog << "Obj Num Error -> convert to zero!" << endl;
		number = 0;
	}
	unsigned char objNo = (char)number;

	unsigned char result[4];
	Encryption *ep = new Encryption;
	//数据转char，加密
	unsigned char posX = (char)ep->Combine(x);
	unsigned char posY = (char)ep->Combine(y);
	//cout << "[Say]PosX : " << bitset<8>(posX) << END;
	//cout << "[Say]PosY : " << bitset<8>(posY) << END;
	unsigned char tempX = CheckNum(posX >> 2);
	//cout << "[Say]tempX : " << bitset<8>(tempX) << END;
	result[0] = ep->map_into_printablechar((int)tempX);
	//cout << "result[0]" << result[0] << endl;

	unsigned char tempO = posX << 6;
	tempO = tempO >> 2;
	unsigned char tempY = posY >> 4;
	tempO |= tempY;
	tempO = CheckNum(tempO);
	//cout << "[Say]tempO: " << bitset<8>(tempO) << END;
	result[1] = ep->map_into_printablechar((int)tempO);
	//cout << "result[1]" << result[1] << endl;

	tempY = posY << 2;
	tempY |= objNo;
	tempY = CheckNum(tempY);
	//cout << "[Say]tempY: " << bitset<8>(tempY) << END;
	result[2] = ep->map_into_printablechar((int)tempY);
	//cout << "result[2]" << result[2] << endl;
	result[3] = 0;
	//cout << "PosMsg : "<< result<< END;

	sayMsg += ((char*)result);
	//cout << "sayMsg : " << sayMsg << END;
	//sayPos = true;
	//sayWithFlag = true;
	return true;
}
bool Say::SayChar(string& sMsg)
{
	sayMsg.clear();
	sayMsg += sMsg;
	return true;
}

bool Say::AddValid()//奇偶校验位
{
	if (sayMsg.empty())
	{
		return false;
	}
	Encryption *ep = new Encryption;
	int count = 0;
	for (size_t i = 0; i < sayMsg.size(); ++i)
	{
		char temp = sayMsg.at(i);
		count += ep->count((int)temp);
	}
	sayMsg += ep->map_into_printablechar(count);
	return true;
}
char Say::SetControl(ControlType ct,SayType st)//控制位
{
	//if (sayMsg.empty())
	//{
	//	//cout << "No Say Message!" << END;
	//	return false;
	//}
	controlHead = (char)ct;

	controlHead = controlHead << 1;
	unsigned char temp = controlHead;
	if (temp & 1)
	{
		controlHead -= 1;
	}

	if (st == Say_Pos)
	{
		controlHead |= 0;
	}
	if (st == Say_Char)
	{
		controlHead |= 1;
	}
	
	/*if(mWorldModel->mBeginToFall || mWorldModel->mIsFalled)
	{
		control |= 2;
	}
	if (sayWithFlag)
	{
		control |= 4;
	}*/
	controlHead = CheckNum(controlHead);
	SayLog << "control type : " << (controlHead) << endl;
	//cout << "control type : " << bitset<8>(controlHead) << endl;
	Encryption *ep = new Encryption;
	controlHead = ep->map_into_printablechar((int)controlHead);
	return controlHead;
}
bool Say::SendSay()
{
	string validSay;
	if (sayMsg.size() > 10)
	{
		validSay = sayMsg.substr(0,9);
	}
	else
		validSay = sayMsg;
	string temp = "(say ";

	Encryption *ep = new Encryption;
	int sayHead = (int)(mWorldModel->mGameTime * 100) % 10;//valid time时间校验
	//cout << "mGametime : " << sayHead<< endl;
	sayHead = sayHead << 2;
	int playerNo = mWorldModel->mMyPlayerNo;
	sayHead |= playerNo;
	//cout << "sayHead : " << bitset<8>(sayHead) << endl;
	char head = ep->map_into_printablechar(sayHead);
	//cout << "char of sayHead : " << head << endl;
	temp += head;
	//cout << "char of control Head : " << controlHead << endl;
	temp += controlHead;
	temp += validSay;
	temp += ")";
	//cout << "message send : " << temp << END; 
	mCmdQuene->InsertSay(temp);
	sayMsg.clear();
	//sayPos = false;
	//sayChar = false;
	//sayWithFlag = false;
	controlHead = 0;
	return true;
}
