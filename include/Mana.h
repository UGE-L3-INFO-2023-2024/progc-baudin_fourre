#ifndef __MANA_H__
#define __MANA_H__

#include "Monsters.h"

typedef struct {
    int quantity;
    int level;
    int max;
} Mana;

/**
 * @brief Initializes a Mana structure with its initial values;
 *
 * @return Mana mana structure initialized
 */
Mana init_mana(void);

/**
 * @brief Increases the mana level, if possible
 *
 * @param mana The address of the Mana structure to modify
 * @return int 1 if it was possible, or else 0
 */
int increase_mana_level(Mana *mana);

/**
 * @brief Increases the mana quantity with the mana won by eliminating a
 * monster
 *
 * @param mana address of the Mana structure to modify
 * @param monster Monster eliminated
 */
void mana_eliminate_monster(Mana *mana, Monster monster);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a tower
 *
 * @param mana Mana structure to modify
 * @return int 1 if buying the tower was possible, or else 0.
 */
int mana_buy_tower(Mana *mana);

/**
 * @brief Decreases the mana quantity, if possible, in order to banish a
 * monster
 *
 * @param mana Address of the Mana structure to modify
 * @param monster monster to banish
 * @return int 1 is banishing the monster was possible, or else 0
 */
int mana_banish_monster(Mana *mana, Monster monster);

/**
 * @brief Decreases the mana quantity, if possible, in order to fuse gems
 *
 * @param mana Address of the Mana structure to modify
 * @return int 1 is fusing gems was possible, or else 0
 */
int mana_fuse_gem(Mana *mana);

#endif  // __MANA_H__
