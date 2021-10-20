//======================================================================
//Author: 
//Mr. Fung Yang
//Senior Technician Engineer Research and Design,
//Robotics and Control system signal processing Labs,
//Department of Electrical, Computer and Software Engineering,
//The University of Auckland.
//
//Written for teaching design course Compsys301 in ECSE department of UOA.
//
//This example program uses the pacman robot simulation library written by Mr. Fung Yang.
//
//Date 2012~2020
//=======================================================================

#define TESTMODE3
//#define TEST_MODE_MAP
#define TESTSENSOR

/* Starting Position Init */
//#define TESTMOVELEFT
//#define TESTMOVERIGHT
//#define TESTALIGN
#define TESTL1

#define TEST_SHORTEST_PATH

 // Simulation parameters
 //{------------------------------------
 #define NITERATIONS 1000
 #define STARTUPDELAY 2 //sec

// More in 'Project.h'
//}------------------------------------

/* Do not touch Includes */
//{------------------------------
#include "mainFungGLAppEngin.h" //a must
#include "mazeGen.h" //just include to use radnom number generation function
#include <vector>
#include <iostream>
#include "highPerformanceTimer.h"//just to include if timer function is required by user.
//}------------------------------------
/* Custom Includes */

extern "C"
{
	#include "pathfinding/PathfindingMain.h"
	//#include "robot_simulation/project.h"
	#include "pathfinding/Navigation/DirectionsList.h"
}

#include "robot_simulation/control.h"
#include "robot_simulation/sensor.h"
#include "robot_simulation/navigation.h"

using namespace std;

//{------------------------------
//these global variables must be defined here with no modification.
float virtualCarLinearSpeed;
float virtualCarAngularSpeed;
float currentCarAngle;
float currentCarPosCoord_X, currentCarPosCoord_Y;

int sensorPopulationAlgorithmID;
float sensorSeparation;
float num_sensors;
extern int maxDarkDefValueTH;

vector<int> virtualCarSensorStates;

vector<ghostInfoPack> ghostInfoPackList;
//}-------------------------------

highPerformanceTimer myTimer;

//just a helper function
void setVirtualCarSpeed(float linearSpeed, float angularSpeed)
{
	virtualCarLinearSpeed = linearSpeed;
	virtualCarAngularSpeed = angularSpeed;
}

//The Only TWO functions Students need to modify to add their own sensor guided
//path following control and Map path search calculations.
//{=================================================
float virtualCarLinearSpeed_seed;		// maximum speed of your robot in mm/s
float virtualCarAngularSpeed_seed;		// maximum angular speed of your robot in degrees/s


//added2021_2_22
float virtualCarLinearSpeedFloor;
float currentCarPosFloor_X, currentCarPosFloor_Y;

static int map2[MAP_SIZE_Y][MAP_SIZE_X]; // copy of static variable that is in readmap file

/* Actuation Functions */
//{------------------------------------
int linearSpeed = DEFAULT_LINEAR_SPEED;
void LinearForward() { virtualCarLinearSpeed_seed = linearSpeed * floorToCoordScaleFactor; }
void LinearZero() { virtualCarLinearSpeed_seed = 0; }
void AngularLeft() { virtualCarAngularSpeed_seed = LEFT_TURNING_SPEED; }
void AngularRight() { virtualCarAngularSpeed_seed = RIGHT_TURNING_SPEED; }
void AngularZero() { virtualCarAngularSpeed_seed = 0; }
void AlignLeft() { virtualCarAngularSpeed_seed = LEFT_ALIGN_SPEED; }
void AlignRight() { virtualCarAngularSpeed_seed = RIGHT_ALIGN_SPEED; }
void AlignZero() { virtualCarAngularSpeed_seed = 0; }

void InitSpeedSeed()
{
	LinearZero();
	AngularZero();
}

int GetCurrentRobotPosX()
{
	return coordToCellX(currentCarPosCoord_X);
}
int GetCurrentRobotPosY()
{
	return coordToCellY(currentCarPosCoord_Y);
}

/* k - starting row index
		m - ending row index
		l - starting column index
		n - ending column index
		i - iterator

 Code retrieved from: https://www.geeksforgeeks.org/print-kth-element-spiral-form-matrix/

Author(s):  andrew1234
shivanisinghss2110
divyeshrabadiya07
divyesh072019
mukesh07
sravankumar8128

*/
void spiralArray(int m, int n, int a[MAP_SIZE_Y][MAP_SIZE_X], int c, int*x, int*y)
{
	int i, k = 0, l = 0;
	int count = 0;

	

	while (k < m && l < n) {
		/* check the first row from
			the remaining rows */
		for (i = l; i < n; ++i) {
			count++;

			if (count == c) {
				(*x) = k;
				(*y) = i;
				printf("%d , %d \n", k, i);
			}
				//cout << a[k][i] << " ";
			
		}
		k++;

		/* check the last column
		from the remaining columns */
		for (i = k; i < m; ++i) {
			count++;

			if (count == c) {
				(*x) = i;
				(*y) = n-1;
				printf("%d , %d \n", i, n-1);
			}
				
		}
		n--;

		/* check the last row from
				the remaining rows */
		if (k < m) {
			for (i = n - 1; i >= l; --i) {
				count++;

				if (count == c) {
					(*x) = m-1;
					(*y) = i;
					printf("%d , %d \n", m-1, i);
				}
					
			}
			m--;
		}

		/* check the first column from
				the remaining columns */
		if (l < n) {
			for (i = m - 1; i >= k; --i) {
				count++;

				if (count == c) {
					(*x) = i;
					(*y) = l;
					printf("%d , %d \n", i, l);

				}
					
					
			}
			l++;
		}
	}
}

// Call in virtual car init
void map2Init() {

	ReadMapFile("map.txt");

	for (int row = 0; row < MAP_SIZE_Y; row++) {
		for (int col = 0; col < MAP_SIZE_X; col++) {
			map2[row][col] = GetMapValue(row, col);
		}
	}

}

/* Driver program to test above functions */
void handleNextGoal(int*posx, int*posy)
{	
	int k = 0; // the node in the matrix that we want to check

	int x;
	int y;

	//loop through the matrix
	while (k < (MAP_SIZE_Y * MAP_SIZE_X - 1)) {
		spiralArray(MAP_SIZE_Y, MAP_SIZE_X, map2, k, &x, &y);
		k++;
		if (map2[x][y] == 0) {
			(*posx) = x;
			(*posy) =y;

			map2[x][y] = 1;
			return;
		}

	}

	return;
}

//}------------------------------------
int virtualCarInit()
{
	cout << "default virtualCarLinearSpeed_seed:" << virtualCarLinearSpeed_seed << endl;
	cout << "default virtualCarAngularSpeed_seed:" << virtualCarAngularSpeed_seed << endl;
	cout << "default virtualCarLinearSpeedFloor:" << virtualCarLinearSpeedFloor << endl;
	cout << endl;

	InitDirectionSensed();

	map2Init();

	// Three options for robot's sensor placement
	// Custom - read in ../config/sensorPos.txt
	sensorPopulationAlgorithmID = PLACE_SENSORS_USER_DEFINED;
	
	// Linear Distribution - Auto Linear distribution
	//sensorPopulationAlgorithmID = PLACE_SENSORS_AUTO_SEP;
	//num_sensors = 3;

	// Linear Distribution - Custom Linear distribution
	//sensorPopulationAlgorithmID = PLACE_SENSORS_SEP_USER_DEFINED;
	//num_sensors = 3;
	//sensorSeparation = 0.2;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//variables below can be initializes in config file,
	//or you can uncomment them to override config file settings.
	//----------------------------------------------
	virtualCarLinearSpeedFloor = 130;//mm
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(7);
	currentCarAngle = 0;

	//virtualCarAngularSpeed_seed = 40;//degree
	//currentCarAngle = 90;//degree
	//maxDarkDefValueTH = 20;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifdef TESTMODE3 //turn 180
	currentCarPosCoord_X = cellToCoordX(3);
	currentCarPosCoord_Y = cellToCoordY(7);
	currentCarAngle = 0;//degree
	virtualCarLinearSpeedFloor = 0; // mm/s
	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;// coord/s
	virtualCarAngularSpeed_seed = 0;
	cout << "updated virtualCarLinearSpeed_seed:" << virtualCarLinearSpeed_seed << endl;
	cout << "updated virtualCarAngularSpeed_seed:" << virtualCarAngularSpeed_seed << endl;
#endif //TESTMODE3

#ifdef TESTSENSOR
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(8);
	currentCarAngle = 0;//degree
	virtualCarLinearSpeedFloor = 0;
	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;//coord
	virtualCarAngularSpeed_seed = 0;
#endif //TESTSENSOR

#ifdef TESTALIGN
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(5);
#endif //TESTALIGN

#ifdef TESTL1
	currentCarAngle = 270;//degree
	currentCarPosCoord_X = cellToCoordX(START_X);
	currentCarPosCoord_Y = cellToCoordY(START_Y);
#endif // TESTL1


	myTimer.resetTimer();
	return 1;
}


int virtualCarUpdate()
{
	static int i = 0;
	static float prev_position = coordToFloorX(currentCarPosCoord_X);
	static float myspeed = virtualCarLinearSpeed_seed;
	static int skip = 1;

	if (skip == 1)
	{
		if (myTimer.getTimer() > STARTUPDELAY)
			skip = 0;
		else
			return 1;
	}

	HandleSensor();

//	if (i < NITERATIONS)
//	{
//		//		setVirtualCarSpeed(virtualCarLinearSpeed_seed * 0.10, 360/10);
//		virtualCarLinearSpeed = virtualCarLinearSpeed_seed;
//		virtualCarAngularSpeed = virtualCarAngularSpeed_seed;
//		cout << "=====================================" << endl;
//		cout << "iteration:" << i << " with speed_seed: " << virtualCarLinearSpeed_seed << " with angular speed_seed: " << virtualCarAngularSpeed_seed << endl;
//
//		cout << "current car floor X, Y, theta = " << coordToFloorX(currentCarPosCoord_X) << " , " << coordToFloorY(currentCarPosCoord_Y) << " , " << currentCarAngle << endl;
//		cout << "current Cell X, Y = " << coordToCellX(currentCarPosCoord_X) << " , " << coordToCellY(currentCarPosCoord_Y) << endl;
//		cout << "del pos:" << coordToFloorX(currentCarPosCoord_X) - prev_position << endl;
//		cout << "-----------------------------------------" << endl;
//
//		prev_position = coordToFloorX(currentCarPosCoord_X);
//		i++;
//}
//	else
//	{
//		stopMovement();
//		if (i == NITERATIONS)
//		{
//			cout << "=====================================" << endl;
//			cout << "iteration:" << i << " with speed_seed: " << virtualCarLinearSpeed_seed << endl;
//
//			cout << "current car floor X, Y, theta = " << coordToFloorX(currentCarPosCoord_X) << " , " << coordToFloorY(currentCarPosCoord_Y) << " , " << currentCarAngle << endl;
//			cout << "current Cell X, Y = " << coordToCellX(currentCarPosCoord_X) << " , " << coordToCellY(currentCarPosCoord_Y) << endl;
//			cout << "del pos:" << coordToFloorX(currentCarPosCoord_X) - prev_position << endl;
//			cout << "-----------------------------------------" << endl;
//		}
//		i++;
//	}

#ifdef TESTMODE3
	static int current_goal = 0;				// tracks the goal the robot currently needs to find <-- TODO: shift this to PathfindingUtility?

	if (!GetIsRobotGoalReached())
	{
		HandlePosition();

		static MotionState nextCommand = NO_STATE;

		if (nextCommand == NO_STATE)
		{
			/* L2 */
			if (!IsDirectionQueueEmpty())
			{
				/* Follow Current Directions to Goal */
				nextCommand = ConvertDirectionToMotionState(GetNextDirection());	// DirectionQueue automatically free()s memory
			}
			else
			{
				nextCommand = NO_STATE;

				/* Prepare Directions to Next Goal */
				if (current_goal < NUMBER_OF_GOALS - 1)	// TODO: Goal tracking and progress should probably be in PathfindingUtility. -1 as increments within if{}
				{
					current_goal++;
					SetStartPos(GoalPositions[current_goal * 2], GoalPositions[current_goal * 2 + 1]);	// <-- TODO: UPDATE!	Temporary example using hacky ideal values; should use ODOMETER?
					FindShortestPathForGoal(current_goal);

					Direction reorientation_direction = GetDirectionToReorientate();
					if (reorientation_direction == FORWARD)
					{
						if (IsDirectionStartAtIntersection())
						{
							// Insert a buffer so the starting intersection is not incorrectly interpreted as part of the direction path
							nextCommand = FOLLOWING;
							printf("--- BUFFER inserted\n");
						}
						else
						{
							// already aligned, no changes required:
							nextCommand = ConvertDirectionToMotionState(GetNextDirection());
							printf("--- No realignment, next command: "); PrintRobotState(nextCommand); printf("\n");
						}

						
					}
					else
					{
						// realign:
						nextCommand = ConvertDirectionToMotionState(reorientation_direction);
						printf("--- Inserted realign direction: "); PrintRobotState(nextCommand); printf("\n");
					}
				}
			}
		}

		/*	This is a sample command structure :

			The robot is driven by its currently sensed path + navigation command
			Navigation command is a MotionState enum stored in NextRobotMotionState.

			Ideally:
				Navigation is handled after HandleSensor() (above) before the following
				section and a command is produced.

				The following section load the command DEPENDING on the encountered path.

					- A counter may be used to track each path met (and went straight)
					  on the same following trace.

			Currently, commands to deal with an intersection is fixed.

			If no command is loaded, robot drives automatically in the following priority:

				Follow a line					-> Straight and automatic line following logic.
				Dead-end and floating off-line	-> U-turn (right)
		*/
		//}---------------------------------

		if (GetRobotMotionState() == FOLLOWING)
		{
			if (SENSED_CROSS_ROAD)
			{
				SetNextRobotMotionState(nextCommand); // Fixed.
				nextCommand = NO_STATE;
			}
			else if (SENSED_T)
			{
				SetNextRobotMotionState(nextCommand); // Fixed.
				nextCommand = NO_STATE;
			}
			else if (SENSED_L_BRANCH_T)
			{
				SetNextRobotMotionState(nextCommand); // Fixed.
				nextCommand = NO_STATE;
			}
			else if (SENSED_R_BRANCH_T)
			{
				SetNextRobotMotionState(nextCommand); // Fixed.
				nextCommand = NO_STATE;
			}
		}
		//}---------------------------------

		/* Update Routine: */

		// Pass command as current state.
		HandleCommands(GetNextRobotMotionState());
		// Perform actuation depending on current RobotMotionState
		HandleMovement();
	}
	else 
	{
		if (GetRobotMotionState() != FOLLOWING)
		{
			// If the robot is currently performing a turn, do not interrupt it.

			if (current_goal < NUMBER_OF_GOALS - 1) { SetGoalReached(FALSE); }	// Continue until all goals reached <-- TODO: clean up and ideally modularise!

			static int leaveCounter = 0;
			leaveCounter++;
			if (leaveCounter > LEAVING_COUNT)
			{
				//setVirtualCarSpeed(0, 360);
				setVirtualCarSpeed(0, 0);	// Creep forward once goal reached. Pause while waiting for new instructions.
			}
		}
	}

	//printf("######################\n");
#endif // TESTMODE3

	myTimer.resetTimer();

	return 1;
}

int main(int argc, char** argv)
{
	//InitFoodList();

#ifdef TEST_SHORTEST_PATH
	//FindShortestPathTest();
	//SetStartPos(START_X, START_Y);
	//FindShortestPathForGoal(0);
#endif

	//FungGlAppMainFuction(argc, argv);
	//handleNextGoal( ); takes x and y pointers to check as next goal node

	return 0;
}
