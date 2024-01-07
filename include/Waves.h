#ifndef __WAVES_H__
#define __WAVES_H__

#include "Monsters.h"

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
 * @param monster_list address of the list of monsters
 * @param map Map where the wave is
 * @param nb_wave number of the wave generated
 * @return int 1 if the wave was generated, 0 if there was an allocation error
 */
int wave_generation(MonsterList *monster_list, Map map, int nb_wave);

#endif // __WAVES_H__
