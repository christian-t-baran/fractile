#include <Magick++.h>
#include <utility>

#include "shape.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once

class Rectangle :
	public Shape
{
public:
	Rectangle(int, int, int, int);
	~Rectangle();

	std::pair<int, int> getCenterCoord() override;
	double getArea() override;
	Magick::Drawable getDrawable() override;

protected:
	int _xLL;
	int _yLL;
	int _xLength;
	int _yLength;
};

#endif