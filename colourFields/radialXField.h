#ifndef RADIAL_X_FIELD_H
#define RADIAL_X_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "radialField.h"
#include "colourField.h"


// Models a Radial XColour Field
class RadialXField :
	public RadialField {

public:
	RadialXField(std::vector<Colour> colours, int radius, double bias) :
		RadialField(colours, radius, bias) {};
	~RadialXField();

	Colour getColourAt(int, int);
};

#endif