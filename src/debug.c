#include <raylib.h>
#include "cube_settings.h"

#define DEBUG_FONT_SIZE 10

//~

void debug_FPS(void) {
    
    const int FPS = GetFPS();
    if (FPS <= 30) {
        DrawText(TextFormat("FPS = %d", GetFPS()), 10, 15, DEBUG_FONT_SIZE, RED);
    }
    else if (FPS >= 30 && FPS < 50) {
        DrawText(TextFormat("FPS = %d", GetFPS()), 10, 15, DEBUG_FONT_SIZE, YELLOW);
    }
    else if (FPS >= 50) {
        DrawText(TextFormat("FPS = %d", GetFPS()), 10, 15, DEBUG_FONT_SIZE, GREEN);
    }
}

//~

void debug_rotation_velocity(RunData *rd) {
    
    if (rd->rv->x > 0) {
        DrawText(TextFormat("rv.x = +%.2f", rd->rv->x), 10, 15+15*1, DEBUG_FONT_SIZE, WHITE);
    } else {
        DrawText(TextFormat("rv.x = %.2f", rd->rv->x), 10, 15+15*1, DEBUG_FONT_SIZE, WHITE);
    }
    if (rd->rv->y > 0) {
        DrawText(TextFormat("rv.y = +%.2f", rd->rv->y), 10, 15+15*2, DEBUG_FONT_SIZE, WHITE);
    } else {
        DrawText(TextFormat("rv.y = %.2f", rd->rv->y), 10, 15+15*2, DEBUG_FONT_SIZE, WHITE);
    }
    if (rd->rv->z > 0) {
        DrawText(TextFormat("rv.z = +%.2f", rd->rv->z), 10, 15+15*3, DEBUG_FONT_SIZE, WHITE);
    } else {
        DrawText(TextFormat("rv.z = %.2f", rd->rv->z), 10, 15+15*3, DEBUG_FONT_SIZE, WHITE);
    }
}

//~
const char *rotation_txt;

void debug_rotation_type(RotType rt) {
    
    switch (rt) {
        
        case ROTATION_TYPE_NONE:
        {
            rotation_txt = "Rotating: NONE";
        }break;
        
        case ROTATION_TYPE_ALL:
        {
            rotation_txt = "Rotating: XYZ";
        }break;
        
        case ROTATION_TYPE_X:
        {
            rotation_txt = "Rotating: ONLY_X";
        }break;
        
        case ROTATION_TYPE_Y:
        {
            rotation_txt = "Rotating: ONLY_Y";
        }break;
        
        case ROTATION_TYPE_Z:
        {
            rotation_txt = "Rotating: ONLY_Z";
        }break;
    }
    
    DrawText(rotation_txt, GetScreenWidth()/2 -MeasureText(rotation_txt, 20)/2, GetScreenHeight() - 40, 20, WHITE);
}


//~

#define BTNS_W 40
#define BTNS_H BTNS_W/2

void debug_button_draw(int x, int y, size_t width, size_t height, 
                       Color fill, Color border, size_t border_width) {
    
    DrawRectangle(x, y, width, height, fill);
    for (int i = 0; i <= border_width; i++) {
        DrawRectangleLines(x+i, y+i, width-i*2, height-i*2, border);
    }
}

void debug_button_positive_draw(int x, int y, size_t width, size_t height, size_t fnt, Color fill) {
    
    debug_button_draw(x, y, width, height, fill, BLUE, 1);
    DrawText("+", x+width/2-MeasureText("+", fnt)/2, y+height/2-DEBUG_FONT_SIZE/2, fnt, BLACK);
}

void debug_button_negative_draw(int x, int y, size_t width, size_t height, size_t fnt, Color fill) {
    
    debug_button_draw(x, y, width, height, fill, BLUE, 1);
    DrawText("-", x+width/2-MeasureText("-", fnt)/2, y+height/2-DEBUG_FONT_SIZE/2, fnt, BLACK);
}

void debug_button_contrasting_draw(int x, int y, size_t width, size_t height, size_t fnt, const char *axis, Color fill_positive, Color fill_negative) {
    
    debug_button_positive_draw(x, y, width, height, fnt, fill_positive);
    debug_button_negative_draw(x+width-2, y, width, height, fnt, fill_negative);
    DrawText(axis, x+width*2+MeasureText(axis, fnt), y+height/2-fnt/2, fnt, WHITE);
    DrawText(axis, x-1-MeasureText(axis, fnt)*2, y+height/2-fnt/2, fnt, WHITE);
}

//~

#define DEBUG_RESET_BUTTON_DIMENSIONS 2.8f*BTNS_H
#define DEBUG_RESET_BUTTON_TEXT_SIZE  DEBUG_FONT_SIZE
#define DEBUG_LIGHT_YELLOW            CLITERAL(Color){ 241, 216, 75, 255 }
#define DEBUG_DARK_BLUE               CLITERAL(Color){ 5, 0, 50, 255 }

void debug_rotation_velocity_reset_default(RunData *rd) {
    const char *reset_text = "reset";
    Color fill, border, reset_text_color;
    
    Rectangle collider = {
        WIN_X/2-BTNS_W-DEBUG_RESET_BUTTON_DIMENSIONS-20,
        0,
        DEBUG_RESET_BUTTON_DIMENSIONS,
        DEBUG_RESET_BUTTON_DIMENSIONS
    };
    collider.x = GetScreenWidth()/2-BTNS_W-DEBUG_RESET_BUTTON_DIMENSIONS-20;
    bool mouse_in_reset_button = CheckCollisionPointRec(GetMousePosition(), collider);
    
    if (mouse_in_reset_button){
        fill = DEBUG_DARK_BLUE;
        border = DEBUG_LIGHT_YELLOW;
        reset_text_color = DEBUG_LIGHT_YELLOW;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->x = aX;
            rd->rv->y = aY;
            rd->rv->z = aZ;
        }
    }
    else {
        fill = LIGHTGRAY;
        border= BLUE;
        reset_text_color = BLACK;
    }
    
    debug_button_draw(collider.x,
                      collider.y,
                      collider.width,
                      collider.height,
                      fill,
                      border,
                      2);
    
    DrawText(reset_text,
             collider.x + MeasureText(reset_text, DEBUG_RESET_BUTTON_TEXT_SIZE)/2,
             collider.y + collider.height/2 - MeasureText("r", DEBUG_RESET_BUTTON_TEXT_SIZE)/2,
             DEBUG_RESET_BUTTON_TEXT_SIZE,
             reset_text_color);
}

//~

#define debug_is_number_pressed(key) (key >= 48 && key <= 57)
#define DEBUG_TEXT_BOX_FONT_SIZE 5.6*DEBUG_FONT_SIZE
#define DEBUG_TEXT_BOX_OFFSET_X 4.5
#define DEBUG_TEXT_BOX_OFFSET_Y 4.5

void debug_text_box_write(TextBox *text_box) {
    if (CheckCollisionPointRec(GetMousePosition(), text_box->collider)) {
        text_box->mouse_on_text = true;
    }
    else {
        text_box->mouse_on_text = false;
    }
    
    if (text_box->mouse_on_text) {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        
        int key = GetCharPressed();
        
        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            if (debug_is_number_pressed(key) && (text_box->letter_count < MAX_INPUT_CHARS)) {
                text_box->name[text_box->letter_count] = (char)key;
                text_box->name[text_box->letter_count+1] = '\0';
                text_box->letter_count++;
            }
            
            key = GetCharPressed();  // Check next character in the queue
        }
        
        if (IsKeyPressed(KEY_BACKSPACE)) {
            text_box->letter_count--;
            if (text_box->letter_count < 0) {
                text_box->letter_count = 0;
            }
            text_box->name[text_box->letter_count] = '\0';
        }
        else if (IsKeyPressed(KEY_LEFT_CONTROL)) {
            text_box->letter_count = 0;
            text_box->name[0] = '\0';
            text_box->collider.width = DEBUG_TEXT_BOX_FONT_SIZE;
        }
        text_box->frames_counter++;
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        text_box->frames_counter = 0;
    }
}

void debug_text_box_draw(TextBox *text_box) {
    if (text_box->letter_count > 1) {
        text_box->collider.width = MeasureText(text_box->name, DEBUG_TEXT_BOX_FONT_SIZE) + DEBUG_TEXT_BOX_OFFSET_X*2;
    }
    else {
        text_box->collider.width = DEBUG_TEXT_BOX_FONT_SIZE;
    }
    
    DrawRectangleRec(text_box->collider, LIGHTGRAY);
    Color text_box_border_color;
    
    if (text_box->mouse_on_text) {
        text_box_border_color = RED;
    }
    else {
        text_box_border_color = BLUE;
    }
    
    debug_button_draw((int)text_box->collider.x,
                      (int)text_box->collider.y,
                      (int)text_box->collider.width,
                      (int)text_box->collider.height,
                      LIGHTGRAY,
                      text_box_border_color,
                      2);
    
    if (text_box->letter_count <= 1 && TextToInteger(text_box->name) != 1) {
        DrawText(text_box->name,
                 (int)text_box->collider.x + MeasureText(text_box->name, DEBUG_TEXT_BOX_FONT_SIZE)/2,
                 (int)text_box->collider.y + DEBUG_TEXT_BOX_OFFSET_Y,
                 DEBUG_TEXT_BOX_FONT_SIZE,
                 BLACK);
    }
    else if (text_box->letter_count <= 1 && TextToInteger(text_box->name) == 1) {
        DrawText(text_box->name,
                 (int)text_box->collider.x + DEBUG_TEXT_BOX_OFFSET_X/2 + DEBUG_TEXT_BOX_FONT_SIZE/3,
                 (int)text_box->collider.y + DEBUG_TEXT_BOX_OFFSET_Y,
                 DEBUG_TEXT_BOX_FONT_SIZE,
                 BLACK);
    }
    else {
        DrawText(text_box->name,
                 (int)text_box->collider.x + DEBUG_TEXT_BOX_OFFSET_X,
                 (int)text_box->collider.y + DEBUG_TEXT_BOX_OFFSET_Y,
                 DEBUG_TEXT_BOX_FONT_SIZE,
                 BLACK);
    }
    
    if (text_box->mouse_on_text) {
        
        if (text_box->letter_count < MAX_INPUT_CHARS) {
            
#define DEBUG_TEXT_BOX_NAME_EMPTY TextIsEqual(text_box->name, "")
            // Draw blinking underscore
            if (((text_box->frames_counter/20)%2) == 0) {
                if (!DEBUG_TEXT_BOX_NAME_EMPTY && TextToInteger(text_box->name) == 1) {
                    DrawText("_",
                             (int)text_box->collider.x + DEBUG_TEXT_BOX_OFFSET_X + MeasureText(text_box->name, DEBUG_TEXT_BOX_FONT_SIZE),
                             (int)text_box->collider.y + DEBUG_TEXT_BOX_OFFSET_Y,
                             DEBUG_TEXT_BOX_FONT_SIZE,
                             MAROON);
                }
                if (!DEBUG_TEXT_BOX_NAME_EMPTY && TextToInteger(text_box->name) > 1) {
                    DrawText("_",
                             (int)text_box->collider.x + DEBUG_TEXT_BOX_OFFSET_X*3 + MeasureText(text_box->name, DEBUG_TEXT_BOX_FONT_SIZE),
                             (int)text_box->collider.y + DEBUG_TEXT_BOX_OFFSET_Y,
                             DEBUG_TEXT_BOX_FONT_SIZE,
                             MAROON);
                }
                if (DEBUG_TEXT_BOX_NAME_EMPTY) {
                    DrawText("_",
                             (int)text_box->collider.x + DEBUG_TEXT_BOX_OFFSET_X + DEBUG_TEXT_BOX_FONT_SIZE/5,
                             (int)text_box->collider.y + DEBUG_TEXT_BOX_OFFSET_Y,
                             DEBUG_TEXT_BOX_FONT_SIZE,
                             MAROON);
                }
            }
        }
    }
}

//~

Rectangle btnsBounds[6] = {
    (Rectangle){WIN_X/2-BTNS_W,        BTNS_W*0-0, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W+BTNS_W, BTNS_W*0-0, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W,        BTNS_H*1-2, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W+BTNS_W, BTNS_H*1-2, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W,        BTNS_H*2-4, BTNS_W, BTNS_H},
    (Rectangle){WIN_X/2-BTNS_W+BTNS_W, BTNS_H*2-4, BTNS_W, BTNS_H}
};

#define DIM_GREEN CLITERAL(Color){ 5, 238, 58, 225 }
#define DIM_RED   CLITERAL(Color){ 240, 51, 65, 225 }

void debug_rotation_velocity_clickable_change(RunData *rd, float button_scalar) {
    
    btnsBounds[0].x = GetScreenWidth()/2-BTNS_W;
    btnsBounds[1].x = GetScreenWidth()/2-BTNS_W+BTNS_W;
    btnsBounds[2].x = GetScreenWidth()/2-BTNS_W;
    btnsBounds[3].x = GetScreenWidth()/2-BTNS_W+BTNS_W;
    btnsBounds[4].x = GetScreenWidth()/2-BTNS_W;
    btnsBounds[5].x = GetScreenWidth()/2-BTNS_W+BTNS_W;
    
    Color fill_positive_1 ,fill_negative_1, fill_positive_2, fill_negative_2, fill_positive_3, fill_negative_3;
    
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
    
    if (CheckCollisionPointRec(mPos, btnsBounds[0])) {
        fill_positive_1 = GREEN;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->x += button_scalar;
        }
    }
    else {
        fill_positive_1 = DIM_GREEN;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[1])) {
        fill_negative_1 = RED;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->x -= button_scalar;
        }
    }
    else {
        fill_negative_1 = DIM_RED;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[2])) {
        fill_positive_2 = GREEN;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->y += button_scalar;
        }
    }
    else {
        fill_positive_2 = DIM_GREEN;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[3])) {
        fill_negative_2 = RED;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->y -= button_scalar;
        }
    }
    else {
        fill_negative_2 = DIM_RED;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[4])) {
        fill_positive_3 = GREEN;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->z += button_scalar;
        }
    }
    else {
        fill_positive_3 = DIM_GREEN;
    }
    
    if (CheckCollisionPointRec(mPos, btnsBounds[5])) {
        fill_negative_3 = RED;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            rd->rv->z -= button_scalar;
        }
    }
    else {
        fill_negative_3 = DIM_RED;
    }
    
    debug_button_contrasting_draw(GetScreenWidth()/2-BTNS_W,
                                  BTNS_H*0-0,
                                  BTNS_W,
                                  BTNS_H,
                                  DEBUG_FONT_SIZE,
                                  "X",
                                  fill_positive_1,
                                  fill_negative_1);
    debug_button_contrasting_draw(GetScreenWidth()/2-BTNS_W,
                                  BTNS_H*1-2,
                                  BTNS_W,
                                  BTNS_H,
                                  DEBUG_FONT_SIZE,
                                  "Y",
                                  fill_positive_2,
                                  fill_negative_2);
    debug_button_contrasting_draw(GetScreenWidth()/2-BTNS_W,
                                  BTNS_H*2-4,
                                  BTNS_W,
                                  BTNS_H,
                                  DEBUG_FONT_SIZE,
                                  "Z",
                                  fill_positive_3,
                                  fill_negative_3);
}

//~

bool debug_mouse_in_debug_area() {
    Rectangle debug_area = {
        WIN_X/2-BTNS_W-DEBUG_RESET_BUTTON_DIMENSIONS-20 -25,
        -10,
        DEBUG_RESET_BUTTON_DIMENSIONS+20+BTNS_W*2+20+MeasureText("9", DEBUG_TEXT_BOX_FONT_SIZE)*MAX_INPUT_CHARS+DEBUG_TEXT_BOX_OFFSET_X*2 +25*3,
        DEBUG_RESET_BUTTON_DIMENSIONS +10+25
    };
    debug_area.x = GetScreenWidth()/2-BTNS_W-DEBUG_RESET_BUTTON_DIMENSIONS-20 -25;
    
    return CheckCollisionPointRec(GetMousePosition(), debug_area);
}

//~

void debug_origin(Vector2 *origin) {
    DrawCircle(origin->x, origin->y, 3, ORANGE);
}

//~

void debug_all(RotType rt, RunData *rd, Vector2 *origin) {
#if defined(DEBUG_ALL)
    
    float text_box_number;
    local_persist TextBox text_box = {
        (Rectangle){ WIN_X/2+BTNS_W+20, 0, DEBUG_TEXT_BOX_FONT_SIZE, DEBUG_TEXT_BOX_FONT_SIZE },
        "1\0", // name
        1,     // letter count
        0,     // frame counter
        false  // mouse on text
    };
    
    text_box.collider.x = GetScreenWidth()/2+BTNS_W+20;
    text_box_number = 0.1f*TextToInteger(text_box.name);
    
    debug_FPS();
    debug_rotation_velocity(rd);
    debug_rotation_type(rt);
    debug_rotation_velocity_reset_default(rd);
    debug_text_box_write(&text_box);
    debug_text_box_draw(&text_box);
    debug_rotation_velocity_clickable_change(rd, text_box_number);
    debug_origin(origin);
    debug_mouse_in_debug_area();
#endif //if defined(DEBUG_ALL)
}

//~