#pragma once
#include <assert.h>

struct Vector
{
    float x, y, z;
	unsigned dimensions;

    Vector(float p_x, float p_y, float p_z)
        :
        x(p_x),
        y(p_y),
        z(p_z),
		dimensions(3)
    {
    }
    
	Vector(float p_x, float p_y)
        :
        x(p_x),
        y(p_y),
        z(0),
		dimensions(2)
    {
    }
    
	Vector(unsigned p_dimensions)
        :
        x(0),
        y(0),
        z(0),
		dimensions(p_dimensions)
    {
    }
    
	float& operator()(unsigned index)
    {
        assert(index != 0 || index != 1 || index != 2);
        switch (index)
		{
			case 0:
				return x;
				break;
			case 1:
				return y;
				break;
			case 2:
				return z;
				break;
        }
        return x; // Never gonna happen because of the assertion!
    }

    // Referenced Copy Constructor
    Vector(const Vector& other)
        :
        x(other.x),
        y(other.y),
        z(other.z),
        dimensions(other.dimensions)
    {
    }

    // Referenced Assignment Operator
    void operator=(const Vector& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->dimensions = other.dimensions;
    }
};

namespace vectors
{
    // Original Function
    void logVector(Vector& v)
    {
        std::cout << v.dimensions << "D vector" << std::endl;
        std::cout << "---------" << std::endl;
        for (int r = 0; r < v.dimensions; r++)
        {
            std::cout << "[ ";
            std::cout << v(r) << " ";
            std::cout << "]";
            std::cout << std::endl;
        }
        std::cout << "---------" << std::endl;
    }
}
