#ifndef CURVE_TILING_H
#define CURVE_TILING_H

#pragma once

void curveTiling();

void hilbertify(int x, int y, int xi, int xj, int yi, int yj, int n, int nmin, int nmax, std::list<Magick::VPath>& path, Magick::Image& image);

#endif