#include <math3D/transform.h>
#include <settings.h>

void transform_cube_points(Matrix3 *Rx, Matrix3 *Ry, Matrix3 *Rz, RotType rt, Vector *pnts, int i) {
    
    Vector rotated = {0};
    
    switch (rt) {
        
        case ROT_NONE: {
            // Do nothing...
        }break;
        
        case ROT_ALL: {
            rotated = matmul(Rx, &pnts[i]);
            rotated = matmul(Rx, &rotated);
            rotated = matmul(Rz, &rotated);
        }break;
        
        case ROT_X: {
            rotated = matmul(Rx, &pnts[i]);
        }break;
        
        case ROT_Y: {
            rotated = matmul(Ry, &pnts[i]);
        }break;
        
        case ROT_Z: {
            rotated = matmul(Rz, &pnts[i]);
        }break;
    }
    
    pnts[i] = (rt == ROT_NONE) ? pnts[i] : rotated;
    
    return;
}

void log_points(Vector pnts[N_POINTS]) {
    for (int i = 0; i < N_POINTS; i++) {
        vector_log(&pnts[i]);
    }
}