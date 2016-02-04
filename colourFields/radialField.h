#ifndef RADIAL_FIELD_H
#define RADIAL_FIELD_H

#pragma once
#include <vector>

#include "../colours/colour.h"
#include "colourField.h"

class RadialField : 
	public ColourField {

public:
	RadialField(std::vector<Colour>, int, double);
	~RadialField();
	void reinitialize() override;
	void setBias(double) override;
	void setPulse() override;
	void stepPulse() override;
	bool finishedPulse() override;
	void setConverge() override;
	void stepConverge() override;
	bool finishedConverge() override;
	Colour getColourAt(int, int) override;

protected:
	std::vector<Colour> _colours;
	std::vector<Colour> _curColours;
	int _radius;
	double _bias;
	int _step;
	bool _pulse;
	bool _converge;
	int _effectSteps;
	int _curEffectStep;
	Colour _pulseColour;
};

void radialFieldTests();

#endif