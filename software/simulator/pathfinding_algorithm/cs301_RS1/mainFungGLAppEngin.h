#ifndef _MAIN_FUNG_GL_APP_ENGIN_
#define _MAIN_FUNG_GL_APP_ENGIN_

#define RED_GHOST 0
#define GREEN_GHOST 1
#define BLUE_GHOST 2

#define PLACE_SENSORS_AUTO_SEP 0
#define PLACE_SENSORS_SEP_USER_DEFINED 1
#define PLACE_SENSORS_USER_DEFINED 2

int FungGlAppMainFuction(int argc, char** argv);
int virtualCarInit();
int virtualCarUpdate();

float pixelToCoordX(float pixel_x);
float pixelToCoordY(float pixel_y);
float coordToPixelX(float coord_x);
float coordToPixelY(float coord_y);
int pixelToCellX(float pixel_x);
int pixelToCellY(float pixel_y);
float cellToPixelX(int cell_x);
float cellToPixelY(int cell_y);
float cellToCoordX(float cell_x);
float cellToCoordY(float cell_y);
int coordToCellX(float coord_x);
int coordToCellY(float coord_y);

//---------------------------------
int pixelToFloorX(float pixel_x);
int pixelToFloorY(float pixel_y);
float floorToPixelX(int floor_x);
float floorToPixelY(int floor_y);
//---------------------------------
float floorToCoordX(float cell_x);
float floorToCoordY(float cell_y);
int coordToFloorX(float coord_x);
int coordToFloorY(float coord_y);
//----------------------------------------------------------
float floorToCellX(float cell_x);
float floorToCellY(float cell_y);
int cellToFloorX(float coord_x);
int cellToFloorY(float coord_y);
//-------------------------------

extern float pixelToCoordScaleFactor;
extern float coordToPixelScaleFactor;
extern float pixelToFloorScaleFactor;
extern float floorToPixelScaleFactor;
extern float floorToCoordScaleFactor;

extern float currentCarPosFloor_X, currentCarPosFloor_Y, virtualCarLinearSpeedFloor, virtualCarAngularSpeed_seed, currentCarAngle;

class ghostInfoPack
{
public:
	double	coord_x, coord_y;
	int direction;
	float speed;
	int ghostType;
};

#endif
