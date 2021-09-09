//======================================================================
//Author: 
//Mr. Fung Yang
//Technician Engineer Research and Design,
//Robotics and control system signal processing Labs,
//Department of Electrical, Computer and Software Engineering,
//The university of Auckland.
//
//Written for teaching design course Compsys301 in ECSE department UOA.
//Date 2012~2018
//=======================================================================

#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <vector>
#include <stdlib.h>     //for rand(), srand()
#include <time.h>       /*time*/
#include <algorithm>    //std::random_shuffle

//using namespace std;

int rand_nextInt(int upperBond);
int rand_nextInt(int lowerBond, int upperBond);
std::vector<int> generateRandomDirections();
void recursion(int r, int c, std::vector<std::vector<int>>& maze,int width, int height);
std::vector<std::vector<int>> generateMaze(int height, int width, int randSeed);
std::vector<std::vector<int>> generateMazeFromStartPos( int height, int width,int r,int c);

#endif