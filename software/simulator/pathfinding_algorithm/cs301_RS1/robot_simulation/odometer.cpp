#include "odometer.h"
#include "../mainFungGLAppEngin.h"
#include "../highPerformanceTimer.h"
#include "../pathfinding/Timer/CPUTimer.h"
#include <stdio.h>

double current_time;
float cell_distance = 0;
float tick_distance = 0;

extern float virtualCarLinearSpeed_seed;
extern highPerformanceTimer myTimer;

void OdometerTick()
{
	current_time = myTimer.getTimer();

	//For very first time calling function - should be no distance travelled - myTimer is reset every tick so no start_time required
	
	tick_distance = virtualCarLinearSpeed_seed * (float)current_time;

	cell_distance += coordToCellX(tick_distance);
	//cell_distance += coordToCellY(tick_distance);
	
}

float GetCellDistance()
{
	//printf("Linear speed: %f\n", virtualCarLinearSpeed_seed);
//	printf("Time per tick: %f\n", current_time);
	printf("Tick distance is: %f\n Cell distance is: %f\n", tick_distance, cell_distance);
	return cell_distance;
}

void OdometerReset()
{
	cell_distance = 0;
}