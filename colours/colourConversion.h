#ifndef COLOUR_CONVERSION_H
#define COLOUR_CONVERSION_H

#include <vector>

#pragma once

const double REF_X = 95.047;
const double REF_Y = 100.000;
const double REF_Z = 108.883;

double convertRGBtoDec(int);

std::vector<double> RGBtoXYZ(int, int, int);
double RGBtoXYZcompander(double);

std::vector<double> LABtoXYZ(double, double, double);
double LABtoXYZhelper(double);

std::vector<int> XYZtoRGB(std::vector<double>);
double XYZtoRGBhelper(double);

std::vector<double> XYZtoLAB(std::vector<double>);
double XYZtoLABhelper(double);

std::vector<double> RGBtoLAB(int, int, int);
std::vector<int> LABtoRGB(double, double, double);

void colourConversionTests();
#endif