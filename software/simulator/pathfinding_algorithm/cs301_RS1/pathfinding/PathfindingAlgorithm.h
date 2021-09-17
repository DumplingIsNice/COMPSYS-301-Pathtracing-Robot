#ifndef PATHFINDING_ALGORITHM_H
#define PATHFINDING_ALGORITHM_H

/*
	Pathfinding Algorithm

	Algorithm specific functionality for pathfinding algorithms.
	This file, not PathfindingUtil.h/c, should be modified for
	implementation of and changes in pathfinding algorithms.

	TODO:
	- handle alternate paths
		- how can we correlate two nodes without causing circular dependencies? can weights prevent this?
	- weighting calculations and InsertInNodeQueue() sorting
		- needed for A* etc

	- deleting leaf branches
	- deleting/free()-ing old nodes, and clearing lists!
	- compile the shortest path!

	- optimise NodeData by splitting words and minimising memory use
*/

// Add a NodeListElement to the NodeQueue.
// The insertion position in the NodeQueue depends on the algorithm.
void InsertInNodeQueue(struct NodeList* NodeQueue, struct NodeListElement* element);

// Used for weight-based algorithms (A*, Dijkstra).
int CalculateNodeWeight(struct NodeData* instigating_node);

// Calculate the shortest path given the start and goal cells, and
// a list of all searched nodes containing the path(s) between them.
void CompileShortestPath();

#endif // !PATHFINDING_ALGORITHM_H
