/**
 * @file Monsters.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of Monsters
 * along the game (movement, damage, effects)
 * @date 2023-11-16
 *
 */

#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include "Element.h"
#include "Map.h"
#include "Queue.h"
#include "Shots.h"
#include "Timer.h"

#define HP_MULT 10

/**
 * @brief Structure representing the effects applied to a monster
 */
typedef struct {
    ElementEffect type[4];
} Effects;

/**
 * @brief Structure representing the information of a monster
 */
typedef struct Monster {
    int speed;
    double hp_init;
    double hp;
    Hue hue;
    Timestamp start_time;
    Position position;
    Coord next_cell;
    Element residue;
    Effects effects;
    ShotList shots;
    LIST_ENTRY(Monster) entries;
    Direction direction;
    int score_mult;
} Monster;

/**
 * @brief Structure representing a linked list of monsters
 */
typedef LIST_HEAD(MonsterList, Monster) MonsterList;

/**
 * @brief Creates a new monster initialized with the given arguments
 *
 * @param map Map where the monster is placed
 * @param speed speed of the monster, in cells per seconds
 * @param HP initial HP of the monster
 * @param start_time time when the monster leaves the nest
 * @param score_mult the value by which the damage to the monster is multiplied
 * when added to the score
 * @return the Monster structure allocated
 */
Monster *create_new_monster(
    const Map *map, int speed, int HP, Timestamp start_time, int score_mult);

/**
 * @brief Frees the space allocated for the list of monsters
 *
 * @param monsters the list of monsters
 */
void free_monsters(MonsterList *monsters);

/**
 * @brief Frees an allocated monster
 *
 * @param monster the monster to free
 */
void free_monster(Monster *monster);

/**
 * @brief Moves the monster on the map for a duration of `time_elapsed`
 *
 * @param map Map where the monster moves
 * @param monster the monster to move
 * @param time_elapsed time elapsed during the movement of the monster in
 * seconds
 */
void move_monster(const Map *map, Monster *monster, double time_elapsed);

/**
 * @brief Gets the value of the damage of the `gem` on the `monster`
 *
 * @param monster the monster to damage
 * @param gem the gem that damages
 * @return the value of the damage
 */
double get_damage(const Monster *monster, Gem gem);

/**
 * @brief Applies the `damage` to the `monster`
 *
 * @param monster the monster to apply the damage to
 * @param damage quantity of damage to apply
 */
void apply_damage(Monster *monster, double damage, double *add_damage);

/**
 * @brief Applies the extra_damage attached to the `monster` if there's one
 *
 * @param monster the Monster structure
 */
void apply_extra_damage(Monster *monster, double *add_damage);

/**
 * @brief Tells if the monster is dead
 *
 * @param monster the monster to check
 * @return true if the monster is dead, false otherwise
 */
bool is_dead_monster(const Monster *monster);

/**
 * @brief Gets the next monster in the radius of pos
 *
 * @param monster a monster in the list to check first and start from
 * @param pos position around which the radius is checked
 * @param radius radius of the circle around pos
 * @return the next monster in radius (can be the first monster passed) or NULL
 * if the list has reached its end
 */
Monster *
get_next_monster_in_radius(Monster *monster, Position pos, double radius);

#endif // __MONSTERS_H__
