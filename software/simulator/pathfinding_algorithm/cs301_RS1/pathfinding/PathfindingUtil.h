#ifndef PATHFINDING_UTIL_H
#define PATHFINDING_UTIL_H

#include "NodeData/NodeList.h"

#include "NodeData/NodeData.h"	// only required in PathfindingUtil.c, but added for convenience of the typedef

#include "NodeData/NodeMap.h"

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

#ifndef TRUE
	#define TRUE	1
#endif
#ifndef FALSE
	#define FALSE	0
#endif


typedef enum CellType {EMPTY, PATH, GOAL} CellType;

/* IsChecked */
int IsCheckedNode(int posx, int posy);

/* Goal Cell */
void SetGoalPos(int posx, int posy);
int GetGoalPosX();
int GetGoalPosY();
int IsGoalReached();
void SetGoalReached(int is_reached);

/* Start Cell */
void SetStartPos(int posx, int posy);
int GetStartPosX();
int GetStartPosY();
int IsStartReached(const NodeData* node);

/* Pathfinding Algorithm Functions */

// Return a reference to the NodeQueue list.
NodeList* GetNodeQueue();

// Classify and return the CellType of the cell at the given coords.
CellType GetCellType(int posx, int posy);

// Used to discover and evaluate new cells.
// Called on a node to evaluate all orthogonally adjacent cells (within map bounds).
void EvaluateAdjacentCells(NodeData* instigating_node);

// Evaluate a newly discovered cell at the given coordinates.
// Controls the flow of evaluation depending on the CellType (empty, path, goal).
void EvaluateCell(NodeData* instigating_node, int posx, int posy);

// Called by EvaluateCell() if the newly discovered cell has the CellType PATH.
// If the path cell is new a node should be created to represent it, and sent to
// the NodeQueue for the pathfinding algorithm to handle.
// If the path cell is preexisting then we have found an alternate path to it, and
// should link the preexisting node to the instigating node that was adjacent to it.
void EvaluatePathCell(NodeData* instigating_node, int posx, int posy);

// Populate NodeData contextually. Uses PathfindingAlgorithm functions for calculating
// weight.
NodeData* PopulateNodeData(const NodeData* instigating_node, NodeData* node, int posx, int posy, int isChecked);



/* Pathfinding Algorithm Functions */

// Insert a node in the NodeQueue. Wrapper for functionality in PathfindingAlgorithm.
void AddToNodeQueue(const NodeData* node);

// Detach the NodeListElement from the top of the NodeQueue, and return it.
NodeListElement* ExtractNextInNodeQueue();

// Returns true if no NodeListElements left in NodeQueue.
int IsNodeQueueEmpty();

// Return a reference to the FinalQueue.
NodeList* GetFinalQueue();

// Insert a node element in the final Queue.
void AddToFinalQueue(const NodeData* node);

NodeListElement* ExtractNextInFinalQueue();

// Returns true if no NodeListElements left in FinalQueue.
int IsFinalQueueEmpty();

// Debug function to visualize nodeData contents
void PrintNodeData(const NodeData* n);

// Debug function to visualize a node list element and its linked elements
// Unfinished
//void PrintNodeListElement(NodeListElement* e);

#endif // !PATHFINDING_UTIL_H
