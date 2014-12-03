#ifndef __COMMANDQUENE_H__
#define __COMMANDQUENE_H__

#include <map>
#include "EnumType.h"

using namespace std;

class CommandQuene
{
public:
	CommandQuene();
	~CommandQuene();
private:
	multimap <CommandPriority,string> mQuene;
	string mSayMessge;

public:
	void InsertCommand( const CommandPriority &comPri, const string &tarString );
	void InsertSay( const string &tarMessage );

	void ClearCommand();
	void ClearSay();

	bool IfQueneEmpty();
	bool IfSayEmpty();

	bool HighestComman( multimap<CommandPriority,string>::iterator &cp );
	void PopCommand( string &tarString );
};

#endif //__COMMANDQUENE_H__