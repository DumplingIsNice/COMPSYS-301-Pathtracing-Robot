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

struct SLListElement* RemoveFollowingSLListElement(struct SLListElement* head_element)
{
	struct SLListElement* element_to_remove = head_element->tail;
	head_element->tail = element_to_remove->tail;
	element_to_remove->tail = NULL;
	return element_to_remove;
}

void AppendToSLList(struct SLList* list, struct SLListElement* element)
{
	if (IsSLListElementValid(list->tail)) {
		InsertSLListElement(list->tail, element);
	}
	else {
		element->tail = NULL;
	}
	
	list->tail = element;

	if (!IsSLListElementValid(list->head)) {
		list->head = element;	// if first element in list, assign as head and tail
	}
}

void PrependToSLList(struct SLList* list, struct SLListElement* element)
{
	if (IsSLListElementValid(list->head)) {
		InsertSLListElement(list->head, element);
	}
	else {
		element->tail = NULL;
	}
	
	list->head = element;

	if (!IsSLListElementValid(list->tail)) {
		list->tail = element;	// if first element in list, assign as head and tail
	}
}

struct SLListElement* RemoveHeadInSLList(struct SLList* list)
{
	struct SLListElement* element_to_remove = list->head;
	list->head = element_to_remove->tail;
	if (list->tail == element_to_remove) {
		list->tail = element_to_remove->tail;	// clean up if list is single element
	}
	return element_to_remove;
}

struct SLListElement* RemoveTailInSLList(struct SLList* list)
{
	struct SLListElement* element_to_remove = list->tail;
	list->tail = element_to_remove->tail;		// should assign NULL
	if (list->head == element_to_remove) {		// clean up if list is single element:
		list->head = element_to_remove->tail;	// should assign NULL
	}
	return element_to_remove;
}

struct SLListElement* GetHeadInSLList(struct SLList* list)
{
	return list->head;
}

struct SLListElement* GetTailInSLList(struct SLList* list)
{
	return list->tail;
}






//void IndexedInsertSLListElement(struct SLList* list, struct SLListElement* element, int index)
//{
//	struct SLListElement* current_element = list->head;
//	for (int i = 0; i < index; i++) {
//		if (IsSLListElementValid(current_element)) {
//			current_element = current_element->tail;
//		} else {
//			// invalid position, return with no change
//			return;
//		}
//	}
//	InsertSLListElement(current_element, element);
//}

#endif // !SLLIST_C
