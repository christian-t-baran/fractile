#ifndef COLOUR_FIELD_H
#define COLOUR_FIELD_H

#pragma once

#include <vector>
#include "../colours/colour.h"


// Abstract base class for ColourFields
class ColourField {
public:
	ColourField(std::vector<Colour> colours, int dim) {};
	~ColourField() {};
	virtual void reinitialize();
	virtual void setPulse(int step);
	virtual void stepPulse();
	virtual bool finishedPulse();
	virtual void setConverge(int step);
	virtual void stepConverge();
	virtual bool finishedConverge();
};

#endif