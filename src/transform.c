#include "cube.h"
#include "cube_settings.h"

void transform_cube_points(RunData *rd, RotType rt, int i) {
    
    Vector rotated = {0};
    
    switch (rt) {
        
        case ROTATION_TYPE_NONE: {
            // Do nothing...
        }break;
        
        case ROTATION_TYPE_ALL: {
            rotated = m3_vector_multiplication(rd->Rx, &rd->pnts[i]);
            rotated = m3_vector_multiplication(rd->Ry, &rotated);
            rotated = m3_vector_multiplication(rd->Rz, &rotated);
        }break;
        
        case ROTATION_TYPE_X: {
            rotated = m3_vector_multiplication(rd->Rx, &rd->pnts[i]);
        }break;
        
        case ROTATION_TYPE_Y: {
            rotated = m3_vector_multiplication(rd->Ry, &rd->pnts[i]);
        }break;
        
        case ROTATION_TYPE_Z: {
            rotated = m3_vector_multiplication(rd->Rz, &rd->pnts[i]);
        }break;
    }
    
    rd->pnts[i] = (rt == ROTATION_TYPE_NONE) ? rd->pnts[i] : rotated;
    
    return;
}
