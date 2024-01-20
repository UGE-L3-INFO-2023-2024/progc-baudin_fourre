/**
 * @file Map.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the generation and reading of the game map
 * @date 2023-11-16
 *
 */

#ifndef __MAP_H__
#define __MAP_H__

#define MAP_WIDTH  28
#define MAP_HEIGHT 22
#define MARGIN     3

#include "Gems.h"
#include "Utils.h"

/**
 * @brief Macro to get the cell at the given coordinates
 */
#define CI(x) (x).col][(x).line

/**
 * @brief Macro to get the cell from a position casted to int
 */
#define CI_RAW_POS(p) ((int) ((p).x))][((int) ((p).y))

/**
 * @brief Enumerates the different types of cells
 */
typedef enum {
    EMPTY = 0,
    TOWER,
    PATH,
    NEST,
    HOME,
} CellType;

/**
 * @brief Structure representing a cell of the map
 */
typedef struct {
    CellType type;
    Coord coord;
    union {
        ActiveGem *gem;
        Direction direction;
    };
} Cell;

/**
 * @brief Structure representing the map
 */
typedef struct {
    Cell cells[MAP_WIDTH][MAP_HEIGHT];
    Coord nest;
} Map;

/**
 * @brief Generates a map with a path from the nest to the home
 *
 * @return the generated map
 */
Map generate_map(void);

/**
 * @brief Get the direction of the cell below `position`
 *
 * @param map Map containing the cells and the path
 * @param position Position where to get the direction
 * @return Direction cardinal direction of the cell, or NONE if the position is
 * not on a PATH
 */
Direction get_position_direction(const Map *map, Position position);

/**
 * @brief Checks if the `coord` are within the map
 *
 * @param coord the coord to check
 * @return true if the coordinates are in the map, false otherwise
 */
bool is_in_map(Coord coord);

#endif // __MAP_H__
