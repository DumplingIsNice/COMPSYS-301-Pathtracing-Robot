#ifndef DIRECTIONSLIST_H
#define DIRECTIONSLIST_H

/*
	Directions List

	A list of directions used by the robot to follow a given path through a maze.
	The directions are relative to the current position of the car.

*/

typedef enum Direction {LEFT, RIGHT, UP, DEADEND} Direction;

typedef struct DirectionListElement {
	struct DirectionListElement*	tail;
	Direction						direction;
} DirectionListElement;


// Get the head of the DirectionQueue
DirectionListElement* GetDirectionQueue();

//
DirectionListElement* NewDirectionListElement(Direction direction);

// Append to the DirectionQueue
void AddToDirectionQueue(DirectionListElement* element);

// Find the direction and add it to the DirectionQueue. Previous and current nodes should be the
// two nodes travelled through by the robot directly before approaching the third (intersection)
// node--the third node being the one we require the direction to.
void AddDirection(struct NodeData* prev_node, struct NodeData* current_node, struct NodeData* next_node);

// Align the direction_delta values from the global coordinate system (up/down/left/right) to
// instead be relative to the current_delta forward direction (assuming movement along only one
// axis at a time!).
void TakeRelativeDeltas(const int* current_delta_x, const int* current_delta_y, int* direction_delta_x, int* direction_delta_y);

// Find the direction from the change in axis.
Direction CalculateDirection(const int* direction_delta_x, const int* direction_delta_y);

//
void PrintDirectionQueue();

//
void DestroyDirectionQueueAndContents();

#endif // !DIRECTIONSLIST_H

