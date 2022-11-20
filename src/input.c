#include "cube.h"
#include "cube_settings.h"

void input_manage_movement(RunData *rd, Vector *mv, Vector2 *origin_offset, Vector pnts[N_POINTS], Color *cube_color) {
    
    switch (GetKeyPressed()) {
        
        case KEY_X:
        {
            rd->rv->x *= -1;
        }
        case KEY_Y:
        {
            rd->rv->y *= -1;
        }
        case KEY_Z:
        {
            rd->rv->z *= -1;
        }
    }
    
    if (IsKeyDown(KEY_UP)) {
        mv->y -= SPEED;
    }
    if (IsKeyDown(KEY_DOWN)) {
        mv->y += SPEED;
    }
    if (IsKeyDown(KEY_LEFT)) {
        mv->x -= SPEED;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        mv->x += SPEED;
    }
    
    if (IsKeyDown(KEY_K)) {
        origin_offset->y -= SPEED;
    }
    if (IsKeyDown(KEY_J)) {
        origin_offset->y += SPEED;
    }
    if (IsKeyDown(KEY_D)) {
        origin_offset->x -= SPEED;
    }
    if (IsKeyDown(KEY_F)) {
        origin_offset->x += SPEED;
    }
    
    for (int i = 0; i < N_POINTS; i++) {
        pnts[i].x += mv->x;
        pnts[i].y += mv->y;
        pnts[i].z += mv->z;
    }
    
    // Reset the points
    if (IsKeyDown(KEY_TAB)) {
        vector_cube_points_reset(pnts);
        origin_offset->x = 0;
        origin_offset->y = 0;
    }
    
    Vector2 mPos = GetMousePosition();
    
    if (!debug_mouse_in_debug_area()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            *cube_color = RED;
            origin_offset->x = mPos.x - GetScreenWidth()/2;
            origin_offset->y = mPos.y - GetScreenHeight()/2;
        }
        else {
            *cube_color = WHITE;
        }
    }
}

RotType input_manage_rotations(RotType initial, Vector pnts[N_POINTS]) {
    RotType rt = initial;
    
    switch (GetKeyPressed()) {
        case KEY_SPACE: {
            
            switch (rt) {
                
                case ROTATION_TYPE_NONE:
                {
                    rt = ROTATION_TYPE_ALL;
                    vector_cube_points_reset(pnts);
                }break;
                
                case ROTATION_TYPE_ALL:
                {
                    rt = ROTATION_TYPE_X;
                    vector_cube_points_reset(pnts);
                }break;
                
                case ROTATION_TYPE_X:
                {
                    rt = ROTATION_TYPE_Y;
                    vector_cube_points_reset(pnts);
                }break;
                
                case ROTATION_TYPE_Y:
                {
                    rt = ROTATION_TYPE_Z;
                    vector_cube_points_reset(pnts);
                }break;
                
                case ROTATION_TYPE_Z:
                {
                    rt = ROTATION_TYPE_NONE;
                    vector_cube_points_reset(pnts);
                }break;
                
            }
        }break;
        
        case KEY_Q:
        {
            rt = ROTATION_TYPE_ALL;
            vector_cube_points_reset(pnts);
        }break;
        
        case KEY_W:
        {
            rt = ROTATION_TYPE_X;
            vector_cube_points_reset(pnts);
        }break;
        
        case KEY_E:
        {
            rt = ROTATION_TYPE_Y;
            vector_cube_points_reset(pnts);
        }break;
        
        case KEY_R:
        {
            rt = ROTATION_TYPE_Z;
            vector_cube_points_reset(pnts);
        }break;
        
        case KEY_T:
        {
            rt = ROTATION_TYPE_NONE;
            vector_cube_points_reset(pnts);
        }break;
        
    }
    return(rt);
}