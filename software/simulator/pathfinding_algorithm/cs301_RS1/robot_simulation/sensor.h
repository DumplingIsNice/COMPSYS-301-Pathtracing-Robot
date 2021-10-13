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

#define SENSE_TRUE  0
#define SENSE_FALSE 1

enum SenseState
{
    STRAIGHT_PATH, EXPECT_TURN, LEFT_TURN, RIGHT_TURN, DEAD_END,
    T_SEC, LEFT_BRANCH_T, RIGHT_BRANCH_T, CROSS_ROAD, NO_PATH
};

void InitDirectionSensed();
Directions*  GetDirectionsSensed();

// Runs ensor FSM logic
void SensorFSM();

// Processes sensor input and populate directionsSensed
void HandleSensor();

// Debug functions to print infomation to terminal
void PrintSenseFSMState(SenseState s);
void PrintSensorStates();

// Get indivisual alignment sensors
int GetRASensor();
int GetLASensor();

#endif // SENSOR_H