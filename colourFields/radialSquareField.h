#ifndef RADIAL_SQUARE_FIELD_H
#define RADIAL_SQUARE_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "radialField.h"
#include "colourField.h"


// Models a Radial XColour Field
class RadialSquareField:
	public RadialField {

public:
	RadialSquareField(std::vector<Colour> colours, int radius, double bias) :
		RadialField(colours, radius, bias) {};
	~RadialSquareField();

	Colour getColourAt(int, int);
};

#endif
