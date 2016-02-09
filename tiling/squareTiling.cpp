#include <Magick++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


#include "../colourFields/fieldFactory.h"
#include "../colourFields/colourField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"
#include "../tiles/rectangle.h"
#include "drawing.h"
#include "squareTiling.h"
#include "tilingGeometry.h"

// Creates an image from a LinearField

void writeSquares(int xLL, int yLL, int xUR, int yUR, int square, ColourField& field, Magick::Image& image) {

	for (int i = xLL; i < xUR; i = i + square) {
		for (int j = yLL; j < yUR; j = j + square) {
			Rectangle square(i, j, square, square);

			drawShape(square, field, image);
		}
	}


}

// Creates a gif from a LinearField effect
void writeSquareBiasedGif(int x, int y, int square, ColourField& field) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(x) + "x" + std::to_string(y);

	while (!field.finishedEffect()) {
		Magick::Image testImage(dimensions.c_str(), "white");
		writeSquares(0, 0, x, y, square, field, testImage);
		testImage.animationDelay(10);

		frames.push_back(testImage);
		field.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}


void writeRecursiveDiagonalSquareImage
	(int xLL, int yLL, int xUR, int yUR, int square, ColourField& field, Magick::Image& image, bool period, int n){
	// if drawing full square
	if (n == 0) {
		Rectangle shape(xLL, yLL, square, square);

		drawShape(shape, field, image);
	}
	// else if drawing secondary square
	else if (n == 1) {
		// if square is odd or small
		if (((square % 2) != 0) || (square <= 4)) {
			writeRecursiveDiagonalSquareImage(xLL, yLL, xUR, yUR, square, field, image, !period, 0);
		}
		else {
			square = square / 2;

			if (period) {
				for (int i = xLL; i < xUR; i = i + square) {
					for (int j = yLL; j < yUR; j = j + square) {
						if ((i == (xLL + square)) && (j == (yLL + square))) {
							writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 0);
						}
						else if ((i == (xLL + square)) || (j == (yLL + square))) {
							if (i == (xLL + square)) {
								writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 1);
							}
							else if (j == (yLL + square)) {
								writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 1);
							}
						}
						// if base square draw it
						else {
							writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 0);
						}
					}
				}
			}
			else {
				for (int i = xLL; i < xUR; i = i + square) {
					for (int j = yLL; j < yUR; j = j + square) {
						if ((i == (xLL + square)) && (j == (yLL + square))) {
							writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 1);
						}
						else if ((i == (xLL + square)) || (j == (yLL + square))) {
							if (i == (xLL + square)) {
								writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 0);
							}
							else if (j == (yLL + square)) {
								writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 0);
							}
						}
						// if base square draw it
						else {
							writeRecursiveDiagonalSquareImage(i, j, i + square, j + square, square, field, image, !period, 1);
						}
					}
				}
			}
			
		}
	}
}

void writeRecursiveSquareImage
	(int xLL, int yLL, int xUR, int yUR, int square, ColourField& field, Magick::Image& image, int n) {

	// if n = 0, just draw square in specified position
	if (n == 0) {
		Rectangle shape(xLL, yLL, square, square);

		drawShape(shape, field, image);
	}
	// if n = 1, subdivide square into 4
	else if (n == 1) {
		square = square / 2;
		writeSquares(xLL, yLL, xUR, yUR, square, field, image);
	}
	// if n = 2, either draw single square or recursive pattern
	else if (n == 2) {

		// if square is odd or small
		if (((square % 2) != 0) || (square <= 4)) {
			writeRecursiveSquareImage(xLL, yLL, xUR, yUR, square, field, image, 0);
		}
		else {
			square = square / 2;

			for (int i = xLL; i < xUR; i = i + square) {
				for (int j = yLL; j < yUR; j = j + square) {
					if ((i == (xLL + square)) && (j == (yLL + square))) {
						writeRecursiveSquareImage(i, j, xUR, yUR, square, field, image, 2);
					}
					// if (0, 1) or (1, 0) square, subdivide it)
					else if ((i == (xLL + square)) || (j == (yLL + square))) {
						if (i == (xLL + square)) {
							writeRecursiveSquareImage(i, j, i + square, j + square, square, field, image, 1);
						}
						else if (j == (yLL + square)) {
							writeRecursiveSquareImage(i, j, i + square, j + square, square, field, image, 1);
						}
					}
					// if base square draw it
					else {
						writeRecursiveSquareImage(i, j, i + square, j + square, square, field, image, 0);
					}
				}
			}
		}
	}

}

void sierpinskiCarpet(int xLL, int yLL, int xUR, int yUR, int square, ColourField& fieldFill, ColourField& fieldBack, Magick::Image& image) {
	square = square / 3;

	for (int i = xLL; i < xUR; i = i + square) {
		for (int j = yLL; j < yUR; j = j + square) {
			if ((i == xLL + square) && (j == yLL + square) ){
				Rectangle shape(i, j, square, square);

				drawShape(shape, fieldBack, image);
			}
			else if (square <= 9) {
				Rectangle shape(i, j, square, square);

				drawShape(shape, fieldFill, image);
			}
			else {
				sierpinskiCarpet(i, j, i + square, j + square, square, fieldFill, fieldBack, image);
			}
		}
	}


}

// Creates a gif from a LinearField effect
void writeRecursiveSquareBiasedGif(int square, ColourField& field, int option) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(square) + "x" + std::to_string(square);
	ColourField* back;

	int iterations;

	if (option == 3) {
		back = fieldFactory(square, square);
		iterations = LCM(field.effectStepTotal(), (*back).effectStepTotal() );
	}
	else {
		iterations = field.effectStepTotal();
	}

	
	for (int i = 0; i < iterations; i++) {
		Magick::Image testImage(dimensions.c_str(), "white");
		if (option == 1) {
			writeRecursiveSquareImage(0, 0, square, square, square, field, testImage, 2);
		}
		else if (option == 2) {
			writeRecursiveDiagonalSquareImage(0, 0, square, square, square, field, testImage, true, 1);
		}
		else if (option == 3) {
			if (field.finishedEffect()) {
				field.reinitialize();
			}
			if ((*back).finishedEffect()) {
				(*back).reinitialize();
			}

			Colour colour1 = Colour(0, 0, 0);
			Colour colour2 = Colour(0, 0, 0);

			std::vector<Colour> colours = std::vector<Colour>();
			colours.push_back(colour1);
			colours.push_back(colour2);

			sierpinskiCarpet(0, 0, square, square, square, field, *back, testImage);

		}
		testImage.animationDelay(10);

		frames.push_back(testImage);
		field.stepForward();
		if (option == 3) {
			(*back).stepForward();
		}
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}


void squareTilingTest() {
	std::cout << "Basic Square Tiling Test" << std::endl;


	std::string colourStr1;
	std::string colourStr2;

	int square;
	int columns;
	int rows;

	std::cout << "Please enter the square size: ";
	std::cin >> square;
	std::cout << "Please enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Please enter the number of columns: ";
	std::cin >> columns;
	
	int x = rows * square;
	int y = columns * square;

	ColourField* field = fieldFactory(x, y);

	writeSquareBiasedGif(x, y, square, *field);
	delete field;

	std::cin.get();
}

void recursiveSubdivideSquare(){
	Magick::InitializeMagick("C:\\ImageMagick");

	std::cout << "Recursive Square Tiling Test" << std::endl;

	std::string colourStr1;
	std::string colourStr2;

	int square;
	int optionTiling;

	std::cout << "Please enter the square size: ";
	std::cin >> square;

	std::cout << "Please enter 1 for left diagonal to right, 2 for split diagonal, 3 for Sierpinski Carpet: ";
	std::cin >> optionTiling;

	ColourField* field = fieldFactory(square, square);

	writeRecursiveSquareBiasedGif(square, *field, optionTiling);
	delete field;

	std::cin.get();
}
