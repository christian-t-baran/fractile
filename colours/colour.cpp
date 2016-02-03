#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>


#include "colour.h"
#include "colourConversion.h"

/*
	Contains implementation of a Colour class
	to represent RGB & LAB representations of colours
*/

// Constructs a colour from a set of 
Colour::Colour(std::string colour) {
	std::string r = colour.substr(1, 2);
	std::string g = colour.substr(3, 2);
	std::string b = colour.substr(5, 2);

	rgb_r = std::stoi(r, nullptr, 16);
	rgb_g = std::stoi(g, nullptr, 16);
	rgb_b = std::stoi(b, nullptr, 16);

	double* LAB = RGBtoLAB(rgb_r, rgb_g, rgb_b);
	
	lab_l = LAB[0];
	lab_a = LAB[1];
	lab_b = LAB[2];

	delete LAB;
}

// Constructs a colour from a set of RGB values
Colour::Colour(int r, int g, int b) {
	rgb_r = r;
	rgb_g = g;
	rgb_b = b;

	double* LAB = RGBtoLAB(r, g, b);

	lab_l = LAB[0];
	lab_a = LAB[1];
	lab_b = LAB[2];

	delete LAB;
}

// Constructs a colour from a set of LAB values
Colour::Colour(double l, double a, double b) {
	lab_l = l;
	lab_a = a;
	lab_b = b;

	int* RGB = LABtoRGB(l, a, b);

	rgb_r = RGB[0];
	rgb_g = RGB[1];
	rgb_b = RGB[2];

	delete RGB;
}

// Returns L* value from LAB
double Colour::getLAB_L()
{
	return lab_l;
}

// Returns a value from LAB
double Colour::getLAB_A()
{
	return lab_a;
}

// Returns b value from LAB
double Colour::getLAB_B()
{
	return lab_b;
}

// Returns r value from RGB
int Colour::getRGB_R()
{
	return rgb_r;
}

// Returns g value from RGB
int Colour::getRGB_G()
{
	return rgb_g;
}

// Returns b value from RGB
int Colour::getRGB_B()
{
	return rgb_b;
}

// Returns a string representation of LAB values
std::string Colour::LAB() {
	std::stringstream LAB;
	LAB << "("
		<< lab_l
		<< ", "
		<< lab_a
		<< ", "
		<< lab_b
		<< ")";
	
	return LAB.str();
}

// Returns a string representation of RGB values
std::string Colour::RGB() {
	std::stringstream RGB;
	RGB << "("
		<< rgb_r
		<< ", "
		<< rgb_g
		<< ", "
		<< rgb_b
		<< ")";
	
	return RGB.str();
}

// Returns hex code for colour
std:: string Colour::hex() {
	std::stringstream hex;
	hex << "#"
		<< std::setfill('0') << std::setw(2) << std::hex << rgb_r
		<< std::setfill('0') << std::setw(2) << std::hex << rgb_g 
		<< std::setfill('0') << std::setw(2) << std::hex << rgb_b;

	return hex.str();
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

}