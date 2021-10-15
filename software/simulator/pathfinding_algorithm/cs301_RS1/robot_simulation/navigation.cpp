#include "navigation.h"

#include "actuation.h"
#include "../pathfinding/PathfindingMain.h"

static int IsRobotGoalReached = 0;

int GetIsRobotGoalReached()
{
	return IsRobotGoalReached;
}

void SetIsRobotGoalReached(int val)
{
	IsRobotGoalReached = val;
}

void HandlePosition()
{
	if (GetCurrentRobotPosX() == GOAL_X && GetCurrentRobotPosY() == GOAL_Y)
	{
		SetIsRobotGoalReached(1);
	}
}