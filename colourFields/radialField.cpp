#include <cmath>
#include <iostream>
#include <vector>

#include "radialField.h"
#include "colourField.h"
#include "fieldGeometry.h"

RadialField::RadialField() {

}

RadialField::RadialField(std::vector<Colour> colours, int x, int y, double bias) {
	_colours = colours;
	_curColours = colours;
	_radius = x / 2;
	_yScale = (double) x / (double) y;
	_bias = bias;
}

RadialField::~RadialField()
{
	
}

// resets effect state
void RadialField::reinitialize()
{
	_curColours = _colours;
	_effectStepCur = 0;
}

// Sets up a strobe effect
void RadialField::setStrobe(int steps, unsigned int depth, double bias, bool direction){
	// fix depth if out of range
	if (depth > (_colours.size() - 1)) {
		depth = _colours.size() - 1;
	}

	_effectDepth = depth;
	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_effectDir = direction;
	_strobe = true;
	_pulse = false;
	_converge = false;
	_flow = false;
}

void RadialField::setFlow(int steps, double bias, bool direction) {
	// add enough steps for full transition on each colour
	_effectStepTotal = steps * _colours.size() + _colours.size();
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_effectDir = direction;
	_flow = true;
	_strobe = false;
	_pulse = false;
	_converge = false;
}

// Sets up a pulse effect
void RadialField::setPulse(Colour pulse, int steps, unsigned int depth, double bias, bool direction){
	// fix depth if out of range
	if (depth > (_colours.size() - 1)) {
		depth = _colours.size() - 1;
	}

	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_pulseColour = pulse;
	_effect = true;
	_effectDir = direction;
	_strobe = false;
	_pulse = true;
	_converge = false;
	_flow = false;

}

// Sets up a converge effect
void RadialField::setConverge(int steps, double bias){
	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_strobe = false;
	_pulse = false;
	_converge = true;
	// _flow = false;
}

// Returns the Colour value at (x, y) pt in the field
Colour RadialField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to coordinates on the Cartesian plane
	int field_x = std::abs(x - _radius);
	int field_y = std::abs(std::round(y * _yScale) - _radius);

	// convert Cartesian coordinates to values on unit square
	double unit_x = field_x / ((double)_radius);
	double unit_y = field_y / ((double)_radius);

	// Formula from http://mathproofs.blogspot.ca/2005/07/mapping-square-to-circle.html
	int circle_x = (unit_x * std::sqrt(1 - ( (unit_y * unit_y) / 2.0) )) * _radius;
	int circle_y = (unit_y * std::sqrt(1 - ( (unit_x * unit_x) / 2.0) )) * _radius;

	// c = sqrt( a^2 + b^2) 
	int distance = std::sqrt((circle_x * circle_x) + (circle_y * circle_y));

	Colour newColour = mapDistanceToColourRange(_radius, distance, _step);

	return newColour;
}

