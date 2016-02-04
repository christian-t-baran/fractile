#include <Magick++.h>
#include <iostream>
#include <string>
#include <vector>

#include "radialField.h"
#include "../colours/colour.h"

double convertRGB(int c) {
	return c / 255.0;
}

void basicRadialFieldTest() {
	Magick::InitializeMagick("C:\\ImageMagick");

	std::string colourStr1;
	std::string colourStr2;

	std::cout << "Please enter first colour (#HEX): ";
	std::cin >> colourStr1;
	std::cout << "Please enter second colour (#HEX): ";
	std::cin >> colourStr2;

	Colour colour1 = Colour(colourStr1);
	Colour colour2 = Colour(colourStr2);

	std::vector<Colour> colours = std::vector<Colour>();

	colours.push_back(colour1);
	colours.push_back(colour2);

	RadialField test = RadialField(colours, 100, 0.5);

	Magick::Image testImage("201x201", "white");

	for (int i = 0; i < 201; i++) {
		for (int j = 0; j < 201; j++) {
			Colour fieldCol = test.getColourAt(i, j);
			// std::cout << "Colour at " << i << "," << j << "   " << fieldCol.hex() << std::endl;
			double r = convertRGB( fieldCol.getRGB_R() );
			double g = convertRGB( fieldCol.getRGB_G() ); 
			double b = convertRGB( fieldCol.getRGB_B() );

			Magick::ColorRGB tempCol(r, g, b);

			testImage.pixelColor(i, j, tempCol);
		}
	}

	testImage.write("basicFieldTest.png");
	
	std::cin.get();
}