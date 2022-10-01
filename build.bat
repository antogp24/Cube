@echo off
gcc -c src/*.c -m32 -I dependencies/raylib-static/include -I include && gcc *.o -o bin/cube.exe -L dependencies\raylib-static\lib -lraylib -lopengl32 -lgdi32 -lwinmm -lmingw32