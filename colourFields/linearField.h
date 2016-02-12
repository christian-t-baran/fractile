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
	void changeDirection();

	void setStrobe(int, unsigned int, double, bool) override;
	void setFlow(int, double, bool) override;
	void setPulse(Colour, int, unsigned int, double, bool) override;
	void setConverge(int, double) override;

	Colour getColourAt(int, int) override;

protected:
	int _x;
	int _y;

	bool _direction = true; // true X, false Y
};

