#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "Monsters.h"

typedef enum {
    NONE,
    PYRO = 1,
    DENDRO = 2,
    HYDRO = 4,
} Element;

/**
 * @brief Adds, if necessary, an element to the field `residue` of the monster, 
 * according to the `shot_hue`
 * 
 * @param monster Address of the Monster structure to modify
 * @param shot_hue Hue of the shot targeting the monster
 */
void add_monster_residue(Monster *monster, Hue shot_hue);

#endif // __ELEMENT_H__
