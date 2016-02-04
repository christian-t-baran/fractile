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
	virtual void setBias(double) = 0;
	virtual void setPulse() = 0;
	virtual void stepPulse() = 0;
	virtual bool finishedPulse() = 0;
	virtual void setConverge() = 0;
	virtual void stepConverge() = 0;
	virtual bool finishedConverge() = 0;
	virtual Colour getColourAt(int, int) = 0;
};

#endif