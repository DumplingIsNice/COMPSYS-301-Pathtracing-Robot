#include "odometer.h"
#include "../mainFungGLAppEngin.h"
#include "../highPerformanceTimer.h"

//Update cycle = 1ms

float start_time;
float end_time;
float floorDistance = 0;

highPerformanceTimer myTimer;

//Based on update time
float time = 0.1;
//For more accurate update time
//float time = start_time - end_time;

void calculateDistance(int travellingStraight) 
{
	start_time = myTimer.getTimer();
	while (travellingStraight) {

	}
	end_time = myTimer.getTimer();
	floorDistance = (start_time-end_time) * virtualCarLinearSpeedFloor;
}

int cellxTravelled()
{
	return floorToCellX(floorDistance);
}

int cellyTravelled()
{
	return floorToCellY(floorDistance);
}