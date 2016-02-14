#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


#include "colour.h"
#include "colourConversion.h"

/*
	Contains implementation of a Colour class
	to represent RGB & LAB representations of colours
*/

// default make black:
Colour::Colour() {
	_rgb_r = 0;
	_rgb_g = 0;
	_rgb_b = 0;

	std::vector<double> LAB = RGBtoLAB(_rgb_r, _rgb_g, _rgb_b);

	_lab_l = LAB[0];
	_lab_a = LAB[1];
	_lab_b = LAB[2];

}

// Constructs a colour from a set of 
Colour::Colour(std::string colour) {
	std::string r = colour.substr(1, 2);
	std::string g = colour.substr(3, 2);
	std::string b = colour.substr(5, 2);

	_rgb_r = std::stoi(r, nullptr, 16);
	_rgb_g = std::stoi(g, nullptr, 16);
	_rgb_b = std::stoi(b, nullptr, 16);

	std::vector<double> LAB = RGBtoLAB(_rgb_r, _rgb_g, _rgb_b);
	
	_lab_l = LAB[0];
	_lab_a = LAB[1];
	_lab_b = LAB[2];
}

// Constructs a colour from a set of RGB values
Colour::Colour(int r, int g, int b) {
	// check & clamp RGB values
	_rgb_r = r;
	_rgb_g = g;
	_rgb_b = b;

	std::vector<double> LAB = RGBtoLAB(r, g, b);

	// check & clamp LAB values
	_lab_l = LAB[0];
	_lab_a = LAB[1];
	_lab_b = LAB[2];
}

// Constructs a colour from a set of LAB values
Colour::Colour(double l, double a, double b) {
	// check & clamp LAB values
	_lab_l = l;
	_lab_a = a;
	_lab_b = b;
	if (_lab_l < VALID_LAB_L_LOWER) {
		std::cout << "LAB L: " << _lab_l << " out of range, clamping to lower" << std::endl;
		_lab_l = VALID_LAB_L_LOWER;
	}
	else if (_lab_l > VALID_LAB_L_UPPER) {
		std::cout << "LAB L: " << _lab_l << " out of range, clamping to upper" << std::endl;
		_lab_l = VALID_LAB_L_UPPER;
	}
	if (_lab_a < VALID_LAB_A_LOWER) {
		std::cout << "LAB A: " << _lab_a << " out of range, clamping to lower" << std::endl;
		_lab_a = VALID_LAB_A_LOWER;
	}
	else if (_lab_a > VALID_LAB_A_UPPER) {
		std::cout << "LAB A: " << _lab_a << " out of range, clamping to upper" << std::endl;
		_lab_a = VALID_LAB_A_UPPER;
	}
	if (_lab_b < VALID_LAB_B_LOWER) {
		std::cout << "LAB B: " << _lab_b << " out of range, clamping to lower" << std::endl;
		_lab_b = VALID_LAB_B_LOWER;
	}
	else if (_lab_b > VALID_LAB_B_UPPER) {
		std::cout << "LAB B: " << _lab_b << " out of range, clamping to upper" << std::endl;
		_lab_b = VALID_LAB_B_UPPER;
	}



	std::vector<int> RGB = LABtoRGB(l, a, b);

	_rgb_r = RGB[0];
	_rgb_g = RGB[1];
	_rgb_b = RGB[2];
}

// Changes a colour to new LAB values
void Colour::changeLAB(double l, double a, double b)
{
	_lab_l = l;
	_lab_a = a;
	_lab_b = b;
	std::vector<int> RGB = LABtoRGB(l, a, b);

	_rgb_r = RGB[0];
	_rgb_g = RGB[1];
	_rgb_b = RGB[2];
}

// Returns L* value from LAB
double Colour::getLAB_L()
{
	return _lab_l;
}

// Returns a value from LAB
double Colour::getLAB_A()
{
	return _lab_a;
}

// Returns b value from LAB
double Colour::getLAB_B()
{
	return _lab_b;
}

// Returns r value from RGB
int Colour::getRGB_R()
{
	return _rgb_r;
}

// Returns g value from RGB
int Colour::getRGB_G()
{
	return _rgb_g;
}

// Returns b value from RGB
int Colour::getRGB_B()
{
	return _rgb_b;
}

// Returns a string representation of LAB values
std::string Colour::LAB() {
	std::stringstream LAB;
	LAB << "("
		<< _lab_l
		<< ", "
		<< _lab_a
		<< ", "
		<< _lab_b
		<< ")";
	
	return LAB.str();
}

// Returns a string representation of RGB values
std::string Colour::RGB() {
	std::stringstream RGB;
	RGB << "("
		<< _rgb_r
		<< ", "
		<< _rgb_g
		<< ", "
		<< _rgb_b
		<< ")";
	
	return RGB.str();
}

// Returns hex code for colour
std:: string Colour::hex() {
	std::stringstream hex;
	hex << "#"
		<< std::setfill('0') << std::setw(2) << std::hex << _rgb_r
		<< std::setfill('0') << std::setw(2) << std::hex << _rgb_g 
		<< std::setfill('0') << std::setw(2) << std::hex << _rgb_b;

	return hex.str();
}

Magick::ColorRGB Colour::toMagick() {
	double r = convertRGBtoDec(_rgb_r);
	double g = convertRGBtoDec(_rgb_g);
	double b = convertRGBtoDec(_rgb_b);

	Magick::ColorRGB tempCol(r, g, b);

	return tempCol;
}


// Tests for Colour class
void colourTestsHex() {
	// Test black
	Colour black = Colour("#000000");

	std::cout << "Representations of black" << std::endl;
	std::cout << "Hex: " << black.hex() << std::endl;
	std::cout << "L*AB: " << black.LAB() << std::endl;
	std::cout << "RGB: " << black.RGB() << std::endl;

	// Test white
	Colour white = Colour("#FFFFFF");
	std::cout << "Representations of white" << std::endl;
	std::cout << "Hex: " << white.hex() << std::endl;
	std::cout << "L*AB: " << white.LAB() << std::endl;
	std::cout << "RGB: " << white.RGB() << std::endl;
	
	// Test brown
	Colour brown = Colour("#a52a2a");
	std::cout << "Representations of brown" << std::endl;
	std::cout << "Hex: " << brown.hex() << std::endl;
	std::cout << "L*AB: " << brown.LAB() << std::endl;
	std::cout << "RGB: " << brown.RGB() << std::endl;

	// Test rebecca purple
	Colour rebeccap = Colour("#663399");
	std::cout << "Representations of rebecca purple" << std::endl;
	std::cout << "Hex: " << rebeccap.hex() << std::endl;
	std::cout << "L*AB: " << rebeccap.LAB() << std::endl;
	std::cout << "RGB: " << rebeccap.RGB() << std::endl;

	// Test dark sea green
	Colour dsgreen = Colour("#8fbc8f");
	std::cout << "Representations of dark sea green" << std::endl;
	std::cout << "Hex: " << dsgreen.hex() << std::endl;
	std::cout << "L*AB: " << dsgreen.LAB() << std::endl;
	std::cout << "RGB: " << dsgreen.RGB() << std::endl;

}

void colourTestsRGB() {
	// Test black
	Colour black = Colour(0, 0, 0);

	std::cout << "Representations of black" << std::endl;
	std::cout << "Hex: " << black.hex() << std::endl;
	std::cout << "L*AB: " << black.LAB() << std::endl;
	std::cout << "RGB: " << black.RGB() << std::endl;

	// Test white
	Colour white = Colour(255, 255, 255);
	std::cout << "Representations of white" << std::endl;
	std::cout << "Hex: " << white.hex() << std::endl;
	std::cout << "L*AB: " << white.LAB() << std::endl;
	std::cout << "RGB: " << white.RGB() << std::endl;

	// Test brown
	Colour brown = Colour(165, 42, 42);
	std::cout << "Representations of brown" << std::endl;
	std::cout << "Hex: " << brown.hex() << std::endl;
	std::cout << "L*AB: " << brown.LAB() << std::endl;
	std::cout << "RGB: " << brown.RGB() << std::endl;

	// Test rebecca purple
	Colour rebeccap = Colour(102, 51, 153);
	std::cout << "Representations of rebecca purple" << std::endl;
	std::cout << "Hex: " << rebeccap.hex() << std::endl;
	std::cout << "L*AB: " << rebeccap.LAB() << std::endl;
	std::cout << "RGB: " << rebeccap.RGB() << std::endl;

	// Test dark sea green
	Colour dsgreen = Colour(143, 188, 143);
	std::cout << "Representations of dark sea green" << std::endl;
	std::cout << "Hex: " << dsgreen.hex() << std::endl;
	std::cout << "L*AB: " << dsgreen.LAB() << std::endl;
	std::cout << "RGB: " << dsgreen.RGB() << std::endl;
}

void colourTestsLAB() {
	// Test black
	Colour black = Colour(0.0, 0.0, 0.0);

	std::cout << "Representations of black" << std::endl;
	std::cout << "Hex: " << black.hex() << std::endl;
	std::cout << "L*AB: " << black.LAB() << std::endl;
	std::cout << "RGB: " << black.RGB() << std::endl;

	// Test white
	Colour white = Colour(100.0, 0.0, 0.009);
	std::cout << "Representations of white" << std::endl;
	std::cout << "Hex: " << white.hex() << std::endl;
	std::cout << "L*AB: " << white.LAB() << std::endl;
	std::cout << "RGB: " << white.RGB() << std::endl;

	// Test brown
	Colour brown = Colour(37.525, 49.689, 30.54);
	std::cout << "Representations of brown" << std::endl;
	std::cout << "Hex: " << brown.hex() << std::endl;
	std::cout << "L*AB: " << brown.LAB() << std::endl;
	std::cout << "RGB: " << brown.RGB() << std::endl;

	// Test rebecca purple
	Colour rebeccap = Colour(32.903, 42.885, -47.154);
	std::cout << "Representations of rebecca purple" << std::endl;
	std::cout << "Hex: " << rebeccap.hex() << std::endl;
	std::cout << "L*AB: " << rebeccap.LAB() << std::endl;
	std::cout << "RGB: " << rebeccap.RGB() << std::endl;

	// Test dark sea green
	Colour dsgreen = Colour(72.087, -23.82, 18.033);
	std::cout << "Representations of dark sea green" << std::endl;
	std::cout << "Hex: " << dsgreen.hex() << std::endl;
	std::cout << "L*AB: " << dsgreen.LAB() << std::endl;
	std::cout << "RGB: " << dsgreen.RGB() << std::endl;

	// Test changeLAB
	Colour dsToBlack = dsgreen;
	dsToBlack.changeLAB(0, 0, 0);
	std::cout << "Representation of dsgreen changed to black" << std::endl;
	std::cout << "Hex: " << dsToBlack.hex() << std::endl;
	std::cout << "L*AB: " << dsToBlack.LAB() << std::endl;
	std::cout << "RGB: " << dsToBlack.RGB() << std::endl;

	// Test dark sea green
	std::cout << "Representations of old dsgreen" << std::endl;
	std::cout << "Hex: " << dsgreen.hex() << std::endl;
	std::cout << "L*AB: " << dsgreen.LAB() << std::endl;
	std::cout << "RGB: " << dsgreen.RGB() << std::endl;
}