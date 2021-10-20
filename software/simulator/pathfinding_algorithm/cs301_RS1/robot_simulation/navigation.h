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

void InitFoodList();
int LoadFoodFile(const char* file_name);
void PrintFoodList();
#endif // NAVIGATION_H