#ifndef PATHFINDING_ALGORITHM_C
#define PATHFINDING_ALGORITHM_C

#include "PathfindingAlgorithm.h"

#include <stdlib.h>	// for abs()
#include "NodeData/NodeList.h"
#include "NodeData/NodeDataOps.h"


void InsertInNodeQueue(NodeList* NodeQueue, NodeListElement* element)
{
	// Depth-first:
	PrependToList(NodeQueue, element);

	// Breadth-first:
	//AppendToList(NodeQueue, element);

	// A*/Dijkstra:
	// Insert in list, sorted from lowest weight to highest weight.
}

// @TODO!
int CalculateNodeWeight(NodeData* instigating_node, NodeData* node, int goal_x, int goal_y)
{
	int h = 0;
	int g = 1;

	// Heuristic (A* only):
	h = abs(goal_x - GetNodeDataPosX(node)) + abs(goal_y - GetNodeDataPosY(node));

	// Analytic:
	if (IsNodeDataValid(instigating_node)) {
		g = GetNodeDataWeight(instigating_node);
	} // else default to g = 1 (for starting node)

	return h + g;
}

// @TODO!
void CompileShortestPath()
{
	;
}


#endif // !PATHFINDING_ALGORITHM_C