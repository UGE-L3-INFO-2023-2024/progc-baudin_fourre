#include "Mana.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "Error.h"
#include "Monsters.h"

// Initializes a mana structure with the initial values
Mana init_mana(void) {
    Mana mana;
    mana.level = 0;
    mana.max = 2000;
    mana.quantity = 150;

    return mana;
}

// Modifies the `error` with new mana error
static void get_mana_error(Error *error) {
    new_error(error, "Not enough mana");
}

// Returns 1 if the quantity of mana is superior to the amount `required`, or
// else 0;
static int enough_mana(Mana mana, int required) {
    assert(required >= 0);
    if (required <= mana.quantity)
        return 1;
    else {
        return 0;
    }
}

// Adds, if possible, `quantity` mana to the mana reserve pointed by `mana`
static void add_mana(Mana *mana, int quantity) {
    assert(mana);
    if (mana->quantity + quantity > mana->max)
        mana->quantity = mana->max;
    else
        mana->quantity += quantity;
}

// Increases the mana level, returns 1 if it was possible, or else 0
int increase_mana_level(Mana *mana, Error *error) {
    assert(mana);
    if (!enough_mana(*mana, mana->max / 4))
        return 0;

    mana->quantity -= mana->max / 4;
    mana->level++;
    mana->max *= 1.4;
    return 1;
}

// Increases the mana quantity with the mana won by eliminating a monster
void mana_eliminate_monster(Mana *mana, Monster monster) {
    assert(mana);
    add_mana(mana, (monster.hp_init * 0.1) * pow(1.3, mana->level));
}

// Decreases the mana quanityt by `required` if possible.
// Returns 1 if it was possible, else 0.
static int mana_remove_required(Mana *mana, int required) {
    assert(required >= 0);
    if (!enough_mana(*mana, required))
        return 0;
    mana->quantity -= required;
    return 1;
}

// Decreases the mana quantity, if possible, in order to banish a monster
int mana_banish_monster(Mana *mana, Monster monster) {
    assert(mana);
    int required = (monster.hp_init * 0.15) * pow(1.3, mana->level);
    if (!mana_remove_required(mana, required)) {
        return 0;
    }
    return 1;
}

// Returns the required amount of mana to buy a new tower
int mana_required_tower(int add) {
    static int nb_tower = 0;
    int required = 0;

    if (nb_tower >= 3)
        required = 100 * pow(2, nb_tower - 3);
    if (add)
        nb_tower++;
    return required;
}

// Decreases the mana quantity, if possible, in order to buy a tower
int mana_buy_tower(Mana *mana, Error *error) {
    assert(mana);
    int required = mana_required_tower(0);
    if (!mana_remove_required(mana, required)) {
        get_mana_error(error);
        return 0;
    }
    mana_required_tower(1);
    return 1;
}

// Decreases the mana quantity, if possible, in order to buy a gem of level
// `level`
int mana_buy_gem(Mana *mana, int level, Error *error) {
    assert(mana);
    int required = 100 * pow(2, level);
    if (!mana_remove_required(mana, required)) {
        get_mana_error(error);
        return 0;
    }
    return 1;
}

// Decreases the mana quantity, if possible, in order to fuse gems
int mana_fuse_gem(Mana *mana, Error *error) {
    assert(mana);
    if (!mana_remove_required(mana, 100)) {
        get_mana_error(error);
        return 0;
    }
    return 1;
}

// Adds mana if the time_left before the newt wave is superior to zero
void mana_new_wave(Mana *mana, double t_left) {
    if (t_left > 0)
        add_mana(mana, (t_left / 100.) * mana->max);
}