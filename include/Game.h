#ifndef __GAME_H__
#define __GAME_H__

#include "Gems.h"
#include "Inventory.h"
#include "Mana.h"
#include "Map.h"
#include "Monsters.h"
#include "Timer.h"
#include "Window.h"

#define GEM_LEVEL_MAX 9

typedef struct {
    Map map;
    Timestamp next_wave;
    MonsterList monsters;
    ActiveGemList active_gems;
    Inventory inventory;
    Mana mana;
    Error error;
} Game;

typedef enum {
    NO_ACTION,
    NEW_TOWER,
    ADD_TOWER,
    FUSE_GEM,
    NEW_GEM,
    ADD_ACTIVEGEM,
    INC_GEM_LEVEL,
    DEC_GEM_LEVEL,
    SELECT_GEM,
    WAIT_TOWER,
} UserAction;

/**
 * @brief Initializes a Game structure with its initial values
 *
 * @return Game
 */
Game init_game(void);

/**
 * @brief Adds a tower to the coordinates given, if possible
 *
 * @param game Address of the Game where the tower is added
 * @param coord Coordinates of the map where the tower is added
 * @return int 1 if the tower could be added, 0 otherwise
 */
int add_tower(Game *game, Coord coord);

/**
 * @brief increases the new gem level by one
 *
 * @param win Address of the WindowInfo structure containing the new gem level
 */
void increase_new_gem_level(WindowInfo *win);

/**
 * @brief decreases the new gem level by one
 *
 * @param win Address of the WindowInfo structure containing the new gem level
 */
void decrease_new_gem_level(WindowInfo *win);

/**
 * @brief Adds a new gem to the game inventory
 *
 * @param game Address of the current game to add the gem to
 * @param level level of the gem to create
 * @return int 1 if the gem could be added, 0 otherwise
 */
int new_gem(Game *game, int level);

/**
 * @brief Moves the monsters of the `game`
 *
 * @param game Address of the current Game
 * @param time Timestamp since the monsters were last moved
 */
void move_monsters(Game *game, Timestamp time);

/**
 * @brief Creates a new activegem in the tower given (if possible) with the
 * selected gem in the inventory
 *
 * @param game address of the current Game to modify
 * @param win Information of the current window
 * @param tower Coordinates of the game where the gem must be added
 */
void add_activegem(Game *game, WindowInfo win, Coord tower);

void move_shots(Game *game, Timestamp time);

void activegems_fire(Game *game);

#endif // __GAME_H__
