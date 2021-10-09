#ifndef DIRECTIONSLIST_C
#define DIRECTIONSLIST_C

#include "DirectionsList.h"

#include "../NodeData/List.h"
#include "../NodeData/NodeDataOps.h"
#include <stdlib.h>
#include <stdio.h>

static List DirectionQueue = { .head = NULL, .tail = NULL };

List* GetDirectionQueue()
{
	return &DirectionQueue;
}

Direction* NewDirection(Direction direction)
{
	Direction* new_direction = malloc(sizeof(Direction));
	if (new_direction == NULL) { return NULL; }
	*new_direction = direction;
	return new_direction;
}

ListElement* NewDirectionListElement(Direction direction)
{
	return NewListElement(NewDirection(direction));
}

void AddToDirectionQueue(ListElement* element)
{
	AppendToList(GetDirectionQueue(), element);
}

void AddDirection(const struct NodeData* prev_node, const struct NodeData* current_node, const struct NodeData* next_node)
{
	int current_delta_x = GetNodeDataPosX(current_node) - GetNodeDataPosX(prev_node);		// +right, -left
	int current_delta_y = GetNodeDataPosY(current_node) - GetNodeDataPosY(prev_node);		// +down, -up

	int direction_delta_x = GetNodeDataPosX(next_node) - GetNodeDataPosX(current_node);
	int direction_delta_y = GetNodeDataPosY(next_node) - GetNodeDataPosY(current_node);

	//printf("current_d_x = %d, current_d_y = %d || direction_d_x = %d, direction_d_y = %d ||    --->    ", current_delta_x, current_delta_y, direction_delta_x, direction_delta_y);
	TakeRelativeDeltas(&current_delta_x, &current_delta_y, &direction_delta_x, &direction_delta_y);
	//printf("relative direction_d_x = %d, relative direction_d_y = %d\n", direction_delta_x, direction_delta_y);
	
	ListElement* element = NewDirectionListElement(CalculateDirection(&direction_delta_x, &direction_delta_y));
	if (element == NULL) { return; }
	AddToDirectionQueue(element);
}

void TakeRelativeDeltas(const int* current_delta_x, const int* current_delta_y, int* direction_delta_x, int* direction_delta_y)
{
	// Assuming movement is only along one axis at a time...
	if ((*current_delta_x & *current_delta_y) != 0) { printf("Error: movement along two axis.\n"); return; }
	if ((*direction_delta_x & *direction_delta_y) != 0) { printf("Error: movement along two axis.\n"); return; }

	// Automatically return forward if there is no change in direction.
	// Note that we must do that here otherwise consecutive LEFT and RIGHT are not handled it correctly.
	// WARNING: The equality operators assume that the current and direction delta are binary and equal in magnitude...if grid implementation is changed this will be wrong!
	if ((*current_delta_x == *direction_delta_x) && (*current_delta_y == *direction_delta_y)) {
		*direction_delta_x = 0;
		*direction_delta_y = -1 * abs(*direction_delta_y);
		return;
	}

	if (*current_delta_x != 0) {
		if (*current_delta_x > 0) {
			// right ... swap
			int temp = *direction_delta_x;
			*direction_delta_x = *direction_delta_y;
			*direction_delta_y = temp;
			return;
		}
		else {
			// left ... swap and invert
			int temp = -1 * (*direction_delta_x);
			*direction_delta_x = -1 * (*direction_delta_y);
			*direction_delta_y = temp;
			return;
		}
	}
	else {
		if (*current_delta_y > 0) {
			// down ... invert
			*direction_delta_x = -1 * (*direction_delta_x);
			*direction_delta_y = -1 * (*direction_delta_y);
			return;
		}
		else {
			// up ... no change!
			return;
		}
	}
}

Direction CalculateDirection(const int* direction_delta_x, const int* direction_delta_y)
{
	// Assuming movement is only along one axis at a time...
	if ((*direction_delta_x & *direction_delta_y) != 0) { printf("Error: movement along two axis.\n"); return DEADEND; }

	if (*direction_delta_x != 0) {
		if (*direction_delta_x > 0) { return RIGHT; }
		else { return LEFT; }
	}
	else {
		if (*direction_delta_y > 0) { return DEADEND; }
		else { return FORWARD; }
	}
	return DEADEND;	// should never be reached
}

void PrintDirectionQueue()
{
	printf("DirectionQueue Contents:\n");
	ListElement* element = GetListHead(GetDirectionQueue());
	int count = 0;

	while (element != NULL) {
		count++;

		Direction direction = *(Direction*)(element->node);
		switch (direction) {
		case LEFT:			printf("%d. LEFT\n", count); break;
		case RIGHT:			printf("%d. RIGHT\n", count); break;
		case FORWARD:			printf("%d. FORWARD\n", count); break;
		default:			printf("%d. Warning: DEADEND\n", count);	// DEADEND should only be reached at the end, or in non-shortest-path situations.
		}

		element = element->tail;
	}

	printf("There are %d elements in the DirectionQueue.\n\n", count);
}

void DestroyDirectionQueueAndContents()
{
	DestroyListElementsAndImmediateContents(GetDirectionQueue());
}

#endif // !DIRECTIONSLIST_C