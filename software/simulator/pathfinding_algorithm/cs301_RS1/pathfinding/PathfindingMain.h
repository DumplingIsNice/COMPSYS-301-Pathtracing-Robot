#ifndef PATHFINDINGMAIN_H
#define PATHFINDINGMAIN_H

/*
	Pathfinding Main

	Overall consolidating file tying together all the pathfinding functions.
	
*/

#include "PathfindingUtil.h"

/* Debug Visualization Settings */
#define WALKED_PATH 8

/* These values should overwrite placeholders in the other files. */
#define MAP_NAME	"map.txt"
#define MAP_SIZE_X	19
#define MAP_SIZE_Y	15

#define GOAL_X		17
#define GOAL_Y		13
#define START_X		1
#define START_Y		1

//
void FindShortestPath();

// Free all dynamically allocated memory.
void CleanUpFindShortestPath();

// Runs Depth First Pathfinding
void DepthFirstSearch();

#endif