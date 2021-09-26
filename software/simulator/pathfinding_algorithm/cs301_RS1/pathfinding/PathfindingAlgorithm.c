#ifndef PATHFINDING_ALGORITHM_C
#define PATHFINDING_ALGORITHM_C

#include "PathfindingAlgorithm.h"

#include <stdlib.h>	// for abs()
#include "NodeData/NodeList.h"
#include "NodeData/NodeDataOps.h"
#include "PathfindingMain.h"

/*
	DEPTH-FIRST
*/
#ifdef DEPTHFIRST
void InsertInNodeQueue(NodeList* NodeQueue, NodeListElement* element)
{
	PrependToList(NodeQueue, element);
}

int CalculateNodeWeight(NodeData* instigating_node, NodeData* node, int goal_x, int goal_y)
{
	int g = 1;

	// Analytic:
	if (IsNodeDataValid(instigating_node)) {
		g = GetNodeDataWeight(instigating_node) + 1;
	} // else default to g = 1 (for starting node)

	return g;
}

NodeData* FindNextNodeInFinalPath(NodeData* node)
{
	if (IsElementValid(GetNodeDataAdjacentNodeListElement(node))) {
		// Return the first NodeData in the list (the instigating node):
		return GetNodeDataAdjacentNodeListElement(node)->node;
	} else {
		return NULL;
	}
}
#endif	// DEPTHFIRST


/*
	BREADTH-FIRST
*/
#ifdef BREADTHFIRST
void InsertInNodeQueue(NodeList* NodeQueue, NodeListElement* element)
{
	AppendToList(NodeQueue, element);
}

int CalculateNodeWeight(NodeData* instigating_node, NodeData* node, int goal_x, int goal_y)
{
	int g = 1;

	// Analytic:
	if (IsNodeDataValid(instigating_node)) {
		g = GetNodeDataWeight(instigating_node) + 1;
	} // else default to g = 1 (for starting node)

	return g;
}

NodeData* FindNextNodeInFinalPath(NodeData* node)
{
	if (IsElementValid(GetNodeDataAdjacentNodeListElement(node))) {
		// Return the first NodeData in the list (the instigating node):
		return GetNodeDataAdjacentNodeListElement(node)->node;
	}
	else {
		return NULL;
	}
}
#endif // BREADTHFIRST


/*
	A*
*/
#ifdef ASTAR
void InsertInNodeQueue(NodeList* NodeQueue, NodeListElement* element)
{
	// A*/Dijkstra:
	// Insert in list, sorted from lowest weight to highest weight.
	NodeListElement* current_element = GetListHead(NodeQueue);
	NodeListElement* prev_element = NULL;

	// Protect start node case
	if (!IsElementValid(current_element))
	{
		PrependToList(GetNodeQueue(), element);
		return;
	}

	while (GetNodeDataWeight(element->node) > GetNodeDataWeight(current_element->node))
	{
		prev_element = current_element;
		if (!IsElementValid(current_element->tail)) { break; }	// End Case
		current_element = current_element->tail;
	}
	
	if (prev_element == NULL) {
		PrependToList(NodeQueue, element);
	} else {
		InsertInList(NodeQueue, prev_element, element);
	}

}

int CalculateNodeWeight(NodeData* instigating_node, NodeData* node, int goal_x, int goal_y)
{
	int h = 0;
	int g = 1;

	// Heuristic (A* only):
	h = abs(goal_x - GetNodeDataPosX(node)) + abs(goal_y - GetNodeDataPosY(node));

	// Analytic:
	if (IsNodeDataValid(instigating_node)) {
		g = GetNodeDataWeight(instigating_node) + 1;
	} // else default to g = 1 (for starting node)

	return h + g;
}

NodeData* FindNextNodeInFinalPath(NodeData* node)
{
	if (IsElementValid(GetNodeDataAdjacentNodeListElement(node))) {
		// Return the NodeData with the lowest weight in the list:
		NodeListElement* current_element = GetNodeDataAdjacentNodeListElement(node);
		NodeData* lowest_weight_node = current_element->node;

		while (IsElementValid(current_element)) {
			// NodeData field in the adjacent_nodes list should never be NULL (unless we've screwed up in adding or deleting).
			if (GetNodeDataWeight(current_element->node) < GetNodeDataWeight(lowest_weight_node)) {
				lowest_weight_node = current_element->node;
			}
			current_element = current_element->tail;
		}
		return lowest_weight_node;
	} else {
		return NULL;
	}
}
#endif // ASTAR


#endif // !PATHFINDING_ALGORITHM_C