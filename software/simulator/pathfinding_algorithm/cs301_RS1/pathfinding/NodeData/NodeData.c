#ifndef NODEDATA_C
#define NODEDATA_C

#include "NodeData.h"

#include "stdlib.h"


int IsNodeDataValid(NodeData* node)
{
	return (node != NULL);
}

NodeData* NewNodeData()
{
	NodeData* node = malloc(sizeof (struct NodeData));
	if (node == NULL) { return NULL; }
	// Initialise to non-garbage values:
	node->posx = 0;
	node->posy = 0;
	node->isChecked = 0;
	node->weight = 0;
	node->num_adjacent_paths = 0;
	node->adjacent_nodes = NULL;
	return node;
}

void DestroyNodeData(NodeData* node)
{
	if (IsNodeDataValid(node)) { free(node); }
}


#endif // !NODEDATA_C
