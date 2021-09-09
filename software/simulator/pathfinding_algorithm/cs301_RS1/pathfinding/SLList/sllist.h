#ifndef SLLIST_H
#define SLLIST_H

/*
	Singly Linked List Archetype 

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


// Append an element to a specific element. Not SLList head/tail safe
// (will not update them).
void InsertSLListElement(struct SLListElement* list_element, struct SLListElement* element);

// Remove an element from a chain of dependencies. 'head_element' should
// be the element directly in front of the element to be removed. Return
// the detached element.
// Not SLList head/tail safe (will not update them).
struct SLListElement* RemoveFollowingSLListElement(struct SLListElement* head_element);

// Append an element to a list (add to end).
void AppendToSLList(struct SLList* list, struct SLListElement* element);

// Prepend an element to a list (add to start).
void PrependToSLList(struct SLList* list, struct SLListElement* element);

// Remove head from list, and return it.
struct SLListElement* RemoveHeadInSLList(struct SLList* list);

// Remove tail from list, and return it.
struct SLListElement* RemoveTailInSLList(struct SLList* list);

// Returns the head (first element) of the list.
struct SLListElement* GetHeadInSLList(struct SLList* list);




//// Insert an element at the given index of a list. Will fail quietly if out of bounds.
//void IndexedInsertSLListElement(struct SLList* list, struct SLListElement* element, int index);

#endif // !SLLIST_H
