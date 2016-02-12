#include <cmath>
#include <iostream>

#include "../colours/colour.h"
#include "angularDoubleReflectionField.h"
#include "fieldGeometry.h"

// default destructor
AngularDoubleReflectionField::~AngularDoubleReflectionField()
{
}

Colour AngularDoubleReflectionField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to distances from origin on Cartesian plane
	int field_x = x - _radius;
	// compensate from drawing from top of image
	int field_y = -(std::round(y * _yScale) - _radius);

	// if direction, reflect around y axis.
	if (!_direction) {
		int temp = field_y;
		field_y = field_x;
		field_x = temp;
	}

	// maybe merge with original class
	// reflect on x axis
	if (field_y < 0) {
		field_y = -field_y;
	}

	if (field_x < 0) {
		field_x = -field_x;
	}

	// calculate angle and adjust for copies
	int angle = getAngle(field_x, field_y);

	// max angle is 90
	Colour newColour = mapDistanceToColourRange(90, angle, _step);

	return newColour;
}
