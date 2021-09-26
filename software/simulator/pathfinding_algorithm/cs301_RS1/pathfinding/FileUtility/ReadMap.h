#ifndef READMAP_H
#define READMAP_H

/*
	Read Map

	Read Map is responsible for reading the map.txt file and storing the
	values.

	Run ReadMapFile() to load the file contents to the static ('private')
	array: int map[MAP_SIZE_Y][MAP_SIZE_X]
	Then access values in the array with GetMapValue().

	MUST DEFINE THE DIMENSIONS OF THE MAP, AND THE NAME OF THE MAP FILE!
*/

#ifndef MAP_SIZE_Y
	#define MAP_SIZE_Y	15
#endif
#ifndef MAP_SIZE_X
	#define MAP_SIZE_X	19
#endif
#ifndef MAP_NAME
	#define MAP_NAME "map.txt"
#endif

// Return the integer value at the given indices in the map array.
int GetMapValue(int row, int col);

// Convert ASCII characters to integer.
int ASCIIToInt(char c);

// Read a gridded .txt file of a map, treating each character as an int.
// Reads data to 'private' system map in ReadMap.c
// Map data must be arranged in rows with no separation or delimiters.
int ReadMapFile(const char* file_name);

// Print the map in grid as 1s and 0s via standard output.
void PrintMap(const int map[MAP_SIZE_Y][MAP_SIZE_X]);

// Prints the 'private' system map in ReadMap.c
void PrintSystemMap();

// Prints the 'private' output map in ReadMap.c (to track runtime position)
void PrintOutputMap();

// Writes the 'private' output map in ReadMap.c (to track runtime position)
void WriteOutputMap(const int x, const int y, const int value);

void CreateFinalMap();

// Prints the 'private' final map in ReadMap.c (for one final pathway)
void PrintFinalMap();

// Writes the 'private' fina  map in ReadMap.c (for one final pathway)
void WriteFinalMap(const int x, const int y, const int value);

// Read the map file and print it to console.
void TestPrintMap();

#endif // !READMAP_H
