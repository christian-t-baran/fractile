#ifndef _TILING_GEOMETRY_H
#define _TILING_GEOMETRY_H

#pragma once

int LCM(int, int);

int GCD(int, int);

std::pair<int, int> midpoint(int, int, int, int);

std::pair<int, int> centerRectangle(int, int, int, int);
std::pair<int, int> centerTriangle(int, int, int, int, int, int);

#endif
