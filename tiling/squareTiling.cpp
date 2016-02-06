#include <Magick++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


#include "../colourFields/linearField.h"
#include "../colourFields/radialField.h"
#include "../colourFields/colourField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"
#include "tilingGeometry.h"

// Creates an image from a LinearField
void writeSquareImage(int x, int y, int square, ColourField& field, Magick::Image& image) {

	for (int i = 0; i < x; i = i + square) {
		for (int j = 0; j < y; j = j + square) {
			std::pair<int, int> coord = centerRectangle(i, i+40, j, j + 40);
			
			Colour fieldCol = field.getColourAt( coord.first, coord.second);
			double r = convertRGBtoDec(fieldCol.getRGB_R());
			double g = convertRGBtoDec(fieldCol.getRGB_G());
			double b = convertRGBtoDec(fieldCol.getRGB_B());

			Magick::ColorRGB tempCol(r, g, b);
			
			image.strokeColor("black");
			image.strokeWidth(1);
			image.fillColor(tempCol);

			image.draw(Magick::DrawableRectangle(i, j + square, i + square, j) );
		}
	}


}

// Creates a gif from a LinearField effect
void writeSquareBiasedGif(int x, int y, int square, ColourField& field) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(x) + "x" + std::to_string(y);

	while (!field.finishedEffect()) {
		Magick::Image testImage(dimensions.c_str(), "white");
		writeSquareImage(x, y, square, field, testImage);
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

	double bias;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create linear field
	std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse: " << std::endl;
	std::cin >> effect;
	std::cout << "Enter 1 to gradate on x axis, 2 for y" << std::endl;
	std::cin >> axis;
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

	return test;
}

RadialField* RadialFieldBuilder(int diameter) {
	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int step;

	double bias;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create radial field
	std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse: ";
	std::cin >> effect;
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

	RadialField* test = new RadialField(colours, (diameter / 2), bias);

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
	std::cout << "Please enter the number of columns";
	std::cin >> columns;
	std::cout << "Please enter the type of field (1 for radial, 2 for linear)";
	std::cin >> option;

	int x = rows * square;
	int y = columns * square;

	ColourField* field = fieldFactory(option, x, y);

	writeSquareBiasedGif(x, y, square, *field);
	delete field;

	std::cin.get();
}