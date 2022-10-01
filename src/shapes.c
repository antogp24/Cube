#include <math3D/shapes.h>

void shapes_line(float ax, float ay, float bx, float by) {
    DrawLine(ax, ay, bx, by, WHITE);
}

void shapes_point(float x, float y) {
    DrawCircle(x, y, 5, WHITE);
}

void shapes_connect(int indexStt, int indexEnd, Vector pnts[8], int offset_x, int offset_y) {
    shapes_line(pnts[indexStt].x + offset_x, pnts[indexStt].y + offset_y,
                pnts[indexEnd].x + offset_x, pnts[indexEnd].y + offset_y);
}
