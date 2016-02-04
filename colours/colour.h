#include <string>

#ifndef COLOUR_H
#define COLOUR_H

#pragma once

//	Representations of Colours
class Colour {
public:
	Colour();
	Colour(std::string);
	Colour(int, int, int);
	Colour(double, double, double);
	void changeLAB(double, double, double);
	int getRGB_R();
	int getRGB_G();
	int getRGB_B();
	double getLAB_L();
	double getLAB_A();
	double getLAB_B();
	std::string RGB();
	std::string LAB();
	std::string hex();

protected:
	double _lab_l;
	double _lab_a;
	double _lab_b;
	int _rgb_r;
	int _rgb_g;
	int _rgb_b;
};

// Set of tests of Colour constructors and string representations
void colourTestsHex();
void colourTestsRGB();
void colourTestsLAB();


#endif
