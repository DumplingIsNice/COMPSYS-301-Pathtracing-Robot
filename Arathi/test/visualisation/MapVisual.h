#ifndef MAPVISUAL_H
#define MAPVISUAL_H

#define MAP_SIZE_Y 15
#define MAP_SIZE_X 15

int GetArrayValue(int row, int col);
void SetArrayValue(int x, int y, int value);
void createBMPFromArrayInput(int array[MAP_SIZE_Y][MAP_SIZE_X]);
void createBMP();
void initBMPFile();





#endif // MAPVISUAL_C
