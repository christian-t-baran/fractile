#include <cmath>

#include "../colours/colour.h"
#include "fieldGeometry.h"
#include "radialSquareField.h"

// default drestructor
RadialSquareField::~RadialSquareField()
{
}

Colour RadialSquareField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to absolute distances from origin on Cartesian plane
	int field_x = std::abs(x - _radius);
	int field_y = std::abs(std::round(y * _yScale) - _radius);

	// calculate maximum distance
	int max_distance = std::sqrt((_radius * _radius) + (_radius * _radius));

	int distance;
	// if x is 0, distance is y
	if (x == 0) {
		distance = field_y;
	}
	// if y is 0, distance is x
	else if (y == 0) {
		distance = field_x;
	}
	// else distance is given by c = sqrt(x^2 + y^2)
	else {
		distance = std::sqrt((field_x * field_x) + (field_y * field_y));
	}

	Colour newColour = mapDistanceToColourRange(_radius, distance, _step);

	return newColour;
}
