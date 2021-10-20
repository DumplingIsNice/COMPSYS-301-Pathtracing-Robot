#include "sensor.h"
#include "control.h"

extern "C"
{
    #include "../pathfinding/Navigation/DirectionsList.h"
}

#include "../mainFungGLAppEngin.h"
#include <stdio.h>
#include <vector>

extern float num_sensors;
extern std::vector<int> virtualCarSensorStates;
extern int linearSpeed;

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


    #ifdef SENSOR_DEBUG
        PrintDirections(GetDirectionsSensed());
    #endif // SENSOR_DEBUG
}

void HandleTurningSpeed(SenseState s)
{
    switch (s)
    {
    case CONFIRM_PATH:
        linearSpeed = CONFIRMING_SPEED;
        break;
        // Necessary for consequtive turns on non-intersections
    case EXPECT_TURN:
        linearSpeed = EXPECTING_SPEED;
        break;
    default:
        linearSpeed = DEFAULT_LINEAR_SPEED;
        break;
    }
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

    static int confirmCounter = 0;
    static SenseState confirmedState = CONFIRM_PATH;
    static int flagRSensor = 0;
    static int flagLSensor = 0;

    // Override turning while turning 
    //if ((GetRobotMotionState() == FOLLOWING) && (GetRASensor() || GetLASensor())) {
    //    currentState = STRAIGHT;
    //}

    // FSM logic is driven by state of centre and forward sensor, branching 
    // by the relative states of right and left sensor according to truthtable
    if (nextState == NO_PATH && currentState != CONFIRM_PATH)
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
            currentState = CONFIRM_PATH;
            flagRSensor = 1;
        }
        else if (L_SENSOR == SENSE_TRUE) {
            currentState = CONFIRM_PATH;
            flagLSensor = 1;
        }
        // Cannot discern dead_end from other turning intersections solely on 
        // f,l,r sensors. Effective dead_end if veered off path, need 
        // reconsideration when implementing alignment logic
        else if (C_SENSOR == SENSE_FALSE && (!GetRASensor() && !GetLASensor())) {
            nextState = DEAD_END;
        }
        break;
    // This state is for handling the edge case where a t, branch 
    // or cross road is entered at an angle. Where one l/r sensor may
    // false register early as a exlusive left/right.
    // This state waits an logs sensors to confirm the path it is on.
    case CONFIRM_PATH:
        d->forward = true;

        confirmCounter++;

        // Logging sensors
        if (R_SENSOR == SENSE_TRUE) {
            flagRSensor = 1;
        }

        if (L_SENSOR == SENSE_TRUE) {
            flagLSensor = 1;
        }
        
        // Wait duration over, analyze logged sensor data
        if (confirmCounter > 2)
        {
            if (GetRASensor() || GetLASensor())
            {
                // Confirm cross road
                if (flagRSensor && flagLSensor)
                {
                    confirmedState = CROSS_ROAD;
                }
                // Confirm L_branch
                else if (flagRSensor)
                {
                    confirmedState = RIGHT_BRANCH_T;
                }
                // Confirm R_branch
                else if (flagLSensor)
                {
                    confirmedState = LEFT_BRANCH_T;
                }
            }
            else
            {
                // Confirm T_sec road
                if (flagRSensor && flagLSensor)
                {
                    confirmedState = T_SEC;
                }
                // Confirm right following road
                else if (flagRSensor)
                {
                    confirmedState = RIGHT_TURN;
                }
                // Confirm left following road
                else if (flagLSensor)
                {
                    confirmedState = LEFT_TURN;
                }
            }
            nextState = confirmedState;
            confirmedState = CONFIRM_PATH;
            confirmCounter = 0;
            flagRSensor = 0;
            flagLSensor = 0;
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

    #ifdef SENSOR_DEBUG
        // Debug information
        printf("Current State is: ");
        PrintSenseFSMState(currentState);
        printf("Next State is: ");
        PrintSenseFSMState(nextState);
    #endif // SENSOR_DEBUG

    // Automatic linear speed control for turning
    HandleTurningSpeed(currentState);

    if (nextState != NO_PATH)
    {
        currentState = nextState;
    }
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
    case CONFIRM_PATH:
        printf("CONFIRM_PATH\n");
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
