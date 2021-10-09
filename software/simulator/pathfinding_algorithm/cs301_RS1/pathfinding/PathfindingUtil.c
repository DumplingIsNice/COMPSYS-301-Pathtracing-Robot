#ifndef PATHFINDING_UTIL_C
#define PATHFINDING_UTIL_C

#include "PathfindingUtil.h"

#include "stdio.h"
#include "NodeData/List.h"
#include "PathfindingAlgorithm.h"
#include "NodeData/NodeDataOps.h"
#include "FileUtility/ReadMap.h"
#include "RebaseWeights.h"
#include "PathfindingMain.h"

#ifndef MAP_SIZE_X				// This should be overridden by ReadMap.h!
	#define MAP_SIZE_X	0
#endif
#ifndef MAP_SIZE_Y
	#define MAP_SIZE_Y	0
#endif

// 'Private' variables
//static int PosXCheckedArray[MAP_SIZE_X] = { 0 };	// @TO REMOVE // Hao: replaced with NodeMap
//static int PosYCheckedArray[MAP_SIZE_Y] = { 0 };	// @TO REMOVE // Hao: replaced with NodeMap
static List NodeQueue = { .head = NULL, .tail = NULL };		// initialise .data to {0}
static List FinalQueue = { .head = NULL, .tail = NULL };

static int goal_x, goal_y, start_x, start_y;
static int goal_reached = FALSE;


/* Node Checked */
int IsCheckedNode(int posx, int posy)
{
	const NodeData* node = NodeMapGet(NodeMapGenKey(posx, posy));
	if (!IsNodeDataValid(node)) { return FALSE; }
	else {
		if (GetNodeDataIsChecked(node)) { return TRUE; }
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

/* Start Cell */
void SetStartPos(int posx, int posy)
{
	start_x = posx;
	start_y = posy;
}
int GetStartPosX()
{
	return start_x; // return pos_x of target cell
}
// @For now, keep every input value as defined in ReadMap.h
int GetStartPosY()
{
	return start_y; // return pos_y of target cell
}

int IsStartReached(const NodeData* node)
{
	if ((GetNodeDataPosX(node) == GetStartPosX()) && (GetNodeDataPosY(node) == GetStartPosY()))
	{
		return TRUE;
	}
	return FALSE;
}

/* Pathfinding Algorithm Functions */

List* GetNodeQueue()
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

	if (posx - 1 >= 0)			{ EvaluateCell(instigating_node, posx - 1, posy); }	// left
	if (posy - 1 >= 0)			{ EvaluateCell(instigating_node, posx, posy - 1); }	// up
	if (posy + 1 < MAP_SIZE_Y)	{ EvaluateCell(instigating_node, posx, posy + 1); }	// down
	if (posx + 1 < MAP_SIZE_X)	{ EvaluateCell(instigating_node, posx + 1, posy); }	// right
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
		// We have discovered a path to an already discovered node...
		// Link the preexisting (adjacent) node to the instigating node.
		// AddToNodeDataAdjacentNode() will reject non-unique values, so
		// calling this on the node that led to the instigating node is not
		// optimised but will not break anything.

		#ifdef DEBUG
				printf("Found Checked Node!\n");
		#endif

		NodeData* preexisting = NodeMapGet(NodeMapGenKey(posx, posy));
		if (preexisting == NULL) { return; }
		AddToNodeDataAdjacentNode(instigating_node, preexisting);
		
		#ifdef WEIGHT_REBASING
			StartRebase(preexisting, instigating_node);
		#endif

		return;
	}
}

NodeData* PopulateNodeData(const NodeData* instigating_node, NodeData* node, int posx, int posy, int isChecked)
{
	SetNodeDataPosX(node, posx);
	SetNodeDataPosY(node, posy);
	SetNodeDataIsChecked(node, isChecked);
	SetNodeDataWeight(node, CalculateNodeWeight(instigating_node, node, GetGoalPosX(), GetGoalPosY()));
	AddToNodeDataAdjacentNode(node, instigating_node);
	return node;
}

void AddToNodeQueue(const NodeData* node)
{
	ListElement* element = NewListElement(node);
	InsertInNodeQueue(&NodeQueue, element);					// <--- ACTUAL FUNCTIONALITY IN PATHFINDING.H
}

ListElement* ExtractNextInNodeQueue()
{
	return RemoveListHead(&NodeQueue);
}

int IsNodeQueueEmpty()
{
	return !IsElementValid(GetListHead(&NodeQueue));
}

List* GetFinalQueue() {
	return &FinalQueue;
}

void AddToFinalQueue(const NodeData* node)
{
	ListElement* element = NewListElement(node);
	PrependToList(&FinalQueue, element);
}

ListElement* ExtractNextInFinalQueue()
{
	return RemoveListHead(&FinalQueue);
}

int IsFinalQueueEmpty()
{
	return !IsElementValid(GetListHead(&FinalQueue));
}

void PrintNodeData(const NodeData* n)
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