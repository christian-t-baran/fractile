#include <Magick++.h>
#include <utility>

#ifndef SHAPE_H
#define SHAPE_H

#pragma once

class Shape {
public:
	Shape() {};
	~Shape() {};

	virtual std::pair<int, int> getCenterCoord() = 0;
	virtual double getArea() = 0;
	virtual Magick::Drawable getDrawable() = 0;
};
#endif