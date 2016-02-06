#pragma once
#include "D:\VisualCPP\Repos\fractile\colourFields\colourField.h"

// Models a LinearColourField
class LinearField :
	public ColourField
{
public:
	LinearField(std::vector<Colour>, int, int, double);
	~LinearField();

	void reinitialize() override;
	void setStep(int) override;
	void setBias(double) override;
	void changeAxis();

	void setStrobe(int, double) override;
	void setPulse(Colour, int, double) override;
	void setConverge(int, double) override;
	void stepForward();
	bool finishedEffect() override;

	Colour getColourAt(int, int) override;

protected:
	std::vector<Colour> _colours;
	std::vector<Colour> _curColours;
	int _x;
	int _y;
	double _bias;
	int _step;
	bool _xAxis;
	bool _effect;

	Colour _pulseColour;
	bool _pulse = false;
	bool _strobe = false;
	bool _converge = false;
	int _effectStepTotal;
	int _effectStepCur;
	double _effectBias;

private:
	Colour stepEffect(Colour, Colour);
};

