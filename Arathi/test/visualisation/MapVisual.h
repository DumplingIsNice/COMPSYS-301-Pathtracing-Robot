#ifndef MAPVISUAL_H
#define MAPVISUAL_H

#define MAP_SIZE_Y 15
#define MAP_SIZE_X 15

void writeMapArray(int x, int y, int value);
void createMazeBMP(int array[MAP_SIZE_Y][MAP_SIZE_X]);

void initBMPFile();





#endif // MAPVISUAL_C
