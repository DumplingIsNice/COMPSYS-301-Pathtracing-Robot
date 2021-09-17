#define LINKEDLIST_H
#include "nodeData.h"

struct node {
	struct nodeData* data;
	bool visited;
	struct node* next;
};

struct linkedList {
	struct node* head;
	struct node* tail;
};

//Create a new node
struct node* newNode();

//Create a new list
struct linkedList* newList();

//Add a node to the start of the list
void prepend(struct linkedList* list, struct node* listNode);

//Add a node to the end of the list
void append(struct linkedList* list, struct node* listNode);


//Remove the head of the list
struct linkedList* removeHead(struct linkedList* list);


//Remove the tail of the list
struct linkedList* removeTail(struct linkedList* list);

//Remove a specific node in the list
struct linkedList* remove(struct linkedList* list);

struct node* getHead(struct linkedList* list);

struct node* getTail(struct linkedList* list);