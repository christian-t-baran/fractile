#include <cmath>
#include <iostream>
#include <utility>

#include "tilingGeometry.h"

int LCM(int a, int b) {
	return std::abs(a * b) / GCD(a, b);
}

int GCD(int a, int b) {
	int gcd;
	if (a == b) {
		gcd = a;
	}
	else if (a > b) {
		gcd = GCD(a - b, b);
	}
	// if b is less than a
	else {
		gcd = GCD(a, b - a);
	}
	return gcd;
}


// Finds the coordinates of the midpoint of a line segment
std::pair<int, int> midpoint(int x1, int x2, int y1, int y2) {
	int xCenter = (x1 + x2) / 2;
	int yCenter = (y1 + y2) / 2;

	return std::pair<int, int>(xCenter, yCenter);

}

double segmentLength(int aX, int aY, int bX, int bY)
{
	double length;

	if (aX == bX) {
		length = std::abs(aY - bY);
	}
	else if (aY == bY) {
		length = std::abs(aX - bX);
	}
	else {
		double lengthX = std::abs(aX - bX);
		double lengthY = std::abs(aY - bY);
		// std::cout << "Length of X coord " << lengthX << std::endl;
		// std::cout << "Length of Y coord " << lengthY << std::endl;

		length = std::sqrt((lengthX * lengthX) + (lengthY * lengthY));
	}

	return length;
}

// Finds the center coordinates of a rectangle
std::pair<int, int> centerRectangle(int xLL, int xUR, int yLL, int yUR) {
	int xCenter = (xLL + xUR) / 2;
	int yCenter = (yLL + yUR) / 2;

	return std::pair<int, int>(xCenter, yCenter);
}

// Finds the center coordinates of a triangle
std::pair<int, int> centerTriangle(int aX, int aY, int bX, int bY, int cX, int cY)
{
	int xCenter = (aX + bX + cX) / 3;
	int yCenter = (aY + bY + cY) / 3;

	return std::pair<int, int>(xCenter, yCenter);
}
