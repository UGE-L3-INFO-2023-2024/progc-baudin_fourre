#include "Mana.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "Monsters.h"

// Initializes a mana structure with the initial values
Mana init_mana(void) {
    Mana mana;
    mana.level = 0;
    mana.max = 2000;
    mana.quantity = 150;

    return mana;
}

// Returns 1 if the quantity of mana is superior to the amount `required`, or
// else 0;
static int enough_mana(Mana mana, int required) {
    assert(required >= 0);
    if (required <= mana.quantity)
        return 1;
    else {
        printf("Not enough mana\n");
        return 0;
    }
}

// Increases the mana level, returns 1 if it was possible, or else 0
int increase_mana_level(Mana *mana) {
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
    mana->quantity += (monster.hp_init * 0.1) * pow(1.3, mana->level);
    if (mana->quantity > mana->max)
        mana->quantity = mana->max;
}

// Decreases the mana quantity, if possible, in order to banish a monster
int mana_banish_monster(Mana *mana, Monster monster) {
    assert(mana);
    int required = (monster.hp_init * 0.15) * pow(1.3, mana->level);
    if (!enough_mana(*mana, required))
        return 0;

    mana->quantity -= required;
    return 1;
}

// Decreases the mana quantity, if possible, in order to buy a tower
int mana_buy_tower(Mana *mana) {
    assert(mana);
    static int nb_tower = 0;
    int required = 0;

    if (nb_tower >= 3)
        required = 100 * pow(2, nb_tower - 3);
    if (!enough_mana(*mana, required))
        return 0;
    mana->quantity -= required;
    return 1;
}

// Decreases the mana quantity, if possible, in order to buy a gem of level
// `level`
int mana_buy_gem(Mana *mana, int level) {
    assert(mana);
    int required = 100 * pow(2, level);
    if (!enough_mana(*mana, required))
        return 0;
    mana->quantity -= required;
    return 1;
}
