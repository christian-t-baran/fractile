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
	RadialDiamondField(std::vector<Colour> colours, int radius, double bias) :
		RadialField(colours, radius, bias) {};
	~RadialDiamondField();

	Colour getColourAt(int, int) override;
};

#endif