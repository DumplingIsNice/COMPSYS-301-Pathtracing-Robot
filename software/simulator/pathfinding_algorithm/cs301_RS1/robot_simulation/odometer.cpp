#include "odometer.h"
#include "../mainFungGLAppEngin.h"
#include "../highPerformanceTimer.h"

//Update cycle = 1ms

float start_time = -1;
float current_time;
float cell_distance = 0;


highPerformanceTimer distanceTimer;

void OdometerTick()
{
	current_time = distanceTimer.getTimer();
	
	//For very first time calling function - should be no distance travelled
	if (start_time == -1) {
		start_time = current_time;
	}

	float tick_distance = virtualCarLinearSpeed_seed * (current_time - start_time);

	cell_distance += floorToCellX(tick_distance);

}

float GetCellDistance()
{
	return cell_distance;
}

void OdometerReset()
{
	cell_distance = 0;
}