#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#define LIST_FOREACH_SAFE(var, head, field, tvar)                              \
	for ((var) = LIST_FIRST((head));                                       \
	     (var) && ((tvar) = LIST_NEXT((var), field), 1); (var) = (tvar))
#include <sys/queue.h>

#include "Element.h"
#include "Map.h"
#include "Shots.h"
#include "Timer.h"

#define HP_MULT 10

typedef struct Monster {
    Timestamp start_time;
    Position position;
    int speed;
    Hue hue;
    double hp_init;
    double hp;
    Element residue;
    ShotList shots;
    LIST_ENTRY(Monster) entries;
    Direction direction;
} Monster;

typedef LIST_HEAD(MonsterList, Monster) MonsterList;

/**
 * @brief Creates a new monster initialized with the given arguments
 *
 * @param map Map where the monster is placed
 * @param speed speed of the monster, in cells per seconds
 * @param HP initial HP of the monster
 * @param start_time time when the monster leaves the nest
 * @return Monster* address of the Monster structure allocated,
 * or NULL if there was an allocation error
 */
Monster *create_new_monster(Map map, int speed, int HP, Timestamp start_time);

/**
 * @brief Frees the space allocated for the list of monsters
 *
 * @param monsters address of the list of monsters
 */
void free_monsters(MonsterList *monsters);

void free_monster(Monster *monster);

/**
 * @brief Adds, if necessary, an element to the field `residue` of the monster,
 * according to the `shot_hue`
 *
 * @param monster Address of the Monster structure to modify
 * @param shot_hue Hue of the shot targeting the monster
 */
void add_monster_residue(Monster *monster, Hue shot_hue);

/**
 * @brief Moves the monster on the map for a duration of
 * `time_elapsed`
 *
 * @param map Map where the monster moves
 * @param monster Address of the monster to modify
 * @param time_elapsed time elapsed during the movement of the monster in seconds
 */
void move_monster(Map map, Monster *monster, double time_elapsed);

void damage_monster(Monster *monster, Gem gem);

bool is_dead_monster(Monster *monster);

#endif  // __MONSTERS_H__
