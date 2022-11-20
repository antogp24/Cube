#include "cube.h"
#include "cube_settings.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIN_X, WIN_Y, "Rotating Cube");
    SetTargetFPS(60);
    RotType rt = ROTATION_TYPE_ALL;
    RunData rd = {0};
    Vector  rv = { aX, aY, aZ };
    Vector2 origin = { WIN_X/2, WIN_Y/2 };
    Vector2 origin_offset = {0};
    Color cube_color = WHITE;
    
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
    
    rd.pnts = (Vector *)points;
    rd.rv =   (Vector *)&rv;
    rd.Rx =   (Matrix3*)&Rx;
    rd.Ry =   (Matrix3*)&Ry;
    rd.Rz =   (Matrix3*)&Rz;
    
    // Game Loop
    //~
    while (!WindowShouldClose()) {
        
        // Logic (Every Frame)
        //~
        
        float dt = GetFrameTime();
        m3_update_rotation_matrices(&rd, dt);
        
        origin.x = GetScreenWidth()/2 + origin_offset.x;
        origin.y = GetScreenHeight()/2 + origin_offset.y;
        
        Vector movement = {0};
        rt = input_manage_rotations(rt, points);
        input_manage_movement(&rd, &movement, &origin_offset, points, &cube_color);
        
        for (int i = 0; i < N_POINTS; i++) {
            transform_cube_points(&rd, rt, i);
        }
        
        // Rendering
        //~
        
        ClearBackground(BLACK);
        BeginDrawing();
        
        // Drawing the points
        for (int i = 0; i < N_POINTS; i++) {
            shapes_point(points[i].x + origin.x, points[i].y + origin.y, cube_color);
        }
        
        // Algorithm to draw the edges (order is set for this)
        for (int i = 0; i < 4; i++) {
            // FACE #1
            shapes_connect(i + 0, ((i + 1) % 4) + 0, points, origin.x, origin.y, cube_color);
            // FACE #2
            shapes_connect(i + 4, ((i + 1) % 4) + 4, points, origin.x, origin.y, cube_color);
            // BETWEEN FACES
            shapes_connect(i + 0, i + 4,             points, origin.x, origin.y, cube_color);
        }
        
        debug_all(rt, &rd, &origin); // Only gets called if DEBUG_ALL is defined in settings
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}

