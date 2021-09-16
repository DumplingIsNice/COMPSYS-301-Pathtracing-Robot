#ifndef NODEDATAOPS_C
#define NODEDATAOPS_C

#include "NodeDataOps.h"


int GetNodeDataPosX(struct NodeData* data)
{
	return data->posx;
	//return (data->pos) >> 16;
}
int GetNodeDataPosY(struct NodeData* data)
{
	return data->posy;
	//return (data->pos) & 0x00FF;
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
	//data->pos = data->pos & 0x00FF;
	//data->pos = data->pos | (pos_x << 16);
}
void SetNodeDataPosY(struct NodeData* data, int pos_y)
{
	data->posy = pos_y;
	//data->pos = data->pos & 0xFF00;
	//data->pos = data->pos | pos_y;
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
		data->adjacent_node_list = NewNodeListElementAndAssign(node_to_add);
		return;
	}

	// Otherwise add a new node, if it is unique...
	struct NodeListElement* current_node_list = data->adjacent_node_list;

	while (IsNodeListElementValid(current_node_list)) {
		if (current_node_list->node == node_to_add) { return; }				// ignore if node already present
		if (!IsNodeListElementValid(current_node_list->tail)) { break; }	// exit loop early if at end of the NodeList
		current_node_list = current_node_list->tail;
	}

	AppendToNodeListElement(current_node_list, NewNodeListElementAndAssign(node_to_add));
}

struct NodeListElement* NewNodeListElementAndAssign(struct SLListElement* node)
{
	struct NodeListElement* element = NewNodeListElement();
	element->node = node;
	return element;
}


#endif // !NODEDATAOPS_C
