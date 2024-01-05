#ifndef __SHOTS_H__
#define __SHOTS_H__

#include "Gems.h"
#include "Map.h"
#include "Timer.h"

#include <stdbool.h>

typedef struct Shot {
    Position position;
    Gem source;
    LIST_ENTRY(Shot) entries;
} Shot;

typedef LIST_HEAD(ShotList, Shot) ShotList;

Shot *create_new_shot(Coord tower, Gem gem);

void free_shots(ShotList *shots);

void free_shot(Shot *shot);

void move_shot(Shot *shot, Position target, double time_elapsed);

#endif // __SHOTS_H__
