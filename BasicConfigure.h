#ifndef __BASICCONFIGURE_H__
#define __BASICCONFIGURE_H__

#include <iostream>     // needed for cout
#include "stdinc.h"
using namespace std;

class BasicConfiguration
{
public:
	BasicConfiguration();
	~BasicConfiguration();

public:
	string		mHostIp;     
	int			mHostPort;
	string		mMyTeamName;       
	int			mMyPlayerNo; 
	string		mMyAgentConf; 
	string		mMyFormation;
	string		mWorldModel;
	float		mDelayTime;

	bool ConfigureArguments(int argc, char* argv[]);
	
private:
	void PrintOptions();
	void PrintInput();	//For test
};

#endif __BASICCONFIGURE_H__