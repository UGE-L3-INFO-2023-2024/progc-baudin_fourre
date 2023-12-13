/**
 * @file Waves.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief
 * @date 2023-11-25
 *
 */

#include "Waves.h"

#include <math.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "Monsters.h"
#include "Time.h"

// Returns a random WaveType according to the probabilities
static WaveType random_wave(int wave_count) {
    int rand_wave;
    if (wave_count <= 5)  // No boss waves until the sixth wave
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
static void get_wave_characteristics(WaveType type, int *nb_monsters,
                                     int *speed) {
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
int wave_generation(MonsterList *monster_list, Map map) {
    static int wave_count = 1;

    Monster *new_monster = NULL;
    int speed, nb_monsters;
    int hp;
    WaveType type;
    timestamp monster_start_time = (timestamp){0, 0};

    type = random_wave(wave_count);
    get_wave_characteristics(type, &nb_monsters, &speed);
    hp = HP_MULT * pow(1.2, wave_count);
    if (type == BOSS)
        hp *= 12;
    // monster_start_time = get instant time

    for (int i = 0; i < nb_monsters; i++) {
        // monster_start_time = add_interval(monster_start_time, i * (1 /
        // speed));
        new_monster = create_new_monster(map, speed, hp, monster_start_time);
        if (!new_monster)
            return 0;
        LIST_INSERT_HEAD(monster_list, new_monster, entries);
    }

    wave_count++;
    return 1;
}
