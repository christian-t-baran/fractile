#include <Magick++.h>
#include <utility>

#include "rectangle.h"
#include "../tiling/tilingGeometry.h"

// Constructs a Rectangle from the lower left coordinates of the rectangle
// and the side lengths
Rectangle::Rectangle(int xLL, int yLL, int xLength, int yLength){
	_xLL = xLL;
	_yLL = yLL;
	_xLength = xLength;
	_yLength = yLength;
}

Rectangle::~Rectangle(){
}

// Returns the center coordinate of the rectangle
std::pair<int, int> Rectangle::getCenterCoord()
{
	return centerRectangle(_xLL, _xLL + _xLength, _yLL, _yLL + _yLength);
}

// Returns the area of the rectangle
double Rectangle::getArea() {
	return _xLength * _yLength;
}

// Returns a Drawable representation of the rectangle
Magick::Drawable Rectangle::getDrawable()
{
	return Magick::DrawableRectangle(_xLL, _yLL + _yLength, _xLL + _xLength, _yLL);
}

