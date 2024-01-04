#ifndef __SHOTS_H__
#define __SHOTS_H__

#include "Map.h"
#include "Timer.h"
#include "Gems.h"

typedef struct Shot {
    Position position;
    Gem source;
    LIST_ENTRY(Shot) entries;
} Shot;

typedef LIST_HEAD(ShotList, Shot) ShotList;

Shot *create_new_shot(Coord tower, Gem gem);

void free_shots(ShotList *shots);

void move_shot(Shot *shot, Position target);

#endif // __SHOTS_H__
