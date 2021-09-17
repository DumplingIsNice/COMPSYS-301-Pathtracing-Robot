#ifndef NODEDATA_C
#define NODEDATA_C

#include "NodeData.h"

#include "stdlib.h"


NodeData* NewNodeData()
{
	NodeData* node = (NodeData*)malloc(sizeof node);
	return node;
}


#endif // !NODEDATA_C
