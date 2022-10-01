#include <rotate.h>

RotType rotateManage(RotType initial, Vector pnts[N_POINTS]) {
    RotType rt = initial;
    
    if (IsKeyPressed(KEY_SPACE)) {
        
        switch (rt) {
            
            case ROT_NONE: {
                rt = ROT_ALL;
                reset_points(pnts);
            }break;
            
            case ROT_ALL: {
                rt = ROT_X;
                reset_points(pnts);
            }break;
            
            case ROT_X: {
                rt = ROT_Y;
                reset_points(pnts);
            }break;
            
            case ROT_Y: {
                rt = ROT_Z;
                reset_points(pnts);
            }break;
            
            case ROT_Z: {
                rt = ROT_NONE;
                reset_points(pnts);
            }break;
        }
    }
    
    return(rt);
}

void reset_points(Vector pnts[N_POINTS]) {
    pnts[0] = (Vector){-SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH}; // Top Left      #0
    pnts[1] = (Vector){+SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH}; // Top Right     #1
    pnts[2] = (Vector){+SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH}; // Bottom Right  #2
    pnts[3] = (Vector){-SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH}; // Bottom Left   #3
    pnts[4] = (Vector){-SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH}; // Top Left      #4
    pnts[5] = (Vector){+SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH}; // Top Right     #5
    pnts[6] = (Vector){+SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH}; // Bottom Right  #6
    pnts[7] = (Vector){-SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH}; // Bottom Left   #7
}