#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Game.h"
#define CELL_SIZE 32

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
