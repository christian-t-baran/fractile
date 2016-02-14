#include <Magick++.h>
#include <utility>

#include "line.h"
#include "../tiling/tilingGeometry.h"

// Constructs a Line from the starting x,y coordinates and the
// ending x, y coordinates
Line::Line(int xStart, int yStart, int xEnd, int yEnd) {
	_xStart = xStart;
	_yStart = yStart;
	_xEnd = xEnd;
	_yEnd = yEnd;
}

Line::~Line() {
}

// Returns the midpoint of the line
std::pair<int, int> Line::getCenterCoord()
{
	return midpoint(_xStart, _xEnd, _yStart, _yEnd);
}

// Returns the length of the line
double Line::getArea() {
	return segmentLength(_xStart, _yStart, _xEnd, _yEnd);
}

// Returns a DrawableLine
Magick::Drawable Line::getDrawable()
{
	return Magick::DrawableLine(_xStart, _yStart, _xEnd, _yEnd);
}

std::string Line::toString()
{
	std::string data;
	data += "Starting coordinate: (" + std::to_string(_xStart) + ", " + std::to_string(_yStart) + ")\n";
	data += "Ending coordinate: (" + std::to_string(_xEnd) + ", " + std::to_string(_yEnd) + ")\n";

	return data;
}

