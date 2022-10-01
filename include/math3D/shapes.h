#ifndef SHAPES_H
#define SHAPES_H

#include <raylib.h>
#include "window.h"
#include "vector.h"

void shapes_line(float ax, float ay, float bx, float by);
void shapes_point(float x, float y);
void shapes_connect(int indexStt, int indexEnd, Vector pnts[8], int offset_x, int offset_y);

#endif
