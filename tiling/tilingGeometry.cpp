#include <utility>

#include "tilingGeometry.h"

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
