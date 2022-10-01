#ifndef SETTINGS_H
#define SETTINGS_H

#include "math3D.h"

#define DEBUG_ALL

// En radianes
static Vector rv = { 
    +0.45f, 
    -0.95f, 
    +0.25f,
};

#define aX rv.x
#define aY rv.y
#define aZ rv.z

static Vector origin = { WIN_X/2, WIN_Y/2, 0 };

#endif
