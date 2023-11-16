#ifndef __GEMS_H__
#define __GEMS_H__

#include "Hue.h"

typedef enum {
    Red,
    Green,
    Blue,
    Mixed,
} GemType;

typedef struct {
    short damage_mult;
    int level;
    Cell *cell;
    time start_time;
    time_interval shot_interval;
    GemType type;
    Hue hue;
    
} Gem;

#endif // __GEMS_H__
