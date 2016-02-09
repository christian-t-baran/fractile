#ifndef COLOUR_FIELD_H
#define COLOUR_FIELD_H

#pragma once

#include <vector>
#include "../colours/colour.h"


// Abstract base class for ColourFields
class ColourField {
public:
	ColourField();
	ColourField(std::vector<Colour> colours);
	~ColourField();

	virtual void reinitialize();
	virtual void setStep(int);
	virtual void setBias(double);
	virtual void setCopies(int);
	virtual Colour getColourAt(int, int);

	virtual void setPulse(Colour, int, double);
	virtual void setStrobe(int, double);
	virtual void setConverge(int, double);

	virtual void stepForward();
	virtual bool finishedEffect();

	virtual int effectStepTotal();
	virtual int effectStepCurrent();

protected:
	std::vector<Colour> _colours;
	std::vector<Colour> _curColours;

	// irrelevant to base class
	double _bias = 0.5;
	int _step = 1;
	int _copies = 1;
	bool _effect = false;

	Colour _pulseColour;
	bool _pulse = false;
	bool _strobe = false;
	bool _converge = false;
	int _effectStepTotal = 1;
	int _effectStepCur = 0;
	double _effectBias = 0.5;
};

#endif