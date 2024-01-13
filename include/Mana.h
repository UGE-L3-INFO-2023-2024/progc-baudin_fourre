#ifndef __MANA_H__
#define __MANA_H__

#include "Error.h"
#include "Monsters.h"
#include <stdint.h>

typedef struct {
    uint64_t quantity;
    uint64_t level;
    uint64_t max;
} Mana;

/**
 * @brief Initializes a Mana structure with its initial values;
 *
 * @return Mana mana structure initialized
 */
Mana init_mana(void);

/**
 * @brief Adds, if possible, `quantity` mana to the mana reserve pointed by
 * `mana`
 *
 * @param mana Address of the Mana structure
 * @param quantity quantity of mana to add
 */
void add_mana(Mana *mana, uint64_t quantity);

/**
 * @brief Increases the mana level, if possible
 *
 * @param mana The address of the Mana structure to modify
 * @param error Address of the Error to modify it there's not enough mana
 * @return bool true if it was possible
 */
bool increase_mana_level(Mana *mana, Error *error);

/**
 * @brief Increases the mana quantity with the mana won by eliminating a
 * monster
 *
 * @param mana address of the Mana structure to modify
 * @param monster Monster eliminated
 */
void mana_eliminate_monster(Mana *mana, const Monster *monster);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a tower
 *
 * @param mana Mana structure to modify
 * @param error Address of the Error to modify it there's not enough mana
 * @return bool true if buying the tower was possible
 */
bool mana_buy_tower(Mana *mana, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to banish a
 * monster
 *
 * @param mana Address of the Mana structure to modify
 * @param monster monster to banish
 * @param error Address of the Error to modify it there's not enough mana
 * @return bool true if banishing the monster was possible
 */
bool mana_banish_monster(Mana *mana, const Monster *monster, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to fuse gems
 *
 * @param mana Address of the Mana structure to modify
 * @param error Address of the Error to modify it there's not enough mana
 * @return bool true if fusing gems was possible
 */
bool mana_fuse_gem(Mana *mana, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a gem
 *
 * @param mana Address of the Mana structure to modify
 * @param level level of the gem to buy
 * @param error Address of the Error to modify it there's not enough mana
 * @return bool true if buying a gem was possible
 */
bool mana_buy_gem(Mana *mana, uint64_t level, Error *error);

/**
 * @brief Gives the amount of mana required in order to buy a new tower
 *
 * @param add true if a new tower has been added, false otherwise
 * @return int the amount of mana required to buy a new tower
 */
uint64_t mana_required_tower(bool add);

/**
 * @brief Adds mana if the time_left before the newt wave is superior to zero
 *
 * @param mana Address of the mana structure to modify
 * @param t_left time left before the next_wave, in seconds
 */
void mana_new_wave(Mana *mana, double t_left);

#endif // __MANA_H__
