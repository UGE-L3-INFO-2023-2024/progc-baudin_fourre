/**
 * @file Graphic-Utils.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to display basic
 * shapes in the window using the MLV library
 * @date 2024-01-12
 *
 */

#ifndef __GRAPHIC_UTILS_H__
#define __GRAPHIC_UTILS_H__

#include "Utils.h"
#include <MLV/MLV_all.h>

typedef struct {
    int x;
    int y;
    int size;
    int length;
} Square, Button;

/**
 * @brief draws a `square` using the color `bkgd_color`
 *
 * @param square Square to draw, with its coordinates
 * @param bkgd_color the color of the square
 */
void draw_square(Square square, MLV_Color bkgd_color);

/**
 * @brief draws the Square `s` as selected by drawing a transparent black square
 * over it
 *
 * @param s
 */
void draw_selected_square(Square s);

/**
 * @brief draws a filled bar according to the information given
 *
 * @param x x-coordinate of the North-West corner of the bar
 * @param y y-coordinate of the North-West corner of the bar
 * @param width width of the bar
 * @param height height of the bar
 * @param filled percentage to which the bare must be filled
 * @param color color with which the bar must be filled
 */
void draw_bar(int x, int y, int width, int height, double filled,
              MLV_Color color);

#endif // __GRAPHIC_UTILS_H__
