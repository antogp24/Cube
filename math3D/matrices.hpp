#pragma once
#include <cmath>

// ROW = HORIZONTAL
// COLUMN = VERTICAL

namespace matrices
{
    float angleX = 0.00015f; // speed of rotation
    float angleY = -0.00095f; // speed of rotation
    float angleZ = 0.00020f; // speed of rotation
    float distance = 2.0f;

    /// Useful Matrices
    /// ---------------------------------------------------------------------- ///
    float projectionOrthographic[2][3] =
    {
        {1, 0, 0},  // Non-square 2x3 matrix used for proyection.
        {0, 1, 0}   // It's purpose is to eliminate the Z axis.
    };

    float** projectionPerspective(float vz)
    {
        float** p = new float* [2];
        for (int i = 0; i < 2; i++)
            p[i] = new float[3];

        // Column 1
        p[0][0] = 1/(distance - vz); // row 1
        p[1][0] = 0; // row 2

        // Column 2
        p[0][1] = 0; // row 1
        p[1][1] = 1/(distance - vz); // row 2

        // Column 3
        p[0][2] = 0; // row 1
        p[1][2] = 0; // row 2

        /*
        {1/(distance - z), 0, 0}
        {0, 1/(distance - z), 0}
        */
        return p;
    };

    float rotationX[3][3] =
    {
        {1.0f,  0.0f,                 0.0f               },
        {0.0f, (float)(+cos(angleX)), (float)(-sin(angleX))},
        {0.0f, (float)(+sin(angleX)), (float)(+cos(angleX))}
    };

    float rotationY[3][3] =
    {
        {(float)(+cos(angleY)), 0.0f, (float)(-sin(angleY))},
        { 0.0f,                 1.0f,                 0.0f},
        {(float)(+sin(angleY)), 0.0f, (float)(+cos(angleY))}
    };

    float rotationZ[3][3] =
    {
        {(float)(+cos(angleZ)), (float)(-sin(angleZ)), 0.0f},
        {(float)(+sin(angleZ)), (float)(+cos(angleZ)), 0.0f},
        { 0.0f,                 0.0f,                1.0f}
    };

    /// Matrix Logging
    /// ---------------------------------------------------------------------- ///

    // Original Function
    template<short rows, short columns>
    void logMatrix(float matrix[rows][columns])
    {
        if (columns == 3)
        {
            std::cout << "   " << rows << "x" << columns << std::endl;
            std::cout << "---------" << std::endl;
            for (int r = 0; r < rows; r++)
            {
                std::cout << "[ ";
                for (int c = 0; c < columns; c++)
                {
                    std::cout << matrix[r][c] << " ";
                }
                std::cout << "]";
                std::cout << std::endl;
            }
            std::cout << "---------" << std::endl;
        }
        else if (columns == 1)
        {
            std::cout << "  " << rows << "x" << columns << std::endl;
            std::cout << "------" << std::endl;
            for (int r = 0; r < rows; r++)
            {
                std::cout << "[ ";
                for (int c = 0; c < columns; c++)
                {
                    std::cout << matrix[r][c] << " ";
                }
                std::cout << "]";
                std::cout << std::endl;
            }
            std::cout << "------" << std::endl;
        }
    }

    // Overload for float**
    template<short rows, short columns>
    void logMatrix(float** matrix)
    {
        if (columns == 3)
        {
            std::cout << "   " << rows << "x" << columns << std::endl;
            std::cout << "---------" << std::endl;
            for (int r = 0; r < rows; r++)
            {
                std::cout << "[ ";
                for (int c = 0; c < columns; c++)
                {
                    std::cout << matrix[r][c] << " ";
                }
                std::cout << "]";
                std::cout << std::endl;
            }
            std::cout << "---------" << std::endl;
        }
        else if (columns == 1)
        {
            std::cout << "  " << rows << "x" << columns << std::endl;
            std::cout << "------" << std::endl;
            for (int r = 0; r < rows; r++)
            {
                std::cout << "[ ";
                for (int c = 0; c < columns; c++)
                {
                    std::cout << matrix[r][c] << " ";
                }
                std::cout << "]";
                std::cout << std::endl;
            }
            std::cout << "------" << std::endl;
        }
    }

    /// Matrix Multiplication Function
    /// ---------------------------------------------------------------------- ///

    // Original Function
    template<short rA, short cA, short rB, short cB>
    float** matmul(float matrix[rA][cA], float vector[rB][cB])
    {
        // Creating the 2D array in the heap
        // It has the rows of A and the columns of B
        float** result = new float*[rA];
        for (int i = 0; i < rA; i++)
            result[i] = new float[cB];

        for (int m_r = 0; m_r < rA; m_r++)
        {
            for (int v_c = 0; v_c < cB; v_c++)
            {
                // The sum of the multiplication
                // of the elements in the row
                float sum = 0;
                for (int m_c = 0; m_c < cA; m_c++)
                {
                    // Each axis in the matrix is multipied
                    // in each row is multiplied by the 
                    // corresponding axis of the vector
                    sum += matrix[m_r][m_c] * vector[m_c][v_c];
                }
                // The current row and column of the matrix is the sum
                result[m_r][v_c] = sum;
            }
        }
        return result;
    }

    // Double Pointer Vector Overload
    template<short rA, short cA, short rB, short cB>
    float** matmul(float matrix[rA][cA], float** vector)
    {
        // Creating the 2D array in the heap
        // It has the rows of A and the columns of B
        float** result = new float*[rA];
        for (int i = 0; i < rA; i++)
            result[i] = new float[cB];

        for (int m_r = 0; m_r < rA; m_r++)
        {
            for (int v_c = 0; v_c < cB; v_c++)
            {
                // The sum of the multiplication
                // of the elements in the row
                float sum = 0;
                for (int m_c = 0; m_c < cA; m_c++)
                {
                    // Each axis in the matrix is multipied
                    // in each row is multiplied by the 
                    // corresponding axis of the vector
                    sum += matrix[m_r][m_c] * vector[m_c][v_c];
                }
                // The current row and column of the matrix is the sum
                result[m_r][v_c] = sum;
            }
        }
        return result;
    }
    // Double Pointer Matrix and Vector Overload
    template<short rA, short cA, short rB, short cB>
    float** matmul(float** matrix, float** vector)
    {
        // Creating the 2D array in the heap
        // It has the rows of A and the columns of B
        float** result = new float*[rA];
        for (int i = 0; i < rA; i++)
            result[i] = new float[cB];

        for (int m_r = 0; m_r < rA; m_r++)
        {
            for (int v_c = 0; v_c < cB; v_c++)
            {
                // The sum of the multiplication
                // of the elements in the row
                float sum = 0;
                for (int m_c = 0; m_c < cA; m_c++)
                {
                    // Each axis in the matrix is multipied
                    // in each row is multiplied by the 
                    // corresponding axis of the vector
                    sum += matrix[m_r][m_c] * vector[m_c][v_c];
                }
                // The current row and column of the matrix is the sum
                result[m_r][v_c] = sum;
            }
        }
        return result;
    }
}