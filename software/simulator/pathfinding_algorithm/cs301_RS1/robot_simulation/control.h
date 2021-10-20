#ifndef CONTROL_H
#define CONTROL_H

#define DEFAULT_LINEAR_SPEED	120
#define CONFIRMING_SPEED		DEFAULT_LINEAR_SPEED/5
#define EXPECTING_SPEED			80
#define LEAVING_COUNT			DEFAULT_LINEAR_SPEED/40

#define TURNING_SPEED			120 //rad/s
#define LEFT_TURNING_SPEED		TURNING_SPEED
#define RIGHT_TURNING_SPEED		-TURNING_SPEED

#define ALIGN_SPEED				35
#define LEFT_ALIGN_SPEED		ALIGN_SPEED //mm/s
#define RIGHT_ALIGN_SPEED		-ALIGN_SPEED //mm/s

#define SENSED_CROSS_ROAD	(GetDirectionsSensed()->left && GetDirectionsSensed()->right) && GetDirectionsSensed()->forward
#define SENSED_T			(GetDirectionsSensed()->left && GetDirectionsSensed()->right) && !GetDirectionsSensed()->forward
#define SENSED_L_BRANCH_T	(GetDirectionsSensed()->left && GetDirectionsSensed()->forward) && !GetDirectionsSensed()->right
#define SENSED_R_BRANCH_T	(GetDirectionsSensed()->right && GetDirectionsSensed()->forward) && !GetDirectionsSensed()->left
#define SENSED_DEAD_END		(!GetDirectionsSensed()->left && !GetDirectionsSensed()->right) && !GetDirectionsSensed()->forward

// Intersection U turn indication flag
//{----------------------------------
typedef enum UturnDir
{
	U_RIGHT, U_LEFT, U_NO
} UturnDir;

static UturnDir tPathUturn = U_NO;
//}----------------------------------

typedef enum MotionState
{
	FOLLOWING, LEFT_TURNING, RIGHT_TURNING, U_TURN, LEAVING, NO_STATE
} MotionState;

MotionState GetRobotMotionState();
MotionState GetNextRobotMotionState();

// Convert directions from DirectionList to MotionState for use in navigation and control logic.
MotionState ConvertDirectionToMotionState(enum Direction direction);

void SetRobotMotionState(const MotionState s);
void SetNextRobotMotionState(const MotionState s);

// Handles commands from navigation
void HandleCommands(MotionState command);

// Performs movement logic based on robot's state
void HandleMovement();

// Runs alignmnet adjustments to AngularSpeed_seed
void HandleAlignment();

// Debug info of Robot State
void PrintRobotState(MotionState m);

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
//void movementDirection(int direction, int speed = 130);
//
//void moveStraight(int speed);
//void turnLeft();
//void turnRight();
//void turnBack();
//void stopMovement();

#endif // CONTROL_H