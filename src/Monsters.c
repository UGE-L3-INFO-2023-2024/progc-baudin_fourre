/**
 * @file Monsters.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of Monsters
 * along the game (movement, damage, effects)
 * @date 2023-11-27
 *
 */

#include "Monsters.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Element.h"
#include "Map.h"
#include "Queue.h"
#include "Utils.h"

// Returns an initialized Effects structure
static Effects init_monster_effects(void) {
    Effects effects;
    for (int i = 0; i < 4; i++) {
        effects.type[i] = init_element_effect();
    }
    return effects;
}

// Returns the adress of the new Monster created with the given arguments
Monster *create_new_monster(
    const Map *map, int speed, int HP, Timestamp start_time, int score_mult) {
    Monster *monster = malloc(sizeof(Monster));
    if (!monster) {
        perror("Crash on monster allocation");
        exit(EXIT_FAILURE);
    }

    *monster = (Monster){
        .hp = HP,
        .hp_init = HP,
        .hue = random_hue(NONE),
        .position = coord_to_center_position(map->nest),
        .residue = NONE,
        .speed = speed,
        .start_time = start_time,
        .effects = init_monster_effects(),
        .score_mult = score_mult,
    };

    LIST_INIT(&monster->shots);
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

// Returns a random speed between 0.9 * `speed` and 1.1 * `speed`
static double rand_speed(double speed) {
    int sign = rand() % 2;
    double var = (rand() % 100) / 1000.0;
    if (sign)
        return (1.0 - var) * speed;
    else
        return (1.0 + var) * speed;
}

// Moves the monster on the `map` for a duration of `time_elapsed`
void move_monster(const Map *map, Monster *monster, double time_elapsed) {
    Vector move = get_direction_vector(monster->direction);
    Position new_pos;
    double speed = rand_speed(monster->speed);
    for (int i = 0; i < 4; i++) {
        if (!is_past_time(monster->effects.type[i].timeout))
            speed *= monster->effects.type[i].speed_mult;
    }

    new_pos = get_new_position(monster->position, speed * time_elapsed, move);
    if (has_past_center_position(
            new_pos, monster->direction, monster->next_cell)) {
        monster->position =
            coord_to_center_position(position_to_coord(monster->position));
        monster->direction = get_position_direction(map, monster->position);
        monster->next_cell = next_cell_coord(
            position_to_coord(monster->position), monster->direction);
    } else if (monster->direction != NODIR)
        monster->position = new_pos;
}

static inline double deg_to_rad(int deg) {
    return deg * (PI / 180.0);
}

// Returns the damage of the monster by the gem
double get_damage(const Monster *monster, Gem gem) {
    const double d = 5.0;
    const int n = gem.level;
    const int t_g = gem.hue;
    const int t_m = monster->hue;
    return d * pow(2, n) * (1.0 - cos(deg_to_rad(t_g - t_m)) / 2.0);
}

// Applies the `damage` to the `monster`
void apply_damage(Monster *monster, double damage, double *add_damage) {
    monster->hp = (monster->hp - damage) > 0 ? monster->hp - damage : 0;
    *add_damage += damage / monster->score_mult;
}

// Applies the extra damage from the element effect of the `monster`, if
// necessary
void apply_extra_damage(Monster *monster, double *add_damage) {
    for (int i = 0; i < 4; i++) {
        if (is_past_time(monster->effects.type[i].timeout)) {
            continue;
        }
        if (is_past_time(monster->effects.type[i].next_damage)) {
            apply_damage(monster, monster->effects.type[i].damage, add_damage);
            monster->effects.type[i].next_damage =
                time_future(monster->effects.type[i].damage_interval);
        }
    }
}

// Returns the address of the next monster in the `radius` of `pos` if start is
// `false`,otherwise the first monster is initialized with the list of monsters
Monster *
get_next_monster_in_radius(Monster *monster, Position pos, double radius) {
    while (
        monster
        && !(is_past_time(monster->start_time)
             && distance_between_positions(monster->position, pos) <= radius))
        monster = LIST_NEXT(monster, entries);

    return monster;
}

bool is_dead_monster(const Monster *monster) {
    return monster->hp == 0;
}
