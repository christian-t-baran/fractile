#include <iostream>
#include <Magick++.h>
#include <string>
#include <vector>

#include "../tiling/drawing.h"
#include "colourField.h"
#include "fieldFactory.h"
#include "fieldTest.h"

void writeFieldGif(int x, int y, ColourField& field, std::string filename) {
	std::vector< Magick::Image > frames;

	while (!(field).finishedEffect()) {
		Magick::Image image(Magick::Geometry(x, y), "white");
		drawField(x, y, field, image);
		image.animationDelay(10);
		frames.push_back(image);
		field.stepForward();
	}
	Magick::writeImages(frames.begin(), frames.end(), filename);

}

std::pair<int, int> getDimensions() {
	int x;
	int y;
	std::cout << "Please enter x dimension: ";
	std::cin >> x;
	std::cout << "Please enter y dimension: ";
	std::cin >> y;

	return std::make_pair(x, y);
}

void singleBias(int x, int y, ColourField& field) {
	writeFieldGif(x, y, field, "fieldTest.gif");

	std::cin.get();
}

void biasRange(int x, int y, ColourField& field){
	field.setBias(0);
	writeFieldGif(x, y, field, "bias000.gif");
	field.reinitialize();

	field.setBias(0.1);
	writeFieldGif(x, y, field, "bias010.gif");
	field.reinitialize();

	field.setBias(0.25);
	writeFieldGif(x, y, field, "bias025.gif");
	field.reinitialize();

	field.setBias(0.5);
	writeFieldGif(x, y, field, "bias050.gif");
	field.reinitialize();

	field.setBias(0.75);
	writeFieldGif(x, y, field, "bias075.gif");
	field.reinitialize();

	field.setBias(0.9);
	writeFieldGif(x, y, field, "bias090.gif");
	field.reinitialize();

	field.setBias(1);
	writeFieldGif(x, y, field, "bias100.gif");

	std::cin.get();
}

void fieldTest() {
	std::cout << "Colour field tests: " << std::endl;

	std::pair<int, int> dim = getDimensions();

	ColourField* field = fieldFactory(dim.first, dim.second);

	int option;
	std::cout << "Please enter 1 for a single bias gif, 2 for a range of biases (predetermined): ";
	std::cin >> option;

	if (option == 1) {
		singleBias(dim.first, dim.second, *field);
	}
	else if (option == 2) {
		biasRange(dim.first, dim.second, *field);
	}
}