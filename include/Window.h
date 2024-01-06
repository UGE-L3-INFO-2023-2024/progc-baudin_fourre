#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <MLV/MLV_all.h>

#include "Map.h"

#define CELL_SIZE      32
#define GAME_WIDTH     (CELL_SIZE * MAP_WIDTH)
#define GAME_HEIGHT    (CELL_SIZE * MAP_HEIGHT)
#define RIGHT_BAR_SIZE (10 * CELL_SIZE)
#define RIGHT_BAR_X    (MAP_WIDTH * CELL_SIZE)
#define INVENTORY_COLS 4

typedef struct {
    int x;
    int y;
    int size;
    int length;
} Square, Button;

typedef struct {
    int new_gem_level;
    int selected_gem;
    MLV_Font *right_bar_font;
    MLV_Font *small_font;
    Button new_tower;
    Button new_gem;
    Button fuse_gem;
    Button inc_gem_level;
    Button dec_gem_level;
    Button inventory;
} WindowInfo;

/**
 * @brief Initializes the graphic window
 *
 * @return WindowInfo structure containing information about the window created
 */
WindowInfo init_graphic(void);

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
void wait_framerate();

/**
 * @brief Refreshes the graphic window with the changes made
 *
 */
void refresh(void);

/**
 * @brief Clears the window (displays a grey rectangle over the window)
 *
 */
void clear_window(void);

/**
 * @brief Quits and frees the window
 *
 * @param image image of the game to free
 */
void quit(void);

#endif
