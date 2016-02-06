#include <utility>

#include "tilingGeometry.h"

// Finds the center coordinates of a rectangle
std::pair<int, int> centerRectangle(int x, int y) {
	int xCenter = x / 2;
	int yCenter = y / 2;

	return std::pair<int, int>(xCenter, yCenter);
}