#ifndef LIST_C
#define LIST_C

#include "List.h"

#include "stdlib.h"		// malloc(), NULL

List* NewList()
{
	List* list = malloc(sizeof(struct List));
	if (list == NULL) { return NULL; }
	// Initialise to non-garbage values:
	list->head = NULL;
	list->tail = NULL;
	return list;
}

ListElement* NewListElement(const void* node)
{
	ListElement* element = malloc(sizeof(struct ListElement));
	if (element == NULL) { return NULL; }
	// Initialise to non-garbage values:
	element->tail = NULL;
	element->node = node;
	return element;
}

int IsListValid(const List* list)
{
	return (list != NULL);
}

int IsElementValid(const ListElement* element)
{
	return (element != NULL);
}

void Insert(ListElement* current, ListElement* add)
{
	add->tail = current->tail;
	current->tail = add;
	return;
}

ListElement* DetachNext(ListElement* preceding_element)
{
	ListElement* to_remove = preceding_element->tail;
	preceding_element->tail = to_remove->tail;
	to_remove->tail = NULL;
	return to_remove;
}

void AppendToList(List* list, ListElement* element)
{
	if (IsElementValid(list->tail)) {
		// If NodeList is not empty then add as normal...
		Insert(list->tail, element);
	}
	else {
		element->tail = NULL;
	}
	list->tail = element;

	if (!IsElementValid(list->head)) {
		list->head = element;	// If the only element in the list, assign as head too.
	}
}

void PrependToList(List* list, ListElement* element)
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

void InsertInList(List* list, ListElement* current, ListElement* add)
{
	if (current == list->tail) {
		AppendToList(list, add);
	}
	else {
		Insert(current, add);
	}
}

ListElement* RemoveListHead(List* list)
{
	ListElement* to_remove = list->head;
	list->head = to_remove->tail;
	if (list->tail == to_remove) {
		list->tail = to_remove->tail;		// Clean up if the list has only one element.
	}
	return to_remove;
}

ListElement* RemoveListTail(List* list)
{
	ListElement* to_remove = list->tail;
	list->tail = to_remove->tail;
	if (list->head == to_remove) {
		list->head = to_remove->tail;			// Clean up if the list has only one element.
	}
	return to_remove;
}

ListElement* GetListHead(const List* list)
{
	return list->head;
}

ListElement* GetListTail(const List* list)
{
	return list->tail;
}


unsigned long DestroyListElements(List* list)
{
	unsigned long bytes = 0;

	ListElement* element = GetListHead(list);
	ListElement* prev_element;

	while (IsElementValid(element)) {
		prev_element = element;
		element = element->tail;
		bytes += sizeof(*prev_element);
		free(prev_element);
	}

	list->head = NULL;
	list->tail = NULL;

	return bytes;
}

unsigned long DestroyListElementsAndImmediateContents(List* list, int* count_destroyed_contents)
{
	unsigned long bytes = 0;

	ListElement* element = GetListHead(list);
	ListElement* prev_element;

	while (IsElementValid(element)) {
		// Note that we do not/cannot call the destructors for node.
		if (element->node != NULL) {
			(*count_destroyed_contents)++;	// *node is not defined at compile time so we cannot use sizeof() on it
			free(element->node);
		}
		prev_element = element;
		element = element->tail;
		bytes += sizeof(*prev_element);
		free(prev_element);
	}

	list->head = NULL;
	list->tail = NULL;

	return bytes;
}

unsigned long DestroyList(List* list)
{
	list->head = NULL;
	list->tail = NULL;

	if (IsListValid(list)) { free(list); return sizeof(struct List); }
	return 0;
}

unsigned long DestroyListElement(ListElement* element)
{
	if (IsElementValid(element)) { free(element); return sizeof(struct ListElement); }
	return 0;
}

#endif // !LIST_C
