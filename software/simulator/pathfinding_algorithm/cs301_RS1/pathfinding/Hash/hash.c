#include "hash.h"

int hash_gen(int x, int y)
{
    return (int)((x << 16) + (y));
}

int conv_pointer_to_int(void* p)
{
    return (int)(long) p;
}

void* conv_int_to_pointer(int i)
{
    return (void*)(long) i;
}