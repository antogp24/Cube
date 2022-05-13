# Cube
A rotating 3D cube made using C++, SFML and matrix multiplication.

- I used java, [processing](https://processing.org/) tutorials from [TheCodingTrain](https://www.youtube.com/c/TheCodingTrain) and translated them to C++ and [SFML](https://www.sfml-dev.org/).

## Links

**Software Rendered 3D in Java Tutorials with Processing:**
1. [Matrix Multiplication for 3D Rendering](https://www.youtube.com/watch?v=tzsgS19RRc8)
2. [3D Rendering with Rotation and Projection](https://www.youtube.com/watch?v=p4Iz0XJY-Qk)

**Wikipedia Page for Rotation Matrices:**
- [Rotation Matrix](https://en.wikipedia.org/wiki/Rotation_matrix)

## Structure

There is only one translation unit (.cpp file), and the code is divided into header files with utilities for matrices, vectors, shapes, etc.
A couple of them contain namespaces to separate the code, and there are functions that return 2D arrays `float matrix[r][c]`, in form of double pointers `float** toReturn`. This is probably why the code is slow, because there is a lot of jumping in memory due to the use of heap allocated 2D arrays, used to represent vectors and matrices. TheCodingTrain, who used java, didn't have this inconvenience of dealing with double pointers, template functions, and multiple overloads. I had multiple crashes because of accidentally accessing out of bound indeces in the arrays, and it was a nightmare. I am so done with this project, but I learned a lot of C++ from it.

## WARNING

I know almost nothing about 3D graphics and this is a beguinner project. Therefore this are the issues:

- The code is a mess and not well documented
- The performance is garbage
- There are templates, double pointers and 2D arrays everywhere in the matrix and vector header files.
- I didn't fully understood some of the algorithms and matrices. For example the __rotation matrices__.

It just works, but it's not pretty or readable.

## Dependencies


You need a C++ toolchain with a compiler and linker, such as MSVC, g++, clang, etc. You also need either download and link the SFML binaries statically or dynamically. I got lazy and used my linux package manager, hence why my makefile doesn't set the include path for the SFML library.
