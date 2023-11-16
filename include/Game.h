#ifndef __GAME_H__
#define __GAME_H__

#include "Map.h"
#include "Monsters.h"
#include "Gems.h"
#include "Inventory.h"
#include "Mana.h"

typedef struct {
    Map map;
    time next_wave;
    MonsterHead monsters;
    GemHead gems;
    Inventory inventory;
    Mana mana;
    // Liste des shots
} Game;

#endif // __GAME_H__
