#include <iostream>

#include "colours/colour.h"
#include "colours/colourConversion.h"
#include "colourFields/radialFieldTest.h"
#include "colourFields/linearFieldTest.h"
#include "tiling\squareTiling.h"

// handles linear field tests
void linearField() {
	int option;
	 
	std::cout << "1 for animation tests, 2 for basic gradients" << std::endl;
	std::cin >> option;

	if (option == 1) {
		effectLinearFieldTest();
	}
	else if (option == 2) {
		basicRadialFieldTest();
	}

	std::cin.get();
}

// handles radial field tests
void radialField() {
	int option;

	std::cout << "1 for animation tests, 2 for basic gradients" << std::endl;
	std::cin >> option;

	if (option == 1) {
		effectRadialFieldTest();
	}
	else if (option == 2) {
		basicRadialFieldTest();
	}

	std::cin.get();
}

void colorfields() {
	int option;

	std::cout << "1 for radial field tests, 2 for linear field tests" << std::endl;
	std::cin >> option;

	if (option == 1) {
		radialField();
	}
	else if (option == 2) {
		linearField();
	}
}

void tiling() {
	squareTilingTest();
}

int main() {
	int option;
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

	std::cout << "1 for tiling tests, 2 for field tests" << std::endl;
	std::cin >> option;

	if (option == 1) {
		tiling();
	}
	else if (option == 2) {
		colorfields();
	}

	std::cin.get();

	return 0;
}