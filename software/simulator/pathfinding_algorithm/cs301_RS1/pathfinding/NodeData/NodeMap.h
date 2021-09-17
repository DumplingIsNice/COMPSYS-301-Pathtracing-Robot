/*
    NodeMap:

        A statically allocated pseudo - hash map.
        Each element(val) holds a references to a NodeData struct,
        and is indexed with a key generates from coordinate (x,y) values.

        keys: are intergers. Literially, they are implemented no different to array indexes.
        vals: are NodeData pointers.

    Note:
        This library relies on the MAP_SIZE definition in READMAP.h

        To use, see TestNodeMape() for examples.

*/

#include <stdio.h>
#include <stdlib.h>

#include "ReadMap.h"
#include "NodeData.h"

#ifndef NODEMAP_H
#define NODEMAP_H

#define HASH_SIZE   MAP_SIZE_X * MAP_SIZE_Y + MAP_SIZE_Y

typedef void* NodeMap;

// Returns NULL if failed.
NodeMap* NodeMapNew();

// Frees NodeMap if it is valid.
void NodeMapFree(NodeMap* h);

// Setter, key-val pair
void NodeMapSet(NodeMap* h, const int key, const void* val);

// Getter, val by key
NodeData* NodeMapGet(const NodeMap* h, const int key);

/*  Note: del does not delete the pointer or the NodeData it points too.
    CAUTION! The NodeData could be lost if not already logged in NodeQueue */
void NodeMapDel(NodeMap* h, const int key);

// Encodes coordinates into key
int NodeMapGenKey(const int posx, const int posy);

/* Debug Functions */

// Helper Func
int IsPtrValid(void* ptr);

// Logas all key and val of NodeMap into arrays
void NodeMapLogAll(const NodeMap* h, int* key, NodeData** val);

// Displays all avaliable keys
void PrintAllKeys();

#endif // NODEMAP_H