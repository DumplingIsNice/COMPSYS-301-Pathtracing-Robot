#ifndef PATHFINDING_UTIL_C
#define PATHFINDING_UTIL_C

#include "PathfindingUtil.h"

#include "stdio.h"
#include "PathfindingAlgorithm.h"
#include "NodeData/NodeDataOps.h"
#include "FileUtility/ReadMap.h"

#ifndef MAP_SIZE_X				// This should be overridden by ReadMap.h!
	#define MAP_SIZE_X	0
#endif
#ifndef MAP_SIZE_Y
	#define MAP_SIZE_Y	0
#endif

// 'Private' variables
//static int PosXCheckedArray[MAP_SIZE_X] = { 0 };	// @TO REMOVE // Hao: replaced with NodeMap
//static int PosYCheckedArray[MAP_SIZE_Y] = { 0 };	// @TO REMOVE // Hao: replaced with NodeMap
static NodeList NodeQueue = { .tail = NULL };		// initialise .data to {0}

static int goal_x, goal_y;
static int goal_reached = FALSE;


/* IsPosChecked */
int IsPosXChecked(NodeData* nodeData, int posx)
{
	return nodeData->isChecked;
}
void SetNodeChecked(NodeData* nodeData, int is_checked)
{
	nodeData->isChecked = is_checked;
}

int IsCheckedNode(int posx, int posy)
{
	NodeData* nodeData = NodeMapGet(NodeMapGenKey(posx, posy));
	if (nodeData == NULL) { return FALSE; }
	else {
		if (GetNodeDataIsChecked(nodeData)) { return TRUE; }
		return FALSE;
	}
}

/* Goal Cell */
// @For now, keep every input value as defined in ReadMap.h
void SetGoalPos(int posx, int posy)
{
	goal_x = posx;
	goal_y = posy;
}
int GetGoalPosX()
{
	return goal_x; // return pos_x of target cell
}
// @For now, keep every input value as defined in ReadMap.h
int GetGoalPosY()
{
	return goal_y; // return pos_y of target cell
}

int IsGoalReached()
{
	return goal_reached;
}

void SetGoalReached(int is_reached)
{
	goal_reached = is_reached;
}



/* Pathfinding Algorithm Functions */

NodeList* GetNodeQueue()
{
	return &NodeQueue;
}

// @TODO
CellType GetCellType(int posx, int posy)
{
	if (posx == GetGoalPosX()) {
		if (posy == GetGoalPosY()) {
			return GOAL;
		}
	}
	if (GetMapValue(posy, posx) == 0) {
		return PATH;
	}
	
	// Else...
	return EMPTY;
}

void EvaluateAdjacentCells(NodeData* instigating_node)
{
	int posx = GetNodeDataPosX(instigating_node);
	int posy = GetNodeDataPosY(instigating_node);

	if (posx - 1 >= 0)			{ EvaluateCell(instigating_node, posx - 1, posy); }	// up
	if (posy + 1 < MAP_SIZE_Y)	{ EvaluateCell(instigating_node, posx, posy + 1); }	// right
	if (posy - 1 >= 0)			{ EvaluateCell(instigating_node, posx, posy - 1); }	// left
	if (posx + 1 < MAP_SIZE_X)	{ EvaluateCell(instigating_node, posx + 1, posy); }	// down
}

void EvaluateCell(NodeData* instigating_node, int posx, int posy)
{
	CellType cell_type = GetCellType(posx, posy);
	switch (cell_type)
	{
	case PATH:	EvaluatePathCell(instigating_node, posx, posy);
		return;
	case GOAL:	SetGoalReached(TRUE);
		return;
	default:	return;
	}
}

// @TODO
void EvaluatePathCell(NodeData* instigating_node, int posx, int posy)
{
	// replace IsNodeChecked() with IsNodeValid(GetNodeFromCoords())
	if (!IsCheckedNode(posx, posy)) {
		// We have discovered a new node...
		// Create and populate the node, set its coords as checked, and
		// send it to the NodeQueue.
		NodeData* new_node = NewNodeData();
		PopulateNodeData(instigating_node, new_node, posx, posy, TRUE);
		AddToNodeDataAdjacentNode(instigating_node, new_node);
		AddToNodeQueue(new_node);
		NodeMapSet(NodeMapGenKey(posx, posy), new_node);
		return;
	} else {
		printf("Found Checked Node!\n");
		// We have found a new path to an already discovered node... 
			// # Hao: Not necessarly, currently we evaluate all directions which will evaluate a checked cell from where we came from
			// Best would be IsCheckedNode && !GetOutputMapValue()
		// Link the preexisting node to the instigating node.
		// 
		// NodeData* preexisting = GetNodeFromCoords(posx, posy);
		// AddToNodeDataAdjacentNode(preexisting, instigating_node);
		// DESIGN CHOICE: singly or doubly linked? Currently only singly.
		// 
		// todo: when changing if statement, save lookup result for reuse here ^	
		return;
	}
}

NodeData* PopulateNodeData(NodeData* instigating_node, NodeData* node, int posx, int posy, int isChecked)
{
	SetNodeDataPosX(node, posx);
	SetNodeDataPosY(node, posy);
	SetNodeChecked(node, isChecked);
	SetNodeDataWeight(node, CalculateNodeWeight(instigating_node, node, GetGoalPosX(), GetGoalPosY()));
	AddToNodeDataAdjacentNode(node, instigating_node);
	return node;
}

void AddToNodeQueue(NodeData* node)
{
	NodeListElement* element = NewNodeListElement(node);
	InsertInNodeQueue(&NodeQueue, element);					// <--- ACTUAL FUNCTIONALITY IN PATHFINDING.H
}

NodeListElement* ExtractNextInNodeQueue()
{
	return RemoveListHead(&NodeQueue);
}

int IsNodeQueueEmpty()
{
	return !IsElementValid(GetListHead(&NodeQueue));
}

void PrintNodeData(NodeData* n)
{
	printf("x: %d, y: %d, checked: %d, num_adjacent_paths: %d, weight: %d\n",
		GetNodeDataPosX(n), GetNodeDataPosY(n), GetNodeDataIsChecked(n),
		GetNodeDataAdjacentPaths(n), GetNodeDataWeight(n));
}

/* Unfinished */
//void PrintNodeListElement(NodeListElement* e)
//{
//    NodeListElement* current_node = e;
//    int i = 1;
//    while (IsElementValid(current_node->tail))
//    {
//        printf("%i th adjacent node.\n", i);
//        PrintNodeData(current_node->node);
//        current_node = current_node->tail;
//        i++;
//    }
//}

#endif // !PATHFINDING_UTIL_C