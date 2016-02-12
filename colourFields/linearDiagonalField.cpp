#include <vector>

#include "linearDiagonalField.h"
#include "fieldGeometry.h"

LinearDiagonalField::~LinearDiagonalField()
{
}

Colour LinearDiagonalField::getColourAt(int x, int y)
{
	// get Colours from vector
	Colour first = _curColours[0];
	Colour second = _curColours[1];

	// get LAB values
	double l1 = first.getLAB_L();
	double l2 = second.getLAB_L();
	double a1 = first.getLAB_A();
	double a2 = second.getLAB_A();
	double b1 = first.getLAB_B();
	double b2 = second.getLAB_B();

	// interpolate new LAB values
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
