#include <string>

#ifndef COLOUR_H
#define COLOUR_H

#pragma once

//	Representations of Colours
class Colour {
private:
	double lab_l;
	double lab_a;
	double lab_b;
	int rgb_r;
	int rgb_g;
	int rgb_b;

public:
	Colour(std::string);
	Colour(int, int, int);
	Colour(double, double, double);
	int getRGB_R();
	int getRGB_G();
	int getRGB_B();
	double getLAB_L();
	double getLAB_A();
	double getLAB_B();
	std::string RGB();
	std::string LAB();
	std::string hex();
};

// Set of tests of Colour constructors and string representations
void colourTestsHex();
void colourTestsRGB();
void colourTestsLAB();


#endif
