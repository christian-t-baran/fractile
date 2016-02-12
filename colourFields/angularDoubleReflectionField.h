#ifndef ANGULAR_SINGLE_REFLECTION_FIELD_H
#define ANGULAR_SINGLE_REFLECTIONFIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "angularField.h"


// Models a Radial XColour Field
class AngularDoubleReflectionField :
	public AngularField {

public:
	AngularDoubleReflectionField(std::vector<Colour> colours, int x, int y, double bias) :
		AngularField(colours, x, y, bias) {};
	~AngularDoubleReflectionField();

	Colour getColourAt(int, int);

	// Gradient reflected on x-axis when true, y-axis when false
};

#endif