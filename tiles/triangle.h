#include <Magick++.h>
#include <utility>

#include "shape.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

class Triangle :
	public Shape
{
public:
	Triangle(int, int, int, int, int, int);
	~Triangle();

	std::pair<int, int> getCenterCoord() override;
	double getArea() override;
	Magick::Drawable getDrawable() override;

protected:
	int _aX;
	int _aY;
	int _bX;
	int _bY;
	int _cX;
	int _cY;
};

#endif
