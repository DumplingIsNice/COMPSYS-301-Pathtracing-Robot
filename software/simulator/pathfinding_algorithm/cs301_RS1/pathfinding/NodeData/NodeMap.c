#include "NodeMap.h"

NodeMap* NodeMapNew()
{
    NodeMap* h = malloc(sizeof(*h) * (HASH_SIZE));
    if (h == NULL)
    {
        return NULL;
    }
    for (int i=0;i<(HASH_SIZE);i++)
    {
        h[i] = NULL;
    }
    return h;
}

void NodeMapFree(NodeMap* h)
{
    if (h != NULL) { free(h); };
}

void NodeMapSet(NodeMap* h, const int key, const void* val)
{
    h[key] = (void*)val;
}

NodeData* NodeMapGet(const NodeMap* h, const int key)
{
    return (NodeData*)h[key];
}

void NodeMapDel(NodeMap* h, const int key)
{
    h[key] = NULL;
}

int NodeMapGenKey(const int posx, const int posy) 
{
    return (posx * MAP_SIZE_Y) + posy;
}

int IsPtrValid(void* ptr)
{
    if (ptr != NULL)
    {
        return 1;
    } else {
        return 0;
    }
}

// @To do, but likely unnecessary
void NodeMapClear()
{
    ;
}

/* Debug Functions */ 

void NodeMapLogAll(const NodeMap* h, int* key, NodeData** val)
{
    printf("## Logging NodeMap: ##\n");
    for (int i=0;i<(HASH_SIZE);i++)
    {
        key[i] = i;
        val[i] = NodeMapGet(h, i);
    }
}

void PrintAllKeys()
{
    printf("## Printing all Keys: ##\n");
    for (int x = 0; x < (MAP_SIZE_X); x++)
    {
        for (int y = 0; y < (MAP_SIZE_Y); y++)
        {
            printf("%d, %d: %d\n", x, y, NodeMapGenKey(x, y));
        }
    }
}

void TestNodeMap()
{
    // Displays all avaliable keys
    PrintAllKeys();

    NodeMap* h = NodeMapNew();
    NodeData* nodeA = NewNodeData();

    int x, y;
    x = 15;
    y = 19;

    int key = NodeMapGenKey(x, y);
    NodeData* val = nodeA;
    nodeA->posx = x;
    nodeA->posy = y;
    nodeA->num_adjacent_paths = 0;
    nodeA->weight = 0;
    nodeA->adjacent_nodes = NULL;

    // This section tests the indivisual getter and setter functions
    printf("## Setting and fetching at (x,y): ##\n");
    NodeMapSet(h, key, val);

    key = NodeMapGenKey(x, y);

    val = NodeMapGet(h, key);

    if (IsPtrValid(val))
    {
        printf("Data posx:%d, posy:%d\n", val->posx, val->posy);
    }

    // This section views the entire NodeMap
    int key_a[HASH_SIZE] = { 0 };
    NodeData* val_a[HASH_SIZE] = { NULL };
    int desx, desy;

    NodeMapLogAll(h, key_a, val_a);

    // Prints the entire NodeMap
    printf("## Printing the NodeMap: ##\n");
    for (int i = 0; i < (HASH_SIZE); i++)
    {
        if (IsPtrValid(val_a[i]))
        {
            desx = val->posx;
            desy = val->posy;
        }
        else {
            desx = -1;
            desy = -1;
        }
        printf("Key: %3d, val: %d, val->posx: %d, val->posy: %d\n", key_a[i], (int)val_a[i], desx, desy);
    }

    NodeMapFree(h);
    DestroyNodeData(nodeA);
}