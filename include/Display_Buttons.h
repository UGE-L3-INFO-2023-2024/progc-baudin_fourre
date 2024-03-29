/**
 * @file Display_Buttons.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to create and dipslay the buttons needed in
 * the game using the MLV library
 * @date 2024-01-12
 *
 */

#ifndef __DISPLAY_BUTTONS_H__
#define __DISPLAY_BUTTONS_H__

#include "Inventory.h"
#include "Window.h"

/**
 * @brief Draws the top buttons of the window
 *
 * @param win WindowInfo containing information on the current window
 */
void draw_top_buttons(WindowInfo *win);

/**
 * @brief Draws the `inventory` and its gems in the right bar, hollow the
 * selected gem if there's one
 *
 * @param inventory the inventory to draw
 * @param win the WindowInfo containing information on the current window
 */
void draw_inventory(Inventory inventory, WindowInfo *win);

#endif // __DISPLAY_BUTTONS_H__
