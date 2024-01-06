#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Color.h"
#include "Game.h"
#include "Mana.h"
#include "Monsters.h"
#include "Window.h"

/**
 * @brief draws the Monster `monster` as a circle centered at its position
 *
 * @param monster Monster structure to draw
 */
void draw_monster(Monster monster);

/**
 * @brief draws the list of `monsters` in the `map`
 *
 * @param monsters
 * @param map
 */
void draw_monsters(MonsterList monsters, Map map);

/**
 * @brief Draw the mana bar at the top of the window
 *
 * @param mana Mana structure to display
 */
void draw_mana(Mana mana);

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
