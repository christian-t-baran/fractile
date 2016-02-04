#include <cmath>
#include <iostream>
#include <vector>

#include "radialField.h"
#include "colourField.h"
#include "fieldGeometry.h"

RadialField::RadialField(std::vector<Colour> colours, int radius, double bias) {
	_colours = colours;
	_curColours = colours;
	_radius = radius;
	_bias = bias;
	_step = 1;
	_pulse = false;
	_converge = false;
}

RadialField::~RadialField()
{
	
}

void RadialField::reinitialize()
{
	_step = 1;
	_curColours = _colours;
	_pulse = false;
	_converge = false;
}

void RadialField::setBias(double bias)
{
	_bias = bias;
}

void RadialField::setPulse()
{
	_pulse = true;
	_converge = false;
}

void RadialField::stepPulse()
{
	// step first current colour forward
}

bool RadialField::finishedPulse()
{
	// return whether all steps completed
	return false;
}

void RadialField::setConverge()
{
	_converge = true;
	_pulse = false;
}

void RadialField::stepConverge()
{
	// step both colours forward
}

bool RadialField::finishedConverge()
{
	// return whether all steps completed
	return false;
}

// Formula from http://mathproofs.blogspot.ca/2005/07/mapping-square-to-circle.html
Colour RadialField::getColourAt(int x, int y)
{
	int field_x = x - _radius;
	int field_y = y - _radius;

	double unit_x = field_x / ((double)_radius);
	double unit_y = field_y / ((double)_radius);
	int circle_x = (unit_x * std::sqrt(1 - ( (unit_y * unit_y) / 2.0) )) * _radius;
	int circle_y = (unit_y * std::sqrt(1 - ( (unit_x * unit_x) / 2.0) )) * _radius;

	// int circle_x = field_x * std::pow(1 - ( (field_y * field_y) / 2.0 ), 1.0 / 2.0);
	// int circle_y = field_y * std::pow(1 - ( (field_x * field_x) / 2.0 ), 1.0 / 2.0);

	int distance = std::sqrt( (circle_x * circle_x) + (circle_y * circle_y) );
	
	// std::cout << "Distance " << distance << std::endl;


	Colour first = _curColours[0];
	Colour second = _curColours[1];

	double l1 = first.getLAB_L();
	double l2 = second.getLAB_L();
	double a1 = first.getLAB_A();
	double a2 = second.getLAB_A();
	double b1 = first.getLAB_B();
	double b2 = second.getLAB_B();

	double l = interpolateDistance(_radius, distance, _step, l2, l1, _bias);
	double a = interpolateDistance(_radius, distance, _step, a2, a1, _bias);
	double b = interpolateDistance(_radius, distance, _step, b2, b1, _bias);

	// std::cout << "LAB : (" << l << ", " << a << ", " << b << ")" << std::endl;

	Colour newColour = Colour(l, a, b);

	return newColour;
}

void radialFieldTests()
{
}
