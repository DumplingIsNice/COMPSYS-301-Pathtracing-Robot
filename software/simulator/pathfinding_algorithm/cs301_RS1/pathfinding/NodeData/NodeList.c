#ifndef NODELIST_C
#define NODELIST_C

#include "NodeList.h"

#include "stdlib.h"		// malloc()

struct NodeListElement* NewNodeListElement(struct SLListElement* node)
{
	struct NodeListElement* element = (struct NodeListElement*)malloc(sizeof element);
	element->node = node;
	return element;
}

int IsNodeListElementValid(struct NodeListElement* element)
{
	return (element != NULL);
}

void AppendToNodeListElement(struct NodeListElement* current_element, struct NodeListElement* new_element)
{
	current_element->tail = new_element;
}

#endif // !NODELIST_C
