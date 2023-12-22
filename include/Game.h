#ifndef __GAME_H__
#define __GAME_H__

#include "Gems.h"
#include "Inventory.h"
#include "Mana.h"
#include "Map.h"
#include "Monsters.h"
#include "Time.h"

typedef struct {
    Map map;
    Timestamp next_wave;
    MonsterList monsters;
    ActiveGemList active_gems;
    Inventory inventory;
    Mana mana;
} Game;

typedef enum {
    NO_ACTION,
    NEW_TOWER,
    ADD_TOWER,
    FUSE_GEM,
    NEW_GEM,
    ADD_ACTIVEGEM,
} UserAction;

/**
 * @brief Adds a tower to the coordinates given, if possible
 *
 * @param game Address of the Game where the tower is added
 * @param coord Coordinates of the map where the tower is added
 * @return int 1 if the tower could be added, 0 otherwise
 */
int add_tower(Game *game, Coord coord);

#endif  // __GAME_H__
