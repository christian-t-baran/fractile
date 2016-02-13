#include <vector>

#include "linearDiagonalField.h"
#include "fieldGeometry.h"

LinearDiagonalField::~LinearDiagonalField()
{
}

Colour LinearDiagonalField::getColourAt(int x, int y)
{
	int maxDistance = _x + _y;
	int distance;

	// if direction is true, go from bottom left
	if (_direction) {
		distance = (x + y);
	}
	// otherwise from top right;
	else {
		distance = (x + std::abs(y - _y) );
	}


	Colour newColour = mapDistanceToColourRange(maxDistance, distance, _step);

	return newColour;
}
