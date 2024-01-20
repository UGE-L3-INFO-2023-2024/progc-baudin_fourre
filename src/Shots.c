/**
 * @file Shots.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of Shots and
 * ShotLists
 * @date 2024-01-04
 *
 */

#include "Shots.h"

#include <stdio.h>
#include <stdlib.h>

Shot *create_new_shot(Coord tower, Gem gem) {
    Shot *shot = malloc(sizeof(Shot));
    if (!shot) {
        perror("Crash on shot allocation");
        exit(EXIT_FAILURE);
    }
    *shot = (Shot){.position = coord_to_center_position(tower), .source = gem};
    return shot;
}

void free_shots(ShotList *shots) {
    Shot *shot = LIST_FIRST(shots), *next_s;
    while (shot != NULL) {
        next_s = LIST_NEXT(shot, entries);
        free_shot(shot);
        shot = next_s;
    }
    LIST_INIT(shots);
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
        .x = (target.x - shot->position.x) / dist,
        .y = (target.y - shot->position.y) / dist,
    };
    shot->position = get_new_position(shot->position, travel, vec);
}
