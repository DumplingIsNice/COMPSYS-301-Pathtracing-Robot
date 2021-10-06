#include "sensor.h"

#include "../mainFungGLAppEngin.h"
#include <stdio.h>
#include <vector>

extern float num_sensors;
extern std::vector<int> virtualCarSensorStates;

void CalcValidDirections(Directions* d)
{
    for (int i = 0; i < num_sensors; i++)
    {
        printf("virtualCarSensorStates %d = %d\n", i, virtualCarSensorStates[i]);
    }

    d->left = !L_SENSOR;
    d->right = !R_SENSOR;
    d->forward = !F_SENSOR;
}

void InitDirectionSensed()
{
    Directions* d = GetDirectionsSensed();
    d->forward = 0;
    d->left = 0;
    d->right = 0;
}

Directions* GetDirectionsSensed()
{
    return &directionsSensed;
}

void TestSensor()
{
    Directions* d = GetDirectionsSensed();
    CalcValidDirections(d);
    PrintDirections(d);
}