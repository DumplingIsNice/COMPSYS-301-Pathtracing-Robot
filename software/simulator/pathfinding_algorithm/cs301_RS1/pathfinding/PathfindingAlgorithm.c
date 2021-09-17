#ifndef PATHFINDING_ALGORITHM_C
#define PATHFINDING_ALGORITHM_C

#include "PathfindingAlgorithm.h"

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
int CalculateNodeWeight(NodeData* instigating_node)
{
	return 0;
}

// @TODO!
void CompileShortestPath()
{
	;
}


#endif // !PATHFINDING_ALGORITHM_C