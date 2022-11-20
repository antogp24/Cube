@echo off

pushd build
gcc -c ..\src\*.c -m32 -I ..\dependencies\raylib-static\include -I ..\include && gcc *.o -o cube.exe -L ..\dependencies\raylib-static\lib -lraylib -lopengl32 -lgdi32 -lwinmm -lmingw32
popd