#ifndef __MAP_H__
#define __MAP_H__

#define MAP_WIDTH 28
#define MAP_HEIGHT 22

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
        Gem gem;
        Direction direction;
    };
} Cell;

typedef struct {
    Cell cells[MAP_WIDTH][MAP_HEIGHT];
    Coord nest;
} Map;

Cell *next_cell_direction(const Map *map, const Cell *cell, Direction dir);

Map generate_map();

#endif  // __MAP_H__
