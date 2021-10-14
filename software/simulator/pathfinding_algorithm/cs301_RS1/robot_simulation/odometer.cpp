#include "odometer.h"
#include "../mainFungGLAppEngin.h"
#include "../highPerformanceTimer.h"

//Update cycle = 1ms

extern float start_time;
extern float end_time;
float floorDistance = 0;

//Based on update time
float time = 0.1;
//For more accurate update time
//float time = start_time - end_time;

void calculateDistance() 
{
	floorDistance = time * virtualCarLinearSpeedFloor;
}

int cellxTravelled()
{
	return floorToCellX(floorDistance);
}

int cellyTravelled()
{
	return floorToCellY(floorDistance);
}