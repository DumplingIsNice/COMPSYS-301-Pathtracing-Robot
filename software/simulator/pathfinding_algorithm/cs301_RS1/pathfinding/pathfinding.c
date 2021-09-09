#ifndef PATHFINDING_C
#define PATHFINDING_C

#include "pathfinding.h"

// 'Private' variables
static int PosXCheckedArray[MAP_SIZE_X];
static int PosYCheckedArray[MAP_SIZE_Y];
static struct SLList NodeQueue;


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
void SetPoxYChecked(int posy, int is_checked)
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
// @TODO
void ReachedGoal()
{
	return;
	/*
		Once the goal cell is reached, stop searching and evaluate the
		shortest path.
	*/
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
		case GOAL:			ReachedGoal();
		default:			return;
	}
}

void EvaluatePathNode(int posx, int posy)
{
	if (IsCheckedNode(posx, posy)) { return; }
	AddToNodeQueue(posx, posy);
}

void AddToNodeQueue(int posx, int posy)
{
	; // create node list element and add to queue (depending on list element)
	// requires fields for NodeData. Use NodeDataOps API, and sllist!

}


#endif // !PATHFINDING_C