#ifndef NODEDATAOPS_H
#define NODEDATAOPS_H

#include "NodeData.h"


/*
	Node Data Operations

	Provides all the getters and setters for the NodeData struct.
	This is a general API that acts as an interface to NodeData.

	NODEDATA SHOULD BY MODIFIED OR READ ONLY VIA NODEDATAOPS FUNCTIONS.
	DO NOT ACCESS EXPLICITLY!
*/

// Destroy NodeData and the NodeListElements in adjacent_nodes (but NOT their contents)
void DestroyNodeDataAndContents(NodeData* node);

int GetNodeDataPosX(const NodeData* node);
int GetNodeDataPosY(const NodeData* node);
int GetNodeDataIsChecked(const NodeData* node);
int GetNodeDataAdjacentPaths(const NodeData* node);
int GetNodeDataWeight(const NodeData* node);
struct ListElement* GetNodeDataAdjacentNodeListElement(const NodeData* node);

void SetNodeDataPosX(NodeData* node, int pos_x);
void SetNodeDataPosY(NodeData* node, int pos_y);
void SetNodeDataIsChecked(NodeData* node, int isChecked);
void SetNodeDataAdjacentPaths(NodeData* node, int adj_paths);
void IncrementNodeDataAdjacentpaths(NodeData* node);
void SetNodeDataWeight(NodeData* node, int weight);
void AddToNodeDataAdjacentNode(NodeData* node, const NodeData* node_to_add);

#endif // !NODEDATA_H
