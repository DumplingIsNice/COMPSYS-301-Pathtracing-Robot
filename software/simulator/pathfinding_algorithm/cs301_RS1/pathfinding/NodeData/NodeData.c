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
	NodeData* node = (NodeData*)malloc(sizeof(*node));
	return node;
}

void DestroyNodeData(NodeData* node)
{
	if (IsNodeDataValid(node)) { free(node); }
}


#endif // !NODEDATA_C
