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

#define TESTMODE0
//#define TESTMODE1
#define TESTMODE3

//#define TEST_MODE_MAP
#define TESTSENSOR
#define TESTMOVELEFT
//#define TESTMOVERIGHT

#define NITERATIONS 100
#define STARTUPDELAY 2 //sec

#define TURNING_SPEED			60 //rad/s
#define LEFT_TURNING_SPEED		TURNING_SPEED
#define RIGHT_TURNING_SPEED		-TURNING_SPEED

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

typedef enum MotionState
{
	FOLLOWING, LEFT_TURNING, RIGHT_TURNING, LEAVING
};

static MotionState RobotMotionState = FOLLOWING;

MotionState GetRobotMotionState() {
	return RobotMotionState;
}

void SetRobotMotionState(const MotionState s) {
	RobotMotionState = s;
}


/*Input speed : takes in a speed for the robot in mm/s*/
void moveStraight(int speed) {

	setVirtualCarSpeed(speed * floorToCoordScaleFactor, 0);
}


void turnLeft() {
	
	setVirtualCarSpeed(0, LEFT_TURNING_SPEED);
	SetRobotMotionState(LEFT_TURNING);
}

void turnRight() {
	setVirtualCarSpeed(0, RIGHT_TURNING_SPEED);
	SetRobotMotionState(RIGHT_TURNING);
}

void turnBack() {
	setVirtualCarSpeed(0, 360);

}


void stopMovement() {
	setVirtualCarSpeed(0, 0);
}


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
void movementDirection(int direction, int speed = 80) {

	if (direction == 0) {
		moveStraight(speed);
	}
	else if (direction == 1) {
		turnLeft();
	}
	else if (direction == 2) {
		turnRight();
	}
	else if (direction == 3) {
		turnBack();
	}
	else {
		stopMovement();
	}

}

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
	virtualCarLinearSpeedFloor = 70;
	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;//coord
#endif //TESTSENSOR

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

	if (i < NITERATIONS)
	{	
		Directions* validDirections = GetDirectionsSensed();
		
		switch (GetRobotMotionState()) 
		{
		case FOLLOWING:
			if (validDirections->forward)
			{
				movementDirection(0); // Straight
			}
			if (validDirections->left)
			{
				movementDirection(1); // Left
			}
			if (validDirections->right)
			{
				movementDirection(2); // Right
			}
			if ((!validDirections->left && !validDirections->right) && !validDirections->forward)
			{
				stopMovement(); // Right
			}
			break;
		case LEFT_TURNING:
			if ((validDirections->forward) && (validDirections->left))
			{
				movementDirection(0); // Straight
				SetRobotMotionState(LEAVING);
			}
			break;
		case RIGHT_TURNING:
			if ((validDirections->forward))
			{
				movementDirection(0); // Straight
				SetRobotMotionState(LEAVING);
			}
			break;
		case LEAVING:
			if (validDirections->forward)
			{
				movementDirection(0); // Straight
			}
			if (!((validDirections->left) && (validDirections->forward)))
			{
				SetRobotMotionState(FOLLOWING);
			}
			if (!((validDirections->right) && (validDirections->forward)))
			{
				SetRobotMotionState(FOLLOWING);
			}
			break;
		default:
			;
		}
		
		i++;
	} 
	else
	{
		stopMovement();
		//currentCarAngle = 180;
	}
#endif // TESTMODE3

#ifdef TESTSENSOR
	//{------------------------------------
	// Rudenmentry self aligning system
	// Alignment sensor located at back for least duration oscillation. 
	// Prob Need to be fix condition to while the robot is under the travel straight command.
	// Requires dynamic readjustment magnitude (PID??)
		// Needs to be fast when center returns to path.
	// Critical note: **We cannot turn on a dime**.
	//updat linear and rotational speed based on sensor information

	//static float alignAngularSpeed = 0.0;
	//static float alignAccAngularSpeed = 2.0;

	//if ((F_SENSOR == SENSE_FALSE) && (C_SENSOR == SENSE_FALSE))
	//{
	//	if (LA_SENSOR == SENSE_TRUE)
	//		setVirtualCarSpeed(virtualCarLinearSpeed_seed, (alignAngularSpeed+=alignAccAngularSpeed));
	//	else if (RA_SENSOR == SENSE_TRUE)
	//		setVirtualCarSpeed(virtualCarLinearSpeed_seed, (alignAngularSpeed-=alignAccAngularSpeed));
	//	else
	//	{
	//		setVirtualCarSpeed(virtualCarLinearSpeed_seed, -2*alignAngularSpeed);
	//		alignAngularSpeed = 0.0;
	//	}
	//	printf("Angular Speed: %f\n", virtualCarAngularSpeed_seed);
	//} 

	//}---------------------------------------
#endif // TEST_SENSOR

	myTimer.resetTimer();

	return 1;
}

//------------------------------------------------------------------------------------------
int virtualCarUpdate0()
{
	//{----------------------------------
	//process sensor state information
	float halfTiltRange = (num_sensors - 20) / 2.0;
	float tiltSum = 0.0;
	float blackSensorCount = 0.0;
	for (int i = 0; i < num_sensors; i++)
	{
		if (virtualCarSensorStates[i] == 0)
		{
			float tilt = (float)i - halfTiltRange;
			tiltSum += tilt;
			blackSensorCount += 1.0;
		}
	}
	int count = 0;
	if (count < 3) {
		setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed);
		count++;
	}else{
		setVirtualCarSpeed(0, 0);
	}
	count = 0;
	
    //}------------------------------------

	////{------------------------------------
	////updat linear and rotational speed based on sensor information
	//if (blackSensorCount > 0.0)
	//{
		//setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed*tiltSum);
		//setVirtualCarSpeed(virtualCarLinearSpeed_seed, 0);
		//setVirtualCarSpeed(0.5, 0);
	//}
	//else
	//{
		//setVirtualCarSpeed(0.0, -90);
	//}
		//setVirtualCarSpeed(0.0, 10.0);
	////}---------------------------------------

	//below is optional. just to provid some status report .
	//{--------------------------------------------------------------
	
	if (myTimer.getTimer() > 0.5)
	{
		myTimer.resetTimer();
		cout << "Sensor State: ";
		for (int i = 0; i < num_sensors; i++)
		{
			cout << virtualCarSensorStates[i] << " ";
		
		}
		cout << endl;
		//for (int i = 0; i < ghostInfoPackList.size(); i++)
		//	cout << ghostInfoPackList[i].ghostType << " , " << ghostInfoPackList[i].direction << endl;
		cout << "=====================================" << endl;
		cout << "current car floor X, Y, theta = " << coordToFloorX(currentCarPosCoord_X) << " , " << coordToFloorY(currentCarPosCoord_Y) << " , " << currentCarAngle << endl;
		cout << "current Cell X, Y = " << coordToCellX(currentCarPosCoord_X) << " , " << coordToCellY(currentCarPosCoord_Y) << endl;
		cout << "-----------------------------------------" << endl;
		cout << " ghost list info:" << endl;
		for (int i = 0; i < ghostInfoPackList.size(); i++)
		{
			cout << "g[" << i << "]: (" << ghostInfoPackList[i].coord_x << ", " << ghostInfoPackList[i].coord_y <<"); [s="<<
				ghostInfoPackList[i].speed<<"; [d="<< ghostInfoPackList[i].direction << "]; [T=" << ghostInfoPackList[i].ghostType<<"]" << endl;
		}
	}
	
	//}---------------------------------------------------------------
	
	return 1;
}
//}=============================================================

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
