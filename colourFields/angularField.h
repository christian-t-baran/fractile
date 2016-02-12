#ifndef ANGULAR_FIELD_H
#define ANGULAR_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "radialField.h"

// Models a Radial XColour Field
class AngularField :
	public RadialField {

public:
	AngularField(std::vector<Colour> colours, int x, int y, double bias) :
		RadialField(colours, x, y, bias) {};
	~AngularField();

	Colour getColourAt(int, int);

	void changeDirection();

protected:
	bool _direction = true;
	// Gradient starts from + x-axis when true
	// from + y-axis when false
};

#endif
