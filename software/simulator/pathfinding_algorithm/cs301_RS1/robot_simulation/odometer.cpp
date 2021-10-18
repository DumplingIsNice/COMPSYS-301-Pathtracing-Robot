#include "odometer.h"
#include "../mainFungGLAppEngin.h"
#include "../highPerformanceTimer.h"

//Update cycle = 1ms

float start_time;
float current_time;
float time;
float floorDistance;
float speed;
extern bool reset;

highPerformanceTimer myTimer;


float calculateDistance() 
{	
	start_time = myTimer.getTimer();
	
	while (!reset)
	{
		current_time = myTimer.getTimer();
		time += (current_time - start_time);
		speed = virtualCarLinearSpeedFloor
	} 

	floorDistance = time * speed;

	if (reset)
	{
		time = 0;
		floorDistance = 0;
	}
}

int cellxTravelled(float floorDistance)
{
	return floorToCellX(floorDistance);
}

int cellyTravelled(float floorDistance)
{
	return floorToCellY(floorDistance);
}