#include <Magick++.h>
#include <iostream>
#include <string>
#include <vector>

#include "linearField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"

// Creates an image from a LinearField
void writeImage(int x, int y, LinearField field, Magick::Image& image) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Colour fieldCol = field.getColourAt(i, j);
			// std::cout << "Colour at " << i << "," << j << "   " << fieldCol.hex() << std::endl;
			double r = convertRGBtoDec(fieldCol.getRGB_R());
			double g = convertRGBtoDec(fieldCol.getRGB_G());
			double b = convertRGBtoDec(fieldCol.getRGB_B());

			Magick::ColorRGB tempCol(r, g, b);

			image.pixelColor(i, j, tempCol);
		}
	}
}

// Creates a gif from a LinearField effect
void writeBiasedGif(int x, int y, LinearField field) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(x) + "x" + std::to_string(y);

	while (!field.finishedEffect()) {
		Magick::Image testImage(dimensions.c_str(), "white");
		writeImage(x, y, field, testImage);
		testImage.animationDelay(10);

		frames.push_back(testImage);
		field.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}

void effectLinearFieldTest() {
	std::cout << "Linear Field Effect Test" << std::endl;

	Magick::InitializeMagick("C:\\ImageMagick");

	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int x;
	int y;
	int axis;
	int step;
	int copies;

	double bias;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create linear field
	std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse: " << std::endl;
	std::cin >> effect;
	std::cout << "Please enter x length: ";
	std::cin >> x;
	std::cout << "Please enter y length: ";
	std::cin >> y;
	std::cout << "Please enter number of copies: ";
	std::cin >> copies;
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

	LinearField test = LinearField(colours, x, y, bias);

	// set up effect
	if (effect == 1) {
		test.setStrobe(effectStep, effectBias);
	}
	else if (effect == 2) {
		test.setConverge(effectStep, effectBias);
	}
	else if (effect == 3) {
		Colour pulse = Colour(colourPulse);
		test.setPulse(pulse, effectStep, effectBias);
	}

	// change axis if y was selected
	if (axis == 2) {
		test.changeAxis();
	}

	test.setStep(step);
	test.setCopies(copies);

	writeBiasedGif(x, y, test);
}

void basicLinearFieldTest() {
	std::cout << "Linear Field Basic Test" << std::endl;

	Magick::InitializeMagick("C:\\ImageMagick");

	std::string colourStr1;
	std::string colourStr2;

	int x;
	int y;
	int axis;
	int step;

	// get input to create linear field
	std::cout << "Please enter x length: ";
	std::cin >> x;
	std::cout << "Please enter y length: ";
	std::cin >> y;
	std::cout << "Enter 1 to gradate on x axis, 2 for y" << std::endl;
	std::cin >> axis;
	std::cout << "Please enter field step (<= radius): ";
	std::cin >> step;
	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colourStr1;
	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colourStr2;

	Colour colour1 = Colour(colourStr1);
	Colour colour2 = Colour(colourStr2);

	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour1);
	colours.push_back(colour2);

	LinearField test = LinearField(colours, x, y, 0.5);

	test.setStep(step);

	// change axis if y was selected
	if (axis == 2) {
		test.changeAxis();
	}

	std::string dimensions = std::to_string(x) + "x" + std::to_string(y);

	Magick::Image testImage(dimensions.c_str(), "white");

	// create images with a bias of 0, 0.1, 0.25, 0.5, 0.75, 0.9 and 1
	test.setBias(0);
	writeImage(x, y, test, testImage);
	testImage.write("bias000.png");

	test.setBias(0.1);
	writeImage(x, y, test, testImage);
	testImage.write("bias010.png");

	test.setBias(0.25);
	writeImage(x, y, test, testImage);
	testImage.write("bias025.png");

	test.setBias(0.5);
	writeImage(x, y, test, testImage);
	testImage.write("bias050.png");

	test.setBias(0.75);
	writeImage(x, y, test, testImage);
	testImage.write("bias075.png");

	test.setBias(0.9);
	writeImage(x, y, test, testImage);
	testImage.write("bias090.png");

	test.setBias(1);
	writeImage(x, y, test, testImage);
	testImage.write("bias100.png");



	std::cin.get();
}