#pragma once
#include <iostream>

struct vec3
{
    float x, y, z;

    vec3(float p_x, float p_y, float p_z)
        :
        x(p_x),
        y(p_y),
        z(p_z)
    {
    }
    vec3(float** arr)
    {
        x = arr[0][0];
        y = arr[1][0];
        z = arr[2][0];
    }
    float** vec3ToFloat()
    {
        float** toReturn = new float* [3];
        for (int i = 0; i < 3; i++)
            toReturn[i] = new float[1];

        toReturn[0][0] = this->x;
        toReturn[1][0] = this->y;
        toReturn[2][0] = this->z;

        return toReturn;
    }
};

std::ostream& operator<<(std::ostream& stream, vec3& vertex3D)
{
    stream << "x: " << vertex3D.x << ", y: " << vertex3D.y << ", z: " << vertex3D.z;
    return stream;
}

namespace vectors
{
    // Original Function
    template<short dimensions>
    void logVector(float vector[dimensions][1])
    {
        std::cout << dimensions << "D vector" << std::endl;
        std::cout << "---------" << std::endl;
        for (int r = 0; r < dimensions; r++)
        {
            std::cout << "[ ";
            std::cout << vector[r][0] << " ";
            std::cout << "]";
            std::cout << std::endl;
        }
        std::cout << "---------" << std::endl;
    }
    // Overload for float**
    template<short dimensions>
    void logVector(float** vector)
    {
        std::cout << dimensions << "D vector" << std::endl;
        std::cout << "---------" << std::endl;
        for (int r = 0; r < dimensions; r++)
        {
            std::cout << "[ ";
            std::cout << vector[r][0] << " ";
            std::cout << "]";
            std::cout << std::endl;
        }
        std::cout << "---------" << std::endl;
    }
}