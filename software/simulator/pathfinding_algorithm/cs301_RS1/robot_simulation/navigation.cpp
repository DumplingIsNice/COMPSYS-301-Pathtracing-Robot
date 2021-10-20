#include "navigation.h"

#include "actuation.h"

extern "C"
{
	#include "../pathfinding/PathfindingMain.h"
}

#include <stdio.h>
#include <stdlib.h>

// 'Private' variable
static int foodMap[MAP_SIZE_Y][MAP_SIZE_X];
static int IsRobotGoalReached = 0;

int GetIsRobotGoalReached()
{
	return IsRobotGoalReached;
}

void SetIsRobotGoalReached(int val)
{
	IsRobotGoalReached = val;
}

void HandlePosition()
{
	if (GetCurrentRobotPosX() == GetGoalPosX() && GetCurrentRobotPosY() == GetGoalPosY())
	{
		SetIsRobotGoalReached(1);
	}
}

/* FoodList Functionality */

void InitFoodList() {
    int status = 0;
	status = LoadFoodFile(FOOD_FILE_PATH);
    switch (status)
    {
    case 1:
        printf("Opened food file!\n");
        break;
    default:
        printf("Failed to open food file!\n");
        break;
    }
}

// Declaration drawn from fileUtility.h
int ASCIIToInt(char c);

int LoadFoodFile(const char* file_name)
{
	FILE* file;
    char c = 0;
    char axis = 'x';
    int x = -1;
    int y = -1;
    int nextCoord = 0;
    int log = 1;

    errno_t err = fopen_s(&file, file_name, "r");

    if (file == NULL)
    {
        return 0;
    }

    while (log)
    {
        c = fgetc(file);
        switch (c)
        {
        case '\n':
            // Next coord y->x.
            axis = 'x';
            printf("y: %d, x: %d\n", y, x);
            foodMap[y][x] = 1;
            nextCoord = 1;
            x = -1;
            y = -1;
            continue;
        case EOF:
            printf("y: %d, x: %d\n", y, x);
            foodMap[y][x] = 1;
            nextCoord = 1;
            x = -1;
            y = -1;
            log = 0;
        case ' ':
            // Next axis x->y.
            axis = 'y';
            continue;
        }
        switch (axis)
        {
        case 'x':
            if (x == -1)
            {
                x = ASCIIToInt(c);
            }
            else
            {
                x = x*10 + ASCIIToInt(c);
            }
            continue;
        case 'y':
            if (y == -1)
            {
                y = ASCIIToInt(c);
            }
            else
            {
                y = y*10 + ASCIIToInt(c);
            }
            continue;
        }
    }
    fclose(file);
    return 1;
}

void PrintFoodList()
{
    printf("# Printing FoodList #\n");
    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {
            printf("%3d", foodMap[i][j]);
        }
        putchar('\n');
    }
}

void LoadFoodMapToGoalList() {

}