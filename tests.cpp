#include <iostream>
#include <Magick++.h>

#include "colours/colour.h"
#include "colours/colourConversion.h"
#include "colourFields/fieldTest.h"
#include "tiling/squareTiling.h"
#include "tiling/triangleTiling.h"
#include "tiling/curveTiling.h"

// handles linear field tests

void colourFields() {
	fieldTest();
}

void squareTiling() {
	int option;

	std::cout << "1 for basic square tiling, 2 for recursive square tiling: " << std::endl;
	std::cin >> option;

	if (option == 1) {
		squareTilingTest();
	}
	else if (option == 2) {
		recursiveSubdivideSquare();
	}
}

void triangleTiling() {
	int option;

	std::cout << "1 for basic triangle tiling, 2 for recursive triangle tiling: " << std::endl;
	std::cin >> option;

	if (option == 1) {
		basicTriangleTiling();
	}
	else if (option == 2) {
		recursiveTriangleTiling();
	}
}

void tiling() {
	int option;

	std::cout << "1 for square tiling, 2 for triangle tiling, 3 for curves: " << std::endl;
	std::cin >> option;

	if ( option == 1) {
		squareTiling();
	}
	else if (option == 2) {
		triangleTiling();
	}
	else if (option == 3) {
		curveTiling();
	}
}

void colourTests() {
	
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
	
	std::cin.get();
}

// argv[0] -> path to ImageMagick
int main(int argc, char *argv[]){
	int option;

	Magick::InitializeMagick(argv[0]);


	std::cout << "1 for tiling tests, 2 for field tests, 3 for colour conversion + colour tests: " << std::endl;
	std::cin >> option;

	if (option == 1) {
		tiling();
	}
	else if (option == 2) {
		colourFields();
	}
	else if (option == 3) {
		colourTests();
	}

	std::cin.get();

	return 0;
}