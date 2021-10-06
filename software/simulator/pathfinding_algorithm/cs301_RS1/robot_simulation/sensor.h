/*
        sensor.h

        Ths library implements the functions for the FSM to: 
        
            - Decoding the sensor input from the robot and determining the type of path/intersection through truth table.
            - Produces the array information of available movement options under that that type of pathway.

*/

#ifndef SENSOR_H
#define SENSOR_H

extern "C"
{
    #include "project.h"
}

// Sensor fecthing macro
#define L_SENSOR    virtualCarSensorStates[0]
#define R_SENSOR    virtualCarSensorStates[1]
#define F_SENSOR    virtualCarSensorStates[2]
#define C_SENSOR    virtualCarSensorStates[3]
#define LA_SENSOR   virtualCarSensorStates[4]
#define RA_SENSOR   virtualCarSensorStates[5]

static Directions directionsSensed;

void CalcValidDirections(Directions* d);
void InitDirectionSensed();
Directions*  GetDirectionsSensed();
void TestSensor();

#endif // SENSOR_H