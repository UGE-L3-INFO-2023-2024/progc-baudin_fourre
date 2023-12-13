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
#include <sys/queue.h>

#include "Element.h"
#include "Map.h"
#include "Utils.h"

// Returns the adress of the new Monster created with the given arguments
Monster *create_new_monster(Map map, int speed, int HP, timestamp start_time) {
    Monster *monster = (Monster *)malloc(sizeof(Monster));
    if (!monster) {
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }
    monster->hp = HP;
    monster->hp_init = HP;
    monster->hue = random_hue(NONE);
    monster->position = (Position){map.nest.col + 0.5, map.nest.line + 0.5};
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
        free(monster);
        monster = NULL;
    }
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

// Moves the monster along the `direction` for a duration of `time_elapsed`
static void move_monster_direction(Monster *monster, Direction direction,
                                   interval time_elapsed) {
    Vector move = get_direction_vector(direction);
    monster->position = get_new_position(
        monster->position, (monster->speed * time_elapsed.tv_usec) / 1000.0,
        move);
}

// Moves the monster on the `map` for a duration of `time_elapsed`
void move_monster(Map map, Monster *monster, interval time_elapsed) {
    if (is_position_center(monster->position)) {
        monster->direction = get_position_direction(map, monster->position);
    }
    if (monster->direction != NODIR)
        move_monster_direction(monster, monster->direction, time_elapsed);
}
