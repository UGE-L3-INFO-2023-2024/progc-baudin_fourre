/**
 * @file Monsters.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief
 * @date 2023-11-25
 *
 */

#include "Monsters.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Element.h"
#include "Map.h"
#include "Queue.h"
#include "Utils.h"

// Returns the adress of the new Monster created with the given arguments
Monster *create_new_monster(const Map *map, int speed, int HP, Timestamp start_time) {
    Monster *monster = malloc(sizeof(Monster));
    if (!monster) {
        perror("Crash on monster allocation");
        exit(EXIT_FAILURE);
    }

    *monster = (Monster) {
        .hp = HP,
        .hp_init = HP,
        .hue = random_hue(NONE),
        .position = coord_to_position(map->nest),
        .residue = NONE,
        .speed = speed,
        .start_time = start_time,
        .effect = init_element_effect(),
    };

    LIST_INIT(&(monster->shots));
    monster->direction = get_position_direction(map, monster->position);
    monster->next_cell = next_cell_coord(map->nest, monster->direction);

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
static double rand_speed(double speed) {
    int sign = rand() % 2;
    double var = (rand() % 100) / 1000.0;
    if (sign)
        return (1.0 - var) * speed;
    else
        return (1.0 + var) * speed;
}

// Moves the monster along the `direction` for a duration of `time_elapsed`
static void move_monster_direction(Monster *monster, Direction direction,
                                   double time_elapsed) {
    Vector move = get_direction_vector(direction);
    double speed = monster->effect.type != LOWER_SPEED
                       ? rand_speed(monster->speed)
                       : rand_speed(monster->effect.speed);
    monster->position = get_new_position(
        monster->position, speed * time_elapsed, move); // TODO time
}

// Moves the monster on the `map` for a duration of `time_elapsed`
void move_monster(const Map *map, Monster *monster, double time_elapsed) {
    if (has_past_center_position(monster->position, monster->direction,
                                 monster->next_cell)) {
        monster->position = coord_to_position(
            (Coord){(int) monster->position.x, (int) monster->position.y});
        monster->direction = get_position_direction(map, monster->position);
        monster->next_cell = next_cell_coord(
            (Coord){(int) monster->position.x, (int) monster->position.y},
            monster->direction);
    }
    if (monster->direction != NODIR)
        move_monster_direction(monster, monster->direction, time_elapsed);
}

static inline double deg_to_rad(int deg) {
    return deg * (M_PI / 180.0);
}

// Returns the damage of the monster by the gem
double get_damage(Monster monster, Gem gem) {
    const double d = 50.0;
    const int n = gem.level;
    const int t_g = gem.hue;
    const int t_m = monster.hue;
    return d * (1 << n) * (1.0 - cos(deg_to_rad(t_g - t_m)) / 2.0);
}

void damage_monster(Monster *monster, Gem gem) {
    const double damage = get_damage(*monster, gem);
    monster->hp = (monster->hp - damage) > 0 ? monster->hp - damage : 0;
}

// Applies the extra damage from the element effect of the `monster`, if
// necessary
void apply_extra_damage(Monster *monster) {
    if (monster->effect.type != EXTRA_DAMAGE)
        return;

    if (is_past_time(monster->effect.timeout)) {
        monster->effect.type = NO_EFFECT;
        return;
    }

    if (is_past_time(monster->effect.damage.next_damage)) {
        monster->hp = (monster->hp - monster->effect.damage.damage) > 0
                          ? monster->hp - monster->effect.damage.damage
                          : 0;
        monster->effect.damage.next_damage = time_future(0.5);
    }
}

bool is_dead_monster(Monster *monster) {
    return monster->hp == 0;
}
