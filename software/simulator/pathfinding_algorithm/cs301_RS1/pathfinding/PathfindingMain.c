#ifndef PATHFINDINGMAIN_C
#define PATHFINDINGMAIN_C

#include "PathfindingMain.h"

#include <stdio.h>
#include "FileUtility/ReadMap.h"
#include "PathfindingAlgorithm.h"
#include "PathfindingUtil.h"
#include "NodeData/NodeDataOps.h"
#include "NodeData/NodeMap.h"
#include "Navigation/DirectionsList.h"

#include "Timer/CPUTimer.h"

void SetMapParameters(int goal_x, int goal_y, int start_x, int start_y)
{
	SetGoalPos(goal_x, goal_y);
	SetStartPos(start_x, start_y);
}

void CleanUpFindShortestPath()
{
	SetGoalReached(FALSE);

	// Free the last of the NodeQueue elements (but not their NodeData!):
	unsigned long node_queue_bytes = DestroyListElements(GetNodeQueue());

	// Free the FinalQueue elements.
	unsigned long final_queue_bytes = DestroyListElements(GetFinalQueue());

	// Free all NodeData values:
	unsigned long total_nodedata_bytes = NodeMapClear();

	// Free all DirectionQueue elements and their Direction enums.
	// unsigned long direction_queue_bytes = DestroyDirectionQueueElementsAndContents();
	unsigned long direction_queue_bytes = 0;

	printf("NodeQueue Bytes: %ld B\n", node_queue_bytes);
	printf("Finished FinalQueue Bytes: %ld B\n", final_queue_bytes);
	printf("Total NodeData Bytes: %ld B\n", total_nodedata_bytes);
	printf("    Sum: %ld B\n", (node_queue_bytes + final_queue_bytes + total_nodedata_bytes));
	printf("DirectionQueue Bytes: %ld B\n", direction_queue_bytes);
	printf("    Total: %ld B\n", (node_queue_bytes + final_queue_bytes + total_nodedata_bytes + direction_queue_bytes));
	printf("\n\n");
}

void FindShortestPathTest()
{
	FindShortestPath(GOAL_X, GOAL_Y, START_X, START_Y);
}

void FindShortestPathForGoal(int goal_number)
{
	if (goal_number >= NUMBER_OF_GOALS) { printf("ERROR: Invalid goal index!\n"); return; }


	int temp_start_x = 0;
	int temp_start_y = 0;

	if (goal_number <= 0) {
		temp_start_x = GetStartPosX();	// use default values for start
		temp_start_y = GetStartPosY();
	}
	else {
		temp_start_x = GoalPositions[(goal_number - 1) * 2];	// otherwise use previous goal values (assuming exact!)
		temp_start_y = GoalPositions[(goal_number - 1) * 2 + 1];
	}

	FindShortestPath(GoalPositions[goal_number * 2], GoalPositions[goal_number * 2 + 1], temp_start_x , temp_start_y);
}

void FindShortestPath(int goal_x, int goal_y, int start_x, int start_y)
{
	/* Performance Counters */
	clock_t time_error = GetCurrentClockTime();
	time_error = GetCurrentClockTime() - time_error;

	clock_t total_time = GetCurrentClockTime();
	clock_t node_queue_time = 0;
	clock_t shortest_path_time = 0;
	clock_t direction_queue_time = 0;

	int nodes_evaluated_count = 0;
	int final_path_length = 0;


	/* 
		Setup 
		
		Clean up values from previous iterations, read the map file,
		and set the start and goal positions.
	*/
	CleanUpFindShortestPath(); // ensure no pre-existing values remain
	ReadMapFile(MAP_NAME);		// read map and set start/goal locations
	SetMapParameters(goal_x, goal_y, start_x, start_y);


	/*
		Evaluate Nodes

		Evaluate nodes from NodeQueue (populated by EvaluateAdjacentCells)
		until goal is reached:
	*/
	node_queue_time = GetCurrentClockTime();

	EvaluateCell(NULL, GetStartPosX(), GetStartPosY());	// Create the starting node and add it to NodeQueue
	NodeData* final_node = NULL;

	while (!IsNodeQueueEmpty())
	{
		ListElement* current_node_element = ExtractNextInNodeQueue();
		EvaluateAdjacentCells(current_node_element->node);
		NodeData* current_node = current_node_element->node;

		#ifdef DEBUG
			printf("### Iteration i: %d ###\n", nodes_evaluated_count);
			WriteOutputMap(current_node->posx, current_node->posy, WALKED_PATH);
			//PrintNodeMap();
			PrintOutputMap();
			PrintNodeData(current_node);
			// Print weights:
			WriteOutputMap(current_node->posx, current_node->posy, current_node->weight);
			WriteFinalMap(current_node->posx, current_node->posy, WeightToMapCode(current_node->weight));
		#endif

		// NodeData saved to NodeMap, so we can discard the list element struct:
		DestroyListElement(current_node_element);

		#ifdef ANALYTIC_VARIANT
			if (IsGoalReached()) {			// hacky assumption that there is only one path cell adjacent to the goal
				final_node = current_node;
				SetGoalReached(FALSE);
			}
		#else
			final_node = current_node;
			if (IsGoalReached()) { break; }	// exit once goal reached (heuristic approach)
		#endif // !ANALYTIC_VARIANT

		nodes_evaluated_count++;
	}
	node_queue_time = GetCurrentClockTime() - node_queue_time;


	/*
		Determine Shortest Path
	*/
	shortest_path_time = GetCurrentClockTime();
	// Note: if goal has not been reached, final_node_ele will be NULL.
	NodeData* next_node = final_node;
	final_path_length = PopulateFinalQueue(final_node);
	shortest_path_time = GetCurrentClockTime() - shortest_path_time;


	/*
		Print Debug Info
	*/
	#ifdef DEBUG
		// Process final output from FinalQueue to FinalMap
		ListElement* current_node_element = GetListHead(GetFinalQueue());
		while (IsElementValid(current_node_element))
		{
			NodeData* current_node = current_node_element->node;

			WriteFinalMap(GetNodeDataPosX(current_node), GetNodeDataPosY(current_node), WALKED_PATH);
			WriteOutputMap(GetNodeDataPosX(current_node), GetNodeDataPosY(current_node), WALKED_PATH);

			current_node_element = current_node_element->tail;
		}

		PrintOutputMap();
		PrintFinalMap();
		CreateFinalMap();
	#endif // DEBUG


	/*
		Generate Direction Queue
	*/
	direction_queue_time = GetCurrentClockTime();
	GenerateDirectionQueue();
	direction_queue_time = GetCurrentClockTime() - direction_queue_time;


	/*
		Performance Overview
	*/
	total_time = GetCurrentClockTime() - total_time;	// note that total_time is bloated by debug and timing overhead

	printf("SHORTEST PATH FROM START (%d, %d) TO GOAL (%d, %d):\n\n", GetStartPosX(), GetStartPosY(), GetGoalPosX(), GetGoalPosY());

	printf("Total number of nodes evaluated: %d\n", nodes_evaluated_count);
	printf("Length of final path: %d\n", final_path_length);
	printf("\n");
	printf("Total time to find shortest path and directions: %ds %dms\n", ConvertToMilliSeconds(total_time, time_error)/1000, ConvertToMilliSeconds(total_time, time_error)%1000);
	printf("\n");
	printf("Time in search algorithm (NodeQueue): %ds %dms\n", ConvertToMilliSeconds(node_queue_time, time_error) / 1000, ConvertToMilliSeconds(node_queue_time, time_error) % 1000);
	printf("Time in shortest path solver (FinalQueue): %ds %dms\n", ConvertToMilliSeconds(shortest_path_time, time_error) / 1000, ConvertToMilliSeconds(shortest_path_time, time_error) % 1000);
	printf("Time to generate DirectionQueue: %ds %dms\n", ConvertToMilliSeconds(direction_queue_time, time_error) / 1000, ConvertToMilliSeconds(direction_queue_time, time_error) % 1000);
	printf("\n");


	/*
		Cleanup
	*/
	CleanUpFindShortestPath(); // prevent memory leaks and reset important parameters

	return;
}

int PopulateFinalQueue(NodeData* final_node) {
	int final_path_length = 0;
	NodeData* next_node = final_node;

	// Trace back to the start node from the goal node and log in FinalQueue.
	// Ends once there are no more valid preceding/instigating nodes
	// (i.e. at start).

	// Artificially create goal node and add to FinalQueue
	EvaluatePathCell(NULL, GetGoalPosX(), GetGoalPosY());
	AddToFinalQueue(NodeMapGet(NodeMapGenKey(GetGoalPosX(), GetGoalPosY())));
	final_path_length++;

	while (!IsStartReached(next_node))
	{
		AddToFinalQueue(next_node);
		next_node = FindNextNodeInFinalPath(next_node);
		final_path_length++;
	}

	// Artificially add start node to FinalQueue
	AddToFinalQueue(NodeMapGet(NodeMapGenKey(GetStartPosX(), GetStartPosY())));
	final_path_length++;

	return final_path_length;
}

void GenerateDirectionQueue()
{
	// At least three nodes must be present in a path for it not to be a straight line.
	// Thus a minimum of three nodes are required to calculate a new direction.
	//if (!IsElementValid(GetListHead(GetFinalQueue()))) { return; }	// if we are using ANALYTIC_VARIANT
	ListElement* next = GetListHead(GetFinalQueue())->tail;
	ListElement* current = GetListHead(GetFinalQueue());
	ListElement* prev = NULL;
	

	while (IsElementValid(next->tail)) {
		prev = current;
		current = next;
		next = next->tail;

		if (GetNodeDataAdjacentPaths(current->node) > 2) { AddDirection(prev->node, current->node, next->node); } // only find for intersection nodes (where there must be more than 2 prev/next nodes)
	}
	DirectionQueueGenerationFinished(); // all directions for this path generated so must call this

	PrintDirectionQueue();

	/*
		From start of FinalQueue to end, iterate through.
		To find the directions for an intersection we must use relative positioning.
			- directions must be relative to the robot's current 'forward' vector.

		Thus the forward vector of the robot is:
			fwd_delta_x = (current_x - last_x): =0 if parallel, >0 if right, <0 if left.
			fwd_delta_y = (current_y - last_y): =0 if parallel, >0 if down, <0 if up.
			[global left: -x, global right: +x, global up: -y, global down: -y]
			The robot must be travelling orthogonally, so no diagonals: !(up&&down) && !(left&&right).

		We perform similar logic on (current_pos - next_pos) to find the direction to take.
		
		We can then find the direction to take relative to the forward vector.
	*/
}


#endif