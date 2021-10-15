#include "sensor.h"
#include "control.h"
#include "actuation.h"

#include <cstdio>

extern "C"
{
	#include "../pathfinding/Navigation/DirectionsList.h"
}

static MotionState NextMotionState = NO_STATE;
static MotionState RobotMotionState = FOLLOWING;

extern float virtualCarLinearSpeed_seed;
extern float virtualCarAngularSpeed_seed;

MotionState GetRobotMotionState() 
{
	return RobotMotionState;
}

MotionState GetNextRobotMotionState()
{
	return NextMotionState;
}

MotionState ConvertDirectionToMotionState(Direction direction)
{
	MotionState motionstate;
	switch (direction)
	{
	case LEFT:			motionstate = LEFT_TURNING;		break;
	case RIGHT:			motionstate = RIGHT_TURNING;	break;
	case FORWARD:		motionstate = FOLLOWING;		break;
	case DEADEND:		motionstate = U_TURN;			break;
	default:			motionstate = NO_STATE;
	}
	return motionstate;
}

void SetRobotMotionState(const MotionState s) 
{
	RobotMotionState = s;
}

void SetNextRobotMotionState(const MotionState s)
{
	NextMotionState = s;
}

// Private Helper: Turning Logic
void HandleTurning()
{
	static int toExit = 0;

	// Leaving original orientiation indication
	if (!GetDirectionsSensed()->forward)
	{
		toExit = 1;
	}

	// Ready to exit intersection
	if (toExit)
	{
		// If U turning at intersection, follow through 
		// (aka make u turn with exit after 2x foward indication)
		if (tPathUturn != U_NO)
		{
			if (GetDirectionsSensed()->forward)
			{
				toExit = 0;
				tPathUturn = U_NO;
			}
		}
		// Finally, enter leaving state when all flag is forfulled.
		else if (GetDirectionsSensed()->forward) {
			SetRobotMotionState(LEAVING);
			toExit = 0;
		}
	}
}

void HandleCommands(MotionState command)
{
	printf("Next Robot Motion State is: ");
	PrintRobotState(GetNextRobotMotionState());
	if (command != NO_STATE)
	{
		SetRobotMotionState(command);

		// Handles intersection U turns 
		if (command == U_TURN)
		{
			if (SENSED_L_BRANCH_T)
			{
				tPathUturn = U_LEFT;
				SetRobotMotionState(LEFT_TURNING);
			}
			else if (SENSED_R_BRANCH_T)
			{
				tPathUturn = U_RIGHT;
				SetRobotMotionState(RIGHT_TURNING);
			}
			// T and cross road uses the same default logic
			else {
				tPathUturn = U_RIGHT;
			}
		}


		SetNextRobotMotionState(NO_STATE);
	}
}

void HandleMovement()
{
	printf("Current Robot Motion State is: ");
	PrintRobotState(GetRobotMotionState());

	Directions* validDirections = GetDirectionsSensed();

	static int leaveCounter = 0;
	InitSpeedSeed();

	switch (GetRobotMotionState())
	{
	case FOLLOWING:
		if (SENSED_DEAD_END)
		{
			AngularRight();
			SetRobotMotionState(U_TURN);
		}
		else if (validDirections->forward)
		{
			HandleAlignment();
			LinearForward();
		}
		else if (validDirections->left)
		{
			AngularLeft();
			SetRobotMotionState(LEFT_TURNING);
		}
		else if (validDirections->right)
		{
			AngularRight();
			SetRobotMotionState(RIGHT_TURNING);
		}
		break;
	case LEFT_TURNING:
		AngularLeft();
		HandleTurning();
		break;
	case RIGHT_TURNING:
		AngularRight();
		HandleTurning();
		break;
	case LEAVING:
		HandleAlignment();
		LinearForward();
		leaveCounter++;
		if (leaveCounter > LEAVING_COUNT)
		{
			SetRobotMotionState(FOLLOWING);
			leaveCounter = 0;
		}
		break;
	case U_TURN:
		SetRobotMotionState(RIGHT_TURNING);
		break;
	default:
		;
	}

	setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed);
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
	case U_TURN:
		printf("U_TURN\n");
		break;
	case NO_STATE:
		printf("NO_STATE\n");
		break;
    default:
        printf("NULL\n");
        break;
    }
}