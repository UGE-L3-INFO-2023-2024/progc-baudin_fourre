/**
 * @file Graphic-Utils.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to display basic
 * shapes in the window using the MLV library
 * @date 2024-01-12
 *
 */

#include "Graphic_Utils.h"

#include "Color.h"
#include <MLV/MLV_all.h>

// draws a square `square` using the color `bkgd_color`
void draw_square(Square square, MLV_Color bkgd_color) {
    MLV_draw_filled_rectangle(
        square.x, square.y, square.size, square.size, bkgd_color);
    MLV_draw_rectangle(
        square.x, square.y, square.size, square.size, MLV_COLOR_BLACK);
}

// draws a bar at the corner (x, y), of size (width x height),
// with its first (`filled`*100)% filled with color `color`
void draw_bar(
    int x, int y, int width, int height, double filled, MLV_Color color) {
    MLV_draw_filled_rectangle(x, y, (int) (width * filled), height, color);
    MLV_draw_filled_rectangle((int) (x + width * filled),
                              y,
                              (int) (width * (1.0 - filled)),
                              height,
                              MLV_COLOR_WHITE);
    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_BLACK);
}

// Creates and returns a new Square structure with the given arguments
Square new_square(int x, int y, int size) {
    return (Square){x, y, size, size};
}

// draws the Square `s` as selected by drawing a transparent black square
// over it
void draw_selected_square(Square s) {
    draw_square(s, SELECTED_COLOR);
}
