#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <math.h>

#define COS(a) (float)cos(a)
#define SIN(a) (float)sin(a)

typedef union Matrix3 {
    struct {
        float m1, m2, m3,
        m4, m5, m6,
        m7, m8, m9;
    };
    float arr[3*3];
}Matrix3;

float *m3Ind(Matrix3 *matrix, int i, int j);
void matrices_update(Vector *angles, Matrix3 *Rx, Matrix3 *Ry, Matrix3 *Rz, float dt);
void matrix_log(Matrix3 *matrix);
Vector matmul(Matrix3 *matrix, Vector *vec);

#endif
