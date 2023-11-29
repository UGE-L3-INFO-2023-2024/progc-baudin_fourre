#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include <sys/queue.h>

#include "Element.h"
#include "Map.h"
#include "Shots.h"
#include "Time.h"

#define HP_MULT 10

typedef struct Monster {
    timestamp start_time;
    Position position;
    int speed;
    Hue hue;
    float hp_init;
    float hp;
    Element residue;
    ShotList shots;
    LIST_ENTRY(Monster)
    entries;
} Monster;

typedef LIST_HEAD(MonsterList, Monster) MonsterList;

/**
 * @brief Creates a new monster initialized with the given arguments
 *
 * @param speed speed of the monster, in cells per seconds
 * @param HP initial HP of the monster
 * @param start_time time when the monster leaves the nest
 * @param position Initial position of the monster (nest)
 * @return Monster* address of the Monster structure allocated,
 * or NULL if there was an allocation error
 */
Monster *create_new_monster(int speed, int HP, timestamp start_time, Position position);

/**
 * @brief Frees the space allocated for the list of monsters
 *
 * @param monsters address of the list of monsters
 */
void free_monsters(MonsterList *monsters);

/**
 * @brief Adds, if necessary, an element to the field `residue` of the monster,
 * according to the `shot_hue`
 *
 * @param monster Address of the Monster structure to modify
 * @param shot_hue Hue of the shot targeting the monster
 */
void add_monster_residue(Monster *monster, Hue shot_hue);

#endif // __MONSTERS_H__
