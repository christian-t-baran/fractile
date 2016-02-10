#include <Magick++.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


#include "../colourFields/fieldFactory.h"
#include "../colourFields/colourField.h"
#include "../colours/colour.h"
#include "../colours/colourConversion.h"
#include "../tiles/rectangle.h"
#include "../tiles/triangle.h"
#include "drawing.h"
#include "triangleTiling.h"
#include "tilingGeometry.h"




void writeTrianglesInSquare(int xLL, int yLL, int xUR, int yUR, int square, ColourField& field, Magick::Image& image) {
	
	for (int i = xLL; i < xUR; i = i + square) {
		for (int j = yLL; j < yUR; j = j + square) {
			// (0, 0) is in left-hand corner
			std::pair<int, int> ul = std::make_pair(i, j);
			std::pair<int, int> ur = std::make_pair(i + square, j);
			std::pair<int, int> ll = std::make_pair(i, j + square);
			std::pair<int, int> lr = std::make_pair(i + square, j + square);
			std::pair<int, int> center = centerRectangle(ll.first, lr.first, ul.second, ll.second);


			Triangle left(ul.first, ul.second, ll.first, ll.second, center.first, center.second);
			Triangle right(ur.first, ur.second, lr.first, lr.second, center.first, center.second);
			Triangle top(ul.first, ul.second, ur.first, ur.second, center.first, center.second);
			Triangle bottom(ll.first, ll.second, lr.first, lr.second, center.first, center.second);

			drawShape(left, field, image);
			drawShape(right, field, image);
			drawShape(bottom, field, image);
			drawShape(top, field, image);

		}
	}


}


// A is bottom left point, B is bottom right point, C is top left point
void splitTriangs(Triangle original, ColourField& fill, ColourField& back, Magick::Image& image) {
	std::pair<int, int> a = original.getA();
	std::pair<int, int> b = original.getB();
	std::pair<int, int> c = original.getC();

	std::pair<int, int> abMP = midpoint(a.first, b.first, a.second, b.second);
	std::pair<int, int> acMP = midpoint(a.first, c.first, a.second, c.second);
	std::pair<int, int> bcMP = midpoint(b.first, c.first, b.second, c.second);

	// A' = A, B' = -AB MP, C' = -AC mp
	Triangle bottomLeft(a.first, a.second, abMP.first, abMP.second, acMP.first, acMP.second);

	// A' = -AC MP, B' = B, C' = -BC mp
	Triangle bottomRight(abMP.first, abMP.second, b.first, b.second, bcMP.first, bcMP.second);

	// A' = -AC MP, B' = -BC mp, C' = -BC mp
	Triangle top(acMP.first, acMP.second, bcMP.first, bcMP.second, c.first, c.second);

	// Construction can be arbitrary
	Triangle center(abMP.first, abMP.second, acMP.first, acMP.second, bcMP.first, bcMP.second);

	drawShape(center, fill, image);

	if (bottomLeft.getArea() > 9) {
		splitTriangs(bottomLeft, fill, back, image);
	}
	else {
		drawShape(bottomLeft, back, image);
	}

	if (bottomRight.getArea() > 9) {
		splitTriangs(bottomRight, fill, back, image);

	}
	else {
		drawShape(bottomRight, back, image);

	}
	if (top.getArea() > 9) {
		splitTriangs(top, fill, back, image);
	}
	else {
		drawShape(top, back, image);
	}

}


void sierpinskiTriangle(int xUL, int xLR, int yUL, int yLR, 
	ColourField& fill, ColourField& back, Magick::Image& image) {
	// bottom left corner
	int aX = xUL;
	int aY = yLR;

	// bottom right corner
	int bX = xLR;
	int bY = yLR;

	// top point
	std::pair<int, int> cPoint = midpoint(xUL, xLR, 0, 0);
	int cX = cPoint.first;
	int cY = cPoint.second;

	Triangle triangle(aX, aY, bX, bY, cX, cY);

	Triangle leftCorner(xUL, yUL, aX, aY, cX, cY);
	Triangle rightCorner(xLR, yUL, bX, bY, cX, cY);
	drawShape(leftCorner, back, image);
	drawShape(rightCorner, back, image);


	splitTriangs(triangle, fill, back, image);
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

void writeRecursiveTriangleBiasedGif(int x, int y, ColourField& fill, ColourField& back) {
	std::vector< Magick::Image > frames;
	std::string dimensions = std::to_string(x) + "x" + std::to_string(y);

	int iterations = LCM(fill.effectStepTotal(), back.effectStepTotal());
	

	for (int i = 0; i < iterations; i++) {
		if (fill.finishedEffect()) {
			fill.reinitialize();
		}
		if (back.finishedEffect()) {
			back.reinitialize();
		}

		Magick::Image frame(dimensions.c_str(), "white");

		sierpinskiTriangle(0, x, 0, y, fill, back, frame);

		frame.animationDelay(10);

		frames.push_back(frame);
		fill.stepForward();
		back.stepForward();
	}

	Magick::writeImages(frames.begin(), frames.end(), "test.gif");
}

void basicTriangleTiling() {
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

void recursiveTriangleTiling() {
	int square;

	std::cout << "Please enter the square size (base for Sierpinksi): ";
	std::cin >> square;

	// adjust for sierpinski
	int adjustedY = std::round(square * (std::sqrt(3) / 2.0));

	ColourField* fill = fieldFactory(square, adjustedY);
	ColourField* back = fieldFactory(square, adjustedY);

	writeRecursiveTriangleBiasedGif(square, adjustedY, *fill, *back);

	std::cin.get();
}