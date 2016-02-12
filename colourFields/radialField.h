#ifndef RADIAL_FIELD_H
#define RADIAL_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "colourField.h"

// Models a Radial Colour Field
class RadialField : 
	public ColourField {

public:
	RadialField(); // TO DO - fix this ugly hack
	RadialField(std::vector<Colour>, int, int, double);
	~RadialField();

	void reinitialize() override;

	void setStrobe(int, unsigned int, double, bool) override;
	void setFlow(int, double, bool) override;
	void setPulse(Colour, int, unsigned int, double, bool) override;
	void setConverge(int, double) override;

	Colour getColourAt(int, int) override;

protected:
	int _radius;
	double _yScale;
};

#endif