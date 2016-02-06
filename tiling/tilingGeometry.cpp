#include <utility>

#include "tilingGeometry.h"

// Finds the center coordinates of a rectangle
std::pair<int, int> centerRectangle(int x1, int x2, int y1, int y2) {
	int xCenter = (x1 + x2) / 2;
	int yCenter = (y1 + y2) / 2;

	return std::pair<int, int>(xCenter, yCenter);
}