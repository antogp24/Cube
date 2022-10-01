#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "math3D/vector.h"
#include "math3D/matrix.h"
#include "rotate.h"

void transform_cube_points(Matrix3 *Rx, Matrix3 *Ry, Matrix3 *Rz, RotType rt, Vector *pnts, int i);
void log_points(Vector pnts[N_POINTS]);

#endif
