#include "sensor.h"
#include "control.h"
#include "actuation.h"

#include <cstdio>

static MotionState PrevRobotMotionState = NO_STATE;
static MotionState RobotMotionState = FOLLOWING;
//static Command NextNavCommand = NO_COMMAND;

MotionState GetRobotMotionState() 
{
	return RobotMotionState;
}

MotionState GetPrevRobotMotionState()
{
	return PrevRobotMotionState;
}

void SetRobotMotionState(const MotionState s) 
{
	RobotMotionState = s;
}

void SetPrevRobotMotionState(const MotionState s)
{
	PrevRobotMotionState = s;
}


//{------------------------------------
// Rudenmentry self aligning system
// Alignment sensor located at back for least duration oscillation. 
// Prob Need to be fix condition to while the robot is under the travel straight command.
// Requires dynamic readjustment magnitude (PID??)
	// Needs to be fast when center returns to path.
// Critical note: **We cannot turn on a dime**.
//updat linear and rotational speed based on sensor information

void HandleAlignment() {

	if ((GetRobotMotionState() == FOLLOWING) || (GetRobotMotionState() == LEAVING))
	{
		if (!GetRASensor() != !GetLASensor())
		{
			if (!GetLASensor())
				AlignRight();
			else if (!GetRASensor())
				AlignLeft();
		}
		else {
			AlignZero();
		}
	}
	//}---------------------------------------
}

void PrintRobotState(MotionState m)
{
    switch (m)
    {
    case FOLLOWING:
        printf("FOLLOWING\n");
        break;
    case LEFT_TURNING:
        printf("LEFT_TURNING\n");
        break;
    case RIGHT_TURNING:
        printf("RIGHT_TURNING\n");
        break;
	case LEAVING:
		printf("LEAVING\n");
		break;
    default:
        printf("NULL\n");
        break;
    }
}