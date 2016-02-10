#ifndef RADIAL_DIAMOND_FIELD_H
#define RADIAL_DIAMOND_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "radialField.h"
#include "colourField.h"


// Models a Radial XColour Field
class RadialDiamondField :
	public RadialField {

public:
	RadialDiamondField(std::vector<Colour> colours, int x, int y, double bias) :
		RadialField(colours, x, y, bias) {};
	~RadialDiamondField();

	Colour getColourAt(int, int);
};

#endif