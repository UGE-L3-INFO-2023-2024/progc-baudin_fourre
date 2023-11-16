#ifndef __SHOTS_H__
#define __SHOTS_H__

#include "Monsters.h"
#include "Map.h"
#include "Time.h"
#include "Gems.h"

typedef struct {
    Monster *target;
    Position position;
    float speed;
    Gem *source;
} Shot;

#endif // __SHOTS_H__
