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
void LinearField::setStrobe(int steps, unsigned int depth, double bias, bool direction) {
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

void LinearField::setFlow(int steps, double bias, bool direction) {
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
void LinearField::setPulse(Colour pulse, int steps, unsigned int depth, double bias, bool direction) {
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
void LinearField::setConverge(int steps, double bias) {
	_effectStepTotal = (steps * (_colours.size() - 1) * 2) + ((_colours.size() - 1) * 2);
	_effectStepCur = 0;
	_effectBias = bias;
	_effect = true;
	_strobe = false;
	_pulse = false;
	_converge = true;
	_flow = false;
}

// Returns the Colour value at (x, y) pt in the field
Colour LinearField::getColourAt(int x, int y)
{
	// interpolate new LAB values
	int maxDistance;
	int distance;

	if(_direction) {
		maxDistance = _x;
		distance = x;
	}
	else {
		maxDistance = _y;
		distance = y;
	}

	Colour newColour = mapDistanceToColourRange(maxDistance, distance, _step);

	return newColour;
}

void LinearField::changeDirection(){
	if (_direction) {
		_direction = false;
	}
	else {
		_direction = true;
	}
}