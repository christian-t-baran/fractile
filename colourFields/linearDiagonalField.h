#ifndef LINEAR_DIAGONAL_FIELD_H
#define LINEAR_DIAGONAL_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "linearField.h"
#include "colourField.h"


// Models a Radial XColour Field
class LinearDiagonalField :
	public LinearField {

public:
	LinearDiagonalField(std::vector<Colour> colours, int x, int y, double bias) :
		LinearField(colours, x, y, bias) {};
	~LinearDiagonalField();

	Colour getColourAt(int, int);
};

#endif
