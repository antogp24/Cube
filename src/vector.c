#include "cube.h"

Vector vector_scale(Vector *v, float scalar) {
    
    Vector result = {0};
    result.x = v->x * scalar;
    result.y = v->y * scalar;
    result.z = v->z * scalar;
    return(result);
}

void vector_log(Vector *v) {
    
    printf("3D vector\n");
    printf("---------\n");
    
    for (int r = 0; r < 3; r++) {
        printf("[ ");
        printf(" %f ", v->arr[r]);
        printf("]");
        printf("\n");
    }
    printf("---------\n");
}

void vector_cube_points_reset(Vector pnts[N_POINTS]) {
    pnts[0] = (Vector){-SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH}; // Top Left      #0
    pnts[1] = (Vector){+SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH}; // Top Right     #1
    pnts[2] = (Vector){+SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH}; // Bottom Right  #2
    pnts[3] = (Vector){-SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH}; // Bottom Left   #3
    pnts[4] = (Vector){-SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH}; // Top Left      #4
    pnts[5] = (Vector){+SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH}; // Top Right     #5
    pnts[6] = (Vector){+SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH}; // Bottom Right  #6
    pnts[7] = (Vector){-SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH}; // Bottom Left   #7
}

void vector_cube_points_log(Vector pnts[N_POINTS]) {
    for (int i = 0; i < N_POINTS; i++) {
        vector_log(&pnts[i]);
    }
}