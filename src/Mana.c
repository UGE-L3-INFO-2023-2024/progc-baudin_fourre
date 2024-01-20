/**
 * @file Mana.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation management of mana according
 * to the different possible addition and removal of mana in the game
 * @date 2023-12-12
 *
 */

#include "Mana.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "Error.h"
#include "Monsters.h"

// Initializes a mana structure with the initial values
Mana init_mana(void) {
    return (Mana){
        .level = 0,
        .max = 2000,
        .quantity = 150,
    };
}

// Returns true if the quantity of mana is superior to the amount `required`, false otherwise
static bool enough_mana(const Mana *mana, double required) {
    assert(required >= 0);
    return required <= mana->quantity;
}

// Decreases the mana quanityt by `required` if possible.
// Returns true if it was possible, false otherwise
static bool mana_remove_required(Mana *mana, double required, Error *error) {
    assert(required >= 0);
    if (!enough_mana(mana, required)) {
        new_error(error, MISSING_MANA);
        return false;
    }
    mana->quantity -= required;
    return true;
}

// Adds, if possible, `quantity` mana to the mana reserve pointed by `mana`
void add_mana(Mana *mana, double quantity) {
    if (mana->quantity + quantity > mana->max)
        mana->quantity = mana->max;
    else
        mana->quantity += quantity;
}

// Increases the mana level, returns true if it was possible, false otherwise
bool increase_mana_level(Mana *mana, Error *error) {
    if (!mana_remove_required(mana, mana->max * 0.25, error)) {
        return false;
    }
    mana->level++;
    mana->max = mana->max * 1.4;
    return true;
}

// Increases the mana quantity with the mana won by eliminating a monster
void mana_eliminate_monster(Mana *mana, const Monster *monster) {
    add_mana(mana, monster->hp_init * 0.1 * pow(1.3, mana->level));
}

// Decreases the mana quantity, if possible, in order to banish a monster
bool mana_banish_monster(Mana *mana, const Monster *monster, Error *error) {
    double required = (monster->hp_init * 0.15) * pow(1.3, mana->level);
    return mana_remove_required(mana, required, error);
}

// Returns the required amount of mana to buy a new tower
double mana_required_tower(int nb_tower) {
    double required = 0;

    if (nb_tower >= 3)
        required = 100 * pow(2, nb_tower - 3);

    return required;
}

// Decreases the mana quantity, if possible, in order to buy a tower
bool mana_buy_tower(Mana *mana, int nb_tower, Error *error) {
    double required = mana_required_tower(nb_tower);
    if (!mana_remove_required(mana, required, error)) {
        return false;
    }
    return true;
}

// Decreases the mana quantity, if possible, in order to buy a gem of level
// `level`
bool mana_buy_gem(Mana *mana, double level, Error *error) {
    double required = 100 * pow(2, level);
    return mana_remove_required(mana, required, error);
}

// Decreases the mana quantity, if possible, in order to fuse gems
bool mana_fuse_gem(Mana *mana, Error *error) {
    return mana_remove_required(mana, 100, error);
}

// Adds mana if the time_left before the newt wave is superior to zero
void mana_new_wave(Mana *mana, double t_left) {
    if (t_left > 0)
        add_mana(mana, (t_left / 100.) * mana->max);
}
