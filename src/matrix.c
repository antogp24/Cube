#include <math3D/matrix.h>
#include <math3D/vector.h>
#include <stdio.h>

/// Indexing them easily
/// ---------------------------------------------------------------------- ///

float *m3Ind(Matrix3 *matrix, int i, int j) {
    return &(matrix->arr[3 * i + j]);
}

/// Useful Matrices
/// ---------------------------------------------------------------------- ///

void matrices_update(Vector *angles, Matrix3 *Rx, Matrix3 *Ry, Matrix3 *Rz, float dt) {
    float aX = angles->x * dt;
    float aY = angles->y * dt;
    float aZ = angles->z * dt;
    
    // Only update the ones that are necessary
    
    *m3Ind(Rx, 1, 1) =  COS(aX);
    *m3Ind(Rx, 1, 2) = -SIN(aX);
    *m3Ind(Rx, 2, 1) =  SIN(aX);
    *m3Ind(Rx, 2, 2) =  COS(aX);
    
    *m3Ind(Ry, 0, 0) =  COS(aY);
    *m3Ind(Ry, 0, 2) = -SIN(aY);
    *m3Ind(Ry, 2, 0) =  SIN(aY);
    *m3Ind(Ry, 2, 2) =  COS(aY);
    
    *m3Ind(Rz, 0, 0) =  COS(aZ);
    *m3Ind(Rz, 0, 1) = -SIN(aZ); 
    *m3Ind(Rz, 1, 0) =  SIN(aZ);
    *m3Ind(Rz, 1, 1) =  COS(aZ); 
}

/// Matrix Logging
/// ---------------------------------------------------------------------- ///

void matrix_log(Matrix3 *matrix) {
    
    printf("   3x3\n");
    printf("---------\n");
    
    for (int r = 0; r < 3; r++) {
        printf("[ ");
        for (int c = 0; c < 3; c++) {
            printf("%f ", *m3Ind(matrix, r, c));
        }
        printf("]");
        printf("\n");
    }
    printf("---------\n");
}

/// Matrix Multiplication Function
/// ---------------------------------------------------------------------- ///

Vector matmul(Matrix3 *matrix, Vector *vec) {
    Vector transformed = {0};
    
    for (int m_r = 0; m_r < 3; m_r++) {
        
        // The sum of the multiplication
        // of the elements in the row
        float sum = 0;
        
        for (int m_c = 0; m_c < 3; m_c++) {
            
            // Each axis in the matrix is multipied
            // in each row is multiplied by the 
            // corresponding axis of the Vector
            sum += *m3Ind(matrix, m_r, m_c) * vec->arr[m_c];
        }
        // The current row and column of the matrix is the sum
        transformed.arr[m_r] = sum;
    }
    
    return transformed;
}
