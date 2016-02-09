#include <cmath>
#include <iostream>
#include <vector>

#include "radialField.h"
#include "colourField.h"
#include "fieldGeometry.h"

RadialField::RadialField() {

}

RadialField::RadialField(std::vector<Colour> colours, int radius, double bias) {
	_colours = colours;
	_curColours = colours;
	_radius = radius;
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
void RadialField::setStrobe(int steps, double bias){
	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_strobe = true;
	_pulse = false;
	_converge = false;
}

// Sets up a pulse effect
void RadialField::setPulse(Colour pulse, int steps, double bias){
	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_pulseColour = pulse;
	_effect = true;
	_strobe = false;
	_pulse = true;
	_converge = false;
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
}

// Steps effect forward
void RadialField::stepForward() {
	if (_effect && ( !finishedEffect() ) ){
		if (_strobe) {
			_curColours[0] = stepEffect(_colours[0], _colours[1]);
		}
		else if (_pulse) {
			_curColours[0] = stepEffect(_colours[0], _pulseColour);
		}
		else if (_converge) {
			_curColours[0] = stepEffect(_colours[0], _colours[1]);
			_curColours[1] = stepEffect(_colours[1], _colours[0]);
		}
	}

	_effectStepCur++;
}

// Returns the Colour value at (x, y) pt in the field
Colour RadialField::getColourAt(int x, int y)
{
	// change (0, 0) coordinates to coordinates on the Cartesian plane
	int field_x = x - _radius;
	int field_y = y - _radius;

	// convert Cartesian coordinates to values on unit square
	double unit_x = field_x / ((double)_radius);
	double unit_y = field_y / ((double)_radius);

	// Formula from http://mathproofs.blogspot.ca/2005/07/mapping-square-to-circle.html
	int circle_x = (unit_x * std::sqrt(1 - ( (unit_y * unit_y) / 2.0) )) * _radius;
	int circle_y = (unit_y * std::sqrt(1 - ( (unit_x * unit_x) / 2.0) )) * _radius;

	// c = sqrt( a^2 + b^2) 
	int distance = std::sqrt((circle_x * circle_x) + (circle_y * circle_y));

	// adjust for copies
	int max = _radius / _copies;
	int step = _step % max;
	distance = distance % max;

	// get Colours from vector
	Colour first = _curColours[0];
	Colour second = _curColours[1];

	// get LAB values
	double l1 = first.getLAB_L();
	double l2 = second.getLAB_L();
	double a1 = first.getLAB_A();
	double a2 = second.getLAB_A();
	double b1 = first.getLAB_B();
	double b2 = second.getLAB_B();

	// interpolate new LAB values
	double l = interpolateDistance(max, distance, step, l2, l1, _bias);
	double a = interpolateDistance(max, distance, step, a2, a1, _bias);
	double b = interpolateDistance(max, distance, step, b2, b1, _bias);
	
	Colour newColour = Colour(l, a, b);

	return newColour;
}

Colour RadialField::stepEffect(Colour c1, Colour c2){
	double l1 = c1.getLAB_L();
	double l2 = c2.getLAB_L();
	double a1 = c1.getLAB_A();
	double a2 = c2.getLAB_A();
	double b1 = c1.getLAB_B();
	double b2 = c2.getLAB_B();

	Colour newCol;

	if (_effectStepCur == _effectStepTotal) {
		newCol = _colours[0];
	}
	else{
		double l;
		double a;
		double b;
		// if even and at halfway point
		if ( (_effectStepTotal % 2) == 0 && (_effectStepCur == (_effectStepTotal / 2) ) ){
			l = l2;
			a = a2;
			b = b2;
		}
		// past halfway travel towards origin
		else if (_effectStepCur > (_effectStepTotal / 2) ) {
			int transitionSteps = _effectStepTotal / 2;
			int effectiveStep = _effectStepCur - transitionSteps;
			double adjustedBias = 1 - _effectBias;

			// interpolate b/w pulse & origin
			l = interpolateStep(_radius, effectiveStep, transitionSteps, l1, l2, adjustedBias);
			a = interpolateStep(_radius, effectiveStep, transitionSteps, a1, a2, adjustedBias);
			b = interpolateStep(_radius, effectiveStep, transitionSteps, b1, b2, adjustedBias);
		}
		// before halfway travel towards 2nd
		else {
			int transitionSteps = _effectStepTotal / 2;
			
			// interpolate b/w origin & pulse
			l = interpolateStep(_radius, _effectStepCur, transitionSteps, l2, l1, _effectBias);
			a = interpolateStep(_radius, _effectStepCur, transitionSteps, a2, a1, _effectBias);
			b = interpolateStep(_radius, _effectStepCur, transitionSteps, b2, b1, _effectBias);
		}
		newCol = Colour(l, a, b);
	}

	return newCol;
}

