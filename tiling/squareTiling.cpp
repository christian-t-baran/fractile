#include <Magick++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


#include "../colourFields/linearField.h"
#include "../colourFields/radialField.h"
#include "../colourFields/radialDiamondField.h"
#include "../colourFields/radialSquareField.h"
#include "../colourFields/radialXField.h"
#include "../colourFields/colourField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"
#include "tilingGeometry.h"

// Creates an image from a LinearField

void writeSquareImage(int x, int y, int square, ColourField& field, Magick::Image& image) {
	std::pair<int, int> coord = centerRectangle(x, x + square, y, y + square);

	Colour fieldCol = field.getColourAt(coord.first, coord.second);
	double r = convertRGBtoDec(fieldCol.getRGB_R());
	double g = convertRGBtoDec(fieldCol.getRGB_G());
	double b = convertRGBtoDec(fieldCol.getRGB_B());

	Magick::ColorRGB tempCol(r, g, b);

	image.strokeColor(tempCol);
	image.strokeWidth(0);
	image.fillColor(tempCol);

	image.draw(Magick::DrawableRectangle(x, y + square, x + square, y));
}


void writeSquares(int xLL, int yLL, int xUR, int yUR, int square, ColourField& field, Magick::Image& image) {

	for (int i = xLL; i < xUR; i = i + square) {
		for (int j = yLL; j < yUR; j = j + square) {
			writeSquareImage(i, j, square, field, image);
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
		writeSquareImage(xLL, yLL, square, field, image);
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
		writeSquareImage(xLL, yLL, square, field, image);
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
// Creates a gif from a LinearField effect
void writeRecursiveSquareBiasedGif(int square, ColourField& field, int option) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(square) + "x" + std::to_string(square);

	while (!field.finishedEffect()) {
		Magick::Image testImage(dimensions.c_str(), "white");
		if (option == 1) {
			writeRecursiveSquareImage(0, 0, square, square, square, field, testImage, 2);
		}
		else if (option == 2) {
			writeRecursiveDiagonalSquareImage(0, 0, square, square, square, field, testImage, true, 1);
		}
		testImage.animationDelay(10);

		frames.push_back(testImage);
		field.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}



LinearField* LinearFieldBuilder(int x, int y) {
	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int axis;
	int step;
	int copies;

	double bias;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create linear field
	std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse): ";
	std::cin >> effect;
	std::cout << "Enter 1 to gradate on x axis, 2 for y: ";
	std::cin >> axis;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;
	std::cout << "Please enter effect step: ";
	std::cin >> effectStep;
	std::cout << "Please enter effect bias: ";
	std::cin >> effectBias;
	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colourStr1;
	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colourStr2;

	// get pulse colour if it applies
	if (effect == 3) {
		std::cout << "Please enter pulse colour (#HEX): ";
		std::cin >> colourPulse;

	}

	Colour colour1 = Colour(colourStr1);
	Colour colour2 = Colour(colourStr2);

	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour1);
	colours.push_back(colour2);

	LinearField* test = new LinearField(colours, x, y, bias);

	// set up effect
	if (effect == 1) {
		(*test).setStrobe(effectStep, effectBias);
	}
	else if (effect == 2) {
		(*test).setConverge(effectStep, effectBias);
	}
	else if (effect == 3) {
		Colour pulse = Colour(colourPulse);
		(*test).setPulse(pulse, effectStep, effectBias);
	}

	// change axis if y was selected
	if (axis == 2) {
		(*test).changeAxis();
	}

	(*test).setStep(step);
	(*test).setCopies(copies);

	return test;
}

RadialField* RadialFieldBuilder(int diameter) {
	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int step;
	int fieldType;
	int copies;

	double bias;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create radial field
	std::cout << "Please enter field type (1 - mapped circle, 2 - square, 3 - X, 4 - diamond): ";
	std::cin >> fieldType;
	std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse): ";
	std::cin >> effect;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter field bias: ";
	std::cin >> bias;
	std::cout << "Please enter effect step: ";
	std::cin >> effectStep;
	std::cout << "Please enter effect bias: ";
	std::cin >> effectBias;
	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colourStr1;
	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colourStr2;
	// get pulse colour if selected
	if (effect == 3) {
		std::cout << "Please enter pulse colour (#HEX): ";
		std::cin >> colourPulse;

	}

	Colour colour1 = Colour(colourStr1);
	Colour colour2 = Colour(colourStr2);

	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour1);
	colours.push_back(colour2);

	RadialField* test;

	if (fieldType == 1) {
		test = new RadialField(colours, diameter / 2, bias);
	}
	else if (fieldType == 2) {
		test = new RadialSquareField(colours, diameter / 2, bias);
	}
	else if (fieldType == 3) {
		test = new RadialXField(colours, diameter / 2, bias);
	}
	else if (fieldType == 4) {
		test = new RadialDiamondField(colours, diameter / 2, bias);
	}

	// set up effect
	if (effect == 1) {
		(*test).setStrobe(effectStep, effectBias);
	}
	else if (effect == 2) {
		(*test).setConverge(effectStep, effectBias);
	}
	else if (effect == 3) {
		Colour pulse = Colour(colourPulse);
		(*test).setPulse(pulse, effectStep, effectBias);
	}

	(*test).setStep(step);
	(*test).setCopies(copies);

	return test;
}

ColourField* fieldFactory(int option, int x, int y) {
	ColourField* field(NULL);

	if (option == 1) {
		field = RadialFieldBuilder(x);
	}
	else if (option == 2) {
		field = LinearFieldBuilder(x, y);
	}

	return field;
}

void squareTilingTest() {
	Magick::InitializeMagick("C:\\ImageMagick");

	std::cout << "Basic Square Tiling Test" << std::endl;


	std::string colourStr1;
	std::string colourStr2;

	int square;
	int columns;
	int rows;
	int option;

	std::cout << "Please enter the square size: ";
	std::cin >> square;
	std::cout << "Please enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Please enter the number of columns: ";
	std::cin >> columns;
	std::cout << "Please enter the type of field (1 for radial, 2 for linear): ";
	std::cin >> option;

	int x = rows * square;
	int y = columns * square;

	ColourField* field = fieldFactory(option, x, y);

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
	int optionField;
	int optionTiling;

	std::cout << "Please enter the square size: ";
	std::cin >> square;

	std::cout << "Please enter the type of field (1 for radial, 2 for linear): ";
	std::cin >> optionField;

	std::cout << "Please enter 1 for left diagonal to right, 2 for split diagonal: ";
	std::cin >> optionTiling;

	ColourField* field = fieldFactory(optionField, square, square);

	writeRecursiveSquareBiasedGif(square, *field, optionTiling);
	delete field;

	std::cin.get();
}
