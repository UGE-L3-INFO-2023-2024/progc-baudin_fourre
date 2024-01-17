/**
 * @file Waves.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to generate Waves of Monsters
 * @date 2023-11-27
 *
 */

#include "Waves.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Monsters.h"
#include "Queue.h"
#include "Timer.h"

// Returns a random WaveType according to the probabilities
static WaveType random_wave(int wave_count) {
    int rand_wave;
    if (wave_count <= 5) // No boss waves until the sixth wave
        rand_wave = rand() % 9;
    else
        rand_wave = rand() % 10;

    if (rand_wave < NORMAL)
        return NORMAL;
    else if (rand_wave < CROWD)
        return CROWD;
    else if (rand_wave < AGILE)
        return AGILE;
    else
        return BOSS;
}

// Returns the characteristics of the wave given its type
static void
get_wave_characteristics(WaveType type, int *nb_monsters, int *speed) {
    switch (type) {
        case NORMAL:
            *nb_monsters = 12;
            *speed = 1;
            break;
        case CROWD:
            *nb_monsters = 24;
            *speed = 1;
            break;
        case AGILE:
            *nb_monsters = 12;
            *speed = 2;
            break;
        case BOSS:
            *nb_monsters = 2;
            *speed = 1;
            break;
    }
}

// Generates a random wave and adds the monsters created to the `monster_list`
void wave_generation(MonsterList *monster_list, const Map *map, int nb_wave) {
    Monster *new_monster = NULL;
    int speed, nb_monsters;
    int hp;
    WaveType type;
    Timestamp monster_start_time;

    type = random_wave(nb_wave);
    get_wave_characteristics(type, &nb_monsters, &speed);
    hp = HP_MULT * pow(1.2, nb_wave);
    if (type == BOSS)
        hp *= 12;

    for (int i = 0; i < nb_monsters; i++) {
        monster_start_time = time_future(i * (1.0 / speed));
        new_monster = create_new_monster(map, speed, hp, monster_start_time);
        LIST_INSERT_HEAD(monster_list, new_monster, entries);
    }
}
