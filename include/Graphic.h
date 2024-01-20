/**
 * @file Graphic.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to display the entirety of the game
 * @date 2023-11-16
 *
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Action.h"
#include "Game.h"
#include "Window.h"

/**
 * @brief draw the entire game based on the current action
 *
 * @param game the game to draw
 * @param action current UserAction of the game
 * @param win the WindowInfo containing information on the window
 */
void draw_game(Game *game, UserAction action, WindowInfo *win);

#endif // __GRAPHIC_H__
