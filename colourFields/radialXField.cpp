#include "../colours/colour.h"
#include "fieldGeometry.h"
#include "radialXField.h"

// default destructor
RadialXField::~RadialXField()
{
}

Colour RadialXField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to absolute distances from origin on Cartesian plane
	int field_x = std::abs(x - _radius);
	int field_y = std::abs(std::round(y * _yScale) - _radius);

	int distance;

	if (field_x > field_y) {
		distance = field_x - field_y;
	}
	else {
		distance = field_y - field_x;
	}

	Colour newColour = mapDistanceToColourRange(_radius, distance, _step);

	return newColour;
}
