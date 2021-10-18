#include "NodeMap.h"

#include "NodeDataOps.h"

void NodeMapSet(const int key, const void* val)
{
    nodeMap[key] = (void*)val;
}

NodeData* NodeMapGet(const int key)
{
    return (NodeData*)nodeMap[key];
}

void NodeMapDel(const int key)
{
    nodeMap[key] = NULL;
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

unsigned long NodeMapClear()
{
    unsigned long bytes = 0;
    for (int x = 0; x < (MAP_SIZE_X); x++) {
        for (int y = 0; y < (MAP_SIZE_Y); y++) {
            NodeData* node = NodeMapGet(NodeMapGenKey(x, y));
            if (IsNodeDataValid(node)) { bytes += DestroyNodeDataAndContents(node);}

            NodeMapDel(NodeMapGenKey(x, y));    // remove invalid reference
        }
    }
    return bytes;
}

/* Debug Functions */ 

void NodeMapLogAll(int* key, NodeData** val)
{
    printf("## Logging NodeMap: ##\n");
    for (int i=0;i<(HASH_SIZE);i++)
    {
        key[i] = i;
        val[i] = NodeMapGet(i);
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

void PrintNodeMap()
{
    int key_a[HASH_SIZE] = { 0 };
    NodeData* val_a[HASH_SIZE] = { NULL };
    int desx, desy;

    NodeMapLogAll(key_a, val_a);

    // Prints the entire NodeMap
    printf("## Printing the NodeMap: ##\n");
    for (int i = 0; i < (HASH_SIZE); i++)
    {
        if (IsPtrValid(val_a[i]))
        {
            desx = val_a[i]->posx;
            desy = val_a[i]->posy;
        }
        else {
            desx = -1;
            desy = -1;
        }
        if ((int)val_a[i])
        {
            printf("Key: %3d, val: %d, val->posx: %d, val->posy: %d\n", key_a[i], (int)val_a[i], desx, desy);
        }
    }
}

void TestNodeMap()
{
    // Displays all avaliable keys
    PrintAllKeys();

    NodeData* nodeA = NewNodeData();
    NodeData* val = nodeA;

    int x, y;
    x = 18;
    y = 14;

    nodeA->posx = x;
    nodeA->posy = y;
    nodeA->num_adjacent_paths = 0;
    nodeA->weight = 0;
    nodeA->adjacent_nodes = NULL;

    // This section tests the indivisual getter and setter functions
    TestNodeMapSet(x, y, nodeA);

    // This section views the entire NodeMap
    PrintNodeMap();

    DestroyNodeData(nodeA);
}

void TestNodeMapSet(const int posx, const int posy, const NodeData* node)
{
    printf("## Setting and fetching at (%d, %d): ##\n", posx, posy);
    NodeData* val = NULL;
    int key = NodeMapGenKey(posx, posy);

    NodeMapSet(key, node);
    val = NodeMapGet(key);

    if (IsPtrValid(val))
    {
        printf("Key: %d\n", key);
        printf("Data posx:%d, posy:%d\n", val->posx, val->posy);
    }
}