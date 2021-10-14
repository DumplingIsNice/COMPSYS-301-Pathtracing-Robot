#ifndef ACTUATION_H
#define ACTUATION_H

/* This file includes all actuation function's signature from main.cpp */

// Sets virtual movement at end of each update
void setVirtualCarSpeed(float linearSpeed, float angularSpeed);

// Modifies virtualCarLinearSpeed_seed and virtualCarAngularSpeed_seed.
void InitSpeedSeed();
void LinearForward();
void LinearZero();
void AngularLeft();
void AngularRight();
void AngularZero();
void AlignLeft();
void AlignRight();
void AlignZero();

#endif // ACTUATION_H