#include <cmath>

#include "../colours/colour.h"
#include "fieldGeometry.h"
#include "radialDiamondField.h"

// default drestructor
RadialDiamondField::~RadialDiamondField()
{
}

Colour RadialDiamondField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to absolute distances from origin on Cartesian plane
	int field_x = std::abs(x - _radius);
	int field_y = std::abs(std::round(y * _yScale) - _radius);

	int max_distance = _radius * 2;

	int distance = field_x + field_y;

	// adjust for copies
	Colour newColour = mapDistanceToColourRange(_radius, distance, _step);

	return newColour;
}
