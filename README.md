# Cube
A rotating 3D cube made using C++, SFML and matrix multiplication.
I used java, processing tutorials from TheCodingTrain and translated it to C++ and SFML.

## Links
---
**Java Tutorials with Processing:**
[3D Rendering with Rotation and Projection](https://www.youtube.com/watch?v=p4Iz0XJY-Qk)
[Matrix Multiplication for 3D Rendering](https://www.youtube.com/watch?v=tzsgS19RRc8)

**Wikipedia Page for Rotation Matrices:**
[Rotation Matrix](https://en.wikipedia.org/wiki/Rotation_matrix)

## WARNING
---
I don't know much about 3D graphics and this is a beguinner project. Therefore this are the issues:

- The code is a mess and not well documented
- The performance is garbage
- There are templates, double pointers and 2D arrays everywhere in the matrix and vector header files.

Tt just works, but it's not pretty or readable.

## How to run the code
---

You need a C++ toolchain with a compiler and linker, such as MSVC, g++, clang, etc. You also need either download and link the SFML binaries statically or dynamically. I got lazy and used my linux package manager, hence why my makefile doesn't set the include path for the SFML library.
