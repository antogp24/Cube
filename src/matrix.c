#include "cube.h"

/// Useful Matrices
/// ---------------------------------------------------------------------- ///

void m3_update_rotation_matrices(RunData *rd, float dt) {
    float angleX = rd->rv->x * dt;
    float angleY = rd->rv->y * dt;
    float angleZ = rd->rv->z * dt;
    
    // Only updating the indeces that are not constant.
    
    m3_index(rd->Rx->arr, 1, 1) =  COS(angleX);
    m3_index(rd->Rx->arr, 1, 2) = -SIN(angleX);
    m3_index(rd->Rx->arr, 2, 1) =  SIN(angleX);
    m3_index(rd->Rx->arr, 2, 2) =  COS(angleX);
    
    m3_index(rd->Ry->arr, 0, 0) =  COS(angleY);
    m3_index(rd->Ry->arr, 0, 2) = -SIN(angleY);
    m3_index(rd->Ry->arr, 2, 0) =  SIN(angleY);
    m3_index(rd->Ry->arr, 2, 2) =  COS(angleY);
    
    m3_index(rd->Rz->arr, 0, 0) =  COS(angleZ);
    m3_index(rd->Rz->arr, 0, 1) = -SIN(angleZ); 
    m3_index(rd->Rz->arr, 1, 0) =  SIN(angleZ);
    m3_index(rd->Rz->arr, 1, 1) =  COS(angleZ); 
}

/// Matrix Logging
/// ---------------------------------------------------------------------- ///

void m3_log(Matrix3 *matrix) {
    
    printf("   3x3\n");
    printf("---------\n");
    
    for (int r = 0; r < 3; r++) {
        printf("[ ");
        for (int c = 0; c < 3; c++) {
            printf("%f ", m3_index(matrix, r, c));
        }
        printf("]");
        printf("\n");
    }
    printf("---------\n");
}

/// Matrix Multiplication Function
/// ---------------------------------------------------------------------- ///

Vector m3_vector_multiplication(Matrix3 *matrix, Vector *vec) {
    Vector transformed = {0};
    
    for (int m_r = 0; m_r < 3; m_r++) {
        
        // The sum of the multiplication
        // of the elements in the row
        float sum = 0;
        
        for (int m_c = 0; m_c < 3; m_c++) {
            
            // Each axis in the matrix is multipied
            // in each row is multiplied by the 
            // corresponding axis of the vector
            sum += m3_index(matrix->arr, m_r, m_c) * vec->arr[m_c];
        }
        // The current row and column of the matrix is the sum
        transformed.arr[m_r] = sum;
    }
    
    return transformed;
}
