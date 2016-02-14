#include <iostream>
#include <Magick++.h>

#include "drawing.h"
#include "../colours/colourConversion.h"
#include "../colourFields/colourField.h"
#include "../tiles/shape.h"

bool isBlack(Magick::ColorRGB col) {
	bool black = false;
	if ((col.red() <= 0.5) && (col.green() <= 0.5) && (col.blue() <= 0.5)) {
		black = true;
	}

	return black;
}

bool isWhite(Magick::ColorRGB col) {
	bool white = false;
	if ((col.red() >= 0.5) && (col.green() >= 0.5) && (col.blue() >= 0.5)) {
		white = true;
	}

	return white;
}

void processImage(int x, int y, ColourField& fill, ColourField& back, Magick::Image& image) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Colour fieldCol;

			Magick::ColorRGB tempCol = fieldCol.toMagick();

			Magick::ColorRGB colorAt = image.pixelColor(i, j);
			if ( isWhite(colorAt) ) {
				Colour fieldCol = fill.getColourAt(i, j);
				Magick::ColorRGB tempCol = fieldCol.toMagick();

				image.pixelColor(i, j, tempCol);
			}
			else if ( isBlack(colorAt) ) {
			}
		}
	}
}

void drawField(int x, int y, ColourField& field, Magick::Image& image) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			Colour fieldCol = field.getColourAt(i, j);

			Magick::ColorRGB tempCol = fieldCol.toMagick();

			image.pixelColor(i, j, tempCol);
		}
	}

}

void drawShape(Shape& shape, ColourField& field, Magick::Image& image) {
	std::pair<int, int> coord = shape.getCenterCoord();

	Colour fieldCol = field.getColourAt(coord.first, coord.second);

	Magick::ColorRGB tempCol = fieldCol.toMagick();

	image.strokeColor(tempCol);
	image.strokeWidth(0);
	image.fillColor(tempCol);

	image.draw(shape.getDrawable());
}