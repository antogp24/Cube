#ifndef DEBUG_H
#define DEBUG_H

#include <raylib.h>
#include "settings.h"

#define DBG_FNT_S 10

// -------------------------------------------------------------------------------------------------- //

void debugFPS(void) {
    
    const int FPS = GetFPS();
    if (FPS <= 30) {
        DrawText(TextFormat("FPS = %d", GetFPS()), 10, 15, DBG_FNT_S, RED);
    }
    else if (FPS >= 30 && FPS < 50) {
        DrawText(TextFormat("FPS = %d", GetFPS()), 10, 15, DBG_FNT_S, YELLOW);
    }
    else if (FPS >= 50) {
        DrawText(TextFormat("FPS = %d", GetFPS()), 10, 15, DBG_FNT_S, GREEN);
    }
}

// -------------------------------------------------------------------------------------------------- //

void debug_rv(void) {
    
    if (rv.x > 0) {
        DrawText(TextFormat("rv.x = +%.2f", rv.x), 10, 15+15*1, DBG_FNT_S, WHITE);
    } else {
        DrawText(TextFormat("rv.x = %.2f", rv.x), 10, 15+15*1, DBG_FNT_S, WHITE);
    }
    if (rv.y > 0) {
        DrawText(TextFormat("rv.y = +%.2f", rv.y), 10, 15+15*2, DBG_FNT_S, WHITE);
    } else {
        DrawText(TextFormat("rv.y = %.2f", rv.y), 10, 15+15*2, DBG_FNT_S, WHITE);
    }
    if (rv.z > 0) {
        DrawText(TextFormat("rv.z = +%.2f", rv.z), 10, 15+15*3, DBG_FNT_S, WHITE);
    } else {
        DrawText(TextFormat("rv.z = %.2f", rv.z), 10, 15+15*3, DBG_FNT_S, WHITE);
    }
}

// -------------------------------------------------------------------------------------------------- //
const char *rotation_txt;

void debugRotType(RotType rt) {
    
    switch (rt) {
        
        case ROT_NONE: {
            rotation_txt = "Rotating: NONE";
        }break;
        
        case ROT_ALL: {
            rotation_txt = "Rotating: XYZ";
        }break;
        
        case ROT_X: {
            rotation_txt = "Rotating: ONLY_X";
        }break;
        
        case ROT_Y: {
            rotation_txt = "Rotating: ONLY_Y";
        }break;
        
        case ROT_Z: {
            rotation_txt = "Rotating: ONLY_Z";
        }break;
    }
    // In all possible cases there is a rotation_txt
    DrawText(rotation_txt, WIN_X/2 -MeasureText(rotation_txt, 20)/2, WIN_Y - 40, 20, WHITE);
}


// -------------------------------------------------------------------------------------------------- //

void drawButton(int x, int y, size_t width, size_t height, 
                Color fill, Color border, size_t border_width) {
    
    DrawRectangle(x, y, width, height, fill);
    for (int i = 0; i <= border_width; i++) {
        DrawRectangleLines(x+i, y+i, width-i*2, height-i*2, border);
    }
}

void drawButtonPositive(int x, int y, size_t width, size_t height, size_t fnt) {
    
    drawButton(x, y, width, height, GREEN, BLUE, 1);
    DrawText("+", x+width/2-MeasureText("+", fnt)/2, y+height/2-DBG_FNT_S/2, fnt, BLACK);
}

void drawButtonNegative(int x, int y, size_t width, size_t height, size_t fnt) {
    
    drawButton(x, y, width, height, RED, BLUE, 1);
    DrawText("-", x+width/2-MeasureText("-", fnt)/2, y+height/2-DBG_FNT_S/2, fnt, BLACK);
}

void drawContrastingButtons(int x, int y, size_t width, size_t height, size_t fnt, const char *axis) {
    
    drawButtonPositive(x, y, width, height, fnt);
    drawButtonNegative(x+width-2, y, width, height, fnt);
    DrawText(axis, x+width*2+MeasureText(axis, fnt), y+height/2-fnt/2, fnt, WHITE);
}

// -------------------------------------------------------------------------------------------------- //

#define BTNS_W 40
#define BTNS_H BTNS_W/2

Rectangle btnsBounds[6] = {
    (Rectangle){WIN_X/2-BTNS_W,        BTNS_W*0-0, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W+BTNS_W, BTNS_W*0-0, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W,        BTNS_H*1-2, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W+BTNS_W, BTNS_H*1-2, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W,        BTNS_H*2-4, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W+BTNS_W, BTNS_H*2-4, BTNS_W, BTNS_H}
};

void debugClickableChange_rv() {
    
    drawContrastingButtons(WIN_X/2-BTNS_W, BTNS_W*0-0, BTNS_W, BTNS_H, DBG_FNT_S, "X");
    drawContrastingButtons(WIN_X/2-BTNS_W, BTNS_H*1-2, BTNS_W, BTNS_H, DBG_FNT_S, "Y");
    drawContrastingButtons(WIN_X/2-BTNS_W, BTNS_H*2-4, BTNS_W, BTNS_H, DBG_FNT_S, "Z");
    
#if 0 // To show the colliders
    Color color;
    for (int i = 0; i < 6; i++) {
        if (i == 0) color = MAGENTA;
        if (i == 1) color = RED;
        if (i == 2) color = GREEN;
        if (i == 3) color = PURPLE;
        if (i == 4) color = ORANGE;
        if (i == 5) color = YELLOW;
        DrawRectangleRec(btnsBounds[i], color);
    }
#endif
    Vector2 mPos = GetMousePosition();
    float btnScalar = 0.1f;
    
    if (CheckCollisionPointRec(mPos, btnsBounds[0])) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            rv.x += btnScalar;
    }
    if (CheckCollisionPointRec(mPos, btnsBounds[1])) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            rv.x -= btnScalar;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[2])) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            rv.y += btnScalar;
    }
    if (CheckCollisionPointRec(mPos, btnsBounds[3])) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            rv.y -= btnScalar;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[4])) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            rv.z += btnScalar;
    }
    if (CheckCollisionPointRec(mPos, btnsBounds[5])) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            rv.z -= btnScalar;
    }
}

// -------------------------------------------------------------------------------------------------- //

void debugOrigin(void) {
    DrawCircle(origin.x, origin.y, 3, ORANGE);
}

// -------------------------------------------------------------------------------------------------- //

void DebugAll(RotType rt) {
#if defined(DEBUG_ALL)
    debugFPS();
    debugClickableChange_rv();
    debug_rv();
    debugRotType(rt);
    debugOrigin();
    //DrawRectangle(SPEED, SPEED, SIDES_LENGTH*2, SIDES_LENGTH*2, WHITE); // for comparison
#endif //if defined(DEBUG_ALL)
}

// -------------------------------------------------------------------------------------------------- //

#endif //DEBUG_H
