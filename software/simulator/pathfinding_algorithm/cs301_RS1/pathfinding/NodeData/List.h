//#ifndef LIST_H
//#define LIST_H
//
///*
//	List
//
//	A generic type singly-linked list that uses void* to reference data.
//
//	For optimisation purposes no checks are performed that that inputs
//	are valid.
//
//	IF YOU INCORRECTLY PASS NULL TO FUNCTIONS YOU WILL CORRUPT YOUR DATA
//	AND/OR CRASH THE SYSTEM.
//
//	The field 'node' is handled very loosely to support easily changing
//	struct types. NodeList operations should never interact with 'node'
//	beyond exposing it for external operations.
//	e.g.	... element->node ...			// okay
//			... element->node->value ...	// wrong; inherent assumption
//	Operations on 'node' should be handled with the NodeDataOps file.
//*/
//
//#ifndef TRUE
//	#define TRUE	1
//#endif
//#ifndef FALSE
//	#define FALSE	0
//#endif
//
//
//typedef struct ListElement {
//	struct ListElement*		tail;
//	void*					data;
//} ListElement;
//
//typedef struct List {
//	ListElement* head;
//	ListElement* tail;
//} List;
//
//
//// Create and allocate memory for a new blank List.
//List* NewList();
//
//// Create and allocate memory for a new blank ListElement.
//ListElement* NewListElement(void* data);
//
//
//// Return TRUE if valid (list != NULL)
//int IsListValid(List* list);
//
//// Return TRUE if valid (list != NULL)
//int IsElementValid(ListElement* element);
//
//// Append an element to a specific element. Not List head/tail safe
//// (will not update them).
//void Insert(ListElement* current, ListElement* add);
//
//// Remove a ListElement from a chain of dependencies.
//// 'preceding_node' should be the element directly before the element to be
//// detached. The detached element is returned.
//// Not List head/tail safe (will not update them).
//ListElement* DetachNext(ListElement* preceding_element);
//
//// Append an element to a List (add to end).
//void AppendToList(List* list, ListElement* element);
//
//// Prepend an element to a List (add to start).
//void PrependToList(List* list, ListElement* element);
//
//// Append an element after a specific element in a list. Is List head/tail safe.
//// Cannot prepend (i.e. replace the head of the list). No checks are performed to
//// ensure the given elements are part of the given list.
//void InsertInList(List* list, ListElement* current, ListElement* add);
//
//// Remove the head NodeListElement from a List, and return it.
//ListElement* RemoveListHead(List* list);
//
//// Remove the tail NodeListElement from a List, and return it.
//ListElement* RemoveListTail(List* list);
//
//// Return the head (first element) of a List.
//ListElement* GetListHead(List* list);
//
//// Return the tail (last element) of a List.
//ListElement* GetListTail(List* list);
//
//
//// Free() the NodeListElement structs, but not the NodeData structs.
//void DestroyListElements(List* list);
//
//// Free() the NodeListElement structs, and their valid NodeData structs.
//void DestroyListElementsAndContents(List* list);
//
//// Free() a List. This does not affect its ListElements.
//void DestroyList(List* list);
//
//// Free() a ListElement. This does not affect its associated data.
//void DestroyListElement(ListElement* element);
//
//#endif // !LIST_H
