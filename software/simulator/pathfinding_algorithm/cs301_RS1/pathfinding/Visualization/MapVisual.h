#ifndef MAPVISUAL_H
#define MAPVISUAL_H

#include "../FileUtility/ReadMap.h"

int GetArrayValue(int row, int col);
void SetArrayValue(int x, int y, int value);
void createBMPFromArrayInput(int array[MAP_SIZE_Y][MAP_SIZE_X]);
void createBMP();
void initBMPFile();

/* Conversion Functions */
int WeightToMapCode(int weight);
int MapCodeToRGB(int code);
int WeightToRGB(int weight);

void TestVisualMap();

#endif // MAPVISUAL_C
