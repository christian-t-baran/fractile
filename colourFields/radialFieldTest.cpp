#include <Magick++.h>
#include <iostream>
#include <string>
#include <vector>

#include "radialField.h"
#include "radialSquareField.h"
#include "radialXField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"

// creates image from a radial field
void writeImage(int imageDim, RadialField field, Magick::Image& image) {
	for (int i = 0; i < imageDim; i++) {
		for (int j = 0; j < imageDim; j++) {
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

// creates gif from a radial field
void writeBiasedGif(int imageDim, RadialField field) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(imageDim) + "x" + std::to_string(imageDim);

	while (!field.finishedEffect()) {
		Magick::Image testImage(dimensions.c_str(), "white");
		writeImage(imageDim, field, testImage);
		testImage.animationDelay(10);

		frames.push_back(testImage);
		field.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}

void effectRadialFieldTest() {
	std::cout << "Radial Field Effect Test" << std::endl;

	Magick::InitializeMagick("C:\\ImageMagick");

	std::string colourStr1;
	std::string colourStr2;
	std::string colourPulse;

	int fieldType;
	int radius;
	int step;

	double bias;
	int effect;
	int effectStep;
	double effectBias;

	// get input to create radial field
	std::cout << "Please enter field type (1 - mapped circle, 2 - square, 3 - X): ";
	std::cin >> fieldType;
	std::cout << "Please enter effect mode (1 - strobe, 2 - converge, 3 - pulse): ";
	std::cin >> effect;
	std::cout << "Please enter radius: ";
	std::cin >> radius;
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

	
	RadialField test;

	if (fieldType == 1) {
		test = RadialField(colours, radius, bias);
	}
	else if (fieldType == 2) {
		test = RadialSquareField(colours, radius, bias);
	}
	else if (fieldType == 3) {
		test = RadialXField(colours, radius, bias);
	}

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
	int imageDim = (radius * 2) + 1;

	test.setStep(step);

	// create gif
	writeBiasedGif(imageDim, test);
}

void basicRadialFieldTest() {
	std::cout << "Radial Field Basic Test" << std::endl;

	Magick::InitializeMagick("C:\\ImageMagick");

	std::string colourStr1;
	std::string colourStr2;
	int radius;
	int step;

	// get input to create radial field
	std::cout << "Please enter radius: ";
	std::cin >> radius;
	std::cout << "Please enter step (<= radius): ";
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

	RadialField test = RadialField(colours, radius, 0.1);

	int imageDim = (radius * 2) + 1;

	test.setStep(step);

	std::string dimensions = std::to_string(imageDim) + "x" + std::to_string(imageDim);

	Magick::Image testImage( dimensions.c_str() , "white");

	// create images with a bias of 0, 0.1, 0.25, 0.5, 0.75, 0.9 and 1
	test.setBias(0);
	writeImage(imageDim, test, testImage);
	testImage.write("bias000.png");

	test.setBias(0.1);
	writeImage(imageDim, test, testImage);
	testImage.write("bias010.png");

	test.setBias(0.25);
	writeImage(imageDim, test, testImage);
	testImage.write("bias025.png");

	test.setBias(0.5);
	writeImage(imageDim, test, testImage);
	testImage.write("bias050.png");

	test.setBias(0.75);
	writeImage(imageDim, test, testImage);
	testImage.write("bias075.png");

	test.setBias(0.9);
	writeImage(imageDim, test, testImage);
	testImage.write("bias090.png");

	test.setBias(1);
	writeImage(imageDim, test, testImage);
	testImage.write("bias100.png");


	
	std::cin.get();
}