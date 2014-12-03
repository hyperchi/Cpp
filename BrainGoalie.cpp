#include "Brain.h"
#define B_GoalieLog gLog<< "[goalie] " 


static float PlayerHeight = 0.58f;

void Brain::ThinkGoalie()
{
	B_GoalieLog << "ThinkGoalie" << endl;	

	GoalieState goalieState = mSituation->GetGoalieState();
	switch (goalieState)
	{
	case GoaS_DefendPos:
		ThinkDefendPos();
		break;
	case GoaS_ClearBall:
		ThinkClearBall();
		break;
	case GoaS_DefendBall:
		ThinkDefendBall();
		break;
	case GoaS_DefendSuper:
		ThinkDefendSuper();
		break;
	case GoaS_GoalKick:
		ThinkGoalKick();
		break;
	case GoaS_Other:
		ThinkGoalieOther();
		break;
	}
}
void Brain::ThinkKickOffBall()
{
	B_GoalieLog << "Kick off Ball" << endl;
	mMotion->DoMotion(MT_GoalieKickOffBall);
}
void Brain::ThinkClearBall()
{
	B_GoalieLog << "clear Ball" << endl;
	mMotion->DoMotion(MT_GoalieClearBall);
}
void Brain::ThinkDefendPos()
{
	B_GoalieLog << "Defend pos" << endl;
	mMotion->DoMotion(MT_GoalieDefendPos);	
}
void Brain::ThinkDefendBall()
{
	B_GoalieLog << "Defend ball" << endl;
	mMotion->DoMotion(MT_GoalieDefendBall);
}
void Brain::ThinkDefendSuper()
{
	B_GoalieLog << "Defend super" << endl;
	mMotion->DoMotion(MT_GoalieDefendSuper);
}
void Brain::ThinkGoalieOther()
{
	B_GoalieLog << "Defend Stand still" << endl;
	mMotion->DoMotion(MT_Stand/*MT_GoalieOther*/);
}
void Brain::ThinkGoalKick()
{
	B_GoalieLog << "Goal kick: Shoot" << endl;

	mMotion->DoMotion(MT_Shoot);
}
