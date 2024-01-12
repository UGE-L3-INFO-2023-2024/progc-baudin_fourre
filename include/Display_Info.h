#ifndef __DISPLAY_INFO_H__
#define __DISPLAY_INFO_H__

#include "Error.h"
#include "Mana.h"
#include "Window.h"

/**
 * @brief Displays the error in the right bar of the window
 *
 * @param error Error containing the type of the message to display
 * @param win WindowInfo containing information on the current window
 */
void display_error(Error *error, WindowInfo win);

/**
 * @brief Draws the mana bar at the top of the window
 *
 * @param mana Mana to draw
 * @param win WindowInfo containing information on the current window
 */
void draw_mana(Mana mana, WindowInfo *win);

#endif // __DISPLAY_INFO_H__
