#pragma once
#include "matrix.hpp"
#include "vector.hpp"
#include <cmath>

// ROW = HORIZONTAL
// COLUMN = VERTICAL

namespace matrices
{
    float distance = 2.0f;

    /// Useful Matrices
    /// ---------------------------------------------------------------------- ///
	Matrix projectionOrthographic(2, 3);
	Matrix rotationX(3, 3);
	Matrix rotationY(3, 3);
	Matrix rotationZ(3, 3);

	void init(float angleX, float angleY, float angleZ)
	{
		projectionOrthographic(0, 0) = 1; projectionOrthographic(0, 1) = 0; projectionOrthographic(0, 2) = 0;
		projectionOrthographic(1, 0) = 0; projectionOrthographic(1, 1) = 1; projectionOrthographic(1, 2) = 0;

		rotationX(0, 0) = 1.0f; rotationX(0, 1) = 0.0f; 				 rotationX(0, 2) = 0.0f;
		rotationX(1, 0) = 0.0f; rotationX(1, 1) = (float)(+cos(angleX)); rotationX(1, 2) = (float)(-sin(angleX));
		rotationX(2, 0) = 0.0f; rotationX(2, 1) = (float)(+sin(angleX)); rotationX(2, 2) = (float)(+cos(angleX));

		rotationY(0, 0) = (float)(+cos(angleY)); rotationY(0, 1) = 0.0f; rotationY(0, 2) = (float)(-sin(angleY));
		rotationY(1, 0) = 0.0f; 				 rotationY(1, 1) = 1.0f; rotationY(1, 2) = 0.0f;
		rotationY(2, 0) = (float)(+sin(angleY)); rotationY(2, 1) = 0.0f; rotationY(2, 2) = (float)(+cos(angleY));
		
		rotationZ(0, 0) = (float)(+cos(angleZ)); rotationZ(0, 1) = (float)(-sin(angleZ)); rotationZ(0, 2) = 0.0f;
		rotationZ(1, 0) = (float)(+sin(angleZ)); rotationZ(1, 1) = (float)(+cos(angleZ)); rotationZ(1, 2) = 0.0f;
		rotationZ(2, 0) = 0.0f; 				 rotationZ(2, 1) = 0.0f; 				  rotationZ(2, 2) = 1.0f;
	}
	/*
    float projectionOrthographic[2][3] =
    {
        {1, 0, 0},  // Non-square 2x3 matrix used for proyection.
        {0, 1, 0}   // It's purpose is to eliminate the Z axis.
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
	*/

    /// Matrix Logging
    /// ---------------------------------------------------------------------- ///

    void logMatrix(Matrix& matrix)
    {
		unsigned short rows = matrix.GetRows();
		unsigned short columns = matrix.GetColumns();
		switch(columns)
		{
			case 3:
				std::cout << "   " << rows << "x" << columns << std::endl;
				std::cout << "---------" << std::endl;
				for (int r = 0; r < rows; r++)
				{
					std::cout << "[ ";
					for (int c = 0; c < columns; c++)
					{
						std::cout << matrix(r, c) << " ";
					}
					std::cout << "]";
					std::cout << std::endl;
				}
				std::cout << "---------" << std::endl;
				break;
			case 1:
				std::cout << "  " << rows << "x" << columns << std::endl;
				std::cout << "------" << std::endl;
				for (int r = 0; r < rows; r++)
				{
					std::cout << "[ ";
					for (int c = 0; c < columns; c++)
					{
						std::cout << matrix(r, c) << " ";
					}
					std::cout << "]";
					std::cout << std::endl;
				}
				std::cout << "------" << std::endl;
				break;
		}
    }

    /// Matrix Multiplication Function
    /// ---------------------------------------------------------------------- ///

    Vector matmul(Matrix& matrix, Vector& vec)
    {
		unsigned short rA = matrix.GetRows();
		unsigned short cA = matrix.GetColumns();
		unsigned short rB = vec.dimensions;
        
		// Creating the 2D array in the heap
        // It has the rows of A (?) and the columns of B (1)
        Vector result(rA);

        for (int m_r = 0; m_r < rA; m_r++)
        {
            // The sum of the multiplication
            // of the elements in the row
            float sum = 0;
            for (int m_c = 0; m_c < cA; m_c++)
            {
                // Each axis in the matrix is multipied
                // in each row is multiplied by the 
                // corresponding axis of the Vector
                sum += matrix(m_r, m_c) * vec(m_c);
            }
            // The current row and column of the matrix is the sum
            result(m_r) = sum;
        }
        return result;
    }
}
