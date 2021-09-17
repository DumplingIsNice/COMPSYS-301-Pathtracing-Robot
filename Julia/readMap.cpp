#ifndef READMAP_C
#define	READMAP_C
#define _CRT_SECURE_NO_WARNINGS
#include "readMap.h"
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 15

void readMapFile() {
	char path[] = "/map.txt";
	int lines = 0;
	FILE *map = fopen(path, "r");
	
	if (map == NULL) {
		printf("Error opening file \n");
	} 

	int* map_array[MAP_SIZE][MAP_SIZE];

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			fscanf(map, " %d", &map_array[i][j]);
			printf("%d", map_array[i][j]);
		}
	}

};


#endif // !READMAP_C



