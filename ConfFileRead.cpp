#include "ConfFileRead.h"

ReadConf::ReadConf( string filePath )
{
	mRCPath = filePath;

	if( !OpenConfFile( mRCPath ) )
	{
		return;
	}	

	ReadConfFile();
}

bool ReadConf::OpenConfFile( string filePath )
{
	if( ( mCF = fopen( filePath.c_str(),"r" ) ) == NULL )
	{
		cout<< " [Error] Can't open Conf File ! " << endl;
		return false;
	}

	return true;
}

void ReadConf::ShowConfFile()
{
	mCFVector.ShowValue();
}

int ReadConf::GetSubMsg( string &msg )
{
	char buff[100];
	strcpy( buff, msg.c_str() );

	int head;		//第一个英文字母处或者‘-’处
	int tail;		//最后一个英文字母或数字处

	for( head = 0;head < msg.size(); head++ )
	{
		if( isalnum(buff[head]) || ( buff[head] == '-' ) )
		{
			break;
		}		
	}

	for( tail = head; tail < msg.size(); tail ++ )
	{
		if( buff[tail] == '\n' || buff[tail] == '\r' || buff[tail] == '\t' 
			|| buff[tail] == ' ' || ((!isalnum(buff[tail]) && buff[tail] != '.' && buff[tail] != '-' && buff[tail] != '_' )) )
		{
			break;
		}
	}
	
	msg.assign( msg.begin() + head, msg.begin() + tail );

	return tail;
}

bool ReadConf::GetOneLineConf( string msg )
{
	
	int					head = 0;
	string				subMsg;
	string				subName;
	//CFVector			subAttr;
	Predicate			subAttr;
	
	while( head < msg.size() )
	{
		subMsg = msg.assign( msg.begin() + head, msg.end() );

		if( head == 0 )
		{			
			head = GetSubMsg( subMsg );
			subName = subMsg;
		}
		else
		{
			head = GetSubMsg( subMsg );
			subAttr.attr.push_back( subMsg );	
		}
	}

	mCFVector.AddChild( subName,subAttr );	

	return true;
}

bool ReadConf::ReadConfFile()
{
	char buf[200];

	while(fgets(buf,200,mCF) != NULL)
	{
		if(buf[0] == '#' || buf[0] == '\n' || buf[0] == '\r' )
		{
			continue ;
		}

		if( !GetOneLineConf( buf ) )
		{
			cout<< "[Warning] " << "Unknown Conf Format ! " << endl;
		}
	}

	fclose( mCF );
}

void ReadConf::Tranversal( const string &name, Predicate &tarP )
{
	multimap<string, Predicate>:: iterator cp = mCFVector.child.begin();

	while( cp != mCFVector.child.end() )
	{
		if( (cp->first) == name )
		{
			tarP.name = name;
			tarP.AddChild( name, (cp->second) );
		}
	
		cp ++;
	}
}

/*************************** TESTING PURPOSES ********************************/

//int main( void )
//{
//	ReadConf rC( string( "agentConf.conf" ) );
//
//	rC.ShowConfFile();
//	
//	/*************************** TESTING PURPOSES ********************************/
//	//string	test1;
//	float	test2;
//	int		test3;
//	bool	test4;
//	float	test5[4];
//
//	Predicate test1;
//
//	rC.Tranversal( "test5",test1);
//	//rC.mCFVector.ShowValue();
//	test1.ShowValue();
//	//rC.mCFVector.GetValue( "test1",test1);
//	//rC.mCFVector.GetValue( "test2",test2);
//	//rC.mCFVector.GetValue( "test3",test3);
//	//rC.mCFVector.GetValue( "test4",test4);
//	//rC.mCFVector.GetValue( "test5",test5,4);
//
//	//cout<< "test1 "<< test1 << endl;
//	//cout<< "test2 "<< test2 << endl;
//	//cout<< "test3 "<< test3 << endl;
//	//cout<< "test4 "<< test4 << endl;
//	//cout<< "test5 ";
//	//for( int i = 0; i < 4; i++ )
//	//{
//	//	cout<< test5[i] <<" ";
//	//}
//	//cout<< endl;
//	
//}