/**
 * @file Shots.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of Shots and
 * ShotLists
 * @date 2024-11-16
 *
 */

#ifndef __SHOTS_H__
#define __SHOTS_H__

#include "Gems.h"

#include <stdbool.h>

/**
 * @brief Structure representing a shot
 */
typedef struct Shot {
    Position position;
    Gem source;
    LIST_ENTRY(Shot) entries;
} Shot;

/**
 * @brief Structure representing a list of shots
 */
typedef LIST_HEAD(ShotList, Shot) ShotList;

/**
 * @brief Creates a new shot
 *
 * @param tower the position of the tower that shot
 * @param gem the gem of the tower that shot
 * @return the new shot allocated
 */
Shot *create_new_shot(Coord tower, Gem gem);

/**
 * @brief Empty the shot list and free theses shots
 *
 * @param shots the shot list to free
 */
void free_shots(ShotList *shots);

/**
 * @brief Frees a shot
 *
 * @param shot the shot to free
 */
void free_shot(Shot *shot);

/**
 * @brief Moves a shot to a target position
 *
 * @param shot the shot to move
 * @param target the target position
 * @param time_elapsed the time elapsed since the last move
 */
void move_shot(Shot *shot, Position target, double time_elapsed);

#endif // __SHOTS_H__
