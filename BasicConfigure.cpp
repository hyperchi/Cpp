#include "BasicConfigure.h"

BasicConfiguration::BasicConfiguration()
{
	mHostIp      = "192.168.0.66";
	mHostPort    = 3100;
	mMyTeamName  = "AmoiensisNQ";
	//mMyTeamName  = "Test";
	mMyPlayerNo	 = 1;
	mMyAgentConf = "agentConf.conf";
	mMyFormation = "formation.conf";
	mWorldModel  = "worldModel.conf";	
	mDelayTime   = 0.0015f;
}
BasicConfiguration::~BasicConfiguration()
{

}
bool BasicConfiguration::ConfigureArguments(int argc, char* argv[])
{
	char * str;
	for( int i = 1 ; i < argc ; i = i + 2  )
	{
		// help is only option that does not have to have an argument
		if( i + 1 >= argc && strncmp( argv[i], "-help", 3 ) != 0 )
		{
			//cout << "Need argument for option: " << argv[i] << endl;
			exit(0);
		}
		else if( strncmp( argv[i], "-help", 3 ) == 0 )
		{
			PrintOptions();
			exit(0);
		}
		// read a command option
		if( argv[i][0] == '-' && strlen( argv[i] ) > 1)
		{
			switch( argv[i][1] )
			{
			case 'h': // host server
				if((i + 1) > argc)
				{
					//cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					mHostIp = argv[i+1];
				}
				break;

			case 'p': // port
				if((i + 1) > argc)
				{
					cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					sscanf(argv[i+1], "%d", &mHostPort);
				}
				break;

			case 'n': // number
				if( (i + 1) > argc )
				{
					cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					sscanf(argv[i+1], "%d", &mMyPlayerNo);
				}
				break;

			case 't': // teamname
				if( (i + 1) > argc )
				{
					cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					mMyTeamName = &argv[i+1][0];
				}
				break;

			case 'f': // formation fomrations file
				if((i + 1) > argc)
				{
					cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					mMyFormation = argv[i+1];
				}			
				break;

			case 'a': // agent fomrations file
				if((i + 1) > argc)
				{
					cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					mMyAgentConf = argv[i+1];
				}					
				break;

			case 'w':
				if((i + 1) > argc)
				{
					cout << "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					mWorldModel = argv[i+1];
				}
				break;

			case 'd':
				if((i + 1) > argc)
				{
					cout<< "Need argument for option: " << argv[i] << endl;
					return false;
				}
				else
				{
					sscanf(argv[i+1], "%f", &mDelayTime);
				}
				break;

			default:
				cout<<" Unknown Argument " << argv[i] << endl;
			}
		}
	}

 /*	if( mMyPlayerNo == 3 )
 	{
 		mMyPlayerNo = 9;
 	}
 	else if( mMyPlayerNo == 4 )
 	{
 		mMyPlayerNo = 10;
 	}*/

	cout<< "BasicConfiguration " << mMyPlayerNo << endl;

	PrintInput();

	return true;
}


void BasicConfiguration::PrintOptions()
{
	cout<< endl;
	cout<< "  usage: AmoiensisNQ [-param_name param_value]              "  << endl;
	cout<< "                                                            " << endl;
	cout<< "  -h (host)            : Specify the server host to connect "  << endl;
	cout<< "  -p (port)            : Specify the server port to connect "  << endl;
	cout<< "  -n (number)          : Specify the agents number in game "   << endl;
	cout<< "  -t (team)            : Specify the team name of agent "      << endl;
	cout<< "  -d (delaytime)       : Specify the delay time configuration " << endl;
	cout<< "  -a (agentconf)       : Specify the agent configuration "     << endl;
	cout<< "  -f (formation)       : Specify the formation configuration " << endl;
	cout<< "  -w (worldmodel)      : Specify the worldmodel configuration" << endl << endl;
}

//For test
void BasicConfiguration::PrintInput()
{
	cout<< endl;
	cout<< "       Options Input              " << endl;
	cout<< "  -hostip       : " << mHostIp		<< endl;
	cout<< "  -port         : " << mHostPort	<< endl;
	cout<< "  -number       : " << mMyPlayerNo	<< endl;
	cout<< "  -teamname     : " << mMyTeamName	<< endl;
	cout<< "  -delaytime    : " << mDelayTime	<< endl;
	cout<< "  -agentconf    : " << mMyAgentConf	<< endl;
	cout<< "  -formation    : " << mMyFormation << endl;
	cout<< "  -worldmodel   : " << mWorldModel  << endl << endl;
}

