/**
 * @file Monsters.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief
 * @date 2023-11-25
 *
 */

#include "Monsters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Queue.h"
#include "Element.h"
#include "Map.h"
#include "Utils.h"

// Returns the adress of the new Monster created with the given arguments
Monster *create_new_monster(Map map, int speed, int HP, Timestamp start_time) {
    Monster *monster = (Monster *)malloc(sizeof(Monster));
    if (!monster) {
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }
    monster->hp = HP;
    monster->hp_init = HP;

    monster->hue = random_hue(NONE);
    monster->position = coord_to_position(map.nest);
    monster->residue = NONE;
    LIST_INIT(&(monster->shots));
    monster->speed = speed;
    monster->start_time = start_time;
    monster->direction = get_position_direction(map, monster->position);

    return monster;
}

// Frees the space allocated for the list of monsters
void free_monsters(MonsterList *monsters) {
    Monster *monster = NULL;
    while (!LIST_EMPTY(monsters)) {
        monster = LIST_FIRST(monsters);
        LIST_REMOVE(monster, entries);
        free_monster(monster);
        monster = NULL;
    }
}

void free_monster(Monster *monster) {
    free_shots(&monster->shots);
    free(monster);
}

// Adds, if necessary, an element to the field `residue` of the monster,
// according to the `shot_hue`
void add_monster_residue(Monster *monster, Hue shot_hue) {
    Element shot_element = hue_to_element(shot_hue);
    if (shot_element == NONE)
        return;

    if (monster->residue == NONE)
        monster->residue = shot_element;
    else {
        get_element_effect(monster->residue, shot_element);
        monster->residue = NONE;
    }
}

// Returns a random speed between 0.9 * `speed` and 1.1 * `speed`
static double rand_speed(int speed) {
    int sign = rand() % 2;
    double var = (rand() % 100) / 1000.0;
    if (sign)
        return (1.0 - var) * (double)speed;
    else
        return (1.0 + var) * (double)speed;
}

// Moves the monster along the `direction` for a duration of `time_elapsed`
static void move_monster_direction(Monster *monster, Direction direction,
                                   double time_elapsed) {
    Vector move = get_direction_vector(direction);
    double speed = rand_speed(monster->speed);
    monster->position = get_new_position(
        monster->position, speed * time_elapsed, move);  // TODO time
}

// Moves the monster on the `map` for a duration of `time_elapsed`
void move_monster(Map map, Monster *monster, double time_elapsed) {
    if (is_position_center(monster->position)) {
        monster->direction = get_position_direction(map, monster->position);
    }
    if (monster->direction != NODIR)
        move_monster_direction(monster, monster->direction, time_elapsed);
}

static inline double deg_to_rad(int deg) {
    return deg * (M_PI / 180.0);
}

void damage_monster(Monster *monster, Gem gem) {
    const double d = 1.0;
    const int n = gem.level;
    const int t_g = gem.hue;
    const int t_m = monster->hue;
    const double damage = d * (1 << n) * (1.0 - cos(deg_to_rad(t_g - t_m)) / 2.0);
    monster->hp -= damage;
    // TODO residus
    monster->residue = gem.type;
}

bool is_dead_monster(Monster *monster) {
    return monster->hp <= 0.0;
}
