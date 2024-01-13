#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include "Element.h"
#include "Map.h"
#include "Queue.h"
#include "Shots.h"
#include "Timer.h"

#define HP_MULT 100

typedef struct {
    ElementEffect type[4];
} Effects;

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
Monster *create_new_monster(const Map *map, int speed, int HP,
                            Timestamp start_time);

/**
 * @brief Frees the space allocated for the list of monsters
 *
 * @param monsters address of the list of monsters
 */
void free_monsters(MonsterList *monsters);

void free_monster(Monster *monster);

/**
 * @brief Moves the monster on the map for a duration of
 * `time_elapsed`
 *
 * @param map Map where the monster moves
 * @param monster Address of the monster to modify
 * @param time_elapsed time elapsed during the movement of the monster in
 * seconds
 */
void move_monster(const Map *map, Monster *monster, double time_elapsed);

/**
 * @brief Gets the value of the damage of the `gem` on the `monster`
 *
 * @param monster
 * @param gem
 * @return double The value of the damage
 */
double get_damage(const Monster *monster, Gem gem);

/**
 * @brief Applies the `damage` to the `monster`
 *
 * @param monster Address of the Monster to apply the damage to
 * @param damage quantity of damage to apply
 */
void apply_damage(Monster *monster, double damage);

/**
 * @brief Applies the extra_damage attached to the `monster` if there's one
 *
 * @param monster Address of the Monster structure
 */
void apply_extra_damage(Monster *monster);

bool is_dead_monster(Monster *monster);

/**
 * @brief Get the next monster in the radius of pos
 *
 * @param monsters list of monsters to initialize the first monster
 * @param pos Position arounnd which the radius is checked
 * @param radius
 * @param start true to initialize the first monster, false to return the next
 * monster in radius
 * @return Monster* the address of the next monster in radius, or NULL if the
 * list has reached its end
 */
Monster *get_next_monster_in_radius(MonsterList *monsters, Position pos,
                                    double radius, bool start);

#endif // __MONSTERS_H__
