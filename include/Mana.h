/**
 * @file Mana.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation management of mana according
 * to the different possible addition and removal of mana in the game
 * @date 2023-11-16
 *
 */

#ifndef __MANA_H__
#define __MANA_H__

#include "Error.h"
#include "Monsters.h"

#define NB_TOWERS_MAX 35

typedef struct {
    double quantity;
    double level;
    double max;
} Mana;

/**
 * @brief Initializes a Mana structure with its initial values
 *
 * @return the initialized mana structure
 */
Mana init_mana(void);

/**
 * @brief Adds, if possible, `quantity` mana to the mana reserve `mana`
 *
 * @param mana the Mana
 * @param quantity quantity of mana to add
 */
void add_mana(Mana *mana, double quantity);

/**
 * @brief Increases the mana level, if possible
 *
 * @param mana the Mana to modify
 * @param error the Error to modify it there's not enough mana
 * @return true if it was possible, false otherwise
 */
bool increase_mana_level(Mana *mana, Error *error);

/**
 * @brief Increases the mana quantity with the mana won by eliminating a
 * monster
 *
 * @param mana the mana to modify
 * @param monster Monster eliminated
 */
void mana_eliminate_monster(Mana *mana, const Monster *monster);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a tower
 *
 * @param mana the mana to modify
 * @param nb_tower The number of current tower in the game
 * @param error the Error to modify it there's not enough mana
 * @return true if buying the tower was possible, false otherwise
 */
bool mana_buy_tower(Mana *mana, int nb_tower, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to banish a monster
 *
 * @param mana the mana to modify
 * @param monster monster to banish
 * @param error the Error to modify it there's not enough mana
 * @return true if banishing the monster was possible, false otherwise
 */
bool mana_banish_monster(Mana *mana, const Monster *monster, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to fuse gems
 *
 * @param mana the mana to modify
 * @param error the Error to modify it there's not enough mana
 * @return true if fusing gems was possible, false otherwise
 */
bool mana_fuse_gem(Mana *mana, Error *error);

/**
 * @brief Decreases the mana quantity, if possible, in order to buy a gem
 *
 * @param mana the mana to modify
 * @param level level of the gem to buy
 * @param error the Error to modify it there's not enough mana
 * @return true if buying a gem was possible, false otherwise
 */
bool mana_buy_gem(Mana *mana, double level, Error *error);

/**
 * @brief Gives the amount of mana required in order to buy a new tower
 *
 * @param nb_tower the number of towers currently in the game
 * @return the amount of mana required to buy a new tower
 */
double mana_required_tower(int nb_tower);

/**
 * @brief Adds mana if the time_left before the newt wave is superior to zero
 *
 * @param mana the mana to modify
 * @param t_left time left before the next_wave, in seconds
 */
void mana_new_wave(Mana *mana, double t_left);

#endif // __MANA_H__
