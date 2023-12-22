#include "Game.h"

#include "Utils.h"

// Returns 0 if a tower couldn't be added to the map at the coordinates
// `coord`, or 1 otherwise
int add_tower(Game *game, Coord coord) {
    if (!is_in_map(coord) ||
        game->map.cells[coord.col][coord.line].type != EMPTY)
        return 0;
    if (!mana_buy_tower(&game->mana))
        return 0;
    game->map.cells[coord.col][coord.line].type = TOWER;
    return 1;
}