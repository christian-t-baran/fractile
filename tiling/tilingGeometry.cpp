#include <utility>

#include "tilingGeometry.h"

// Finds the center coordinates of a rectangle
// 
std::pair<int, int> centerRectangle(int xLL, int xUR, int yLL, int yUR) {
	int xCenter = (xLL + xUR) / 2;
	int yCenter = (yLL + yUR) / 2;

	return std::pair<int, int>(xCenter, yCenter);
}