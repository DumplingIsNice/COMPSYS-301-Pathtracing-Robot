#ifndef PATHFINDINGMAIN_H
#define PATHFINDINGMAIN_H

/*
	Pathfinding Main

	Overall consolidating file tying together all the pathfinding functions.
	
*/

#include "PathfindingUtil.h"

/* Debug Visualization Settings */
//#define DEBUG
#define WALKED_PATH 8

/* Static Values for Testing Purposes Only */
#define GOAL_X		5 //17
#define GOAL_Y		5 //13
#define START_X		1
#define START_Y		1

/* Goal Locations */
#define NUMBER_OF_GOALS	2
const static int GoalPositions[2 * NUMBER_OF_GOALS] = {		// {goal1_x, goal1_y, goal2_x, goal2_y, ...};
					5, 5,
					5, 5};
					//7, 7,
					//4, 1,
					//17, 10};	

/* These values should overwrite placeholders in the other files. */
#define MAP_NAME	"./map/map.txt"
#define MAP_SIZE_X	19
#define MAP_SIZE_Y	15

/* Algorithm Variations*/
#define		WEIGHT_REBASING		// allow node weighting to change dynamically when cheaper alternate paths are found
//#define		ANALYTIC_VARIANT	// use ONLY for DEPTHFIRST and BREADTHFIRST to evaluate all nodes to ensure shortest path is found
//#define		DEPTHFIRST
//#define		BREADTHFIRST
#define ASTAR


// Dynamically set the goal and start positions.
void SetMapParameters(int goal_x, int goal_y, int start_x, int start_y);

// Free all dynamically allocated memory.
void CleanUpFindShortestPath();

// Calls FindShortestPath() with the static testing values as arguments.
void FindShortestPathTest();

// Calls FindShortestPath() for the specified goal (from GoalPositions[]).
// Start position is used from GetGoalPosX/Y();
void FindShortestPathForGoal(int goal_number);

// PRIMARY FUNCTION. Evaluates all nodes, finds the shortest path, populates the DirectionQueue, etc.
void FindShortestPath(int goal_x, int goal_y, int start_x, int start_y);

// Populate FinalQueue using NodeMap and final_node (node adjacent to the goal node).
// Returns the total number of elements added to the FinalQueue.
int PopulateFinalQueue(NodeData* final_node);

// 
void GenerateDirectionQueue();


#endif