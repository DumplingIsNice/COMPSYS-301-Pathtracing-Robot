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

extern int GoalPositions[2 * NUMBER_OF_GOALS];

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
    int roboX = GetCurrentRobotPosX();
    int roboy = GetCurrentRobotPosY();

    static int i = 0;

	if (roboX == GetGoalPosX() && roboy == GetGoalPosY())
	{
		SetIsRobotGoalReached(1);
	}

    printf("###Handled Position!###\n");
    printf("Before Visits map at (%d, %d) = %d\n", roboX, roboy, GetVisitsMap(roboX, roboy));
    SetVisitsMap(roboX, roboy, 1);
    printf("Visits map at (%d, %d) = %d\n", roboX, roboy, GetVisitsMap(roboX, roboy));
    if (i > 10)
    {
        PrintVisitsMap();
        i = 0;
    }
    i++;
}

/* FoodList Functionality */

void PrintGoalPosition()
{
    for (int i = 0; i < (2*NUMBER_OF_GOALS)+1; i += 2) {
        printf("Pair %d is x = %d, y = %d\n", i / 2, GoalPositions[i], GoalPositions[i + 1]);
    }
}

void InitFoodList() {
    int status = 0;
	status = LoadFoodFile(FOOD_FILE_PATH);
    switch (status)
    {
    case 1:
        printf("Opened food file!\n");
        PrintFoodList();
        break;
    default:
        printf("Failed to open food file!\n");
        break;
    }

    LoadFoodMapToArray(GoalPositions);
    PrintGoalPosition();
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

void LoadFoodMapToArray(int a[]) {
    int food, k;
    k = 0;
    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {
            food = foodMap[i][j];
            if (food == 1)
            {
                //printf("Pair is x = %d, y = %d\n", j, i);
                a[k] = j;
                a[k+1] = i;
                k+=2;
            }
        }
    }
}

int VisitsMap[MAP_SIZE_Y][MAP_SIZE_X]; // copy of static variable that is in readmap file

int GetVisitsMap(const int x, const int y)
{
    return VisitsMap[y][x];
}

void SetVisitsMap(int x, int y, int val)
{
    VisitsMap[y][x] = val;
}

void PrintVisitsMap()
{
    PrintMap(VisitsMap);
}
#pragma optimize("", off)
/* k - starting row index
        m - ending row index
        l - starting column index
        n - ending column index
        i - iterator

 Code retrieved from: https://www.geeksforgeeks.org/print-kth-element-spiral-form-matrix/

    Author(s):  andrew1234
    shivanisinghss2110
    divyeshrabadiya07
    divyesh072019
    mukesh07
    sravankumar8128

*/
void spiralArray(int m, int n, int a[MAP_SIZE_Y][MAP_SIZE_X], int c, int* x, int* y)
{
    int i, k = 0, l = 0;
    int count = 0;

    while (k < m && l < n) {
        /* check the first row from
            the remaining rows */
        for (i = l; i < n; ++i) {
            count++;

            if (count == c) {
                (*x) = k;
                (*y) = i;
                printf("%d , %d \n", k, i);
            }
            //cout << a[k][i] << " ";

        }
        k++;

        /* check the last column
        from the remaining columns */
        for (i = k; i < m; ++i) {
            count++;

            if (count == c) {
                (*x) = i;
                (*y) = n - 1;
                printf("%d , %d \n", i, n - 1);
            }

        }
        n--;

        /* check the last row from
                the remaining rows */
        if (k < m) {
            for (i = n - 1; i >= l; --i) {
                count++;

                if (count == c) {
                    (*x) = m - 1;
                    (*y) = i;
                    printf("%d , %d \n", m - 1, i);
                }

            }
            m--;
        }

        /* check the first column from
                the remaining columns */
        if (l < n) {
            for (i = m - 1; i >= k; --i) {
                count++;

                if (count == c) {
                    (*x) = i;
                    (*y) = l;
                    printf("%d , %d \n", i, l);

                }
            }
            l++;
        }
    }
}

// Call in virtual car init
void VisitsMapInit() {

    ReadMapFile(MAP_NAME);

    for (int row = 0; row < MAP_SIZE_Y; row++) {
        for (int col = 0; col < MAP_SIZE_X; col++) {
            VisitsMap[row][col] = GetMapValue(row, col);
        }
    }
    PrintVisitsMap();
}

/* Driver program to test above functions */
void handleNextGoal(int* posx, int* posy)
{
    int k = 0; // the node in the matrix that we want to check

    int x = 0;
    int y = 0;

    //loop through the matrix
    while (k < (MAP_SIZE_Y * MAP_SIZE_X - 1)) {
        spiralArray(MAP_SIZE_Y, MAP_SIZE_X, VisitsMap, k, &x, &y);
        k++;
        if (VisitsMap[x][y] == 0) {
            (*posx) = x;
            (*posy) = y;
            SetIsRobotGoalReached(0);
            VisitsMap[x][y] = 1;
            return;
        }
    }

    return;
}
#pragma optimize("", on)