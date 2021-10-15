#ifndef DIRECTIONSLIST_C
#define DIRECTIONSLIST_C

#include "DirectionsList.h"
#include "../../robot_simulation/control.h"

#include "../NodeData/List.h"
#include "../NodeData/NodeDataOps.h"
#include <stdlib.h>
#include <stdio.h>

static List DirectionQueue = { .head = NULL, .tail = NULL };

static Direction last_evaluated_global_orientation = INVALID;	// temp value used to store the global orientation values found at AddDirection() time
static Direction final_global_orientation = INVALID;			// the global orientation of the robot at the time it reaches the end of the path
static Direction new_starting_orientation = INVALID;			// the global orientation of the robot at the start of the new direction queue

List* GetDirectionQueue()
{
	return &DirectionQueue;
}

//MotionState* NewDirection(MotionState direction)
//{
//	MotionState* new_direction = malloc(sizeof(MotionState));
//	if (new_direction == NULL) { return NULL; }
//	*new_direction = direction;
//	return new_direction;
//}
Direction* NewDirection(Direction direction)
{
	Direction* new_direction = malloc(sizeof(Direction));
	if (new_direction == NULL) { return NULL; }
	*new_direction = direction;
	return new_direction;
}

unsigned long DestroyDirection(Direction* direction)
{
	if (direction != NULL) { free(direction); return sizeof(Direction); }
	return 0;
}

//ListElement* NewDirectionListElement(MotionState direction)
ListElement* NewDirectionListElement(Direction direction)
{
	return NewListElement(NewDirection(direction));
}

int IsDirectionQueueEmpty()
{
	if (!IsElementValid(GetListHead(GetDirectionQueue()))) {
		UpdateFinalOrientationDirection();
		return TRUE;
	} else {
		return FALSE;
	}
}

Direction GetNextDirection()
{
	if (!IsElementValid(GetListHead(GetDirectionQueue()))) { UpdateFinalOrientationDirection(); return INVALID; }

	ListElement* element = RemoveListHead(GetDirectionQueue());
	Direction direction = *((Direction*)(element->node));
	DestroyDirection((Direction*)(element->node));
	DestroyListElement(element);

	UpdateFinalOrientationDirection();
	return direction;
}

Direction GetDirectionToReorientate()
{
	return TakeRelativeDirections(&final_global_orientation, &new_starting_orientation);
}

void UpdateFinalOrientationDirection()
{
	final_global_orientation = last_evaluated_global_orientation;
}

void UpdateNewStartingOrientationDirection()
{
	new_starting_orientation = last_evaluated_global_orientation;
}

void AddToDirectionQueue(ListElement* element)
{
	if (!IsElementValid(GetListHead(GetDirectionQueue()))) { UpdateNewStartingOrientationDirection(); }	// update on first direction
	AppendToList(GetDirectionQueue(), element);
}

void AddDirection(const struct NodeData* prev_node, const struct NodeData* current_node, const struct NodeData* next_node)
{
	int current_delta_x = GetNodeDataPosX(current_node) - GetNodeDataPosX(prev_node);		// +right, -left
	int current_delta_y = GetNodeDataPosY(current_node) - GetNodeDataPosY(prev_node);		// +down, -up

	int direction_delta_x = GetNodeDataPosX(next_node) - GetNodeDataPosX(current_node);
	int direction_delta_y = GetNodeDataPosY(next_node) - GetNodeDataPosY(current_node);

	last_evaluated_global_orientation = CalculateDirection(&current_delta_x, &current_delta_y);		// update each new direction so that only the final direction persists

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
	if ((*current_delta_x != 0) && (*current_delta_y != 0)) { printf("Error: movement along two or no axis.\n"); return; }
	if ((*direction_delta_x != 0) && (*direction_delta_y != 0)) { printf("Error: movement along two or no axis.\n"); return; }

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

Direction TakeRelativeDirections(const Direction* current_direction, const Direction* next_direction)
{
	int current_x = 0;
	int current_y = 0;
	int next_x = 0;
	int next_y = 0;

	switch (*current_direction) {
	case LEFT:			current_x = -1;	break;
	case RIGHT:			current_x = 1;	break;
	case DEADEND:		current_y = 1;	break;
	default:			current_y = -1;	//default to FORWARD
	}

	switch (*next_direction) {
	case LEFT:			next_x = -1;	break;
	case RIGHT:			next_x = 1;		break;
	case DEADEND:		next_y = 1;		break;
	default:			next_y = -1;	//default to FORWARD
	}

	TakeRelativeDeltas(&current_x, &current_y, &next_x, &next_y);
	return CalculateDirection(&next_x, &next_y);
}

//MotionState CalculateDirection(const int* direction_delta_x, const int* direction_delta_y)
Direction CalculateDirection(const int* direction_delta_x, const int* direction_delta_y)
{
	// Assuming movement is only along one axis at a time...
	if ((*direction_delta_x != 0) && (*direction_delta_y != 0)) { printf("Error: movement along two or no axis.\n"); return INVALID; } // xor

	if (*direction_delta_x != 0) {
		if (*direction_delta_x > 0) { return RIGHT_TURNING; }
		else { return LEFT_TURNING; }
	}
	else {
		if (*direction_delta_y > 0) { return NO_STATE; }
		else { return FOLLOWING; }
	}
	//return NO_STATE;	// should never be reached
	return INVALID;	// should never be reached
}

void PrintDirectionQueue()
{
	printf("DirectionQueue Contents:\n");
	ListElement* element = GetListHead(GetDirectionQueue());
	int count = 0;

	while (element != NULL) {
		count++;

		MotionState direction = *(MotionState*)(element->node);
		switch (direction) {
		//case LEFT_TURNING:			printf("%d. LEFT_TURNING\n", count); break;
		//case RIGHT_TURNING:			printf("%d. RIGHT_TURNING\n", count); break;
		//case FOLLOWING:			printf("%d. FOLLOWING\n", count); break;
		//default:			printf("%d. Warning: NO_STATE\n", count);	// DEADEND should only be reached at the end, or in non-shortest-path situations.

		case LEFT:			printf("%d. LEFT\n", count); break;
		case RIGHT:			printf("%d. RIGHT\n", count); break;
		case FORWARD:		printf("%d. FORWARD\n", count); break;
		case DEADEND:		printf("%d. Warning: DEADEND\n", count);	// DEADEND should only be reached at the end, or in non-shortest-path situations.
		default:			printf("%d. Warning: INVALID\n", count);
		}

		element = element->tail;
	}

	printf("There are %d elements in the DirectionQueue.\n\n", count);
}

unsigned long DestroyDirectionQueueElementsAndContents()
{
	unsigned long bytes = 0;
	int direction_instances_destroyed = 0;

	bytes = DestroyListElementsAndImmediateContents(GetDirectionQueue(), &direction_instances_destroyed);
	bytes = direction_instances_destroyed * sizeof(MotionState);

	return bytes;
}

void PrintDirections(Directions* d)
{
	printf("left: %d, right: %d, forward %d\n", d->left, d->right, d->forward);
}

#endif // !DIRECTIONSLIST_C