#include <iostream>
#include <Magick++.h>

#include "drawing.h"
#include "../colours/colourConversion.h"
#include "../colourFields/colourField.h"
#include "../tiles/shape.h"

void drawField(int x, int y, ColourField& field, Magick::Image& image) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Colour fieldCol = field.getColourAt(i, j);
			double r = convertRGBtoDec(fieldCol.getRGB_R());
			double g = convertRGBtoDec(fieldCol.getRGB_G());
			double b = convertRGBtoDec(fieldCol.getRGB_B());

			Magick::ColorRGB tempCol(r, g, b);

			image.pixelColor(i, j, tempCol);
		}
	}

}

void drawShape(Shape& shape, ColourField& field, Magick::Image& image) {
	std::pair<int, int> coord = shape.getCenterCoord();

	Colour fieldCol = field.getColourAt(coord.first, coord.second);
	double r = convertRGBtoDec(fieldCol.getRGB_R());
	double g = convertRGBtoDec(fieldCol.getRGB_G());
	double b = convertRGBtoDec(fieldCol.getRGB_B());

	Magick::ColorRGB tempCol(r, g, b);

	image.strokeColor(tempCol);
	image.strokeWidth(0);
	image.fillColor(tempCol);

	image.draw(shape.getDrawable());
}