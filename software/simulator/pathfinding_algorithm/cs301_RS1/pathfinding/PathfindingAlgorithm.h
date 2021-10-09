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
void InsertInNodeQueue(struct List* NodeQueue, struct ListElement* element);

// Used for weight-based algorithms (A*, Dijkstra).
int CalculateNodeWeight(const struct NodeData* instigating_node, const struct NodeData* node, int goal_x, int goal_y);

// Return the most suitable NodeData from adjacent_nodes list.
struct NodeData* FindNextNodeInFinalPath(const struct NodeData* node);

#endif // !PATHFINDING_ALGORITHM_H
