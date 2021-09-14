#ifndef HASH_H
#define HASH_H

#include "khash.h"

/*
	Hashmap Implementations

    This file contains all functions used in interacting with hashmap.
    The hashmap in this projetc is intended to track the existence of 
    discovered nodes.

    The plan is to hash the (x, y) coordinate positions of cells/nodes
    and store a pointer to that node's instance in a hashmap bucket. 

    This file includes the "khash.h" from the Klib generic library.
    Two example programs have been included with this file to demonstrate 
    the khash library's usage.

*/

// Generates a unique natural number from pair of values
int hash_gen(int x, int y);

// Conversion for hashed values
int conv_pointer_to_int(void* p);
void* conv_int_to_pointer(int i);

#endif // !HASH_H