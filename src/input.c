#include <input.h>
#include <math3D/transform.h>
#include <settings.h>

void Input(Vector *rv, Vector *mv, Vector pnts[N_POINTS]) {
    
    if (IsKeyPressed(KEY_X)) {
        rv->x *= -1;
    }
    if (IsKeyPressed(KEY_Y)) {
        rv->y *= -1;
    }
    if (IsKeyPressed(KEY_Z)) {
        rv->z *= -1;
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
    
    for (int i = 0; i < N_POINTS; i++) {
        pnts[i].x += mv->x;
        pnts[i].y += mv->y;
        pnts[i].z += mv->z;
    }
    
    // Reset the points
    if (IsKeyDown(KEY_ZERO)) {
        reset_points(pnts);
    }
}
