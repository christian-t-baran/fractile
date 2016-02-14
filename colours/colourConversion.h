#ifndef COLOUR_CONVERSION_H
#define COLOUR_CONVERSION_H

#include <vector>

#pragma once

// valid colour ranges
const int VALID_RGB_LOWER = 0;
const int VALID_RGB_UPPER = 255;
const double VALID_LAB_L_LOWER = 0;
const double VALID_LAB_L_UPPER = 100;
const double VALID_LAB_A_LOWER = -86.188001161251748;
const double VALID_LAB_A_UPPER = 98.24941490526;
const double VALID_LAB_B_LOWER = -107.9;
const double VALID_LAB_B_UPPER = 94.487327241851375;

// XYZ references
const double REF_X = 95.047;
const double REF_Y = 100.000;
const double REF_Z = 108.883;

// Conversion values
const double EPSILON = 0.008856;
const double KAPPA = 903.3;


double convertRGBtoDec(int);

void clampRGB(std::vector<int>&);

std::vector<double> RGBtoXYZ(int, int, int);
double RGBtoXYZcompander(double);

std::vector<double> LABtoXYZ(double, double, double);
double LABtoXYZhelperXZ(double);
double LABtoXYZhelperY(double);

std::vector<int> XYZtoRGB(std::vector<double>);
double XYZtoRGBhelper(double);

std::vector<double> XYZtoLAB(std::vector<double>);
double XYZtoLABhelper(double);

std::vector<double> RGBtoLAB(int, int, int);
std::vector<int> LABtoRGB(double, double, double);

void colourConversionTests();
#endif