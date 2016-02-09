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
	void changeAxis();

	void setStrobe(int, double) override;
	void setPulse(Colour, int, double) override;
	void setConverge(int, double) override;
	void stepForward() override;

	Colour getColourAt(int, int) override;

protected:
	std::vector<Colour> _colours;
	std::vector<Colour> _curColours;
	int _x;
	int _y;

	bool _xAxis = true;

private:
	Colour stepEffect(Colour, Colour);
};

