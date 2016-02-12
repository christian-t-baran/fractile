#include <cmath>
#include <iostream>

#include "../colours/colour.h"
#include "fieldGeometry.h"
#include "angularField.h"

// default destructor
AngularField::~AngularField()
{
}

Colour AngularField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to distances from origin on Cartesian plane
	int field_x = x - _radius;
	// compensate from drawing from top of image
	int field_y = -( std::round(y * _yScale) - _radius );

	if (!_direction) {
		int temp = field_y;
		field_y = field_x;
		field_x = temp;
	}

	int angle = getAngle(field_x, field_y);

	// max angle is 360
	Colour newColour = mapDistanceToColourRange(360, angle, _step);

	return newColour;
}

void AngularField::changeDirection()
{
	if (_direction) {
		_direction = !_direction;
	}
	else {
		_direction = !_direction;
	}
}
