#ifndef __ENUMTYPE_H__
#define __ENUMTYPE_H__

#include <map>
#include <string>

namespace EnumTypes 
{
	enum SideT
	{
		SD_LEFT,     
		SD_RIGHT,    
		SD_UNKNOWN  
	};

	enum PlayModeT
	{
		PM_BEFORE_KICK_OFF,        //before kick off         
		PM_KICK_OFF_LEFT,          //kick off for left team  
		PM_KICK_OFF_RIGHT,         //kick off for right team 
		PM_PLAY_ON,                //play on (during match)  
		PM_KICK_IN_LEFT,           //kick in for left team   
		PM_KICK_IN_RIGHT,          //kick in for right team  
		PM_CORNER_KICK_LEFT,       //corner kick left team   
		PM_CORNER_KICK_RIGHT,      //corner kick right team  
		PM_GOAL_KICK_LEFT,         //goal kick for left team 
		PM_GOAL_KICK_RIGHT,        //goal kick for right team
		PM_OFFSIDE_LEFT,           //offside for left team   
		PM_OFFSIDE_RIGHT,          //offside for right team  
		PM_GOAL_LEFT,              //goal scored by team left
		PM_GOAL_RIGHT,             //goal scored by team right
		PM_FREE_KICK_LEFT,         //free kick for left team 
		PM_FREE_KICK_RIGHT,        //free kick for right team
		PM_GAME_OVER,              //game over                              
		PM_UNKNOWN                 //unknown play mode    
	};

	enum FlagT
	{
		FLAG_OUR_LEFT,    
		FLAG_OUR_RIGHT, 
		FLAG_OPP_LEFT, 
		FLAG_OPP_RIGHT,  
		FLAG_COUNT
	};

	enum GoalT
	{
		GOAL_OUR_LEFT,
		GOAL_OUR_RIGHT, 
		GOAL_OPP_LEFT,
		GOAL_OPP_RIGHT,  
		GOAL_COUNT
	};

	enum FlagAndGoalT
	{
		FAG_FLAG_OUR_LEFT,    
		FAG_FLAG_OUR_RIGHT, 
		FAG_FLAG_OPP_LEFT, 
		FAG_FLAG_OPP_RIGHT, 
		FAG_GOAL_OUR_LEFT,
		FAG_GOAL_OUR_RIGHT, 
		FAG_GOAL_OPP_LEFT,
		FAG_GOAL_OPP_RIGHT, 
		FAG_COUNT,
	};

	enum HJointT				 //一自由度各个关节
	{
/*		Head_1,
		Head_2,
		LARM_1,
		RARM_1,
		LARM_2,
		RARM_2,
		LARM_3,
		RARM_3,
		LARM_4,
		RARM_4,
		LLEG_1,
		RLEG_1,
		LLEG_2,
		RLEG_2,
		LLEG_3,
		RLEG_3,
		LLEG_4,
		RLEG_4,
		LLEG_5,
		RLEG_5,
		LLEG_6,
		RLEG_6, */ 
		Head_1,
		Head_2,
		LARM_1,
		LARM_2,
		LARM_3,
		LARM_4,
		LLEG_1,
		LLEG_2,
		LLEG_3,
		LLEG_4,
		LLEG_5,
		LLEG_6,
		RARM_1,	
		RARM_2,
		RARM_3,
		RARM_4,	
		RLEG_1,
		RLEG_2,	
		RLEG_3,		
		RLEG_4,		
		RLEG_5,		
		RLEG_6,
		HJCOUNT
	};

	enum CommandPriority
	{
		CP_Beam,
		CP_GetUp,
		CP_Normal,
	};
	
	enum PlayerRole
	{
		/*
		PR_Forward,
		PR_Center,
		PR_Guard,
		PR_Goalie,
		FR_Free,
		FR_Count,
		*/
//9V9
		PR_Forward_1,
		PR_Forward_2,
		PR_Center_1,
		PR_Center_2,
		PR_Center_3,
		PR_Center_4,
		PR_Guard_1,
		PR_Guard_2,
		PR_Guard_3,
		PR_Goalie,
		FR_Free,
		FR_Count,
	};

	enum AttackApproach
	{
		AA_Shoot,
		AA_Pass,
		AA_Dribble,
		AA_Intercept,
		AA_RunPosition,
		AA_Defense,
	};

	enum AttDefkTrend
	{
		ADT_FullDefence,
		ADT_TrendDefence,
		ADT_NormalDefence,
		ADT_NormalAttack,
		ADT_TrendAttack,
		ADT_FullAttack,
	};

	enum OppStrength
	{
		OS_Strong,
		OS_Normal,
		OS_Weak,
	};

	enum BasicStrategy
	{
		BSA_Dribble,
		BSA_Pass,
		BSA_Shoot,
		BSA_RunPosition,
		BSD_Intercept,
		BSD_ClearBall,
		BSD_Block,
		BSD_CornerBall,

	};

	enum GoalieState
	{
		GoaS_ClearBall,
		GoaS_DefendPos,
		GoaS_DefendSuper,
		GoaS_DefendBall,
		GoaS_GoalKick,
		GoaS_Other,
	};

	//enum UJointT				 //universal joint type
	//{
	//	LLEG_2_3,                // Left hip joint - moving front & back, open & close 
	//	RLEG_2_3,                // Right hip joint - moving front & back, open & close 
	//	LLEG_5_6,                // Left ankle joint 
	//	RLEG_5_6,                // Right ankle joint 
	//	LARM_1_2,                // Left shoulder joint - moving front & back, open & close
	//	RARM_1_2,                // Right shoulder joint - moving front & back, open & close 
	//	UJCOUNT
	//} ;

	//enum JointFreedomT				 //hinge joint type
	//{
	//	J_Head1,
	//	J_Head2,
	//	J_LeftArm1,
	//	J_LeftArm2,
	//	J_LeftArm3,
	//	J_LeftArm4,
	//	J_LeftLeg1,
	//	J_LeftLeg2,
	//	J_LeftLeg3,
	//	J_LeftLeg4,
	//	J_LeftLeg5,
	//	J_LeftLeg6,
	//	J_RightArm1,
	//	J_RightArm2,
	//	J_RightArm3,
	//	J_RightArm4,
	//	J_RightLeg1,
	//	J_RightLeg2,
	//	J_RightLeg3,
	//	J_RightLeg4,
	//	J_RightLeg5,
	//	J_RightLeg6,
	//	J_HJCOUNT
	//} ;
	enum ObjectType
	{
		Say_OurTeam,
		Say_OppTeam,
		Say_Ball
	};

	enum SayType
	{
		Say_Pos,
		Say_Char
	};

	enum ControlType
	{
		Our1,			//一个我方球员
		Our2,			//两个我方球员
		OurAll,			//三个我方球员
		Opp1,			//一个对方球员
		Opp2,			//两个对方球员
		OppAll,			//三个对方球员
		Our1Opp1,		//一个我方+一个对方
		Our1Opp2,		//一个我方+两个对方
		Our2Opp1,		//两个我方+一个对方
		Our1Ball,		//一个我方+一个球
		Our2Ball,		//两个我方+一个球
		OurPBallPOpp,	//一个我方+一个球+一个对方
		Opp1Ball,		//一个对方+一个球
		Opp2Ball,		//两个对方+一个球
	};

	typedef std::map<std::string, PlayModeT> PlayModeMap;
	typedef std::map<std::string, HJointT> HJMap;
};

using namespace EnumTypes;

#endif __ENUMTYPE_H__