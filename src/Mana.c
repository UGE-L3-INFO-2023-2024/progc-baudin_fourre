#include "Mana.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

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

// Returns 1 if the quantity of mana is superior to the amount `required`, or
// else 0;
static bool enough_mana(const Mana *mana, uint64_t required) {
    assert(required >= 0);
    return required <= mana->quantity;
}

// Decreases the mana quanityt by `required` if possible.
// Returns 1 if it was possible, else 0.
static bool mana_remove_required(Mana *mana, uint64_t required, Error *error) {
    assert(required >= 0);
    if (!enough_mana(mana, required)) {
        new_error(error, MISSING_MANA);
        return false;
    }
    mana->quantity -= required;
    return true;
}

// Adds, if possible, `quantity` mana to the mana reserve pointed by `mana`
void add_mana(Mana *mana, uint64_t quantity) {
    assert(mana);
    if (mana->quantity + quantity > mana->max)
        mana->quantity = mana->max;
    else
        mana->quantity += quantity;
}

// Increases the mana level, returns 1 if it was possible, or else 0
bool increase_mana_level(Mana *mana, Error *error) {
    assert(mana);
    if (!mana_remove_required(mana, mana->max / 4, error)) {
        return false;
    }
    mana->level++;
    mana->max = (mana->max * 14) / 10;
    return true;
}

// Increases the mana quantity with the mana won by eliminating a monster
void mana_eliminate_monster(Mana *mana, const Monster *monster) {
    assert(mana);
    add_mana(mana, monster->hp_init * 0.1 * pow(1.3, mana->level));
}

// Decreases the mana quantity, if possible, in order to banish a monster
bool mana_banish_monster(Mana *mana, const Monster *monster, Error *error) {
    assert(mana);
    uint64_t required = (monster->hp_init * 0.15) * pow(1.3, mana->level);
    return mana_remove_required(mana, required, error);
}

// Returns the required amount of mana to buy a new tower
uint64_t mana_required_tower(bool add) {
    static int nb_tower = 0;
    uint64_t required = 0;

    if (nb_tower >= 3)
        required = 100 * (1L << (nb_tower - 3));

    if (add)
        nb_tower++;

    return required;
}

// Decreases the mana quantity, if possible, in order to buy a tower
bool mana_buy_tower(Mana *mana, Error *error) {
    assert(mana);
    uint64_t required = mana_required_tower(false);
    if (!mana_remove_required(mana, required, error)) {
        return false;
    }
    mana_required_tower(true);
    return true;
}

// Decreases the mana quantity, if possible, in order to buy a gem of level
// `level`
bool mana_buy_gem(Mana *mana, uint64_t level, Error *error) {
    assert(mana);
    uint64_t required = 100 * (1L << level);
    return mana_remove_required(mana, required, error);
}

// Decreases the mana quantity, if possible, in order to fuse gems
bool mana_fuse_gem(Mana *mana, Error *error) {
    assert(mana);
    return mana_remove_required(mana, 100, error);
}

// Adds mana if the time_left before the newt wave is superior to zero
void mana_new_wave(Mana *mana, double t_left) {
    assert(mana);
    if (t_left > 0)
        add_mana(mana, (t_left / 100.) * mana->max);
}
