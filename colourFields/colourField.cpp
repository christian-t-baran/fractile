#include "vector"

#include "../colours/colour.h"
#include "colourField.h"

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

void ColourField::setStrobe(int steps, double bias) {
}

void ColourField::setPulse(Colour pulse, int steps, double bias) {
}

void ColourField::setConverge(int steps, double bias) {
}

void ColourField::stepForward() {
	++_effectStepCur;
}

bool ColourField::finishedEffect() {
	return _effectStepCur >= _effectStepTotal;
}

int ColourField::effectStepCurrent() {
	return _effectStepCur;
}

int ColourField::effectStepTotal() {
	return _effectStepTotal;
}


Colour ColourField::getColourAt(int x, int y) {
	return _colours[0];
}