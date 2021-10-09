#ifndef REBASEWEIGHTS_C
#define	REBASEWEIGHTS_C

#include "RebaseWeights.h"

#include <stdlib.h>
#include "NodeData/NodeDataOps.h"
#include "NodeData/List.h"

static List RebaseWeightQueue = { .head = NULL, .tail = NULL };


struct RebaseData* NewRebaseData(struct NodeData* rebased, struct NodeData* to_rebase)
{
	RebaseData* data = malloc(sizeof(struct RebaseData));
	if (data == NULL) { return NULL; }
	data->rebased = rebased;
	data->to_rebase = to_rebase;
	return data;
}

ListElement* NewRebaseListElement(struct NodeData* rebased, struct NodeData* to_rebase)
{
	return NewListElement(NewRebaseData(rebased, to_rebase));
}

void DestroyRebaseListElement(ListElement* element)
{
	if (IsElementValid(element)) {
		RebaseData* data = (RebaseData*)(element->node);
		if (data != NULL) { free(data); }

		DestroyListElement(element);
	}
}


void StartRebase(struct NodeData* alternate, struct NodeData* instigating)
{
	ListElement* new_rebase = NewRebaseListElement(alternate, instigating);
	RebaseWeight(new_rebase);

	while (!IsRebaseWeightQueueEmpty()) {
		new_rebase = GetNextinRebaseWeightQueue();
		RebaseWeight(new_rebase);
		DestroyRebaseListElement(new_rebase);
	}
}

void RebaseWeight(ListElement* element)
{
	NodeData* rebased = ((RebaseData*)(element->node))->rebased;
	NodeData* to_rebase = ((RebaseData*)(element->node))->to_rebase;

	if (GetNodeDataWeight(to_rebase) > (GetNodeDataWeight(rebased) + 1)) {
		SetNodeDataWeight(to_rebase, GetNodeDataWeight(rebased) + 1);

		// Queue all nodes in adjacent_nodes to also be checked for rebasing.
		ListElement* element = GetNodeDataAdjacentNodeListElement(to_rebase);
		while (IsElementValid(element)) {
			ListElement* new_rebase = NewRebaseListElement(to_rebase, element->node);
			AddToRebaseWeightQueue(new_rebase);
			element = element->tail;
		}
	}
}

void AddToRebaseWeightQueue(ListElement* element)
{
	AppendToList(&RebaseWeightQueue, element);
}

ListElement* GetNextinRebaseWeightQueue()
{
	return RemoveListHead(&RebaseWeightQueue);
}

int IsRebaseWeightQueueEmpty()
{
	return !IsElementValid(GetListHead(&RebaseWeightQueue));
}



#endif // !REBASEWEIGHTS_C