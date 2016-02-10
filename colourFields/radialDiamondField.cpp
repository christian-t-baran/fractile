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
	max_distance = max_distance / _copies;
	int step = _step % max_distance;
	distance = distance % max_distance;

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
	double l = interpolateDistance(max_distance, distance, step, l2, l1, _bias);
	double a = interpolateDistance(max_distance, distance, step, a2, a1, _bias);
	double b = interpolateDistance(max_distance, distance, step, b2, b1, _bias);

	Colour newColour = Colour(l, a, b);

	return newColour;
}
