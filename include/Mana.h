#ifndef __MANA_H__
#define __MANA_H__

#include "Error.h"
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
int increase_mana_level(Mana *mana, Error *error);

/**
 * @brief Increases the mana quantity with the mana won by eliminating a
 * monster
 *
 * @param mana address of the Mana structure to modify
 * @param monster Monster eliminated
 */
void mana_eliminate_monster(Mana *mana, Monster monste, Error *errorr);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a tower
 *
 * @param mana Mana structure to modify
 * @return int 1 if buying the tower was possible, or else 0.
 */
int mana_buy_tower(Mana *mana, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to banish a
 * monster
 *
 * @param mana Address of the Mana structure to modify
 * @param monster monster to banish
 * @return int 1 is banishing the monster was possible, or else 0
 */
int mana_banish_monster(Mana *mana, Monster monster, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to fuse gems
 *
 * @param mana Address of the Mana structure to modify
 * @return int 1 is fusing gems was possible, or else 0
 */
int mana_fuse_gem(Mana *mana, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a gem
 *
 * @param mana Address of the Mana structure to modify
 * @param level level of the gem to buy
 * @return int 1 is buying a gem was possible, or else 0
 */
int mana_buy_gem(Mana *mana, int level, Error *error);

/**
 * @brief Gives the amount of mana required in order to buy a new tower
 *
 * @param add 1 if a new tower has been added, 0 otherwise
 * @return int the amount of mana required to buy a new tower
 */
int mana_required_tower(int add);

#endif  // __MANA_H__
