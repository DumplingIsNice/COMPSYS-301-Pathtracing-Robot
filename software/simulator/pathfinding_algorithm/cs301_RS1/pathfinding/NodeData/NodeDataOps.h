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

int GetNodeDataPosX(NodeData* node);
int GetNodeDataPosY(NodeData* node);
int GetNodeDataAdjacentPaths(NodeData* node);
int GetNodeDataWeight(NodeData* node);

void SetNodeDataPosX(NodeData* node, int pos_x);
void SetNodeDataPosY(NodeData* node, int pos_y);
void SetNodeDataAdjacentPaths(NodeData* node, int adj_paths);
void SetNodeDataWeight(NodeData* node, int weight);
void AddToNodeDataAdjacentNode(NodeData* node, NodeData* node_to_add);


#endif // !NODEDATA_H
