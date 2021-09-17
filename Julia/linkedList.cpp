#define LINKEDLIST_C
#include "linkedList.h"

#include <stdio.h>
#include <stdlib.h>

struct node* newNode() {
	struct node* newNode = (node *) malloc(sizeof newNode);
	return newNode;
}

struct linkedList* newList() {
	struct linkedList* newList = (linkedList*)malloc(sizeof newList);
	return newList;
}

void prepend(struct linkedList* list, struct node* listNode) {
	listNode->next = list->head;
	list->head = listNode;
}

void append(struct linkedList* list, struct node* listNode) {
	list->tail->next = listNode;
	list->tail = listNode;
}

struct linkedList* removeHead(struct linkedList* list) {
	node* temp = list->head->next;
	list->head->next = NULL;
	list->head = temp;
	delete temp;
	return list;
}

struct linkedList* removeTail(struct linkedList* list) {
	node* current = list->head;
	while (current->next->next != NULL) {
		current = current->next;
	}
	current->next = NULL;
	list->tail = current;
	delete current;
	return list;
}

struct linkedList* remove(struct linkedList* list, struct node* listNode) {
	if (listNode->next != NULL) {
		node* current = list->head;
		while (current->next != listNode) {
			current = current->next;
		}
		current->next = listNode->next;
		delete current;
	}
	return list;
}

struct node* getHead(struct linkedList* list) {
	return list->head;
}

struct node* getTail(struct linkedList* list) {
	return list->tail;
}

