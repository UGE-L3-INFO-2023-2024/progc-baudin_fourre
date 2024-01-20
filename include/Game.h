/**
 * @file Game.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions defining the game play, allowing the creation and
 * update of the Game structure
 * @date 2023-11-16
 *
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "Gems.h"
#include "Inventory.h"
#include "Mana.h"
#include "Map.h"
#include "Monsters.h"
#include "Timer.h"
#include "Window.h"

#include <stdbool.h>

#define GEM_LEVEL_MAX 32

/**
 * @brief Structure containing the information of the game
 */
typedef struct {
    Map map;
    Timestamp next_wave;
    int wave_count;
    MonsterList monsters;
    ActiveGemList active_gems;
    Inventory inventory;
    Mana mana;
    Error error;
    bool defeat;
    double total_damage;
} Game;

/**
 * @brief Initializes a Game structure with its initial values
 *
 * @return the initialized Game
 */
Game init_game(void);

/**
 * @brief Adds a tower to the coordinates given, if possible
 *
 * @param game the game where the tower is added
 * @param win the WindowInfo containing the information on the
 * current window
 * @param coord Coordinates of the map where the tower is added
 * @return true if the tower could be added, false otherwise
 */
bool add_tower(Game *game, WindowInfo *win, Coord coord);

/**
 * @brief Increases the new gem level by one
 *
 * @param win the WindowInfo structure containing the new gem level
 */
void increase_new_gem_level(WindowInfo *win);

/**
 * @brief Decreases the new gem level by one
 *
 * @param win the WindowInfo structure containing the new gem level
 */
void decrease_new_gem_level(WindowInfo *win);

/**
 * @brief Adds a new gem to the game inventory
 *
 * @param game the current game to add the gem to
 * @param level level of the gem to create
 * @return true if the gem could be added, false otherwise
 */
bool new_gem(Game *game, int level);

/**
 * @brief Moves the monsters of the `game`
 *
 * @param game the current game
 * @param time Timestamp since the monsters were last moved
 */
void move_monsters(Game *game, Timestamp time);

/**
 * @brief Creates a new activegem in the tower given (if possible) with the
 * selected gem in the inventory
 *
 * @param game the current Game to modify
 * @param win Information of the current window
 * @param tower Coordinates of the game where the gem must be added
 */
void add_activegem(Game *game, WindowInfo win, Coord tower);

/**
 * @brief Adds a new wave of monsters to the game
 *
 * @param game the Game to modify
 */
void add_wave(Game *game);

/**
 * @brief Removes the activegem from the `tower` and puts it back in the
 * inventory
 *
 * @param game the current Game
 * @param tower Coordinates of the tower where to remove the ActiveGem
 */
void remove_activegem(Game *game, Coord tower);

/**
 * @brief Moves all the shots of the game
 *
 * @param game the current game
 * @param time Timestamp since the shots were last moved
 */
void move_shots(Game *game, Timestamp time);

/**
 * @brief Creates the new shots from the active gems of the game
 *
 * @param game the current game
 */
void activegems_fire(Game *game);

/**
 * @brief Damages the monsters of the game according to the shots
 *
 * @param game the current game
 */
void damage_monsters(Game *game);

/**
 * @brief Fuses the gems given, removing the latter from the inventory and
 * adding the resulting one
 *
 * @param game the current game
 * @param gem1 index of the first gem in the inventory of the Game
 * @param gem2 index of the second gem in the inventory of the Game
 */
void game_fuse_gems(Game *game, int gem1, int gem2);

/**
 * @brief Updates the `game` according to the time the game was last updated
 *
 * @param game the game to update
 * @param cur_time time of the last update
 */
void update_game(Game *game, Timestamp prev_time);

/**
 * @brief Frees the allocated values of the Game
 *
 * @param game the game to free
 */
void free_game(Game *game);

#endif // __GAME_H__
