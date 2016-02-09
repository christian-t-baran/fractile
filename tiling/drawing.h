#ifndef DRAWING_H
#define DRAWING_H

#pragma once

#include <Magick++.h>

#include "../colourFields/colourField.h"
#include "../tiles/shape.h"

void drawField(int x, int y, ColourField& field, Magick::Image& image);

void drawShape(Shape& shape, ColourField& field, Magick::Image& image);

#endif