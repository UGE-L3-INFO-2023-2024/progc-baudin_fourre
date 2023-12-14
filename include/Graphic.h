#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Game.h"
#define CELL_SIZE 32
#define GAME_WIDTH (CELL_SIZE * MAP_WIDTH)
#define GAME_HEIGHT (CELL_SIZE * MAP_HEIGHT)
#define RIGHT_BAR_SIZE (10 * CELL_SIZE)
#define RIGHT_BAR_X (MAP_WIDTH * CELL_SIZE)

#define BUTTON_BKGD_COLOR MLV_COLOR_GREY
#define TOWER_COLOR MLV_COLOR_BLACK
#define RIGHT_BAR_COLOR MLV_COLOR_LIGHT_GREY

typedef struct {
    int x;
    int y;
    int size;
} Square;

/**
 * @brief Initializes the graphic window
 *
 */
void init_graphic(void);

/**
 * @brief Displays a black grid over the window
 *
 */
void draw_grid(void);

/**
 * @brief draws a bar on the right of the game window
 *
 */
void draw_right_bar(void);

/**
 * @brief Displays the path of the map
 *
 * @param map Map containing the `path` to draw
 */
void draw_path(Map map);

/**
 * @brief Waits `time` seconds
 *
 * @param time
 */
void wait_milliseconds(int time);

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
 * @brief draws the Monster `monster` as a circle centered at its position
 *
 * @param monster Monster structure to draw
 */
void draw_monster(Monster monster);

/**
 * @brief Draw the mana bar at the top of the window
 *
 * @param mana Mana structure to display
 */
void draw_mana(Mana mana);

/**
 * @brief Clears the path by displaying grey rectangles over each cell
 *
 * @param map Map of the path to clear
 */
void clear_path(Map map);

/**
 * @brief Quits and frees the window
 *
 * @param image image of the game to free
 */
void quit(void);

#endif  // __GRAPHIC_H__
