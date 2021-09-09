#ifndef SLLIST_C
#define SLLIST_C

#include "sllist.h"
#include "stdio.h"	// import NULL


struct SLList* NewSLList()
{
	struct SLList* list = malloc(sizeof list);
	return list;
}

struct SLListElement* NewSLListElement()
{
	struct SLListElement* element = malloc(sizeof element);
	return element;
}

int IsSLListValid(struct SLList* list)
{
	if (list != NULL) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int IsSLListElementValid(struct SLListElement* element)
{
	if (element != NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void InsertSLListElement(struct SLListElement* list_element, struct SLListElement* element)
{
	element->tail = list_element->tail;
	list_element->tail = element;

	return;
}

void AppendToSLList(struct SLList* list, struct SLListElement* element)
{
	InsertSLListElement(list->tail, element);
	list->tail = element;
}

void PrependToSLList(struct SLList* list, struct SLListElement* element)
{
	InsertSLListElement(list->head, element);
	list->head = element;
}

void IndexedInsertSLListElement(struct SLList* list, struct SLListElement* element, int index)
{
	struct SLListElement* current_element = list->head;
	for (int i = 0; i < index; i++) {
		if (current_element != NULL) {
			current_element = current_element->tail;
		} else {
			// invalid position, return with no change
			return;
		}
	}
	InsertSLListElement(current_element, element);
}

#endif // !SLLIST_C
