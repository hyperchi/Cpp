#include "CommandHandle.h"

CommandHandle::CommandHandle( TRoboCupConnection * connetion, CommandQuene * cmdQuene )
{
	//mCommand.empty();
	mConnetion = connetion;
	mCmdQuene = cmdQuene;
}
CommandHandle::~CommandHandle()
{

}

bool CommandHandle::SendPlayerInformation( int playerNo, string teamName )
{
	char cmd[128];

	sprintf( cmd, "(init (unum %d)(teamname %s))", playerNo, teamName.c_str() );

	SendCommand( cmd );
}

bool CommandHandle::SendPlayerInitializePosition( float initX, float initY, float initZ, float initAng )
{
	char cmd[128];

	sprintf( cmd, "(move %0.2f %0.2f %0.2f %0.2f)", initX, initY, initZ, initAng );

	SendCommand( cmd );
}

bool CommandHandle::SendPlayerBeamPosition( float beamX, float beamY, float beamAng )
{
	char cmd[128];

	sprintf( cmd, "(beam %0.2f %0.2f %0.2f)", beamX, beamY, beamAng );

	SendCommand( cmd );
}

bool CommandHandle::SendCommand( const char * str ) const
{
	string fin = string(str) + "(syn)";
	return mConnetion->sendCommand( fin.c_str() );
}
bool CommandHandle::SendCommand()
{
	string cmd;

	mCmdQuene->PopCommand( cmd );
	mCmdQuene->ClearCommand();
	///////////////////////////////////////
	// For Debug //
	///////////////////////////////////////

	//static int msgNum = 0;
	//msgNum ++;
	//char numString[15];
	//sprintf( numString, "( %d )", msgNum );

	//string sendMsg = string(numString) + cmd;

	//SendCommand( sendMsg.data() );
	///////////////////////////////////////



	SendCommand( cmd.c_str() );
}