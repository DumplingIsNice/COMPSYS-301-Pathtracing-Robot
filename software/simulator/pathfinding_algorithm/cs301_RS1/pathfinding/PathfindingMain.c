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


void SetMapParameters(int goal_x, int goal_y, int start_x, int start_y)
{
	SetGoalPos(goal_x, goal_y);
	SetStartPos(start_x, start_y);
}

void CleanUpFindShortestPath()
{
	// @TODO:
	// Add a counter that sums sizeof() values for RAM-usage evaluation?

	// Free the last of the NodeQueue elements (but not their NodeData!):
	DestroyListElements(GetNodeQueue());

	// Free the FinalQueue elements.
	DestroyListElements(GetFinalQueue());

	// Free all NodeData values:
	NodeMapClear();

	// Free all direction queue:
	DestroyDirectionQueueAndContents();
}

void FindShortestPathTest()
{
	FindShortestPath(GOAL_X, GOAL_Y, START_X, START_Y);
}

void FindShortestPath(int goal_x, int goal_y, int start_x, int start_y)
{
	// Read map and set up goal location:
	ReadMapFile(MAP_NAME);
	SetMapParameters(goal_x, goal_y, start_x, start_y);

	// Create the starting node and add it to NodeQueue:
	EvaluateCell(NULL, GetStartPosX(), GetStartPosY());
	
	// Performance counters:
	int nodes_evaluated_count	= 0;
	int final_path_length		= 0;

	// Evaluate nodes from NodeQueue (populated by EvaluateAdjacentCells) 
	// until goal is reached:
	NodeListElement*	current_node_element	= NULL;
	NodeData* current_node = NULL;
	NodeData* final_node = NULL;

	/*
		Evaluate Nodes
	*/
	while (!IsNodeQueueEmpty())
	{
		current_node_element = ExtractNextInNodeQueue();
		EvaluateAdjacentCells(current_node_element->node);
		current_node = current_node_element->node;

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

	/*
		Determine Shortest Path
	*/
	// Note: if goal has not been reached, final_node_ele will be NULL.
	NodeData* next_node = final_node;
	final_path_length = PopulateFinalQueue(final_node);

	/*
		Print Debug Info
	*/
	#ifdef DEBUG
		// Process final output from FinalQueue to FinalMap
		while (!IsFinalQueueEmpty())
		{
			current_node_element = ExtractNextInFinalQueue();
			current_node = current_node_element->node;

			WriteFinalMap(GetNodeDataPosX(current_node), GetNodeDataPosY(current_node), WALKED_PATH);

			WriteOutputMap(GetNodeDataPosX(current_node), GetNodeDataPosY(current_node), WALKED_PATH);
		}

		PrintOutputMap();
		PrintFinalMap();
		CreateFinalMap();
	#endif // DEBUG

	/*
		Performance Overview
	*/
	printf("Total number of nodes evaluated: %d\n", nodes_evaluated_count);
	printf("Length of final path: %d\n", final_path_length);
	printf("\n");
	printf("Time to find shortest path: %d\n", 0);
	printf("RAM used by NodeQueue and NodeMap: %d\n", 0);

	/*
		Cleanup
	*/
	CleanUpFindShortestPath(); // prevent memory leaks

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
	NodeListElement* next = GetListHead(GetFinalQueue())->tail;
	NodeListElement* current = GetListHead(GetFinalQueue());
	NodeListElement* prev = NULL;
	

	while (IsElementValid(next->tail)) {
		prev = current;
		current = next;
		next = next->tail;

		AddDirection(prev, current, next);
	}

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
		Must use LUT/switch case to decode, since there is no immediately apparent easy
		way to derive relative direction from coords (I don't think vectors will work here).
	*/
}


#endif