#include "Shots.h"

#include <stdlib.h>
#include <stdio.h>

Shot *create_new_shot(Coord tower, Gem gem) {
    Shot *shot = malloc(sizeof(Shot));
    if (!shot) {
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }
    *shot = (Shot){
        .position = coord_to_position(tower),
        .source = gem
    };
    return shot;
}

void free_shots(ShotList *shots) {
    Shot *shot = LIST_FIRST(shots), *next_s;
    while (shot != NULL) {
        next_s = LIST_NEXT(shot, entries);
        free_shot(shot);
        shot = next_s;
    }
}

void free_shot(Shot *shot) {
    free(shot);
}

void move_shot(Shot *shot, Position target, double time_elapsed) {
    double dist = distance_between_positions(shot->position, target);
    double travel = time_elapsed * 3.0;
    if (dist <= travel) {
        shot->position = target;
    }
    Vector vec = {
        .x = shot->position.x - target.x / dist,
        .y = shot->position.y - target.y / dist,
    };
    shot->position = get_new_position(shot->position, travel, vec);
}
