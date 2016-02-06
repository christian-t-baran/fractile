#ifndef COLOUR_FIELD_H
#define COLOUR_FIELD_H

#pragma once

#include <vector>
#include "../colours/colour.h"


// Abstract base class for ColourFields
class ColourField {
public:
	ColourField() {};
	ColourField(std::vector<Colour> colours, int dim) {};
	~ColourField() {};

	virtual void reinitialize() = 0;
	virtual void setStep(int) = 0;
	virtual void setBias(double) = 0;
	virtual Colour getColourAt(int, int) = 0;

	virtual void setPulse(Colour, int, double) = 0;
	virtual void setStrobe(int, double) = 0;
	virtual void setConverge(int, double) = 0;
	virtual void stepForward() = 0;
	virtual bool finishedEffect() = 0;
};

#endif