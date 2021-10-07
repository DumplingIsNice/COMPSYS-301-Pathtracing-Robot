#ifndef REBASEWEIGHTS_C
#define	REBASEWEIGHTS_C

#include "RebaseWeights.h"

#include <stdlib.h>
#include "NodeData/NodeDataOps.h"
#include "NodeData/NodeList.h"

static RebaseListElement* RebaseWeightQueueHead = NULL;


RebaseListElement* NewRebaseListElement(struct NodeData* rebased, struct NodeData* to_rebase)
{
	RebaseListElement* element = malloc(sizeof(struct RebaseListElement));
	if (element == NULL) { return NULL; }
	element->tail = NULL;
	element->rebased = rebased;
	element->to_rebase = to_rebase;
	return element;
}

void DestroyRebaseListElement(RebaseListElement* element)
{
	if (element != NULL) { free(element); }
}


void StartRebase(struct NodeData* alternate, struct NodeData* instigating)
{
	RebaseListElement* new_rebase = NewRebaseListElement(alternate, instigating);
	RebaseWeight(new_rebase);

	while (!IsRebaseWeightQueueEmpty()) {
		new_rebase = GetNextinRebaseWeightQueue();
		RebaseWeight(new_rebase);
		DestroyRebaseListElement(new_rebase);
	}
}

void RebaseWeight(RebaseListElement* element)
{
	NodeData* rebased = element->rebased;
	NodeData* to_rebase = element->to_rebase;

	if (GetNodeDataWeight(to_rebase) > (GetNodeDataWeight(rebased) + 1)) {
		SetNodeDataWeight(to_rebase, GetNodeDataWeight(rebased) + 1);

		// Queue all nodes in adjacent_nodes to also be checked for rebasing.
		NodeListElement* element = GetNodeDataAdjacentNodeListElement(to_rebase);
		while (IsElementValid(element)) {
			RebaseListElement* new_rebase = NewRebaseListElement(to_rebase, element->node);
			AddToRebaseWeightQueue(new_rebase);
			element = element->tail;
		}
	}
}

void AddToRebaseWeightQueue(RebaseListElement* element)
{
	if (RebaseWeightQueueHead == NULL) {
		// Queue has no elements...
		RebaseWeightQueueHead = element;
	}
	else {
		// Append...
		RebaseListElement* next = RebaseWeightQueueHead;
		RebaseListElement* prev = next;
		while (next != NULL) {
			prev = next;
			next = next->tail;
		}
		prev->tail = element;
	}
}

RebaseListElement* GetNextinRebaseWeightQueue()
{
	if (RebaseWeightQueueHead == NULL) { return NULL; }

	RebaseListElement* head = RebaseWeightQueueHead;
	RebaseWeightQueueHead = head->tail;
	return head;
}

int IsRebaseWeightQueueEmpty()
{
	return (RebaseWeightQueueHead == NULL);
}



#endif // !REBASEWEIGHTS_C