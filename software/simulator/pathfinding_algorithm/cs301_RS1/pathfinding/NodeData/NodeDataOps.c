#ifndef NODEDATAOPS_C
#define NODEDATAOPS_C

#include "NodeDataOps.h"


int GetNodeDataPosX(struct NodeData* data)
{
	return data->posx;
}
int GetNodeDataPosY(struct NodeData* data)
{
	return data->posy;
}
int GetNodeDataAdjacentPaths(struct NodeData* data)
{
	return data->num_adjacent_paths;
}
int GetNodeDataWeight(struct NodeData* data)
{
	return data->weight;
}


void SetNodeDataPosX(struct NodeData* data, int pos_x)
{
	data->posx = pos_x;
}
void SetNodeDataPosY(struct NodeData* data, int pos_y)
{
	data->posy = pos_y;
}
void SetNodeDataAdjacentPaths(struct NodeData* data, int adj_paths)
{
	data->num_adjacent_paths = adj_paths;
}
void SetNodeDataWeight(struct NodeData* data, int weight)
{
	data->weight = weight;
}
void AddToNodeDataAdjacentNodeList(struct NodeData* data, struct SLListElement* node_to_add)
{
	// If the list is empty...
	if (!IsNodeListElementValid(data->adjacent_node_list)) {
		data->adjacent_node_list = NewNodeListElement(node_to_add);
		return;
	}

	// Otherwise add a new node, if it is unique...
	struct NodeListElement* current_node_list = data->adjacent_node_list;

	while (IsNodeListElementValid(current_node_list)) {
		if (current_node_list->node == node_to_add) { return; }				// ignore if node already present
		if (!IsNodeListElementValid(current_node_list->tail)) { break; }	// exit loop early if at end of the NodeList
		current_node_list = current_node_list->tail;
	}

	AppendToNodeListElement(current_node_list, NewNodeListElement(node_to_add));
}


#endif // !NODEDATAOPS_C
