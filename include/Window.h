/**
 * @file Window.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to initialize and manage graphic windows of
 * the MLV library
 * @date 2023-12-25
 *
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <MLV/MLV_all.h>

#include "Graphic_Utils.h"
#include "Map.h"

#define RIGHT_BAR_COLS 10
#define INVENTORY_COLS 4

typedef struct {
    int cell_size;
    int new_gem_level;
    int selected_gem;
    int nb_towers;
    MLV_Font *right_bar_font;
    MLV_Font *small_font;
    Button new_tower;
    Button new_gem;
    Button fuse_gem;
    Button inc_gem_level;
    Button dec_gem_level;
    Button inventory;
    Button increase_mana_level;
} WindowInfo;

/**
 * @brief Initializes the graphic window
 *
 * @param win Address of the WindowInfo structure to intialize
 */
void init_graphic(WindowInfo *win);

/**
 * @brief Creates a new Square with the given arguments
 *
 * @param x x-coordinate of the top-left corner
 * @param y y-coordinate of the top-right corner
 * @param size size of the sides of the square
 * @return Square the Square created
 */
Square new_square(int x, int y, int size);

/**
 * @brief Waits according to the set framerate
 *
 */
void wait_framerate(void);

/**
 * @brief Refreshes the graphic window with the changes made
 *
 */
void refresh(void);

/**
 * @brief Clears the window (displays a grey rectangle over the window)
 *
 * @param win Address of the WindowInfo containing information on the window to
 * quit
 */
void clear_window(WindowInfo win);

/**
 * @brief Quits and frees the window
 *
 * @param win Address of the WindowInfo containing information on the window to
 * quit
 */
void quit(WindowInfo *win);

#endif
