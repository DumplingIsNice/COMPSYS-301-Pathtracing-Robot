#ifndef ODOMETER_H
#define ODOMETER_H

//reads an exten flag to determine whether the robot is moving straight, takes the time and converts into a floor distance
float calculateDistance();

int cellxTravelled(float floorDistance);

int cellyTravelled(float floorDistance);

#endif //ODOMETER_H
