#ifndef FIELD_GEOMETRY_H
#define FIELD_GEOMETRY_H


#pragma once

#include "../colours/colour.h"

// define PI
const double PI = 3.141592653589793238462643383279502884;

int degToRad(double);
int getAngle(int, int);

// double interpolateDistance(int, int, int, double, double, double);
// double interpolateDistanceNoBias(int, int, int, double, double);

int correspondingStep(int, int, int, double);

double interpolateStep(int, int, double, double, double);

Colour interpolateColour(Colour, Colour, int, int, double, bool);

#endif 



