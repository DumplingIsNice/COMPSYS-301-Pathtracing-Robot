#ifndef REBASEWEIGHTS_H
#define	REBASEWEIGHTS_H

/*
	Rebase Weights

	For our pathfinding algorithms to be analytic the weights for each
	node must be dynamic, the expression relative:
	weight = (min(prev_node_weights) + 1)

	Thus node weights must be semi-recursively rebased when a new node
	is found to be adjacent to a preexisting node with a lower weight.
	This lower weight should propagate through the alternate path and its
	dependents.
*/

typedef struct RebaseListElement {
	struct RebaseListElement* tail;
	struct NodeData* rebased;
	struct NodeData* to_rebase;
} RebaseListElement;


RebaseListElement* NewRebaseListElement(struct NodeData* rebased, struct NodeData* to_rebase);

void DestroyRebaseListElement(RebaseListElement* element);

// Begin rebasing weights, where 'alternate' is a node with an alternate
// path to, and lower weight than, the 'instigating' node.
void StartRebase(struct NodeData* alternate, struct NodeData* instigating);

// Evaluate the given cell, and rebase it and queue adjacent nodes if applicable.
void RebaseWeight(RebaseListElement* element);

// Append to RebaseWeightQueue
void AddToRebaseWeightQueue(RebaseListElement* element);

// Detach and return the head of the RebaseWeightQueue.
RebaseListElement* GetNextinRebaseWeightQueue();

// Returns true if the RebaseWeightQueue is empty.
int IsRebaseWeightQueueEmpty();


#endif // !REBASEWEIGHTS_H
