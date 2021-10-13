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

// TESTMODE0: horizonal travel at fixed speed for 10 iterations, display position
// TESTMODE1: travel in a circle 

//#define TESTMODE0
//#define TESTMODE1

#define TESTMODE3
//#define TEST_MODE_MAP
#define TESTSENSOR

/* Starting Position Init */
//#define TESTMOVELEFT
//#define TESTMOVERIGHT
#define TESTALIGN

// Simulation parameters
//{------------------------------------
#define NITERATIONS 1000
#define STARTUPDELAY 2 //sec

#define DEFAULT_LINEAR_SPEED	120
#define LEAVING_COUNT			DEFAULT_LINEAR_SPEED/40

#define TURNING_SPEED			120 //rad/s
#define LEFT_TURNING_SPEED		TURNING_SPEED
#define RIGHT_TURNING_SPEED		-TURNING_SPEED

#define ALIGN_SPEED				20
#define LEFT_ALIGN_SPEED		ALIGN_SPEED //mm/s
#define RIGHT_ALIGN_SPEED		-ALIGN_SPEED //mm/s
//}------------------------------------

#include "mainFungGLAppEngin.h" //a must
#include "mazeGen.h" //just include to use radnom number generation function
#include <vector>
#include <iostream>
#include "highPerformanceTimer.h"//just to include if timer function is required by user.

/* Custom Includes */

extern "C"
{
	#include "pathfinding/PathfindingMain.h"
	#include "robot_simulation/project.h"
}

#include "robot_simulation/control.h"
#include "robot_simulation/sensor.h"

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

/* Actuation Functions */
//{------------------------------------
void LinearForward() { virtualCarLinearSpeed_seed = DEFAULT_LINEAR_SPEED * floorToCoordScaleFactor; }
void LinearZero() { virtualCarLinearSpeed_seed = 0; }
void AngularLeft() { virtualCarAngularSpeed_seed = LEFT_TURNING_SPEED; }
void AngularRight()	{ virtualCarAngularSpeed_seed = RIGHT_TURNING_SPEED; }
void AngularZero() { virtualCarAngularSpeed_seed = 0; }
void AlignLeft() { virtualCarAngularSpeed_seed = LEFT_ALIGN_SPEED; }
void AlignRight() { virtualCarAngularSpeed_seed = RIGHT_ALIGN_SPEED; }
void AlignZero() { virtualCarAngularSpeed_seed = 0; }

void InitSpeedSeed()
{
	LinearZero();
	AngularZero();
}

///*Input speed : takes in a speed for the robot in mm/s*/
//void moveStraight(int speed) {
//
//	virtualCarLinearSpeed_seed = speed * floorToCoordScaleFactor;
//}
//
//void moveZero() {
//	virtualCarLinearSpeed_seed = 0;
//}
//
//void turnLeft() {
//	
//	virtualCarLinearSpeed_seed = 0 * floorToCoordScaleFactor;
//	virtualCarAngularSpeed_seed = LEFT_TURNING_SPEED;
//}
//
//void turnRight() {
//	virtualCarLinearSpeed_seed = 0 * floorToCoordScaleFactor;
//	virtualCarAngularSpeed_seed = RIGHT_TURNING_SPEED;
//}
//
//void turnBack() {
//	virtualCarLinearSpeed_seed = 0 * floorToCoordScaleFactor;
//	virtualCarAngularSpeed_seed = 360;
//}
//
//void stopMovement() {
//	InitSpeedSeed();
//}
//
///*Input direction : takes an integer for the directions
//					0 - straight
//					1- left
//					2- right
//					3- back
//					4 - stop
//This can be changed to the macros used in the other files for better integration
//Input speed is an optional parameter used for setting the speed when moving straight
//If no value is supplied it will assume default of 130 mm/s
//
//The turning functions that are called set the linear and angular speed of the car,
//it doesnt take into account the iterations the turns should be called for, this should be handled,
//by the called. When testing this the turns took two iterations to complete
//
//[we're trying to implement this in here as well]
//*/
//void movementDirection(int direction, int speed = DEFAULT_LINEAR_SPEED) {
//
//	if (direction == 0) {
//		moveStraight(speed);
//	}
//	else if (direction == 1) {
//		turnLeft();
//	}
//	else if (direction == 2) {
//		turnRight();
//	}
//	else if (direction == 3) {
//		turnBack();
//	}
//	else {
//		stopMovement();
//	}
//
//}
//}------------------------------------
int virtualCarInit()
{
	cout << "default virtualCarLinearSpeed_seed:" << virtualCarLinearSpeed_seed << endl;
	cout << "default virtualCarAngularSpeed_seed:" << virtualCarAngularSpeed_seed << endl;
	cout << "default virtualCarLinearSpeedFloor:" << virtualCarLinearSpeedFloor << endl;
	cout << endl;

	InitDirectionSensed();

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
  
#ifdef TESTMODE0
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(7);
	currentCarAngle = 0;//degree
	virtualCarLinearSpeedFloor = 70;
	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;//coord
	virtualCarAngularSpeed_seed = 0;
#endif //TESTMODE0

#ifdef TESTMODE3 //turn 180
	currentCarPosCoord_X = cellToCoordX(3);
	currentCarPosCoord_Y = cellToCoordY(7);
	currentCarAngle = 0;//degree
	virtualCarLinearSpeedFloor = 0; // mm/s
	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;// coord/s
	virtualCarAngularSpeed_seed = 180;
	cout << "updated virtualCarLinearSpeed_seed:" << virtualCarLinearSpeed_seed << endl;
	cout << "updated virtualCarAngularSpeed_seed:" << virtualCarAngularSpeed_seed << endl;
#endif //TESTMODE3

#ifdef TESTSENSOR
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(8);
	currentCarAngle = 0;//degree
	virtualCarLinearSpeedFloor = 0;
	virtualCarLinearSpeed_seed = 0;//coord
#endif //TESTSENSOR

#ifdef TESTALIGN
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(5);
#endif //TESTALIGN

#ifdef TESTMOVERIGHT
	currentCarPosCoord_X = cellToCoordX(4);
	currentCarPosCoord_Y = cellToCoordY(2);
#endif //TESTMOVERIGHT

#ifdef TESTMOVELEFT
	currentCarPosCoord_X = cellToCoordX(1);
	currentCarPosCoord_Y = cellToCoordY(2);
#endif //TESTMOVELEFT


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

	printf("Current Robot Motion State is: ");
	PrintRobotState(GetRobotMotionState());
	printf("Prev Robot Motion State is: ");
	PrintRobotState(GetPrevRobotMotionState());

	static int toExit = 0;
	static int leaveCounter = 0;
	InitSpeedSeed();

	Directions* validDirections = GetDirectionsSensed();
		
	switch (GetRobotMotionState())
	{
	case FOLLOWING:
		if (validDirections->forward)
		{
			HandleAlignment();
			LinearForward();
		}
		if (validDirections->left)
		{
			AngularLeft();
			SetRobotMotionState(LEFT_TURNING);
		}
		if (validDirections->right)
		{
			AngularRight();
			SetRobotMotionState(RIGHT_TURNING);
		}
		if ((!validDirections->left && !validDirections->right) && !validDirections->forward)
		{
			AngularRight();
			SetRobotMotionState(U_TURN);
		}
		break;
	case LEFT_TURNING:
		AngularLeft();
		if (!validDirections->forward) 
		{ 
			toExit = 1;
		}
		if (toExit && validDirections->forward)
		{
			SetRobotMotionState(LEAVING);
			toExit = 0;
		}
		break;
	case RIGHT_TURNING:
		AngularRight();
		if (!validDirections->forward)
		{
			toExit = 1;
		}
		if (toExit && validDirections->forward)
		{
			SetRobotMotionState(LEAVING);
			toExit = 0;
		}
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
		AngularRight();
		if (validDirections->forward)
		{
			SetRobotMotionState(LEAVING);
		}
	default:
		;
	}
		
	setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed);
#endif // TESTMODE3

	myTimer.resetTimer();

	return 1;
}

int main(int argc, char** argv)
{

#ifdef TEST_MODE_MAP
	//FindShortestPath();
	//PrintOutputMap();
	//PrintFinalMap();
	//CreateFinalMap();
#endif

	FungGlAppMainFuction(argc, argv);

	return 0;
}
