#include "navigation.h"

#include "actuation.h"

extern "C"
{
	#include "../pathfinding/PathfindingMain.h"
}


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
	if (GetCurrentRobotPosX() == GetGoalPosX() && GetCurrentRobotPosY() == GetGoalPosY())
	{
		SetIsRobotGoalReached(1);
	}
}