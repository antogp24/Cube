#include <math3D/vector.h>
#include <stdio.h>

Vector vector_scale(Vector *v, float scalar) {
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
    return(*v);
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

