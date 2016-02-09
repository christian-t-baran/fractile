#include <cmath>
#include <list>
#include <Magick++.h>
#include <utility>


#include "triangle.h"
#include "../tiling/tilingGeometry.h"

// Constructs a triangle from 3 points
Triangle::Triangle(int aX, int aY, int bX, int bY, int cX, int cY) {
	_aX = aX;
	_aY = aY;
	_bX = bX;
	_bY = bY;
	_cX = cY;
	_cY = cY;
}

// Default destructor
Triangle::~Triangle() {
}

// Returns the coordinate of the centroid of a triangle
std::pair<int, int> Triangle::getCenterCoord()
{
	return centerTriangle(_aX, _aY, _bX, _bY, _cX, _cY);
}

// Gets area of triangle using Heron's formula
double Triangle::getArea() {

	double ab = segmentLength(_aX, _aY, _bX, _bY);
	double ac = segmentLength(_aX, _aY, _cX, _cY);
	double bc = segmentLength(_bX, _bY, _cX, _cY);

	double s = (ab + ac + bc) / 3.0;
	
	double area = std::sqrt(s * (s - ab) * (s - ac) * (s - bc) );

	return area;
}

// Returns a Drawable corresponding to the triangle
Magick::Drawable Triangle::getDrawable()
{
	std::list<Magick::Coordinate> coords;
	coords.push_back(Magick::Coordinate(_aX, _aY));
	coords.push_back(Magick::Coordinate(_bX, _bY));
	coords.push_back(Magick::Coordinate(_cX, _cY));

	return Magick::DrawablePolygon(coords);
}

