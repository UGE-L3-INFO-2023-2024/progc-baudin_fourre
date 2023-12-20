#ifndef __GAME_H__
#define __GAME_H__

#include "Map.h"
#include "Monsters.h"
#include "Gems.h"
#include "Inventory.h"
#include "Mana.h"
#include "Time.h"

typedef struct {
    Map map;
    Timestamp next_wave;
    MonsterList monsters;
    ActiveGemList active_gems;
    Inventory inventory;
    Mana mana;
} Game;

#endif // __GAME_H__
