#include <iostream>
#include <Magick++.h>

#include "../colours/colour.h"
#include "../colourFields/colourField.h"
#include "../colourFields/fieldFactory.h"
#include "../tiles/line.h"
#include "curveTiling.h"
#include "drawing.h"


// See: http://www.fundza.com/algorithmic/space_filling/hilbert/basics/index.html
void hilbert(int x, int y, int xi, int xj, int yi, int yj, int n, std::list<Magick::VPath>& path) {
	if (n <= 0) {
		int pX = x + ((xi + yi) / 2);
		int pY = y + ((xj + yj) / 2);

		path.push_back(Magick::PathLinetoAbs(Magick::Coordinate(pX, pY)));
	}
	else {
		hilbert(x, y, yi / 2, yj / 2, xi / 2, xj / 2, n - 1, path); // bottom left quadrant
		hilbert(x+(xi/2), y+(xj/2), xi/2, xj/2, yi/2, yj/2, n - 1, path); // top left quadrant
		hilbert(x + (xi / 2) + (yi / 2), y + (xj / 2) + (yj / 2), xi / 2, xj / 2, yi / 2, yj / 2, n - 1, path);
		hilbert(x+(xi/2)+yi, y+(xj/2)+yj, -yi/2, -yj/2, -xi/2, -xj/2, n-1, path);
	}
}

void writeCurveGif(int square, int iterations, ColourField& fill, ColourField& back) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(square) + "x" + std::to_string(square);

	while ( !fill.finishedEffect() ) {
		Magick::Image frame(dimensions.c_str(), "black");
		std::list<Magick::VPath>* path = new std::list<Magick::VPath>();

		frame.animationDelay(10);
		frame.strokeColor("white");

		hilbert(0, 0, square, 0, 0, square, iterations, *path);		
		frame.draw(Magick::DrawablePath(*path));

		// clean up memory
		delete path;

		processImage(square, square, fill, back, frame);

		frames.push_back(frame);
		fill.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}

void curveTiling() {
	std::cout << "Curve generator" << std::endl;

	int square;
	int iterations;

	std::cout << "Please give the size of the square: ";
	std::cin >> square;
	std::cout << "Please give the number of iterations to render: ";
	std::cin >> iterations;

	std::cout << "Please supply a foreground field" << std::endl;
	ColourField* fill = fieldFactory(square, square);

	std::cout << "Please supply a background field" << std::endl;
	ColourField* back = fieldFactory(square, square);

	writeCurveGif(square, iterations, *fill, *back);

	std::cin.get();
}