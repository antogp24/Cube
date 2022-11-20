#ifndef CUBE_H
#define CUBE_H

//~ NOTE(anto): Global Headers

#include <stdio.h>
#include <raylib.h>
#include <math.h>

//~ NOTE(anto): primitive types and keywords

#define global_variable static
#define local_persist static
#define internal_function static

//~ NOTE(anto): Vectors

typedef union Vector {
    struct {
        float x, y, z;
    };
    float arr[3];
}Vector;

#define N_POINTS 8
#define SIDES_LENGTH 50.0f // 50

Vector vector_scale(Vector *v, float scalar);
void   vector_log(Vector *v);
void   vector_cube_points_reset(Vector pnts[N_POINTS]);
void   vector_cube_points_log(Vector pnts[N_POINTS]);


//~ NOTE(anto): Matrices

#define COS(a) (float)cos(a)
#define SIN(a) (float)sin(a)

typedef union Matrix3 {
    struct {
        float m1, m2, m3,
        m4, m5, m6,
        m7, m8, m9;
    };
    float arr[3*3];
}Matrix3;

typedef Matrix3 m3;

//~ NOTE(anto): Runtime Cube Data

typedef struct RunData {
    Vector  *pnts;
    Vector  *rv;
    Matrix3 *Rx;
    Matrix3 *Ry;
    Matrix3 *Rz;
}RunData;

//~

#define m3_index(matrix_array, i, j) matrix_array[3 * i + j]
void    m3_update_rotation_matrices(RunData *rd, float dt);
void    m3_log(Matrix3 *matrix);
Vector  m3_vector_multiplication(Matrix3 *matrix, Vector *vec);


//~ NOTE(anto): Shapes

#define shapes_line(ax, ay, bx, by, color)                                    DrawLine(ax, ay, bx, by, color)
#define shapes_point(x, y, color)                                             DrawCircle(x, y, 5, color)
#define shapes_connect(indexStt, indexEnd, pnts, offset_x, offset_y, color)   shapes_line(pnts[indexStt].x+offset_x,\
pnts[indexStt].y+offset_y,\
pnts[indexEnd].x+offset_x,\
pnts[indexEnd].y+offset_y,\
color)


//~ NOTE(anto): Rotations switching

typedef enum RotType {
    ROTATION_TYPE_NONE,
    ROTATION_TYPE_ALL,
    ROTATION_TYPE_X,
    ROTATION_TYPE_Y,
    ROTATION_TYPE_Z,
}RotType;


//~ NOTE(anto): Transformations

void transform_cube_points(RunData *rd, RotType rt, int i);


//~ NOTE(anto): Window

#define WIN_X 640
#define WIN_Y 480

//~ NOTE(anto): Input

#define SPEED 10
void    input_manage_movement(RunData *rd, Vector *mv, Vector2 *origin_offset, Vector pnts[N_POINTS], Color *cube_color);
RotType input_manage_rotations(RotType initial, Vector pnts[N_POINTS]);


//~ NOTE(anto): Debugging

#define MAX_INPUT_CHARS 5

typedef struct TextBox {
    Rectangle collider;
    char name[MAX_INPUT_CHARS+1];
    int letter_count;
    int frames_counter;
    bool mouse_on_text;
}TextBox;

#define DEBUG_FUNCTIONS_INTERNAL 0
#define DEBUG_FUNCTIONS_EXTERNAL 1

#if DEBUG_FUNCTIONS_INTERNAL // Keep them internal to the debug source file or have them global
void debug_FPS(void);
void debug_rotation_velocity(RunData *rd);
void debug_rotation_type(RotType rt);
void debug_button_draw(int x, int y, size_t width, size_t height, Color fill, Color border, size_t border_width);
void debug_button_positive_draw(int x, int y, size_t width, size_t height, size_t fnt, Color fill);
void debug_button_negative_draw(int x, int y, size_t width, size_t height, size_t fnt, Color fill);
void debug_button_contrasting_draw(int x, int y, size_t width, size_t height, size_t fnt, const char *axis, Color fill_positive, Color fill_negative);
void debug_rotation_velocity_reset_default(RunData *rd);
void debug_text_box_write(TextBox *text_box);
void debug_text_box_draw(TextBox *text_box);
void debug_rotation_velocity_clickable_change(RunData *rd, float button_scalar);
void debug_origin(Vector2 *origin);
#endif

bool debug_mouse_in_debug_area();
void debug_all(RotType rt, RunData *rd, Vector2 *origin);


//~

#endif //CUBE_H
