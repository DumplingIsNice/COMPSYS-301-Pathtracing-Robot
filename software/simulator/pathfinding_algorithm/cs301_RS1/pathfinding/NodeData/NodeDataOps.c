#ifndef NODEDATAOPS_C
#define NODEDATAOPS_C

#include "NodeDataOps.h"

#include "NodeList.h"


int GetNodeDataPosX(NodeData* node)
{
	return node->posx;
	//return (node->pos) >> 16;
}
int GetNodeDataPosY(NodeData* node)
{
	return node->posy;
	//return (node->pos) & 0x00FF;
}
int GetNodeDataIsChecked(NodeData* node)
{
	return node->isChecked;
}
int GetNodeDataAdjacentPaths(NodeData* node)
{
	return node->num_adjacent_paths;
}
int GetNodeDataWeight(NodeData* node)
{
	return node->weight;
}
NodeData* GetNodeDataAdjacentNode(NodeData* node)
{
	return node->adjacent_nodes->node;
}
NodeListElement* GetNodeDataAdjacentNodeListElement(NodeData* node)
{
	return node->adjacent_nodes;
}


void SetNodeDataPosX(NodeData* node, int pos_x)
{
	node->posx = pos_x;
	//node->pos = node->pos & 0x00FF;
	//node->pos = node->pos | (pos_x << 16);
}
void SetNodeDataPosY(NodeData* node, int pos_y)
{
	node->posy = pos_y;
	//node->pos = node->pos & 0xFF00;
	//node->pos = node->pos | pos_y;
}
void SetNodeDataIsChecked(NodeData* node, int isChecked)
{
	node->isChecked = isChecked;
}
void SetNodeDataAdjacentPaths(NodeData* node, int adj_paths)
{
	node->num_adjacent_paths = adj_paths;
}
void SetNodeDataWeight(NodeData* node, int weight)
{
	node->weight = weight;
}

void AddToNodeDataAdjacentNode(NodeData* node, NodeData* node_to_add)
{
	// If the list is empty...
	if (!IsElementValid(node->adjacent_nodes)) {
		node->adjacent_nodes = NewNodeListElement(node_to_add);
		return;
	}
	// Otherwise add a new node (if it is unique)...
	NodeListElement* current_node = node->adjacent_nodes;

	while (IsElementValid(current_node->tail)) {
		if (current_node->node == node_to_add) { return; }
		current_node = current_node->tail;
	}
	Insert(current_node, NewNodeListElement(node_to_add));
}


#endif // !NODEDATAOPS_C
