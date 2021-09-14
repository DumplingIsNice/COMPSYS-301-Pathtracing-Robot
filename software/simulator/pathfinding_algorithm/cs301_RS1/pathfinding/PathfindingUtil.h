#ifndef PATHFINDING_UTIL_H
#define PATHFINDING_UTIL_H

#include "SLList/sllist.h"

/*
	Pathfinding Util

	Pathfinding functions with functionality independent from the
	current algorithm.


	Pseudo code:
		EvaluateCell(start_posx, start_posy);			// create the starting node

		while(!IsNodeQueueEmpty())
		{
			current_node = ExtractNextInNodeQueue();
			EvaluateAdjacentCells(..current_node posx and posy...);
			
			if (IsGoalReached()) {
				break;
			}
		}

		CompileShortestPath();
		// Last processed node (tail of ProcessedNodeQueue) is the cell that reached the goal cell.
		// Work backwards from there, through ProcessedNodeQueue, until there is a path from start
		// to goal.
*/

#ifndef MAP_SIZE_X
	#define MAP_SIZE_X	10	// This should be overridden by the actual map size!
#endif
#ifndef MAP_SIZE_Y
	#define MAP_SIZE_Y	10
#endif

#ifndef TRUE
	#define TRUE	1
#endif
#ifndef FALSE
	#define FALSE	0
#endif


enum CellType {EMPTY, PATH, GOAL};



/* IsPosChecked */

int IsPosXChecked(int posx);
int IsPosYChecked(int posy);
void SetPosXChecked(int posx, int is_checked);
void SetPosYChecked(int posy, int is_checked);

int IsCheckedNode(int posx, int posy);


/* Goal Cell */

int GetGoalPosX();
int GetGoalPosY();
int IsGoalReached();
void SetGoalReached(int is_reached);


/* Pathfinding Algorithm Functions */

// Call EvaluateCell() on all orthogonally adjacent cells within bounds.
void EvaluateAdjacentCells(int posx, int posy, struct SLListElement* instigating_node);

// Return the cell type, using the map and goal cell.
enum CellType GetCellType(int posx, int posy);

// Assign the cell to be further evaluated depending on the cell type.
// Call this on each new cell.
void EvaluateCell(int posx, int posy, struct SLListElement* instigating_node);

// Check if the node has been checked before, and if it hasn't add it to
// the NodeQueue (to be processed).
void EvaluatePathNode(int posx, int posy, struct SLListElement* instigating_node);

// Wrapper for algorithm-specific functionality in Pathfinding.h 
void AddToNodeQueue(int posx, int posy, struct SLListElement* instigating_node);

// Remove the head node from NodeQueue, append it to ProcessedNodeQueue,
// and return the node, ready to process.
struct SLListElement* ExtractNextInNodeQueue();

// Returns true if there are no elements in the NodeQueue.
int IsNodeQueueEmpty();


#endif // !PATHFINDING_UTIL_H
