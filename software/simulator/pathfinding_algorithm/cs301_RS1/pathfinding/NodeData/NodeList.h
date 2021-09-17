#ifndef NODELIST_H
#define NODELIST_H

/*
	Node List

	!!! NodeList has replaced the deprecated SLList !!!

	For optimisation purposes no checks are performed that that inputs
	are valid.

	IF YOU INCORRECTLY PASS NULL TO FUNCTIONS YOU WILL CORRUPT YOUR DATA
	AND/OR CRASH THE SYSTEM.

	The field 'data' is handled very loosely to support easily changing
	struct types. SLList operations should never interact with 'data'
	beyond exposing it for external operations.
	e.g.	... element->data ...			// okay
			... element->data->value ...	// wrong; inherent assumption
	Operations on 'data' should be handled with the NodeDataOps file.
*/

#ifndef TRUE
	#define TRUE	1
#endif
#ifndef FALSE
	#define FALSE	0
#endif


typedef struct NodeListElement {
	struct NodeListElement* tail;
	struct NodeData* node;
} NodeListElement;

typedef struct NodeList {
	NodeListElement* head;
	NodeListElement* tail;
} NodeList;


// Create and allocate memory for a new blank NodeList.
NodeList* NewNodeList();

// Create and allocate memory for a new blank NodeListElement.
NodeListElement* NewNodeListElement(struct NodeData* node);


// Return TRUE if valid (list != NULL)
int IsListValid(NodeList* list);

// Return TRUE if valid (list != NULL)
int IsElementValid(NodeListElement* element);

// Append an element to a specific element. Not NodeList head/tail safe
// (will not update them).
void Insert(NodeListElement* current, NodeListElement* new);

// Remove a NodeListElement from a chain of dependencies.
// 'preceding_node' should be the element directly before the element to be
// detached. The detached element is returned.
// Not NodeList head/tail safe (will not update them).
NodeListElement* DetachNext(NodeListElement* preceding_node);

// Append an element to a NodeList (add to end).
void AppendToList(NodeList* list, NodeListElement* element);

// Prepend an element to a NodeList (add to start).
void PrependToList(NodeList* list, NodeListElement* element);

// Remove the head NodeListElement from a NodeList, and return it.
NodeListElement* RemoveListHead(NodeList* list);

// Remove the tail NodeListElement from a NodeList, and return it.
NodeListElement* RemoveListTail(NodeList* list);

// Return the head (first element) of a NodeList.
NodeListElement* GetListHead(NodeList* list);

// Return the tail (last element) of a NodeList.
NodeListElement* GetListTail(NodeList* list);


// Free() the NodeListElement structs, but not the NodeData structs.
void DestroyListElements(NodeList* list);

// Free() the NodeListElement structs, and their valid NodeData structs.
void DestroyListElementsAndContents(NodeList* list);

// Free() a NodeList. This does not affect its NodeListElements.
void DestroyList(NodeList* list);

#endif // !NODELIST_H
