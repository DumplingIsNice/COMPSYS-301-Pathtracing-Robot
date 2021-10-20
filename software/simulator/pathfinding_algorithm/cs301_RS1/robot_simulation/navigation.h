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
void spiralArray(int m, int n, int a[MAP_SIZE_Y][MAP_SIZE_X], int c, int* x, int* y);
// Call in virtual car init
void VisitsMapInit();
/* Driver program to test above functions */
void handleNextGoal(int* posx, int* posy);

int GetVisitsMap(const int x, const int y);
void SetVisitsMap(const int x, const int y, const int val);
void PrintVisitsMap();
#endif // NAVIGATION_H