#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Game.h"
#include "Mana.h"
#include "Monsters.h"
#include "Window.h"

/**
 * @brief draws the game in int entirety according to the current action
 *
 * @param game Game structure to draw
 * @param action current UserAction of the game
 * @param win address of the WindowInfo containing information on the graphic
 * window
 */
void draw_game(Game game, UserAction action, WindowInfo *win);

#endif // __GRAPHIC_H__
