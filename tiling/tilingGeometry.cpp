#include <utility>

#include "tilingGeometry.h"

int LCM(int x, int y) {
	return 0;
}

int GCD(int x, int y) {
	return 0;
}


// Finds the coordinates of the midpoint of a line segment
std::pair<int, int> midpoint(int x1, int x2, int y1, int y2) {
	int xCenter = (x1 + x2) / 2;
	int yCenter = (y1 + y2) / 2;

	return std::pair<int, int>(xCenter, yCenter);

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
