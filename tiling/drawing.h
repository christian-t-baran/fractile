#ifndef DRAWING_H
#define DRAWING_H

#pragma once

#include <Magick++.h>

#include "../colourFields/colourField.h"
#include "../tiles/shape.h"

void processImage(int x, int y, ColourField& fill, ColourField& back, Magick::Image& image);

void drawField(int x, int y, ColourField& field, Magick::Image& image);

void drawShape(Shape& shape, ColourField& field, Magick::Image& image);

int readImage();

std::pair<int, int> getBW(int, int, int, int, Magick::Image& image);

std::pair<int, int> getBW(int x1, int x2, int y1, int y2, Magick::Image& image);

#endif