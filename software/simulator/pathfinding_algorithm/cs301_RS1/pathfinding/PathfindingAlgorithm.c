#ifndef PATHFINDING_ALGORITHM_C
#define PATHFINDING_ALGORITHM_C

#include "PathfindingAlgorithm.h"

#include "NodeData/NodeDataOps.h"


void InsertInNodeQueue(struct SLList* NodeQueue, struct SLListElement* node)
{
	// Breadth-first (as adding each new node to top)
	PrependToSLList(&NodeQueue, node);
}

// @TODO!
int CalculateNodeWeight(struct SLListElement* node)
{
	return 0;
}

// @TODO!
void CompileShortestPath()
{
	;
}


#endif // !PATHFINDING_ALGORITHM_C