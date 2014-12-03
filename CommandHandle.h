//******************************************************************
//						CommandHandle  类  ( Server 0.6 ）
//											By:	Leo		2008-9-10
//																
//						处理消息队列的类
//	
//	决策出的动作放在消息队列中,每一个周期由该类弹出一帧发送给服务器
//
//******************************************************************
#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#include <iostream>     // needed for cout
#include <stdio.h>

#include "EnumType.h"
#include "Connection.h"
#include "CommandQuene.h"

using namespace std;

class CommandHandle
{
public:
	CommandHandle( TRoboCupConnection * connetion, CommandQuene * cmdQuene );
	~CommandHandle();

public:	
	//string mCommand;
	
	bool SendPlayerInformation( int playerNo, string teamName );
	bool SendPlayerInitializePosition( float initX, float initY, float initZ, float initAng );
	bool SendPlayerBeamPosition( float beamX, float beamY, float beamAng );

	bool SendCommand( const char * str ) const;
	bool SendCommand();

private:
	TRoboCupConnection * mConnetion;
	CommandQuene * mCmdQuene;
};


#endif __COMMANDHANDLER_H__