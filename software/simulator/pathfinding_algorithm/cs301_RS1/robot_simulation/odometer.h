#ifndef ODOMETER_H
#define ODOMETER_H

//Updates everytick and sums the distance travelled in cells
void OdometerTick();

//Returns the number of cells travelled as a float
float GetCellDistance();

//Sets the distance to 0
void OdometerReset();

#endif //ODOMETER_H
