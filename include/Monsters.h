#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include <sys/queue.h>
#include "Hue.h"
#include "Element.h"
#include "Map.h"

typedef struct _monster {
    time start_time;
    Position position;
    float speed;
    Hue hue;
    int hp;
    Element residu;
    LIST_ENTRY(_monster) entries;
} Monster;

typedef LIST_HEAD(_monster_head, entries) MonsterHead;

#endif // __MONSTERS_H__
