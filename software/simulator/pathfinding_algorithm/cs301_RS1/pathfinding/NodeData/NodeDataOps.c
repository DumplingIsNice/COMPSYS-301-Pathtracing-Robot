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


#endif // !NODEDATAOPS_C
