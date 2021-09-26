#ifndef VISUALISATION_C
#define VISUALISATION_C

//#define _CRT_SECURE_NO_WARNINGS



#include "MapVisual.h"

#ifndef MAP_SIZE_X				// This should be overridden by ReadMap.h!
    #define MAP_SIZE_X	19
#endif
#ifndef MAP_SIZE_Y
    #define MAP_SIZE_Y	15
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WEIGHT 500
#define MAX_MAP_CODE 265
#define MIN_MAP_CODE 10

static int width = MAP_SIZE_X * 10;
static int height = MAP_SIZE_Y * 10;
static int finalPathArray[MAP_SIZE_Y][MAP_SIZE_X];

int GetArrayValue(int row, int col)
{
    return finalPathArray[row][col];
}

void SetArrayValue(int x, int y, int value)
{
    finalPathArray[y][x] = value;
}


/*
* Takes in an input array with the map locations. The 1 and 0 will be coded as wall and path and 
* the chosen path should be added in as 2. 
* 
*/
void createBMPFromArrayInput(int array[MAP_SIZE_Y][MAP_SIZE_X]) {
  

    int size = width * height * 4; //for 32-bit bitmap only

    char header[54] = { 0 };
    strcpy(header, "BM");
    memset(&header[2], (int)(54 + size), 1);
    memset(&header[10], (int)54, 1);//always 54
    memset(&header[14], (int)40, 1);//always 40
    memset(&header[18], (int)width, 1);
    memset(&header[22], (int)height, 1);
    memset(&header[26], (short)1, 1);
    memset(&header[28], (short)32, 1);//32bit
    memset(&header[34], (int)size, 1);//pixel size

    unsigned char* pixels = malloc(size);
    // Check if the memory has been successfully
    // allocated by malloc or not
    if (pixels == NULL) {
        printf("Memory not allocated.\n");
        return;
    }

    for (int row = 0; row < MAP_SIZE_Y; row++) {
        for (int col = 0; col < MAP_SIZE_X; col++) {

            for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        int num = MAP_SIZE_Y-1 - row;
                        int p = ((row*10 + i) * width + col*10 + j) * 4;

                        if (array[num][col] == 0) {
                            pixels[p + 0] = 200; //blue
                            pixels[p + 1] = 200;//green
                            pixels[p + 2] = 200;//red
                        }
                        else if (array[num][col] == 1) {
                            pixels[p + 0] = 0; //blue
                            pixels[p + 1] = 0;//green
                            pixels[p + 2] = 0;//red
                        }
                        else if (array[num][col] == 8) {
                            pixels[p + 0] = 0; //blue
                            pixels[p + 1] = 127;//green
                            pixels[p + 2] = 127;//red
                        }
                        else {
                            pixels[p + 0] = 255 - MapCodeToRGB(array[num][col]); //blue
                            pixels[p + 1] = 255 - MapCodeToRGB(array[num][col]);//green
                            pixels[p + 2] = 255 - MapCodeToRGB(array[num][col]);//red
                        }

                    }
                }


        }
    }

    FILE* ft;
    char const* name = "mazeArrayInput.bmp";
    errno_t err = fopen_s(&ft,name, "w+");
    if (ft == NULL)
    {
        fprintf(stderr, "cannot open target file %s\n", name);
        exit(1);
    }
    
    fwrite(header, 1, 54, ft);
     fwrite(pixels, 1, size, ft);
     free(pixels);
    
    fclose(ft);

}


/*
* Creates a BMP file of the map using the static array located in this file. The caller of this function
* should ensure that the array is populated with values before using this function.
*
*/
/*void createBMP() {
  

    int size = width * height * 4; //for 32-bit bitmap only

    char header[54] = { 0 };
    strcpy(header, "BM");
    memset(&header[2], (int)(54 + size), 1);
    memset(&header[10], (int)54, 1);//always 54
    memset(&header[14], (int)40, 1);//always 40
    memset(&header[18], (int)width, 1);
    memset(&header[22], (int)height, 1);
    memset(&header[26], (short)1, 1);
    memset(&header[28], (short)32, 1);//32bit
    memset(&header[34], (int)size, 1);//pixel size

    unsigned char* pixels = malloc(size);
    // Check if the memory has been successfully
    // allocated by malloc or not
    if (pixels == NULL) {
        printf("Memory not allocated.\n");
        return;
    }

    for (int row = 0; row < MAP_SIZE_Y; row++) {
        for (int col = 0; col < MAP_SIZE_X; col++) {

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    int num = MAP_SIZE_Y - 1 - row;
                    int p = ((row * 10 + i) * width + col * 10 + j) * 4;
                    if (finalPathArray[num][col] == 0) {
                        pixels[p + 0] = 0; //blue
                        pixels[p + 1] = 127;//green
                        pixels[p + 2] = 0;//red
                    }
                    if (finalPathArray[num][col] == 1) {
                        pixels[p + 0] = 127; //blue
                        pixels[p + 1] = 0;//green
                        pixels[p + 2] = 0;//red
                    }
                    if (finalPathArray[num][col] == 2) {
                        pixels[p + 0] = 0; //blue
                        pixels[p + 1] = 127;//green
                        pixels[p + 2] = 0;//red
                    }

                }
            }


        }
    }

    FILE* ft;
    char const* name = "maze.bmp";
    errno_t err = fopen_s(&ft, name, "w+");
    if (ft == NULL)
    {
        fprintf(stderr, "cannot open target file %s\n", name);
        exit(1);
    }

    fwrite(header, 1, 54, ft);
    fwrite(pixels, 1, size, ft);
    free(pixels);

    fclose(ft);

}

// Currently not used. Just left over function from original attempts. Can directly call create BMP functions
void initBMPFile() {
    int size = width * height * 4; //for 32-bit bitmap only

    char header[54] = { 0 };
    strcpy(header, "BM");
    memset(&header[2], (int)(54 + size), 1);
    memset(&header[10], (int)54, 1);//always 54
    memset(&header[14], (int)40, 1);//always 40
    memset(&header[18], (int)width, 1);
    memset(&header[22], (int)height, 1);
    memset(&header[26], (short)1, 1);
    memset(&header[28], (short)32, 1);//32bit
    memset(&header[34], (int)size, 1);//pixel size

    unsigned char* pixels = malloc(size);
    // Check if the memory has been successfully
    // allocated by malloc or not
    if (pixels == NULL) {
        printf("Memory not allocated.\n");
        return;
    }

    FILE* fout;

        for (int row = height - 1; row >= 0; row--) {
            for (int column = 0; column < width; column++) {
                int p = (row * width + column) * 4;
                //rbg for gray
                pixels[p + 0] = 185; //blue
                pixels[p + 1] = 184;//green
                pixels[p + 2] = 181;//red
            }
        }
        
        errno_t err = fopen_s(&fout,"maze.bmp", "a");

        if (fout == NULL)
        {
            return;
        }
        fwrite(header, 1, 54, fout);
        fwrite(pixels, 1, size, fout);
        free(pixels);
        fclose(fout);
}


void TestVisualMap()
{
    int map2[MAP_SIZE_Y][MAP_SIZE_X];

    ReadMapFile("map.txt");
    printf("\n ");

    for (int row = 0; row < MAP_SIZE_Y; row++) {
        for (int col = 0; col < MAP_SIZE_X; col++) {
            map2[row][col] = GetMapValue(row, col);
            printf("%d ", map2[row][col]);
        }
        printf("\n ");
    }

    createBMPFromArrayInput(map2);
}

*/

int WeightToMapCode(int weight)
{
    return (int)((((float)weight) / 500) * MAX_MAP_CODE) + MIN_MAP_CODE;
}
int MapCodeToRGB(int code)
{
    if ((code <= MAX_MAP_CODE) && (code >= MIN_MAP_CODE)) { return code - 10; }
    return 0;
}
#endif 