#include "linkedList.h"
#include "nodeData.h"
#include "nodeDataOps.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	return 0;
}


void depthFirstSearch(node* startNode, node* goalNode)
{
	linkedList* stack = newList();
	linkedList* queue = newList();
	node* currentNode = startNode;
	currentNode->visited = true;
	while (currentNode != goalNode) {
		//if there only one adjacent node (dead end)
		//	
		//for each adjacent node of currentNode
			// check if adjacent node is valid route
			// create new node
			// assign x & y position + other node data
			// add adjacent node to queue
			//if queue node is not visited		
				//currentNode = top of queue
	}

}

