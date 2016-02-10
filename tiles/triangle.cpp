#include <cmath>
#include <iostream>
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
	_cX = cX;
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

	double s = (ab + ac + bc) / 2.0;
	
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

std::string Triangle::toString() {
	std::string coords;
	coords += "A: (" + std::to_string(_aX) + ", " + std::to_string(_aY) + ")\n";
	coords += "B: (" + std::to_string(_bX) + ", " + std::to_string(_bY) + ")\n";
	coords += "C: (" + std::to_string(_cX) + ", " + std::to_string(_cY) + ")\n";

	return coords;
}

std::pair<int, int> Triangle::getA() {
	return std::make_pair(_aX, _aY);
}

std::pair<int, int> Triangle::getB() {
	return std::make_pair(_bX, _bY);
}

std::pair<int, int> Triangle::getC() {
	return std::make_pair(_cX, _cY);
}

