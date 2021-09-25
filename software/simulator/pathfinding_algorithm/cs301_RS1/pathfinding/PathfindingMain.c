#ifndef PATHFINDINGMAIN_C
#define PATHFINDINGMAIN_C

#include "PathfindingMain.h"

#include <stdio.h>
#include "FileUtility/ReadMap.h"
#include "PathfindingUtil.h"
#include "NodeData/NodeDataOps.h"
#include "NodeData/NodeMap.h"



void FindShortestPath()
{
	// Read map and set up goal location:
	ReadMapFile(MAP_NAME);
	SetGoalPos(GOAL_X, GOAL_Y);

	// Create the starting node and add it to NodeQueue:
	EvaluateCell(NULL, START_X, START_Y);
	

	// Evaluate until goal reached:
	NodeListElement* current_node_element	= NULL;
	NodeData*		 final_node				= NULL;

	while (!IsNodeQueueEmpty())
	{
		current_node_element = ExtractNextInNodeQueue();
		EvaluateAdjacentCells(current_node_element->node);
		final_node = current_node_element->node;

		// NodeData saved to NodeMap, so we can discard the list element struct:
		DestroyListElement(current_node_element);

		if (IsGoalReached()) {
			break;
		}
	}


	// Determine shortest path:
	// Note: if goal has not been reached, final_node_ele will be NULL.
	NodeData* current_node = final_node;

	while (IsNodeDataValid(current_node))
	{
		// Note:
		// Should print the location of each node.
		// GetNodeDataAdjacentNode will only give the first adjacent node
		// (i.e. instigating node).
		// @TODO: Replace this with weight-based preference
		current_node = GetNodeDataAdjacentNode(current_node);
	}

	// Ends once there are no more valid preceding/instigating nodes
	// (i.e. at start).

	// Prevent memory leaks:
	CleanUpFindShortestPath();
	return;
}


void CleanUpFindShortestPath()
{
	// @TODO:
	// Add a counter that sums sizeof() values for RAM-usage evaluation?

	// Free the last of the NodeQueue elements (but not their NodeData!):
	DestroyListElements(GetNodeQueue());
	// Free all NodeData values:
	NodeMapClear();
}


#endif