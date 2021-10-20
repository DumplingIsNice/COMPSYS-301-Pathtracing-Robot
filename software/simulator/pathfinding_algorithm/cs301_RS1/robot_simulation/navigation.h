#ifndef NAVIGATION_H
#define NAVIGATION_H

#ifndef FOOD_FILE_PATH
	#define FOOD_FILE_PATH "./foodList/foodList.txt"
#endif

#define MAP_SIZE_X	19
#define MAP_SIZE_Y	15

#ifndef DEBUG
	#define DEBUG
#endif

int GetIsRobotGoalReached();
void SetIsRobotGoalReached(int val);

void HandlePosition();

// Foodlist interaction functionality
void InitFoodList();
// Loads food file into a 2d Array
int LoadFoodFile(const char* file_name);
void PrintFoodList();
// Loads the values in the food map into an array in alternating
// x1, y1, x2, y2...
void LoadFoodMapToArray(static int a[]);
#endif // NAVIGATION_H