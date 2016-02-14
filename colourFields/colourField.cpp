#include <iostream>
#include "vector"

#include "../colours/colour.h"
#include "colourField.h"
#include "fieldGeometry.h"

ColourField::ColourField() {
	std::vector<Colour> colours(1);
	colours[0] = Colour(0, 0, 0);
	
	_colours = colours;
	_curColours = colours;
}

ColourField::ColourField(std::vector<Colour> colours) {
	_colours = colours;
	_curColours = colours;
}

ColourField::~ColourField() {
}

void ColourField::reinitialize() {
	_effectStepCur = 0;
}

void ColourField::setStep(int step) {
	_step = step;
}

void ColourField::setCopies(int copies) {
	_copies = copies;
}

void ColourField::setBias(double bias)
{
	_bias = bias;
}

void ColourField::setStrobe(int steps, unsigned int depth, double bias, bool direction) {
}

void ColourField::setPulse(Colour pulse, int steps, unsigned int depth, double bias, bool direction) {
}


void ColourField::setFlow(int steps, double bias, bool direction) {
}

void ColourField::setConverge(int steps, double bias) {
}


void ColourField::stepForward() {
	if (_effect && (!finishedEffect())) {
		if (_strobe) {
			stepStrobePulse();
		}
		else if (_pulse) {
			stepStrobePulse();
		}
		else if (_flow) {
			stepFlow();
		}
		else if (_converge) {
			stepConverge();
		}
	}

	_effectStepCur++;
}

// steps strobe or pulse effect forward
void ColourField::stepStrobePulse() {
	// starting point in vector
	int start;
	if (_effectDir) {
		start = 0;
	}
	else {
		start = _curColours.size() - 1;
	}

	// time for half of total effect
	int transitionSteps = _effectStepTotal / 2;

	// whether past halfway
	bool halfway = _effectStepCur > transitionSteps;

	// adjust bias & step 
	double adjustedBias = _bias;
	if (halfway) {
		adjustedBias = 1 - adjustedBias;
	}

	int adjustedStep = _effectStepCur;
	if (halfway) {
		adjustedStep = adjustedStep - transitionSteps;
	}

	// adjust starting offset if pulse effect
	int startOffset = 1;
	if (_pulse) {
		startOffset = 0;
	}

	// adjust all colours in depth
	for (int i = startOffset; i <= _effectDepth; i++) {
		//before halfway
		if (!halfway) {
			// start from inside
			if (_effectDir) {
				Colour c1 = _colours[start + i];
				Colour c2 = _colours[start];
				if (_pulse) {
					c2 = _pulseColour;
				}
				_curColours[start + i] = interpolateColour(c1, c2, adjustedStep, transitionSteps, adjustedBias, true);
			}
			// start from outside
			else {
				Colour c1 = _colours[start - i];
				Colour c2 = _colours[start];
				if (_pulse) {
					c2 = _pulseColour;
				}
				_curColours[start - i] = interpolateColour(c1, c2, adjustedStep, transitionSteps, adjustedBias, true);
			}
		}
		//after halfway
		else {
			// start from inside
			if (_effectDir) {
				Colour c1 = _colours[start];
				Colour c2 = _colours[start + i];
				if (_pulse) {
					c1 = _pulseColour;
				}
				_curColours[start + i] = interpolateColour(c1, c2, adjustedStep, transitionSteps, adjustedBias, true);
			}
			// start from outside
			else {
				Colour c1 = _colours[start];
				Colour c2 = _colours[start - i];
				if (_pulse) {
					c1 = _pulseColour;
				}
				_curColours[start - i] = interpolateColour(c1, c2, adjustedStep, transitionSteps, adjustedBias, true);
			}
		}
	}

}

// steps converge forwrad
void ColourField::stepConverge() {
	// account for extra added steps
	int transitionSteps = (_effectStepTotal / ((_colours.size() - 1) * 2)) - 1;

	int curStep = _effectStepCur % (transitionSteps + 1);

	// whether past halfway
	bool halfway = _effectStepCur >= ( _effectStepTotal / 2 );

	bool odd = (_colours.size() % 2) != 0;

	int left = 1;
	int right = _colours.size() - 2;

	int offset = _effectStepCur / (transitionSteps + 1);
	if (halfway) {
		offset -= _colours.size() - 1;
	}

	left += offset;
	right -= offset;

	// travel through middle changing colours
	if (left == right) {
		_effectStepCur += transitionSteps;
	}
	else if (!halfway) {
		Colour cStart = _colours[0];
		Colour cLeft = _colours[left];

		Colour cEnd = _colours[_colours.size() - 1];
		Colour cRight = _colours[right];

		if (left < right) {
			_curColours[left] = interpolateColour(cLeft, cStart, curStep, transitionSteps, 0.5, true);
			_curColours[right] = interpolateColour(cRight, cEnd, curStep, transitionSteps, 0.5, true);
		}
		else {
			int beforeLeft = left - 1;
			int beforeRight = right + 1;

			_curColours[left] = interpolateColour(cEnd, cStart, curStep, transitionSteps, 0.5, true);
			_curColours[right] = interpolateColour(cStart, cEnd, curStep, transitionSteps, 0.5, true);

			if ((beforeLeft > beforeRight) && (beforeLeft != beforeRight) && (beforeLeft != 0) && (beforeRight != _colours.size())) {
				Colour cBeforeRight = _colours[beforeRight];
				Colour cBeforeLeft = _colours[beforeLeft];

				_curColours[beforeRight] = interpolateColour(cEnd, cBeforeLeft, curStep, transitionSteps, 0.5, true);
				_curColours[beforeLeft] = interpolateColour(cStart, cBeforeRight, curStep, transitionSteps, 0.5, true);
			}

		}
	}
	else {
		Colour cStart = _colours[_colours.size() - 1];
		Colour cLeft = _colours[left];

		Colour cEnd = _colours[0];
		Colour cRight = _colours[right];

		if (left < right) {
			_curColours[left] = interpolateColour(cRight, cStart, curStep, transitionSteps, 0.5, true);
			_curColours[right] = interpolateColour(cLeft, cEnd, curStep, transitionSteps, 0.5, true);
		}
		else {
			int beforeLeft = left - 1;
			int beforeRight = right + 1;

			_curColours[left] = interpolateColour(cEnd, cStart, curStep, transitionSteps, 0.5, true);
			_curColours[right] = interpolateColour(cStart, cEnd, curStep, transitionSteps, 0.5, true);

			if ((beforeLeft > beforeRight) && (beforeLeft != beforeRight) && (beforeLeft != 0) && (beforeRight != _colours.size())) {
				Colour cBeforeRight = _colours[beforeRight];
				Colour cBeforeLeft = _colours[beforeLeft];

				_curColours[beforeRight] = interpolateColour(cEnd, cBeforeRight, curStep, transitionSteps, 0.5, true);
				_curColours[beforeLeft] = interpolateColour(cStart, cBeforeLeft, curStep, transitionSteps, 0.5, true);
			}

		}
	}
	

}

// steps flow forward
void ColourField::stepFlow() {
	// total steps = number of colours * transition + number of colours (to add transition end) 
	int transitionSteps = (_effectStepTotal / _colours.size() ) - 1;

	// effectively 0-transitionStep so need + 1
	int curStep = _effectStepCur % (transitionSteps + 1);
	int currentOffset = _effectStepCur / (transitionSteps + 1);
	
	// update all colours
	for (int i = 0; i < _colours.size(); i++) {
		int firstIndex;
		int secondIndex;

		// add the offset or subtract depending on direction
		if (_effectDir) {
			firstIndex = (i + currentOffset) % _colours.size();
			secondIndex = (i + 1 + currentOffset) % _colours.size();
		}
		else {
			firstIndex = (i - currentOffset);
			// if negative, wrap index
			if (firstIndex < 0) {
				firstIndex = _colours.size() - firstIndex;
			}
			firstIndex = firstIndex % _colours.size();

			secondIndex = (i - 1 - currentOffset);
			// if negative, wrap index
			if (secondIndex < 0) {
				secondIndex = _colours.size() + secondIndex;
			}
			secondIndex = secondIndex % _colours.size();

		}

		Colour c1 = _colours[firstIndex];
		Colour c2 = _colours[secondIndex];

		_curColours[i] = interpolateColour(c1, c2, curStep, transitionSteps, 0.5, true);
	}

}


bool ColourField::finishedEffect() {
	return _effectStepCur >= _effectStepTotal;
}

int ColourField::effectStepCurrent() {
	return _effectStepCur;
}

int ColourField::effectStepTotal() {
	int effectSteps = _effectStepTotal;

	// adjust for skipped steps in converge algorithm
	// if odd number of colours
	if (_converge && ((_colours.size() % 2) != 0) ){
		int transitionSteps = (_effectStepTotal / ((_colours.size() - 1) * 2)) - 1;
	}

	return effectSteps;
}


Colour ColourField::getColourAt(int x, int y) {
	return _colours[0];
}

// gets the colour at adjusted max, distance, and range
Colour ColourField::mapDistanceToColourRange(int max, int distance, int step)
{
	// adjust for copies
	max = max / _copies;
	step = _step % (max + 1);
	distance = distance % (max + 1);

	// calculate current step
	int curStep = correspondingStep(max, distance, step, _bias);

	std::pair<int, int> indices = neighbours(curStep, max / step, _colours.size());

	// steps between each colour
	std::pair<int, int> totalAndRemainder = stepsBetween(max / step, _colours.size());

	int colStepTotal = totalAndRemainder.first;

	int colStepCur;
	if (curStep == 0) {
		colStepCur = 0;
	}
	else {
		colStepCur = curStep % (colStepTotal);
	}

	// if at the end add on the remainder
	if (indices.first == (_colours.size() - 2)) {
		colStepCur += totalAndRemainder.second;
		colStepTotal += totalAndRemainder.second;
	}

	bool applyBias = false;
	// if even and in the middle (1 less than half way, apply bias to interpolation
	if ((_colours.size() % 2 == 0) && (indices.first == ((_colours.size() / 2) - 1))) {
		applyBias = true;
	}

	// get Colours from vector
	Colour first = _curColours[indices.first];
	Colour second = _curColours[indices.second];

	Colour newColour = interpolateColour(first, second, colStepCur, colStepTotal, _bias, applyBias);

	return newColour;
}


Colour ColourField::stepEffect(Colour c1, Colour c2) {
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
			l = interpolateStep(effectiveStep, transitionSteps, l1, l2, adjustedBias);
			a = interpolateStep(effectiveStep, transitionSteps, a1, a2, adjustedBias);
			b = interpolateStep(effectiveStep, transitionSteps, b1, b2, adjustedBias);
		}
		// before halfway travel towards 2nd
		else {
			int transitionSteps = _effectStepTotal / 2;

			// interpolate b/w origin & pulse
			l = interpolateStep(_effectStepCur, transitionSteps, l2, l1, _effectBias);
			a = interpolateStep(_effectStepCur, transitionSteps, a2, a1, _effectBias);
			b = interpolateStep(_effectStepCur, transitionSteps, b2, b1, _effectBias);
		}
		newCol = Colour(l, a, b);
	}

	return newCol;
}

// returns steps between elements, and remainder
std::pair<int, int> stepsBetween(int totalSteps, int numElements) {
	return std::make_pair(totalSteps / (numElements - 1), totalSteps % (numElements - 1));
}

// returns adjacent elements (corresponding to current step)
std::pair<int, int> neighbours(int curStep, int totalSteps, int numElements) {
	int interval = stepsBetween(totalSteps, numElements).first;

	int first = curStep / interval;
	
	// end boundary
	if (first > (numElements - 2)) {
		first = numElements - 2;
	}

	std::pair<int, int> adjacent;
	if (curStep = totalSteps) {
		adjacent = std::make_pair(numElements - 2, numElements - 1);
	}
	else {
		adjacent = std::make_pair(first, first + 1);
	}


	return std::make_pair(first, first+1);
}
