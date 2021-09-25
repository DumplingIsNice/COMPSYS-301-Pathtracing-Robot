#ifndef NODELIST_C
#define NODELIST_C

#include "NodeList.h"

#include "stdlib.h"		// malloc(), NULL

NodeList* NewNodeList()
{
	NodeList* list = malloc(sizeof(struct NodeList));
	if (list == NULL) { return NULL; }
	// Initialise to non-garbage values:
	list->head = NULL;
	list->tail = NULL;
	return list;
}

NodeListElement* NewNodeListElement(struct NodeData* node)
{
	NodeListElement* element = malloc(sizeof(struct NodeListElement));
	if (element == NULL) { return NULL; }
	// Initialise to non-garbage values:
	element->tail = NULL;
	element->node = node;
	return element;
}

int IsListValid(NodeList* list)
{
	return (list != NULL);
}

int IsElementValid(NodeListElement* element)
{
	return (element != NULL);
}

void Insert(NodeListElement* current, NodeListElement* new)
{
	new->tail = current->tail;
	current->tail = new;
	return;
}

NodeListElement* DetachNext(NodeListElement* preceding_node)
{
	NodeListElement* to_remove = preceding_node->tail;
	preceding_node->tail = to_remove->tail;
	to_remove->tail = NULL;
	return to_remove;
}

void AppendToList(NodeList* list, NodeListElement* element)
{
	if (IsElementValid(list->tail)) {
		// If NodeList is not empty then add as normal...
		Insert(list->tail, element);
	} else {
		element->tail = NULL;
	}
	list->tail = element;

	if (!IsElementValid(list->head)) {
		list->head = element;	// If the only element in the list, assign as head too.
	}
}

void PrependToList(NodeList* list, NodeListElement* element)
{
	if (IsElementValid(list->head)) {
		// If NodeList is not empty then link tail as normal...

		if (!IsElementValid(list->tail)) {
			// If there is only one element in the list then update tail...
			list->tail = list->head;
		}
		element->tail = list->head;
	}
	else {
		element->tail = NULL;
	}
	list->head = element;

	if (!IsElementValid(list->tail)) {
		list->tail = element;	// If this is the only element in the list, assign as tail too.
	}
}

void InsertInList(NodeList* list, NodeListElement* current, NodeListElement* add)
{
	if (current == list->tail) {
		AppendToList(list, add);
	} else {
		Insert(current, add);
	}
}

NodeListElement* RemoveListHead(NodeList* list)
{
	NodeListElement* to_remove = list->head;
	list->head = to_remove->tail;
	if (list->tail == to_remove) {
		list->tail = to_remove->tail;		// Clean up if the list has only one element.
	}
	return to_remove;
}

NodeListElement* RemoveListTail(NodeList* list)
{
	NodeListElement* to_remove = list->tail;
	list->tail = to_remove->tail;
	if (list->head == to_remove) {
		list->head = to_remove->tail;			// Clean up if the list has only one element.
	}
	return to_remove;
}

NodeListElement* GetListHead(NodeList* list)
{
	return list->head;
}

NodeListElement* GetListTail(NodeList* list)
{
	return list->tail;
}


void DestroyListElements(NodeList* list)
{
	NodeListElement* element = GetListHead(list);
	NodeListElement* prev_element;

	while (IsElementValid(element)) {
		prev_element = element;
		element = element->tail;
		free(prev_element);
	}
}

void DestroyListElementsAndContents(NodeList* list)
{
	NodeListElement* element = GetListHead(list);
	NodeListElement* prev_element;

	while (IsElementValid(element)) {
		// DestroyNodeData() could be used here, but would increase coupling (as it requires #include "NodeData.h").
		if (element->node != NULL) { free(element->node); }
		prev_element = element;
		element = element->tail;
		free(prev_element);
	}
}

void DestroyList(NodeList* list)
{
	if (IsListValid(list)) { free(list); }
}

void DestroyListElement(NodeListElement* element)
{
	if (IsElementValid(element)) { free(element); }
}

#endif // !NODELIST_C
