#ifndef SLLIST_H
#define SLLIST_H

/*
	Singly Linked List Archetype 

	For optimisation purposes there are minimal/no checks that inputs are
	valid. If you incorrectly pass NULL to functions you will corrupt
	your data and/or crash the system.

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

struct SLListElement {
	struct	SLListElement*	tail;
	struct	NodeData*		data;
};

struct SLList {
	struct	SLListElement* head;
	struct	SLListElement* tail;
};

// Create and allocate memory for a new blank SLList.
struct SLList* NewSLList();

// Create and allocate memory for a new blank SLListElement.
struct SLListElement* NewSLListElement();

// Return 1 if valid (not NULL) 
int IsSLListValid(struct SLList* list);

// Return 1 if valid (not NULL) 
int IsSLListElementValid(struct SLListElement* element);

// Append an element to a specific element. Will fail quietly if either
// element is invalid.
void InsertSLListElement(struct SLListElement* list_element, struct SLListElement* element);

// Append an element to a list (add to start). Fails quietly.
void AppendToSLList(struct SLList* list, struct SLListElement* element);

// Prepend an element to a list (add to end). Fails quietly.
void PrependToSLList(struct SLList* list, struct SLListElement* element);

// Insert an element at the given index of a list. Will fail quietly if out of bounds.
void IndexedInsertSLListElement(struct SLList* list, struct SLListElement* element, int index);

#endif // !SLLIST_H
