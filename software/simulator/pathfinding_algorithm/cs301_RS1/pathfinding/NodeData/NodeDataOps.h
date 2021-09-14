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

int GetNodeDataPosX(struct NodeData* data);
int GetNodeDataPosY(struct NodeData* data);
int GetNodeDataAdjacentPaths(struct NodeData* data);
int GetNodeDataWeight(struct NodeData* data);

void SetNodeDataPosX(struct NodeData* data, int pos_x);
void SetNodeDataPosY(struct NodeData* data, int pos_y);
void SetNodeDataAdjacentPaths(struct NodeData* data, int adj_paths);
void SetNodeDataWeight(struct NodeData* data, int weight);
void AddToNodeDataAdjacentNodeList(struct NodeData* data, struct SLListElement* node_to_add);




#endif // !NODEDATA_H
