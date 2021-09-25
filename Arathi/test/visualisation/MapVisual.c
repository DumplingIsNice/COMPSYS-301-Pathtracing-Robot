#ifndef VISUALISATION_C
#define VISUALISATION_C

//#define _CRT_SECURE_NO_WARNINGS


#include "MapVisual.h"
#include "ReadMap.h"

#ifndef MAP_SIZE_X				// This should be overridden by ReadMap.h!
    #define MAP_SIZE_X	19
#endif
#ifndef MAP_SIZE_Y
    #define MAP_SIZE_Y	15
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int width = MAP_SIZE_X * 10;
static int height = MAP_SIZE_Y * 10;

void createPathBMP(int array[MAP_SIZE_Y][MAP_SIZE_X]) {
    //xpos = xpos * 10;
    //ypos = ypos * 10;

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
                        int p = ((row*10 + i) * width + col*10 + j) * 4;
                        if (array[row][col] == 0) {
                            pixels[p + 0] = 0; //blue
                            pixels[p + 1] = 127;//green
                            pixels[p + 2] = 0;//red
                        }
                        if (array[row][col] == 1) {
                            pixels[p + 0] = 127; //blue
                            pixels[p + 1] = 0;//green
                            pixels[p + 2] = 0;//red
                        }
                        if (array[row][col] == 2) {
                            pixels[p + 0] = 0; //blue
                            pixels[p + 1] = 0;//green
                            pixels[p + 2] = 127;//red
                        }

                    }
                }


        }
    }

    


    FILE* ft;
    char const* name = "maze.bmp";
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





int main(void)
{
    int map2[MAP_SIZE_Y][MAP_SIZE_X] = { 0 };


    ReadMapFile("map.txt");

    for (int row = 0; row < MAP_SIZE_Y; row++) {
        for (int col = 0; col < MAP_SIZE_X; col++) {
            map2[row][col] = GetMapValue(row, col);
            printf("%d ", map2[row][col]);
        }
    }
    
    createPathBMP(map2);


    return 0;
}






#endif 