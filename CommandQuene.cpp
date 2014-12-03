#include "CommandQuene.h"
#include "Logger.h"
#define CQLOG gLog << "[CQ    ] "

CommandQuene::CommandQuene()
{
	mQuene.clear();
}
CommandQuene::~CommandQuene()
{

}

void CommandQuene::InsertCommand( const CommandPriority &comPri, const string &tarString )
{
	mQuene.insert( make_pair(comPri,tarString) );
}

void CommandQuene::InsertSay( const string &sayMessage )
{
	mSayMessge = sayMessage;
}

void CommandQuene::ClearSay()
{
	mSayMessge.clear();
}

void CommandQuene::ClearCommand()
{
	mQuene.clear();
}

bool CommandQuene::IfQueneEmpty()
{
	return mQuene.empty();
}

bool CommandQuene::IfSayEmpty()
{
	return mSayMessge.empty();
}

bool CommandQuene::HighestComman( multimap<CommandPriority,string>::iterator &cp )
{
	if( IfQueneEmpty() )
	{
		return false;
	}
	else
	{
		cp = mQuene.find( CP_Beam );

		if( cp == mQuene.end() )
		{
			cp = mQuene.find( CP_GetUp );

			if( cp == mQuene.end() )
			{
				cp = mQuene.begin();
			}		
		}
	}

	return true;
}

void CommandQuene::PopCommand( string &tarString )
{
	multimap<CommandPriority,string>::iterator cp;
	if( !HighestComman( cp ) )
	{
		tarString = "(he1 0.00)(he2 0.00)(lae1 0.00)(lae2 0.00)(lae3 0.00)(lae4 0.00)(lle1 0.00)(lle2 0.00)(lle3 0.00)(lle4 0.00)(lle5 0.00)(lle6 0.00)(rae1 0.00)(rae2 0.00)(rae3 0.00)(rae4 0.00)(rle1 0.00)(rle2 0.00)(rle3 0.00)(rle4 0.00)(rle5 0.00)(rle6 0.00)";
	}
	else
	{
		tarString = cp->second;	
		tarString += mSayMessge;
		mQuene.erase( cp );
	}
}