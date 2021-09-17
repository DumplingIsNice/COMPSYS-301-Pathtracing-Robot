#ifndef READMAP_C
#define READMAP_C

#include "ReadMap.h"

#include <stdio.h>
#include <stdlib.h>

// 'Private' variable
static int map[MAP_SIZE_Y][MAP_SIZE_X];


int GetMapValue(int row, int col)
{
    return map[row][col];
}

int ASCIIToInt(char c)
{
    return (int)c - 48;
}

int ReadMapFile(const char* file_name, int map[MAP_SIZE_Y][MAP_SIZE_X])
{
    FILE* file;
    char c = 0;
    int i, j;
    i = 0;
    j = 0;

    errno_t err = fopen_s(&file, file_name, "r");

    if (file == NULL)
    {
        return 0;
    }

    while (EOF != (c = fgetc(file)))
    {
        switch (c)
        {
        case '\n':
            putchar('\n');
            i = 0;
            j++;
            continue;
        case ' ':
            break;
        }
        printf("%d ", ASCIIToInt(c));
        map[j][i++] = ASCIIToInt(c);
    }
    fclose(file);
    return 1;
}

void PrintMap(int map[MAP_SIZE_Y][MAP_SIZE_X])
{
    for (int i = 0; i < MAP_SIZE_Y; i++) {
        for (int j = 0; j < MAP_SIZE_X; j++) {
            printf("%d ", map[i][j]);
        }
        putchar('\n');
    }
}

void TestPrintMap()
{
    int map[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };

    if (!ReadMapFile(MAP_NAME, map))
    {
        printf("Failed to open map file.\n");
    }
    else {
        printf("Successfully read map!\n");
    }

    PrintMap(map);
}


#endif // !READMAP_C
