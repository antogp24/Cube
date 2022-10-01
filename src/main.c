#include <stdio.h>
#include <raylib.h>
#include "math3D.h"
#include "debug.h"
#include "input.h"
#include "rotate.h"
#include "settings.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIN_X, WIN_Y, "Rotating Cube");
    SetTargetFPS(60);
    RotType rt = ROT_ALL;
    
    Vector points[N_POINTS] = {
        // First Face
        {-SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH}, // Top Left      #0
        {+SIDES_LENGTH, -SIDES_LENGTH, -SIDES_LENGTH}, // Top Right     #1
        {+SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH}, // Bottom Right  #2
        {-SIDES_LENGTH, +SIDES_LENGTH, -SIDES_LENGTH}, // Bottom Left   #3
        // Second Face
        {-SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH}, // Top Left      #4
        {+SIDES_LENGTH, -SIDES_LENGTH, +SIDES_LENGTH}, // Top Right     #5
        {+SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH}, // Bottom Right  #6
        {-SIDES_LENGTH, +SIDES_LENGTH, +SIDES_LENGTH}  // Bottom Left   #7
    };
    
    Matrix3 Rx = {
        1,       0,        0,        
        0, COS(aX), -SIN(aX),
        0, SIN(aX),  COS(aX),
    };
    
    Matrix3 Ry = {
        COS(aY), 0, -SIN(aY),        
        0,       1,        0,
        SIN(aY), 0,  COS(aY),
    };
    
    Matrix3 Rz = {
        COS(aZ), -SIN(aZ), 0,        
        SIN(aZ),  COS(aZ), 0,
        0,        0,       1,
    };
    
    // Game Loop
    // ------------------------------------------------------------------------- //
    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {
        
        float dt = GetFrameTime();
        matrices_update(&rv, &Rx, &Ry, &Rz, dt);
        
        // Logic (Every Frame)
        // ------------------------------------------------------------------------- //
        
        Vector movement = { 0, 0, 0 };
        rt = rotateManage(rt, points);
        Input(&rv, &movement, points);
        
        Vector transformed[N_POINTS];
        
        for (int i = 0; i < N_POINTS; i++) {
            transform_cube_points(&Rx, &Ry, &Rz, rt, points, i);
        }
        
        // Rendering
        // ------------------------------------------------------------------------- //
        
        ClearBackground(BLACK);
        BeginDrawing();
        
        // Drawing the points
        for (int i = 0; i < N_POINTS; i++) {
            shapes_point(points[i].x + origin.x, points[i].y + origin.y);
        }
        
        // Algorithm to draw the edges
        for (int i = 0; i < 4; i++) {
            // FACE #1
            shapes_connect(i, (i + 1) % 4,           points, origin.x, origin.y);
            // FACE #2
            shapes_connect(i + 4, ((i + 1) % 4) + 4, points, origin.x, origin.y);
            // BETWEEN FACES
            shapes_connect(i, i + 4,                 points, origin.x, origin.y);
        }
        
        DebugAll(rt); // Only gets called if DEBUG_ALL is defined in settings
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

