#ifndef VECTOR_H
#define VECTOR_H

typedef union Vector {
    struct {
        float x, y, z;
    };
    float arr[3];
}Vector;

#define N_POINTS 8
#define SIDES_LENGTH 50.0f // 50

Vector vector_scale(Vector *v, float scalar);
void vector_log(Vector *v);

#endif
