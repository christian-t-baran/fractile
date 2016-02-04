#include <iostream>

#include "colours/colour.h"
#include "colours/colourConversion.h"
#include "colourFields/radialFieldTest.h"

int main() {
	/*
	std::cout << "Colour conversion tests: " << std::endl;
	colourConversionTests();
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "Colour hex constructor tests: " << std::endl;
	colourTestsHex();
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "Colour RGB constructor tests: " << std::endl;
	colourTestsRGB();
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "Colour LAB constructor tests: " << std::endl;
	colourTestsLAB();
	std::cout << std::endl << std::endl << std::endl;
	*/

	std::cout << "Radial Field Basic Test" << std::endl;
	basicRadialFieldTest();

	std::cin.get();

	return 0;
}