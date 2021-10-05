#ifndef PATHFINDINGMAIN_H
#define PATHFINDINGMAIN_H

/*
	Pathfinding Main

	Overall consolidating file tying together all the pathfinding functions.
	
*/

#include "PathfindingUtil.h"

/* Debug Visualization Settings */
#define WALKED_PATH 8

/* Static Values for Testing Purposes Only */
#define GOAL_X		17
#define GOAL_Y		13
#define START_X		1
#define START_Y		1

/* These values should overwrite placeholders in the other files. */
#define MAP_NAME	"./map/map.txt"
#define MAP_SIZE_X	19
#define MAP_SIZE_Y	15


//#define DEBUG

#define		WEIGHT_REBASING		// allow node weighting to change dynamically when cheaper alternate paths are found
//#define		ANALYTIC_VARIANT	// use ONLY for DEPTHFIRST and BREADTHFIRST to evaluate all nodes to ensure shortest path is found
//#define		DEPTHFIRST
//#define		BREADTHFIRST
#define ASTAR

// Calls FindShortestPath() with the static testing values as arguments.
void FindShortestPathTest();

//
void FindShortestPath(int goal_x, int goal_y, int start_x, int start_y);

// Dynamically set the goal and start positions.
void SetMapParameters(int goal_x, int goal_y, int start_x, int start_y);

// Free all dynamically allocated memory.
void CleanUpFindShortestPath();

#endif