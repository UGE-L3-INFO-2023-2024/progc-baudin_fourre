#ifndef __MAP_H__
#define __MAP_H__

#define MAP_WIDTH  28
#define MAP_HEIGHT 22
#define MARGIN     3

#include "Gems.h"
#include "Utils.h"

#define CI(x) (x).col][(x).line

typedef enum {
    EMPTY = 0,
    TOWER,
    PATH,
    NEST,
    HOME,
} CellType;

typedef struct {
    CellType type;
    Coord coord;
    union {
        ActiveGem *gem;
        Direction direction;
    };
} Cell;

typedef struct {
    Cell cells[MAP_WIDTH][MAP_HEIGHT];
    Coord nest;
} Map;

Cell *next_cell_direction(const Map *map, const Cell *cell, Direction dir);

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
 * @param coord The Coord to check
 * @return int 1 if the coordinates are in the map, 0 otherwise
 */
int is_in_map(Coord coord);

#endif // __MAP_H__
