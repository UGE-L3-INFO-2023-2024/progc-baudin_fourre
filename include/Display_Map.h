#ifndef __DISPLAY_MAP_H__
#define __DISPLAY_MAP_H__

#include "Gems.h"
#include "Graphic_Utils.h"
#include "Map.h"
#include "Monsters.h"
#include "Shots.h"
#include "Window.h"

/**
 * @brief Draws a tower centered in the square
 *
 * @param s Square to center the tower in
 */
void draw_tower_in_square(Square s);

/**
 * @brief Draw a gem centered in the square `s`
 *
 * @param s Square to center the gem in
 * @param color Color of the gem to draw
 */
void draw_gem_color_in_square(Square s, MLV_Color color);

/**
 * @brief Draws a gem centered in the square `s`
 *
 * @param s Square to center the gem in
 * @param gem Gem to draw
 * @param font Font chosen to write the level of the gem with, or NULL to chose
 * the default font
 */
void draw_gem_in_square(Square s, Gem gem, MLV_Font *font);

/**
 * @brief draws the list of activegems by drawing gems in the correct towers
 *
 * @param activegems
 */
void draw_activegems(ActiveGemList activegems);

/**
 * @brief Draws the list of shots on the map
 *
 * @param shots the list of shots to draw
 */
void draw_shots(ShotList shots);

// draws the list of `monsters` on their position of the `map`
/**
 * @brief draws the list of monsters on their position of the map
 *
 * @param monsters List of monsters to draw
 * @param map Map on which the monsters move
 */
void draw_monsters(MonsterList monsters, const Map *map);

/**
 * @brief Draws the grid of the map, according to the type of each cell
 *
 * @param map address of the Map to draw
 */
void draw_map(const Map *map);

#endif // __DISPLAY_MAP_H__
