#ifndef LINKEDLIST_H
#define LINKEDLIST_H


struct Singlylinkedlist {
    struct Singlylinkedlist*    tail;    // No typedef or forward declaration, must define as struct
    int     value;
};

struct Doublylinkedlist {
    struct Doublylinkedlist*   head;
    struct Doublylinkedlist*   tail;
    int     value;
};

// Create a new Singlylinkedlist and return a reference to the head.
struct Singlylinkedlist* NewSinglylinkedlistElement();

// Setter
void ChangeSinglylinkedlistElementValue(struct Singlylinkedlist* list, int value);
// Setter
void ChangeSinglylinkedlistElementTail(struct Singlylinkedlist* list, struct Singlylinkedlist* newTail);


// Add a new value to the end of the list
void AppendSinglylinkedlist(struct Singlylinkedlist* list, int value);

// Remove the explicitly given element. Returns the new head (may be unchanged)
struct Singlylinkedlist* RemoveSinglylinkedlistElement(struct Singlylinkedlist* head, struct Singlylinkedlist* element);

// Free list element from memory. Warning: does not reassign tails! Use only after cleaning up!
void DestroySinglylinkedlistElement(struct Singlylinkedlist* element);

// Delete entire list from memory
void DestroySinglylinkedlist(struct Singlylinkedlist* head);



// For debugging
void PrintSinglylinkedlistElementValue(struct Singlylinkedlist* list);
void PrintAllSinglylinkedlistElementValues(struct Singlylinkedlist* list);


#endif