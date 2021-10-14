#include "sensor.h"
#include "control.h"

#include "../mainFungGLAppEngin.h"
#include <stdio.h>
#include <vector>

extern float num_sensors;
extern std::vector<int> virtualCarSensorStates;

static Directions directionsSensed;
static SenseState currentState = NO_PATH;
static SenseState nextState = NO_PATH;

void InitDirectionSensed()
{
    Directions* d = GetDirectionsSensed();
    d->forward = false;
    d->left = false;
    d->right = false;
}

Directions* GetDirectionsSensed()
{
    return &directionsSensed;
}

void HandleSensor()
{
    SensorFSM();

    // Debug information
    PrintDirections(GetDirectionsSensed());
}

int GetRASensor() {
    return RA_SENSOR == SENSE_TRUE;
}

int GetLASensor() {
    return LA_SENSOR == SENSE_TRUE;
}

void SensorFSM()
{
    Directions* d = GetDirectionsSensed();

    // Override turning while turning 
    //if ((GetRobotMotionState() == FOLLOWING) && (GetRASensor() || GetLASensor())) {
    //    currentState = STRAIGHT;
    //}

    // FSM logic is driven by state of centre and forward sensor, branching 
    // by the relative states of right and left sensor according to truthtable
    if (nextState == NO_PATH)
    {
        if (GetRASensor()||GetLASensor()) {
            if ((R_SENSOR == SENSE_TRUE) && (L_SENSOR == SENSE_TRUE)) {
                currentState = CROSS_ROAD;
            }
            else if (R_SENSOR == SENSE_TRUE) {
                currentState = RIGHT_BRANCH_T;
            }
            else if (L_SENSOR == SENSE_TRUE) {
                currentState = LEFT_BRANCH_T;
            }
            else /* (R_SENSOR == SENSE_FALSE) && (L_SENSOR == SENSE_FALSE) */ {
                currentState = STRAIGHT_PATH;
            }
        }
        else /* (GetRASensor()||GetLASensor() == SENSE_FALSE) */ {
            currentState = EXPECT_TURN;
        }
    }
    // Exit descerning for turns
    // This is the PENDING section
    else {
        switch (GetRobotMotionState())
        {
        case RIGHT_TURNING:
            if (GetRASensor()) {
                currentState = STRAIGHT_PATH;
                nextState = NO_PATH;
            }
            break;
        case LEFT_TURNING:
            if (GetLASensor()) {
                currentState = STRAIGHT_PATH;
                nextState = NO_PATH;
            }
            break;
        default:
            if (GetRASensor() || GetLASensor()) {
                currentState = STRAIGHT_PATH;
                nextState = NO_PATH;
            }
            break;
        }
    }

    InitDirectionSensed();

    switch (currentState)
    {
    case STRAIGHT_PATH:
        d->forward = true;
        break;
    case EXPECT_TURN:
        d->forward = true;
        if ((R_SENSOR == SENSE_TRUE) && (L_SENSOR == SENSE_TRUE)) {
            nextState = T_SEC;
        }
        else if (R_SENSOR == SENSE_TRUE) {
            nextState = RIGHT_TURN;
        }
        else if (L_SENSOR == SENSE_TRUE) {
            nextState = LEFT_TURN;
        }
        // Cannot decern dead_end from other turning intersections soley on 
        // f,l,r sensors. Effective dead_end if veered off path, need 
        // reconsideration when implementing alignment logic
        else if (C_SENSOR == SENSE_FALSE && (!GetRASensor() && !GetLASensor())) {
            nextState = DEAD_END;
        }
        break;
    case LEFT_TURN:
        d->left = true;
        break;
    case RIGHT_TURN:
        d->right = true;
        break;
    case DEAD_END:
        break;
    case T_SEC:
        d->left = true;
        d->right = true;
        nextState = PENDING;
        break;
    case LEFT_BRANCH_T:
        d->forward = true;
        d->left = true;
        nextState = PENDING;
        break;
    case RIGHT_BRANCH_T:
        d->forward = true;
        d->right = true;
        nextState = PENDING;
        break;
    case CROSS_ROAD:
        d->forward = true;
        d->left = true;
        d->right = true;
        nextState = PENDING;
        break;
    default:
        ;
    }

    // Debug information
    printf("Current State is: ");
    PrintSenseFSMState(currentState);
    printf("Next State is: ");
    PrintSenseFSMState(nextState);
    //PrintSensorStates();

    if (nextState != NO_PATH)
        currentState = nextState;
}

void PrintSenseFSMState(SenseState s)
{
    switch (s)
    {
    case STRAIGHT_PATH:
        printf("STRAIGHT\n");
        break;
    case EXPECT_TURN:
        printf("EXPECT_TURN\n");
        break;
    case LEFT_TURN:
        printf("LEFT_TURN\n");
        break;
    case RIGHT_TURN:
        printf("RIGHT_TURN\n");
        break;
    case DEAD_END:
        printf("DEAD_END\n");
        break;
    case T_SEC:
        printf("T_SEC\n");
        break;
    case LEFT_BRANCH_T:
        printf("LEFT_BRANCH_T\n");
        break;
    case RIGHT_BRANCH_T:
        printf("RIGHT_BRANCH_T\n");
        break;
    case CROSS_ROAD:
        printf("CROSS_ROAD\n");
        break;
    case PENDING:
        printf("PENDING\n");
        break;
    default:
        printf("NULL\n");
        break;
    }
}

void PrintSensorStates()
{
    for (int i = 0; i < num_sensors; i++)
    {
        printf("virtualCarSensorStates %d = %d\n", i, virtualCarSensorStates[i]);
    }
}
