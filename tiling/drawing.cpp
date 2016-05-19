#include <iostream>
#include <Magick++.h>

#include "drawing.h"
#include "../colours/colourConversion.h"
#include "../colourFields/colourField.h"
#include "../tiles/shape.h"
#include "curveTiling.h"

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

int readImage() {

	Magick::Image image;
	try {
		std::vector<Magick::Image> origFrames;
		// std::list<Magick::Image> processedFrames;

		// Read a file into image object
		Magick::readImages(&origFrames, "input.gif");

		for (int i = 0; i < origFrames.size(); i++) {
			// origFrames[i].oilPaint();
			// origFrames[i].gaussianBlur(2.0, 3.0);
			origFrames[i].edge();
			// origFrames[i].motionBlur(5.0, 2.0, 0);
		}

		/*
		while( !origFrames.empty() ){
			Magick::Image curFrame = origFrames.front();
			origFrames.pop_front();

			curFrame.type(Magick::GrayscaleType);
			curFrame.edge();

			
			Magick::Geometry dim = curFrame.size();

			Magick::Image frame(dim, "black");
			std::list<Magick::VPath>* path = new std::list<Magick::VPath>();

			frame.animationDelay(10);
			frame.strokeColor("white");

			hilbertify(0, 0, dim.width(), 0, 0, dim.height(), 0, 4, 7, *path, curFrame);

			frame.draw(Magick::DrawablePath(*path));
			delete path;

			processedFrames.push_back(frame);
			
		}
		*/

		// Write the image to a file 
		Magick::writeImages(origFrames.begin(), origFrames .end(), "output.gif");
	}

	catch (Magick::Exception &error_){
		std::cout << "Caught exception: " << error_.what() << std::endl;
		return 1;
	}

	return 0;
}

std::pair<int, int> getBW(int x1, int x2, int y1, int y2, Magick::Image& image){
	int black = 0;
	int white = 0;

	int area = x2 * y2;

	for (int i = x1; i < x2; i++) {
		for (int j = y1; i < y2; j++) {
			Magick::ColorRGB colorAt = image.pixelColor(i, j);

			if (isWhite(colorAt)) {
				white++;
			}
			else {
				black++;
			}
			/*
			if ((black > (area / 2)) || (white > (area / 2)) ) {
				break;
			}
			*/
		}
	}

	return std::make_pair(black, white);
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