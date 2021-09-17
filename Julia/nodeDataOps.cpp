#ifndef nodeDataOPS_C
#define nodeDataOPS_C

#include "nodeDataOps.h"
#include "nodeData.h"

int GetnodeDataPosX(struct nodeData* data)
{
	return data->posx;
}
int GetnodeDataPosY(struct nodeData* data)
{
	return data->posy;
}
int GetnodeDataAdjacentPaths(struct nodeData* data)
{
	return data->num_adjacent_paths;
}
int GetnodeDataWeight(struct nodeData* data)
{
	return data->weight;
}


void SetnodeDataPosX(struct nodeData* data, int pos_x)
{
	data->posx = pos_x;
}
void SetnodeDataPosY(struct nodeData* data, int pos_y)
{
	data->posy = pos_y;
}
void SetnodeDataAdjacentPaths(struct nodeData* data, int adj_paths)
{
	data->num_adjacent_paths = adj_paths;
}
void SetnodeDataWeight(struct nodeData* data, int weight)
{
	data->weight = weight;
}


#endif // !nodeDataOPS_C