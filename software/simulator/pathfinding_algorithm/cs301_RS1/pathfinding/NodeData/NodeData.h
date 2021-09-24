#ifndef NODEDATA_H
#define NODEDATA_H

/*
	Node Data

	Node Data instances hold all relevant information for
	each node. This data is used to analyse each node,
	and use the nodes in pathfinding algorithms.

	The contents of this node may be changed freely. All
	interactions with NodeData instances should be performed
	through the provided NodeDataOps API functions.

	FIELDS SHOULD NEVER BE ACCESSED EXPLICITLY. ALWAYS USE NODEDATAOPS
	GETTER/SETTER FUNCTIONS TO MODIFY OR READ.
*/

typedef struct NodeData {
	int	posx;
	int posy;
	int isChecked;
	int num_adjacent_paths;
	int weight;
	struct NodeListElement* adjacent_nodes;
} NodeData;


// Create and allocate memory for a blank NodeData.
NodeData* NewNodeData();

// Free() NodeData struct
void DestroyNodeData(NodeData* node);

#endif // !NODEDATA_H
