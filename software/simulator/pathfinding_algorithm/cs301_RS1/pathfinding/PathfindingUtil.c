#ifndef PATHFINDING_UTIL_C
#define PATHFINDING_UTIL_C

#include "PathfindingUtil.h"

#include "stdio.h"
#include "PathfindingAlgorithm.h"
#include "NodeData/NodeDataOps.h"

// 'Private' variables
static int PosXCheckedArray[MAP_SIZE_X] = { 0 };
static int PosYCheckedArray[MAP_SIZE_Y] = { 0 };
static struct SLList NodeQueue = { .tail = NULL };	// initialise .data to {0}
static struct SLList ProcessedNodeQueue = { .tail = NULL };	// initialise .data to {0}
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
void EvaluateAdjacentCells(int posx, int posy)
{
	// (x+-1,y) and (x,y+-1)
	if (posx + 1 <= MAP_SIZE_X) {	EvaluateCell(posx + 1, posy); }
	if (posx - 1 >= 0) {			EvaluateCell(posx - 1, posy); }
	if (posy + 1 <= MAP_SIZE_Y) {	EvaluateCell(posx, posy + 1); }
	if (posy - 1 >= 0) {			EvaluateCell(posx, posy - 1); }
}
// @TODO
enum CellType GetCellType(int posx, int posy)
{
	if (posx == GetGoalPosX()) {
		if (posy == GetGoalPosY()) {
			return GOAL;
		}
	} else if (1 == 1) {	// if map[posx][poxy] == 1
		return PATH;
	} else {
		return EMPTY;
	}
}

void EvaluateCell(int posx, int posy)
{
	enum CellType cell_type = GetCellType(posx, posy);
	
	switch (cell_type) {
		case PATH:			EvaluatePathNode(posx, posy);
		case GOAL:			SetGoalReached(TRUE);
		default:			return;
	}
}

void EvaluatePathNode(int posx, int posy)
{
	if (IsCheckedNode(posx, posy)) { return; }
	SetPosXChecked(posx, TRUE);
	SetPosYChecked(posy, TRUE);

	AddToNodeQueue(posx, posy);
}

struct SLListElement* ExtractNextInNodeQueue()
{
	struct SLListElement* node = RemoveHeadInSLList(&NodeQueue);
	AppendToSLList(&ProcessedNodeQueue, node);
	return node;
}

int IsNodeQueueEmpty()
{
	return IsSLListElementValid(GetHeadInSLList(&NodeQueue));
}

void AddToNodeQueue(int posx, int posy)
{
	struct SLListElement* node = NewSLListElement();
	SetNodeDataPosX(node->data, posx);
	SetNodeDataPosY(node->data, posy);
	SetNodeDataWeight(node->data, CalculateNodeWeight(node));	// must come after posx and posy added to node
	//SetNodeDataAdjacentPaths(node->data, ...);

	InsertInNodeQueue(&NodeQueue, posx, posy); // <--- ACTUAL FUNCTIONALITY IN PATHFINDING.H
}


#endif // !PATHFINDING_UTIL_C