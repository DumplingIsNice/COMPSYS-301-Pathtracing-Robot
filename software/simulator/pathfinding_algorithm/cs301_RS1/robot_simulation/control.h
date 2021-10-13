#ifndef CONTROL_H
#define CONTROL_H

enum MotionState
{
	FOLLOWING, LEFT_TURNING, RIGHT_TURNING, U_TURN, LEAVING, NO_STATE
};

MotionState GetRobotMotionState();
MotionState GetPrevRobotMotionState();

void SetRobotMotionState(const MotionState s);
void SetPrevRobotMotionState(const MotionState s);

// Runs alignmnet adjustments to AngularSpeed_seed
void HandleAlignment();

// Debug info of Robot State
void PrintRobotState(MotionState m);

void moveStraight(int speed);
void turnLeft();
void turnRight();
void turnBack();
void stopMovement();

void AlignLeft();
void AlignRight();
void AlignZero();

/*Input direction : takes an integer for the directions
					0 - straight
					1- left
					2- right
					3- back
					4 - stop
This can be changed to the macros used in the other files for better integration
Input speed is an optional parameter used for setting the speed when moving straight
If no value is supplied it will assume default of 130 mm/s

The turning functions that are called set the linear and angular speed of the car,
it doesnt take into account the iterations the turns should be called for, this should be handled,
by the called. When testing this the turns took two iterations to complete

[we're trying to implement this in here as well]
*/
void movementDirection(int direction, int speed = 130);

#endif // CONTROL_H