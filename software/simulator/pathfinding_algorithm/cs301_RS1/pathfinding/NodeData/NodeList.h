#ifndef NODELIST_H
#define NODELIST_H

/*
	Node List

	Node List is a singly linked list of references to nodes.
	It is used as a container of otherwise unconnected nodes. The primary use-case
	is for holding references to adjacent nodes, as part of NodeData. As a result
	there are very few supported operations.

	@TODO: Replace with templated sllist?
	
	NodeList should NOT be used for NodeQueue or ProcessedNodeQueue, as those
	lists do not require this abstraction and overhead.
*/

struct NodeListElement {
	struct NodeListElement*	tail;
	struct SLListElement*	node;
};


// Create and allocate memory for a new blank SLListElement.
struct NodeListElement* NewNodeListElement(struct SLListElement* node);

// Return 1 if valid (element != NULL) 
int IsNodeListElementValid(struct NodeListElement* element);

// Add to the tail of an element.
void AppendToNodeListElement(struct NodeListElement* current_element, struct NodeListElement* new_element);

#endif // !NODELIST_H
