#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include <sys/queue.h>
#include "Hue.h"
#include "Element.h"
#include "Map.h"
#include "Shots.h"

typedef struct Monster {
    time start_time;
    Position position;
    float speed;
    Hue hue;
    int hp;
    Element residu;
    ShotList shots;
    LIST_ENTRY(Monster) entries;
} Monster;

typedef LIST_HEAD(MonsterList, entries) MonsterList;

#endif // __MONSTERS_H__
