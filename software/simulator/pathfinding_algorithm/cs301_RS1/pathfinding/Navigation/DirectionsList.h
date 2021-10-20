#ifndef DIRECTIONSLIST_H
#define DIRECTIONSLIST_H

/*
	Directions List

	A list of directions used by the robot to follow a given path through a maze.
	Direction vectors are initially calculated relative to global positioning,
	before being adjusted such that the final DirectionQueue directions are
	relative to the position of the robot as it travels through the maze.

	- Usage Guide -
	Generate the DirectionQueue with AddDirection() for all relevant nodes.
	Once all nodes are processed, call DirectionQueueGenerationFinished().
	Get the next direction with GetNextDirection().
	-- repeat until IsDirectionQueueEmpty() returns true --
	After generating the next set of directions use GetDirectionToReorientate()!


	Global positioning:
		Left	: Left
		Right	: Right
		Forward	: Up
		Deadend	: Down

	NOTE:
	When directions for one path have been completed and directions for another path
	have just been generated, call GetDirectionToReorientate() to get the relative
	difference (as a direction) between the ending orientation and the starting
	orientation.

	NOTE:
	UpdateFinalOrientationDirection() must be called externally if GetNextDirection()
	is never called when DirectionQueue is empty! This is in the case that travelling
	a path to a goal is terminated early!

*/


/* Enum is used only when specifying a specific direction (i.e. in Navigation). */
typedef enum Direction {LEFT, RIGHT, FORWARD, DEADEND, INVALID} Direction;

/* Struct is used for passing infomation on currently valid paths (i.e. SensorFSM->MovementController). */
typedef struct Directions {
	int left;
	int right;
	int forward;
} Directions;

// Prints a Directions struct to consol.
void PrintDirections(Directions* d);

// Get the List DirectionQueue
struct List* GetDirectionQueue();

// Instance in memory to use with List.h pointers
Direction* NewDirection(Direction direction);

// Destroy the Direction instance and return the number of bytes freed.
unsigned long DestroyDirection(Direction* direction);

// Returns new ListElement instance populated with new direction instance.
struct ListElement* NewDirectionListElement(Direction direction);

// Returns TRUE if empty, false if there is at least one valid element.
// Handles UpdateFinalOrientationDirection()!
// WARNING: IF THIS IS NOT USED, MUST MANUALLY CALL UpdateFinalOrientationDirection(...)!
int IsDirectionQueueEmpty();

// Returns the direction from the top of the DirectionQueue, deleting the ListElement and updating the queue.
Direction GetNextDirection();

// Returns the difference in direction between the orientation the last path ended at, and the orientation the new path begins at.
// Call directly after the new directions have been generated. Do not call if this is the first time directions have been generated (there is no orientation history).
// Returns FORWARD if no change is required (i.e. same orientation).
Direction GetDirectionToReorientate();

// Call externally for checking if we should expect the starting node of the next path to be an intersection.
// Used for tolerances and handling avoiding falsely reading the starting node as the first path intersection.
int IsDirectionStartAtIntersection();

// Call externally once all directions have been generated (i.e., all nodes processed).
// - Stores the current value of last_evaluated_global_orientation to final_global_orientation, for further processing in UpdateFinalOrientationDirection()
// WARNING: MUST CALL EXTERNALLY!
void DirectionQueueGenerationFinished();

// Used internally, called when the final direction in the DirectionQueue has been taken or all directions for the current path have been created.
// Use final_global_orientation (orientation prior to last direction) and final_relative_direction to get the final global orientation for once all directions have been followed.
// MUST CALL EXTERNALLY IF GetNextDirection() IS NOT CALLED!
void UpdateFinalOrientationDirection(Direction final_relative_direction);

// Used internally, called when the first in a new list of directions has been created. 
void UpdateNewStartingOrientationDirection();

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

// Return the direction relative to the difference between the current and the next direction.
// Note that this is very inneficient, use only when absolutely required.
Direction TakeRelativeDirections(const Direction* current_direction, const Direction* next_direction, int is_next_direction_relative);

// Find the direction from the change in axis.
Direction CalculateDirection(const int* direction_delta_x, const int* direction_delta_y);

//
void PrintDirectionQueue();

// Destroy the DirectionQueue contents and elements, and return the number of bytes freed.
unsigned long DestroyDirectionQueueElementsAndContents();

#endif // !DIRECTIONSLIST_H

