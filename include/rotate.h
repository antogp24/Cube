/* date = September 25th 2022 3:58 pm */

#ifndef ROTATE_H
#define ROTATE_H

#include <raylib.h>
#include "math3D/vector.h"

typedef enum RotType {
    ROT_NONE,
    ROT_ALL,
    ROT_X,
    ROT_Y,
    ROT_Z,
}RotType;

RotType rotateManage(RotType initial, Vector pnts[N_POINTS]);
void reset_points(Vector pnts[N_POINTS]);

#endif //ROTATE_H
