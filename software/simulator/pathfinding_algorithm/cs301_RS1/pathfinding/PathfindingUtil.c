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
static int PosXCheckedArray[MAP_SIZE_X] = { 0 };	// @TO REMOVE
static int PosYCheckedArray[MAP_SIZE_Y] = { 0 };	// @TO REMOVE
static NodeList NodeQueue = { .tail = NULL };		// initialise .data to {0}
static int GoalReached = FALSE;


/* IsPosChecked */
int IsPosXChecked(int posx)
{
	return PosXCheckedArray[posx];
}
int IsPosYChecked(int posy)
{
	return PosYCheckedArray[posy];
}
void SetPosXChecked(int posx, int is_checked)
{
	PosXCheckedArray[posx] = is_checked;
}
void SetPosYChecked(int posy, int is_checked)
{
	PosYCheckedArray[posy] = is_checked;
}

int IsCheckedNode(int posx, int posy)
{
	if (IsPosXChecked(posx) && IsPosYChecked(posy)) { return TRUE; }
	return FALSE;
}


/* Goal Cell */
// @TODO
int GetGoalPosX()
{
	return 0; // return pos_x of target cell
}
// @TODO
int GetGoalPosY()
{
	return 0; // return pos_y of target cell
}

int IsGoalReached()
{
	return GoalReached;
}

void SetGoalReached(int is_reached)
{
	GoalReached = is_reached;
}



/* Pathfinding Algorithm Functions */

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

	if (posx + 1 < MAP_SIZE_X)	{ EvaluateCell(instigating_node, posx + 1, posy); }
	if (posx - 1 >= 0)			{ EvaluateCell(instigating_node, posx - 1, posy); }
	if (posy + 1 < MAP_SIZE_Y)	{ EvaluateCell(instigating_node, posx, posy + 1); }
	if (posy - 1 >= 0)			{ EvaluateCell(instigating_node, posx, posy - 1); }
}

void EvaluateCell(NodeData* instigating_node, int posx, int posy)
{
	CellType cell_type = GetCellType(posx, posy);
	switch (cell_type)
	{
	case PATH:	EvaluatePathCell(instigating_node, posx, posy);
	case GOAL:	SetGoalReached(TRUE);
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
		SetPosXChecked(posx, TRUE);
		SetPosYChecked(posy, TRUE);

		NodeData* new_node = NewNodeData();
		PopulateNodeData(instigating_node, new_node, posx, posy);
		AddToNodeQueue(new_node);
		return;
	} else {
		// We have found a new path to an already discovered node...
		// Link the preexisting node to the instigating node.
		// 
		//NodeData* preexisting = GetNodeFromCoords(posx, posy);
		//AddToNodeDataAdjacentNode(preexisting, instigating_node);
		// DESIGN CHOICE: singly or doubly linked? Currently only singly.
		// 
		// todo: when changing if statement, save lookup result for reuse here ^	
		return;
	}
}

NodeData* PopulateNodeData(NodeData* instigating_node, NodeData* node, int posx, int posy)
{
	SetNodeDataPosX(node, posx);
	SetNodeDataPosY(node, posy);
	SetNodeDataWeight(node, CalculateNodeWeight(instigating_node));
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


#endif // !PATHFINDING_UTIL_C