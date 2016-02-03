#ifndef COLOUR_CONVERSION_H
#define COLOUR_CONVERSION_H

#pragma once

const double REF_X = 95.047;
const double REF_Y = 100.000;
const double REF_Z = 108.883;

double* RGBtoXYZ(int, int, int);
double RGBtoXYZcompander(double);

double* LABtoXYZ(double, double, double);
double LABtoXYZhelper(double);

int* XYZtoRGB(double[]);
double XYZtoRGBhelper(double);

double* XYZtoLAB(double[]);
double XYZtoLABhelper(double);

double* RGBtoLAB(int, int, int);
int* LABtoRGB(double, double, double);

void colourConversionTests();
#endif