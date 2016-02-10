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

	void setStrobe(int, double) override;
	void setPulse(Colour, int, double) override;
	void setConverge(int, double) override;

	void stepForward() override;

	Colour getColourAt(int, int) override;

protected:
	std::vector<Colour> _colours;
	std::vector<Colour> _curColours;

	int _radius;
	double _yScale;

private:
	Colour stepEffect(Colour, Colour);
};

#endif