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

void draw_grid(void);

/**
 * @brief Waits `time` seconds
 *
 * @param time
 */
void wait_seconds(int time);

/**
 * @brief Refreshes the graphic window with the changes made
 *
 */
void refresh(void);

void clear_window(void);

/**
 * @brief Quits and frees the window
 *
 * @param image image of the game to free
 */
void quit(void);

#endif // __GRAPHIC_H__
