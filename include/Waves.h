/**
 * @file Waves.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to generate Waves of Monsters
 * @date 2023-11-16
 *
 */

#ifndef __WAVES_H__
#define __WAVES_H__

#include "Monsters.h"

/**
 * @brief Enumerates the different types of waves
 */
typedef enum {
    NORMAL = 5,
    CROWD = 7,
    AGILE = 9,
    BOSS = 10,
} WaveType;

/**
 * @brief Generates a new random wave adding the monsters created to the
 * monster list
 *
 * @param monster_list the list of monsters
 * @param map Map where the wave is
 * @param nb_wave number of the wave generated
 */
void wave_generation(MonsterList *monster_list, const Map *map, int nb_wave);

#endif // __WAVES_H__
