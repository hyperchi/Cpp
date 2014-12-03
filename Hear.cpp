#include "Hear.h"
#include <bitset>

bool Hear::ExamMsg()
{
	if (mHeardMessage.empty())
	{
		//cout << "mHeardMessage is empty" << endl;
		return false;
	}
	char ini = mHeardMessage[0];
	Encryption *ep = new Encryption;
	//cout << "char of recHead : " << ini << endl;
	int head = ep->map_from_printablechar(ini);
	//cout << "head : " << bitset<8>(head) << END;
	int sendTime = head >> 2;
	int recTime = (int)(mHearTime * 100) % 10;
	//cout << "sendtime : " << bitset<8>(sendTime) << endl;
	//cout << "recTime : " << bitset<8>(recTime) << endl;
	//cout << "sendTime : " << sendTime << " " << "recTime : " << recTime << endl;
	if (recTime < sendTime)
	{
		recTime += 10;
		if (recTime - sendTime > 4)
		{
			//cout << "exam msg false!" << endl;
			return false;
		}		
	}
	else
	{
		if (recTime - sendTime > 4)
		{
			//cout << "exam msg false!" << endl;
			return false;
		}	
	}
	sendTime = sendTime << 2;
	//cout << "sendtime 2 : " << bitset<8>(sendTime) << END;
	playerHeardFrom = head^sendTime;
	//cout << "playerNo : " << bitset<8>(playerHeardFrom) << END;
	//HearLog << "PlayerHeardFrom : " << playerHeardFrom << END;
	//cout << "return!\n";
	if( ep ) 
	{
		delete ep;
		ep = NULL;
	}
	return true;
}
bool Hear::ParseHearMsg(float validFormX,float validFormY)
{
	//cout << "Parse Hear Msg \n";
	if (ExamMsg())
	{
		switch (ParseControlMode())
		{
		case 0:			
			//cout<<"ParsePosMsg : "<< endl;
			ParsePosMsg(validFormX,validFormY);	
			break;
		case 1:
			//HearLog<<"ParseCharMsg : "<< END;
			ParseCharMsg();
			break;
		}
		//sayWithFlag = false;
		//sayerFalled = false;
		return true;
	}
	else
		return false;
}
int Hear::ParseControlMode()
{
	//cout << "Parse Control Mode \n";
	char control = mHeardMessage[1];
	//cout << "control type : " << bitset<8>(control) << endl;
	int temp = control >> 1;
	switch (temp)
	{
	case OurAll:
		controlMode = OurAll;
		break;
	case Our2Ball:
		controlMode = Our2Ball;
		break;
	case OurPBallPOpp:
		controlMode = OurPBallPOpp;
		break;
	case Opp2Ball:
		controlMode = Opp2Ball;
		break;
	case OppAll:
		controlMode = OppAll;
		break;
	}
	//cout << "control mode  :" << controlMode << endl;
	temp = temp << 1;
	temp = control^temp;
	//cout << "say mode  :" << temp << endl;
	if (temp == Say_Pos)
	{
		sayMode = Say_Pos;
		return 0;
	}
	if (temp == Say_Char)
	{
		sayMode = Say_Char;
		return 1;
	}
}
string Hear::ParseCharMsg()
{
	int length = mHeardMessage.length();
	string charMsg = mHeardMessage.substr(2,length - 1);
	//HearLog << charMsg;
	return charMsg;
}
void Hear::ParsePosWithFlag(float formX,float formY)
{
	//cout << "formX : " << formX << " formY : " << formY << endl;
	ballPos.clear();
	OurPos.clear();
	OppPos.clear();
	bool isBall = false;
	bool isOpp = false;
	bool isOur = false;

	Encryption *ep = new Encryption;
	int msgLength = mHeardMessage.size();
	string tempMsg = mHeardMessage.substr(2,msgLength-1);
	//cout << "tempMsg:" << tempMsg << endl;
	vector<string> pos(tempMsg.size());
	int j = 0;
	for (size_t i = 0; i < tempMsg.size(); ++i)
	{			
		if (!(i%3) && i != 0)
		{
			j++;
		}
		pos[j]+= tempMsg[i];
	}
	//HearLog << "j = " << j << endl;
	vector<int> posBeforeConvert;
	for (size_t i = 0; i <= j; ++i)
	{
		posBeforeConvert.clear();
		//cout << "pos[" <<i<<"]:"<<pos[i]<< endl;
		unsigned char tempChar[5];
		string a = pos[i];
		tempChar[0] = (char)ep->map_from_printablechar(a[0]);
		//cout << "tempChar[0] : " << bitset<8>(tempChar[0]) << END;
		tempChar[1] = (char)ep->map_from_printablechar(a[1]);
		//cout << "tempChar[1] : " << bitset<8>(tempChar[1]) << END;
		tempChar[2] = (char)ep->map_from_printablechar(a[2]);
		//cout << "tempChar[2] : " << bitset<8>(tempChar[2]) << END;

		

		unsigned char pos1x = tempChar[0]<< 2;
		//cout << "tempChar[0]<< 2 : " << bitset<8>(pos1x) << END;
		unsigned char pos1y = tempChar[1]>> 4;
		//cout << "tempChar[1]>> 4 : " << bitset<8>(pos1y) << END;
		pos1x |= pos1y;
		//cout << "pos1x | pos1y : " << bitset<8>(pos1x) << END;
		posBeforeConvert.push_back(pos1x);


		pos1y = tempChar[1] << 4;
		//cout << "tempChar[1]<< 4 : " << bitset<8>(pos1y) << END;
		unsigned char pos1z = tempChar[2] >> 2;
		//cout << "pos1z = tempChar[2] >>  : " << bitset<8>(pos1z) << END;
		pos1y |= pos1z;
		//cout << "pos1y | pos1z : " << bitset<8>(pos1y) << END;
		posBeforeConvert.push_back(pos1y);

		pos1z = tempChar[2] >> 1;
		if (pos1z & 1)
		{
			isBall = true;
		}
		else
		{
			if (tempChar[2] & 1)
			{
				isOpp = true;
			}
			else 
			{
				isOur = true;
			}
		}		

		//HearLog << "posBeforeConvert : " << endl;
		for (size_t i = 0; i < posBeforeConvert.size(); ++i)
		{
			//HearLog << posBeforeConvert[i] << " ";
		}
		for (size_t i = 0; i < posBeforeConvert.size(); ++i)
		{
			int left = posBeforeConvert[i];
			left = left >> 3;
			int right = (left << 3)^posBeforeConvert[i];
			float num = left + right * 0.125;
			if (i%2 == 0)
			{
				num -= formX / 2;
			}
			else
			{
				num -= formY / 2;
			}
			if (isBall)
			{
				ballPos.push_back(num);
			}
			if (isOpp)
			{
				OppPos.push_back(num);
			}
			if (isOur)
			{
				OurPos.push_back(num);
			}
		}	
		isBall = false;
		isOpp = false;
		isOur = false;
	}
}
void Hear::ParsePosMsg(float formX,float formY)
{
	//cout << "formX : " << formX << " formY : " << formY << endl;
	posParsed.clear();
	vector<int> posBeforeConvert;
	Encryption *ep = new Encryption;
	int msgLength = mHeardMessage.size();
	//int checkValid = ep->map_from_printablechar(mHeardMessage[msgLength - 1]);
	//string tempMsg = mHeardMessage.substr(2,msgLength-2);
	string tempMsg = mHeardMessage.substr(2,msgLength-1);
	//cout << "tempMsg:" << tempMsg << endl;
	vector<string> pos(tempMsg.size());

	int j = 0;
	for (size_t i = 0; i < tempMsg.size(); ++i)
	{			
		if (!(i%3) && i != 0)
		{
			j++;
		}
		pos[j]+= tempMsg[i];
	}
	//HearLog << "test!"<< endl;
	//HearLog << "j = " << j << endl;
	for (size_t i = 0; i <= j; ++i)
	{
		//cout << "pos[" <<i<<"]:"<<pos[i]<< endl;
		unsigned char tempChar[5];
		string a = pos[i];
		tempChar[0] = (char)ep->map_from_printablechar(a[0]);
		//cout << "tempChar[0] : " << bitset<8>(tempChar[0]) << END;
		tempChar[1] = (char)ep->map_from_printablechar(a[1]);
		//cout << "tempChar[1] : " << bitset<8>(tempChar[1]) << END;
		tempChar[2] = (char)ep->map_from_printablechar(a[2]);
		//cout << "tempChar[2] : " << bitset<8>(tempChar[2]) << END;
		unsigned char pos1x = tempChar[0]<< 2;
		//cout << "tempChar[0]<< 2 : " << bitset<8>(pos1x) << END;
		unsigned char pos1y = tempChar[1]>> 4;
		//cout << "tempChar[1]>> 4 : " << bitset<8>(pos1y) << END;
		pos1x |= pos1y;
		//cout << "pos1x | pos1y : " << bitset<8>(pos1x) << END;
		posBeforeConvert.push_back(pos1x);
		pos1y = tempChar[1] << 4;
		//cout << "tempChar[1]<< 4 : " << bitset<8>(pos1y) << END;
		pos1y |= tempChar[2];
		//cout << "pos1y | tempChar[2] : " << bitset<8>(pos1y) << END;
		posBeforeConvert.push_back(pos1y);
	}
	//cout << "posBeforeConvert : " << endl;
// 	for (size_t i = 0; i < posBeforeConvert.size(); ++i)
// 	{
// 		cout << posBeforeConvert[i] << " ";
// 	}
	//cout << endl;
	for (size_t i = 0; i < posBeforeConvert.size(); ++i)
	{
		int left = posBeforeConvert[i];
		left = left >> 3;
		int right = (left << 3)^posBeforeConvert[i];
		float num = left + right * 0.125;
		if (i%2 == 0)
		{
			num -= formX / 2;
		}
		else
		{
			num -= formY / 2;
		}
		posParsed.push_back(num);
	}
	//cout << "the parsed pos :" << endl;
	if( ep ) 
	{
		delete ep;
		ep = NULL;
	}
	PrintVector(posParsed);
}
void Hear::PrintVector(vector<float>& vf)
{
// 	for (size_t i = 0; i < vf.size();++i)
// 	{
// 		cout << vf[i] << " " ;
// 	}
// 	cout << endl;
}