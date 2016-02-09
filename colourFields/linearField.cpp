#include <vector>

#include "linearField.h"
#include "fieldGeometry.h"


// Constructs a linear field from a set of colours, dimensions, and bias
LinearField::LinearField(std::vector<Colour> colours, int x, int y, double bias){
	_colours = colours;
	_curColours = colours;
	_x = x;
	_y = y;
	_bias = bias;
}


LinearField::~LinearField()
{
}

// resets effect state
void LinearField::reinitialize()
{
	_curColours = _colours;
	_effectStepCur = 0;
}

// Sets up a strobe effect
void LinearField::setStrobe(int steps, double bias) {
	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_strobe = true;
	_pulse = false;
	_converge = false;
}

// Sets up a pulse effect
void LinearField::setPulse(Colour pulse, int steps, double bias) {
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
void LinearField::setConverge(int steps, double bias) {
	_effectStepTotal = steps * 2;
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_strobe = false;
	_pulse = false;
	_converge = true;
}

// Steps effect forward
void LinearField::stepForward() {
	if (_effect && (!finishedEffect())) {
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
Colour LinearField::getColourAt(int x, int y)
{
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
	int max;
	int step;
	int distance;

	if( _xAxis) {
		max = _x / _copies;
		step = _step % max;
		distance = x  % max;
	}
	else {
		max = _y / _copies;
		step = _step % max;
		distance = y % max;
	}

	double l = interpolateDistance(max, distance, step, l2, l1, _bias);
	double a = interpolateDistance(max, distance, step, a2, a1, _bias);
	double b = interpolateDistance(max, distance, step, b2, b1, _bias);

	Colour newColour = Colour(l, a, b);

	return newColour;
}

Colour LinearField::stepEffect(Colour c1, Colour c2) {
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
	else {
		double l;
		double a;
		double b;
		int length;

		if (_xAxis) {
			length = _x;
		}
		else {
			length = _y;
		}


		// if even and at halfway point
		if ((_effectStepTotal % 2) == 0 && (_effectStepCur == (_effectStepTotal / 2))) {
			l = l2;
			a = a2;
			b = b2;
		}
		// past halfway travel towards origin
		else if (_effectStepCur > (_effectStepTotal / 2)) {
			int transitionSteps = _effectStepTotal / 2;
			int effectiveStep = _effectStepCur - transitionSteps;
			double adjustedBias = 1 - _effectBias;

			// interpolate b/w pulse & origin
			l = interpolateStep(length, effectiveStep, transitionSteps, l1, l2, adjustedBias);
			a = interpolateStep(length, effectiveStep, transitionSteps, a1, a2, adjustedBias);
			b = interpolateStep(length, effectiveStep, transitionSteps, b1, b2, adjustedBias);
		}
		// before halfway travel towards 2nd
		else {
			int transitionSteps = _effectStepTotal / 2;

			// interpolate b/w origin & pulse
			l = interpolateStep(length, _effectStepCur, transitionSteps, l2, l1, _effectBias);
			a = interpolateStep(length, _effectStepCur, transitionSteps, a2, a1, _effectBias);
			b = interpolateStep(length, _effectStepCur, transitionSteps, b2, b1, _effectBias);
		}
		newCol = Colour(l, a, b);
	}

	return newCol;
}

void LinearField::changeAxis(){
	if (_xAxis) {
		_xAxis = false;
	}
	else {
		_xAxis = true;
	}
}