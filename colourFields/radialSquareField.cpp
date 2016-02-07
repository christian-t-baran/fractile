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
	int field_y = std::abs(y - _radius);

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
	double l = interpolateDistance(max_distance, distance, _step, l2, l1, _bias);
	double a = interpolateDistance(max_distance, distance, _step, a2, a1, _bias);
	double b = interpolateDistance(max_distance, distance, _step, b2, b1, _bias);

	Colour newColour = Colour(l, a, b);

	return newColour;
}
