#ifndef __SHOTS_H__
#define __SHOTS_H__

#include "Map.h"
#include "Time.h"
#include "Gems.h"

typedef struct Shot {
    Position position;
    float speed;
    Gem source;
    LIST_ENTRY(Shot) entries;
} Shot;

typedef LIST_HEAD(ShotList, Shot) ShotList;

#endif // __SHOTS_H__
