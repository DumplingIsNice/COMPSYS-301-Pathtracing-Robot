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

#define MAP_SIZE_Y 15
#define MAP_SIZE_X 19

#define MAP_NAME "map.txt"


// Return the integer value at the given indices in the map array.
int GetMapValue(int row, int col);

// Convert ASCII characters to integer.
int ASCIIToInt(char c);

// Read a gridded .txt file of a map, treating each character as an int.
// Map data must be arranged in rows with no separation or delimiters.
int ReadMapFile(const char* file_name, int map[MAP_SIZE_Y][MAP_SIZE_X]);

// Print the map in grid as 1s and 0s via standard output.
void PrintMap(int map[MAP_SIZE_Y][MAP_SIZE_X]);

// Read the map file and print it to console.
void TestPrintMap();

#endif // !READMAP_H
