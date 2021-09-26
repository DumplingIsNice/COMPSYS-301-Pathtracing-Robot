#ifndef PATHFINDINGMAIN_C
#define PATHFINDINGMAIN_C

#include "PathfindingMain.h"

#include <stdio.h>
#include "FileUtility/ReadMap.h"
#include "PathfindingAlgorithm.h"
#include "PathfindingUtil.h"
#include "NodeData/NodeDataOps.h"
#include "NodeData/NodeMap.h"

void FindShortestPath()
{
	// Read map and set up goal location:
	ReadMapFile(MAP_NAME);
	SetGoalPos(GOAL_X, GOAL_Y);
	SetStartPos(START_X, START_Y);

	// Create the starting node and add it to NodeQueue:
	EvaluateCell(NULL, START_X, START_Y);
	
	// Performance counters:
	int nodes_evaluated_count	= 0;
	int final_path_length		= 0;

	// Evaluate nodes from NodeQueue (populated by EvaluateAdjacentCells) 
	// until goal is reached:
	NodeListElement*	current_node_element	= NULL;
	NodeData*			current_node			= NULL;
	NodeData*			final_node				= NULL;

	/*
		Evaluate Nodes
	*/
	while (!IsNodeQueueEmpty())
	{
		current_node_element = ExtractNextInNodeQueue();
		EvaluateAdjacentCells(current_node_element->node);
		current_node = current_node_element->node;

		#ifdef DEBUG
			printf("### Iteration i: %d ###\n", i);
			WriteOutputMap(current_node->posx, current_node->posy, WALKED_PATH);
			//PrintNodeMap();
			PrintOutputMap();
			PrintNodeData(current_node);
		#endif

		#ifdef PRINT_WEIGHT
			WriteFinalMap(current_node->posx, current_node->posy, current_node->weight);
		#endif // PRINT_WEIGHT


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

	// Ends once there are no more valid preceding/instigating nodes
	// (i.e. at start).

	// Trace back to start with goal and log in FinalQueue

	// Artificially creates goal node and add to FinalQueue
	EvaluatePathCell(NULL, GetGoalPosX(), GetGoalPosY());
	AddToFinalQueue(NodeMapGet(NodeMapGenKey(GetGoalPosX(), GetGoalPosY())));

	// Trace NextNodeInFinalPath
	while (!IsStartReached(next_node))
	{
		AddToFinalQueue(next_node);
		next_node = FindNextNodeInFinalPath(next_node);
		final_path_length++;
	}

	// Artificially add start to FinalQueue
	AddToFinalQueue(NodeMapGet(NodeMapGenKey(GetStartPosX(), GetStartPosY())));

	// Process final output from FinalQueue to FinalMap
	while (!IsFinalQueueEmpty())
	{
		current_node_element = ExtractNextInFinalQueue();
		current_node = current_node_element->node;

		WriteFinalMap(GetNodeDataPosX(current_node), GetNodeDataPosY(current_node), WALKED_PATH);
	}

	/*
		Cleanup
	*/
	CleanUpFindShortestPath();	// prevent memory leaks

	/*
		Performance Overview
	*/
	printf("Total number of nodes evaluated: %d\n", nodes_evaluated_count);
	printf("Length of final path: %d\n", final_path_length);
	printf("\n");
	printf("Time to find shortest path: %d\n", 0);
	printf("RAM used by NodeQueue and NodeMap: %d\n", 0);

	return;
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
}

#endif