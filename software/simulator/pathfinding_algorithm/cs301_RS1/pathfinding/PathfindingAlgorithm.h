#ifndef PATHFINDING_ALGORITHM_H
#define PATHFINDING_ALGORITHM_H

/*
	Pathfinding Algorithm

	Algorithm specific functionality for pathfinding algorithms.
	This file, not PathfindingUtil.h/c, should be modified for
	implementation of and changes in pathfinding algorithms.

	TODO:
	- handle alternate paths
		- pass instigating node to other function calls? prevents checking the instigating node.
		- how can we correlate two nodes without causing circular dependencies? can weights prevent this?
	- weighting calculations and InsertInNodeQueue() sorting
		- needed for A* etc

	- deleting leaf branches
	- deleting/free()-ing old nodes, and clearing lists!
	- compile the shortest path!

	- optimise NodeData by splitting words and minimising memory use
*/

#include "SLList/sllist.h"

// Create and add a node to a NodeQueue.
// The insertion position in the NodeQueue depends on the algorithm.
void InsertInNodeQueue(struct SLList* NodeQueue, struct SLListElement* node);

// Used for weight-based algorithms (A*, Dijkstra)
int CalculateNodeWeight(struct SLListElement* node);

// Calculate the shortest path given the start and goal cells, and
// a list of all searched nodes containing the path(s) between them.
void CompileShortestPath();

#endif // !PATHFINDING_ALGORITHM_H
