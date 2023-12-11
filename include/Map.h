#ifndef __MAP_H__
#define __MAP_H__

#define MAP_WIDTH 28
#define MAP_HEIGHT 22

#include "Gems.h"
#include "Utils.h"

typedef enum {
    EMPTY,
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
    Cell *nest;
} Map;

#endif // __MAP_H__
