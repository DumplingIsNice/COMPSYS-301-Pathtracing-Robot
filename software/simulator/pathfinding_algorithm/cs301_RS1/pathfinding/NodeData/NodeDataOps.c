#ifndef NODEDATAOPS_C
#define NODEDATAOPS_C

#include "NodeDataOps.h"
#include <stddef.h>
//#include "NodeList.h"
#include "List.h"

unsigned long DestroyNodeDataAndContents(NodeData* node)
{
	unsigned long bytes = 0;

	ListElement* current_element = GetNodeDataAdjacentNodeListElement(node);
	ListElement* prev_element;

	while (IsElementValid(current_element)) {
		prev_element = current_element;
		current_element = current_element->tail;
		bytes += DestroyListElement(prev_element);
	}
	bytes += DestroyNodeData(node);

	return bytes;
}

int GetNodeDataPosX(const NodeData* node)
{
	return node->posx;
	//return (node->pos) >> 16;
}
int GetNodeDataPosY(const NodeData* node)
{
	return node->posy;
	//return (node->pos) & 0x00FF;
}
int GetNodeDataIsChecked(const NodeData* node)
{
	return node->isChecked;
}
int GetNodeDataAdjacentPaths(const NodeData* node)
{
	if (IsNodeDataValid(node)) { return node->num_adjacent_paths; }
	return -1;
}
int GetNodeDataWeight(const NodeData* node)
{
	return node->weight;
}
ListElement* GetNodeDataAdjacentNodeListElement(const NodeData* node)
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
	if (IsNodeDataValid(node)) { node->num_adjacent_paths = adj_paths; }
}
void IncrementNodeDataAdjacentpaths(NodeData* node)
{
	if (IsNodeDataValid(node)) { node->num_adjacent_paths = 1 + node->num_adjacent_paths; }
}
void SetNodeDataWeight(NodeData* node, int weight)
{
	node->weight = weight;
}

void AddToNodeDataAdjacentNode(NodeData* node, const NodeData* node_to_add)
{
	if (!IsNodeDataValid(node)) { return; }
	if (!IsNodeDataValid(node_to_add)) { return; }

	if (!IsElementValid(node->adjacent_nodes)) {
		// If list is empty...
		node->adjacent_nodes = NewListElement(node_to_add);

		IncrementNodeDataAdjacentpaths(node);
		return;
	}
	// Otherwise add a new node (if it is unique)...
	ListElement* current_node = node->adjacent_nodes;
	ListElement* prev_node = current_node;

	while (IsElementValid(current_node)) {
		if (current_node->node == node_to_add) { return; }
		prev_node = current_node;
		current_node = current_node->tail;
	}
	Insert(prev_node, NewListElement(node_to_add));

	IncrementNodeDataAdjacentpaths(node);
}

#endif // !NODEDATAOPS_C
