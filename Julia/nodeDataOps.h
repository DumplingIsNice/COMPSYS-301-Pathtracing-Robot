#ifndef nodeDataOPS_H
#define nodeDataOPS_H

#include "nodeData.h"
//Author: Callum McDowell
/*
	Node Data Operations
	Provides all the getters and setters for the nodeData struct.
	This is a general API that acts as an interface to nodeData.
	nodeData SHOULD BY MODIFIED OR READ ONLY VIA nodeDataOPS FUNCTIONS.
	DO NOT ACCESS EXPLICITLY!
*/

int GetnodeDataPosX(struct nodeData* data);
int GetnodeDataPosY(struct nodeData* data);
int GetnodeDataAdjacentPaths(struct nodeData* data);
int GetnodeDataWeight(struct nodeData* data);

void SetnodeDataPosX(struct nodeData* data, int pos_x);
void SetnodeDataPosY(struct nodeData* data, int pos_y);
void SetnodeDataAdjacentPaths(struct nodeData* data, int adj_paths);
void SetnodeDataWeight(struct nodeData* data, int weight);




#endif // !nodeData_H