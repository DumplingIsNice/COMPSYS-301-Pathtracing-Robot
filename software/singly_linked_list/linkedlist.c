#ifndef LINKEDLIST_C
#define LINKEDLIST_C


#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

struct Singlylinkedlist* NewSinglylinkedlistElement()
{
    struct Singlylinkedlist* list = malloc(sizeof list);
    return list;
};

void ChangeSinglylinkedlistElementValue(struct Singlylinkedlist* list, int value)
{
    list->value = value;
};

void ChangeSinglylinkedlistElementTail(struct Singlylinkedlist* list, struct Singlylinkedlist* newTail)
{
    list->tail = newTail;
};



void AppendSinglylinkedlist(struct Singlylinkedlist* list, int value)
{
    struct Singlylinkedlist* currentTail;
    struct Singlylinkedlist* nextTail;
    currentTail = list;
    nextTail    = list->tail;
    
    while (nextTail != NULL) {
        currentTail = nextTail;
        nextTail    = nextTail->tail;
    }
    
    struct Singlylinkedlist* toAppend = NewSinglylinkedlistElement();
    // ChangeSinglylinkedlistElementValue(toAppend, value);
    toAppend->value = value;
    
    // ChangeSinglylinkedlistElementTail(currentTail->tail, toAppend);
    currentTail->tail = toAppend;
};

struct Singlylinkedlist* RemoveSinglylinkedlistElement(struct Singlylinkedlist* head, struct Singlylinkedlist* element)
{
    struct Singlylinkedlist* currentTail;
    struct Singlylinkedlist* nextTail;
    currentTail = head;
    nextTail    = head->tail;
    
    if (head == element) {
        DestroySinglylinkedlistElement(head);
        return nextTail; 
        
    } else {
        
        while (nextTail != element) {
            currentTail = nextTail;
            nextTail    = nextTail->tail;
        }
        currentTail->tail = nextTail->tail;
        DestroySinglylinkedlistElement(nextTail);
        
        return head;
    }
};

void DestroySinglylinkedlistElement(struct Singlylinkedlist* element) {
    free(element);
    // We want to free only the pointers and the value, so it is not required to go through each element.
};

void DestroySinglylinkedlist(struct Singlylinkedlist* head) {
    struct Singlylinkedlist* currentTail;
    struct Singlylinkedlist* nextTail;
    currentTail = head;
    nextTail = head;
    
    while (nextTail != NULL) {
        currentTail = nextTail;
        nextTail = nextTail->tail;
        DestroySinglylinkedlistElement(currentTail);
    }
};


// For debugging
void PrintSinglylinkedlistElementValue(struct Singlylinkedlist* list)
{
    printf("%d\n", list->value);
};
void PrintAllSinglylinkedlistElementValues(struct Singlylinkedlist* list)
{
    struct Singlylinkedlist* currentTail;
    struct Singlylinkedlist* nextTail;
    currentTail = list;
    nextTail    = list->tail;
    
    PrintSinglylinkedlistElementValue(currentTail);
    
    while (nextTail != NULL) {
        currentTail = nextTail;
        nextTail    = nextTail->tail;
        PrintSinglylinkedlistElementValue(currentTail);
    }
};


#endif