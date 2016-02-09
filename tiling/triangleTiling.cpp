#include <Magick++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


#include "../colourFields/fieldFactory.h"
#include "../colourFields/colourField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"
#include "../tiles/triangle.h"
#include "drawing.h"
#include "triangleTiling.h"
#include "tilingGeometry.h"




void writeTrianglesInSquare(int xLL, int yLL, int xUR, int yUR, int square, ColourField& field, Magick::Image& image) {

	for (int i = xLL; i < xUR; i = i + square) {
		for (int j = yLL; j < yUR; j = j + square) {
			std::pair<int, int> ll = std::make_pair(i, j);
			std::pair<int, int> ul = std::make_pair(i, j + square);
			std::pair<int, int> lr = std::make_pair(i + square, j);
			std::pair<int, int> ur = std::make_pair(i + square, j + square);
			std::pair<int, int> center = centerRectangle(i, i + square, j, j + square);

			Triangle left(ll.first, ll.second, ul.first, ul.second, center.first, center.second);
			Triangle right(lr.first, lr.second, ur.first, ur.second, center.first, center.second);
			Triangle top(ul.first, ul.second, ur.first, ur.second, center.first, center.second);
			Triangle bottom(ll.first, ll.second, lr.first, lr.second, center.first, center.second);

			drawShape(left, field, image);
			drawShape(right, field, image);
			drawShape(bottom, field, image);
			drawShape(top, field, image);

		}
	}


}


void sierpinskiTriangle() {

}

void writeTriangleBiasedGif(int x, int y, int square, ColourField& field) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(x) + "x" + std::to_string(y);

	while (!field.finishedEffect()) {
		Magick::Image testImage(dimensions.c_str(), "white");
		writeTrianglesInSquare(0, 0, x, y, square, field, testImage);
		testImage.animationDelay(10);

		frames.push_back(testImage);
		field.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}

void triangleTilingTest() {
	std::cout << "Basic Triangle Test" << std::endl;

	int square;
	int columns;
	int rows;

	std::cout << "Please enter the square size (subdivided into 4 triangles): ";
	std::cin >> square;
	std::cout << "Please enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Please enter the number of columns: ";
	std::cin >> columns;

	int x = rows * square;
	int y = columns * square;

	ColourField* field = fieldFactory(x, y);

	writeTriangleBiasedGif(x, y, square, *field);
	delete field;

	std::cin.get();
}