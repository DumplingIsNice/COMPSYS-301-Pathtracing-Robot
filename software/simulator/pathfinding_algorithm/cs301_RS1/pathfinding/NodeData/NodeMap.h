/*
    NodeMap:

        A statically allocated pseudo - hash map.
        Each element(val) holds a references to a NodeData struct,
        and is indexed with a key generates from coordinate (x,y) values (0-(MAX-1)).

        keys: are intergers. Literially, they are implemented no different to array indexes.
        vals: are NodeData pointers.

        24/09/2021:
            - Refactored NodeMap to allocate a static hashmap.
            - Removed dynamic allocation.
            
        (CAUTION: ONLY FUNCTIONAL FOR MAP_SIZE_ FIXED AT COMPILE TIME)

    Note:
        This library relies on the MAP_SIZE_ definition in READMAP.h

        To use, see TestNodeMap() for examples.

*/

#ifndef NODEMAP_H
#define NODEMAP_H

#include <stdio.h>
#include <stdlib.h>

#include "../FileUtility/ReadMap.h"
#include "NodeData.h"

#define HASH_SIZE   MAP_SIZE_X * MAP_SIZE_Y + MAP_SIZE_Y

typedef void* NodeMap;

static NodeMap* nodeMap[HASH_SIZE] = {0};

// Setter, key-val pair
void NodeMapSet(const int key, const void* val);

// Getter, val by key
NodeData* NodeMapGet(const int key);

/*  Note: del does not delete the pointer or the NodeData it points too.
    CAUTION! The NodeData could be lost if not already logged in NodeQueue */
void NodeMapDel(const int key);

// Free() all valid NodeData structs within the NodeMap.
void NodeMapClear();

// Encodes coordinates into key
int NodeMapGenKey(const int posx, const int posy);

/* Debug Functions */

// Helper Func
int IsPtrValid(void* ptr);

// Logas all key and val of NodeMap into arrays
void NodeMapLogAll(int* key, NodeData** val);

// Displays all avaliable keys
void PrintAllKeys();

// Example of SOME of NodeMap Functionality
void TestNodeMap();
void TestNodeMapSet(const int posx, const int posy, const NodeData* node);

#endif // NODEMAP_H