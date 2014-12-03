#include "Formation.h"
#define FormationLog gLog << "[format] "


Formation::Formation( WorldModel *wm )
{
	mWorldModel = wm;

	Initial();
}
Formation::~Formation()
{

}

void Formation::Initial()
{
	ReadConf rC( mWorldModel->GetFormationConfPath() ); 
	Predicate tempP;

	rC.Tranversal( "Goalie_X", tempP );
	tempP.GetValue( "Goalie_X", mBasicPositionX[PR_Goalie] );

	rC.Tranversal( "Goalie_Y", tempP );
	tempP.GetValue( "Goalie_Y", mBasicPositionY[PR_Goalie] );

	rC.Tranversal( "Guard_1_X", tempP );
	tempP.GetValue( "Guard_1_X", mBasicPositionX[PR_Guard_1] );

	rC.Tranversal( "Guard_1_Y", tempP );
	tempP.GetValue( "Guard_1_Y", mBasicPositionY[PR_Guard_1] );

	rC.Tranversal( "Guard_2_X", tempP );
	tempP.GetValue( "Guard_2_X", mBasicPositionX[PR_Guard_2] );

	rC.Tranversal( "Guard_2_Y", tempP );
	tempP.GetValue( "Guard_2_Y", mBasicPositionY[PR_Guard_2] );


	rC.Tranversal( "Guard_3_X", tempP );
	tempP.GetValue( "Guard_3_X", mBasicPositionX[PR_Guard_3] );

	rC.Tranversal( "Guard_3_Y", tempP );
	tempP.GetValue( "Guard_3_Y", mBasicPositionY[PR_Guard_3] );

	rC.Tranversal( "Center_1_X", tempP );
	tempP.GetValue( "Center_1_X", mBasicPositionX[PR_Center_1] );

	rC.Tranversal( "Center_1_Y", tempP );
	tempP.GetValue( "Center_1_Y", mBasicPositionY[PR_Center_1] );
	
	rC.Tranversal( "Center_2_X", tempP );
	tempP.GetValue( "Center_2_X", mBasicPositionX[PR_Center_2] );

	rC.Tranversal( "Center_2_Y", tempP );
	tempP.GetValue( "Center_2_Y", mBasicPositionY[PR_Center_2] );

	rC.Tranversal( "Center_3_X", tempP );
	tempP.GetValue( "Center_3_X", mBasicPositionX[PR_Center_3] );

	rC.Tranversal( "Center_3_Y", tempP );
	tempP.GetValue( "Center_3_Y", mBasicPositionY[PR_Center_3] );

	rC.Tranversal( "Center_4_X", tempP );
	tempP.GetValue( "Center_4_X", mBasicPositionX[PR_Center_4] );

	rC.Tranversal( "Center_4_Y", tempP );
	tempP.GetValue( "Center_4_Y", mBasicPositionY[PR_Center_4] );
	
	rC.Tranversal( "Forward_1_X", tempP );
	tempP.GetValue( "Forward_1_X", mBasicPositionX[PR_Forward_1] );

	rC.Tranversal( "Forward_1_Y", tempP );
	tempP.GetValue( "Forward_1_Y", mBasicPositionY[PR_Forward_1] );
	
	rC.Tranversal( "Forward_2_X", tempP );
	tempP.GetValue( "Forward_2_X", mBasicPositionX[PR_Forward_2] );

	rC.Tranversal( "Forward_2_Y", tempP );
	tempP.GetValue( "Forward_2_Y", mBasicPositionY[PR_Forward_2] );

	rC.Tranversal( "Free_X", tempP );
	tempP.GetValue( "Free_X", mBasicPositionX[FR_Free] );

	rC.Tranversal( "Free_Y", tempP );
	tempP.GetValue( "Free_Y", mBasicPositionY[FR_Free] );

	mMyRole = GetMyRole( );

	FormationLog << "My Role: " << mMyRole << endl;
}


PlayerRole Formation::GetRole( unsigned int num )
{
	PlayerRole myRole;

	switch( num )
	{
	/*case 1:
		myRole = PR_Goalie;		// 规定 1 号球员为 守门员
		break;
		
	case 2:
		myRole = PR_Guard;		// 规定 2 号球员为 后卫
		break;

	case 3:
		myRole = PR_Center;		// 规定 3 号球员为 中场
		break;

	case 4:
		myRole = PR_Forward;	// 规定 4 号球员为 前锋
		break;

	default:
		myRole = FR_Free;		// 规定其他球员为“自由人”*/
	
    
//9V9
	case 1:	
		myRole = PR_Goalie;			// 规定 1 号球员为 守门员
		break;
	case 2:
		myRole = PR_Guard_1;		// 规定 2 号球员为 后卫
		break;
	case 3:
		myRole = PR_Guard_2;		// 规定 3 号球员为 后卫
		break;
	case 4:
	//	myRole = PR_Center_1;		// 规定 4 号球员为 中场
		myRole = PR_Guard_3;		// 规定 4 号球员为 后卫
		break;
	case 5:
		myRole = PR_Center_2;		// 规定 5 号球员为 中场
		break;
	case 6:
		myRole = PR_Center_3;		// 规定 6 号球员为 中场
		break;
	case 7:
		myRole = /*PR_Forward_2*/PR_Center_4;		// 规定 7 号球员为 中场
		break;
	case 8:
		myRole = PR_Forward_1;		// 规定 8 号球员为 前锋
		break;
	case 9:
		myRole = /*PR_Center_4*/PR_Forward_2;		// 规定 9 号球员为 前锋
		break;
	default:
		myRole = FR_Free;			// 规定其他球员为“自由人”*/
	}
	return myRole;
}

PlayerRole Formation::GetMyRole()
{
	return GetRole( mWorldModel->mMyPlayerNo );
}

float Formation::GetMyBasicPosX()
{
	return mBasicPositionX[mMyRole];
}

float Formation::GetMyBasicPosY()
{
	return mBasicPositionY[mMyRole];
}