#ifndef DIRECTIONSLIST_H
#define DIRECTIONSLIST_H

/*
	Directions List

	A list of directions used by the robot to follow a given path through a maze.
	Direction vectors are initially calculated relative to global positioning,
	before being adjusted such that the final DirectionQueue directions are
	relative to the position of the robot as it travels through the maze.

	Global positioning:
		Left	: Left
		Right	: Right
		Forward	: Up
		Deadend	: Down

*/

/* Enum is used only when specifying a specific direction (i.e. in Navigation). */
typedef enum Direction {LEFT, RIGHT, FORWARD, DEADEND} Direction;

/* Struct is used for passing infomation on currently valid paths (i.e. SensorFSM->MovementController). */
typedef struct Directions {
	int left;
	int right;
	int forward;
} Directions;

// Prints a Directions struct to consol.
void PrintDirections(Directions* d);

// Get the head of the DirectionQueue
struct List* GetDirectionQueue();

// Instance in memory to use with List.h pointers
Direction* NewDirection(Direction direction);

//
struct ListElement* NewDirectionListElement(Direction direction);

// Append to the DirectionQueue
void AddToDirectionQueue(struct ListElement* element);

// Find the direction and add it to the DirectionQueue. Previous and current nodes should be the
// two nodes travelled through by the robot directly before approaching the third (intersection)
// node--the third node being the one we require the direction to.
void AddDirection(const struct NodeData* prev_node, const struct NodeData* current_node, const struct NodeData* next_node);

// Align the direction_delta values from the global coordinate system (up/down/left/right) to
// instead be relative to the current_delta forward direction (assuming movement along only one
// axis at a time!).
void TakeRelativeDeltas(const int* current_delta_x, const int* current_delta_y, int* direction_delta_x, int* direction_delta_y);

// Find the direction from the change in axis.
Direction CalculateDirection(const int* direction_delta_x, const int* direction_delta_y);

//
void PrintDirectionQueue();

// Destroy the DirectionQueue contents and elements, and return the number of bytes freed.
unsigned long DestroyDirectionQueueElementsAndContents();

#endif // !DIRECTIONSLIST_H

