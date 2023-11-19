#ifndef __GEMS_H__
#define __GEMS_H__

#include <sys/queue.h>
#include "Hue.h"
#include "Element.h"

typedef struct {
    short damage_mult;
    int level;
    Hue hue;
    Element type;
} Gem;

typedef struct ActiveGem {
    Gem gem;
    Cell *tower;
    time start_time;
    time_interval shot_interval;
    // last shot ?
    LIST_ENTRY(ActiveGem) entries;
} ActiveGem;

typedef LIST_HEAD(ActiveGemList, ActiveGem) ActiveGemList;

#endif // __GEMS_H__
