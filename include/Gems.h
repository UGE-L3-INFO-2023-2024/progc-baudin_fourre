/**
 * @file Gems.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of Gems and
 * ActiveGems
 * @date 2023-11-16
 *
 */

#ifndef __GEMS_H__
#define __GEMS_H__

#include "Element.h"
#include "Queue.h"
#include "Timer.h"
#include "Utils.h"

/**
 * @brief Structure representing a gem
 */
typedef struct {
    short damage_mult;
    int level;
    Hue hue;
    Element type;
} Gem;

/**
 * @brief Structure representing an active gem (a gem that has been placed on a
 * tower)
 */
typedef struct ActiveGem {
    Gem gem;
    Coord tower;
    Timestamp start_time;
    double shot_interval;
    Timestamp next_shot;
    LIST_ENTRY(ActiveGem) entries;
} ActiveGem;

/**
 * @brief Structure representing a linked list of active gems
 */
typedef LIST_HEAD(ActiveGemList, ActiveGem) ActiveGemList;

/**
 * @brief Generates a random pure gem
 *
 * @param level level of the gem to be created
 * @return Gem gem created
 */
Gem generate_pure_gem(int level);

/**
 * @brief Creates an active gem from a gem and adds it to the list of active
 * gems
 *
 * @param activegem_list the list of active gems
 * @param gem the gem to add to the list
 * @param tower the cell where the active gem will be placed
 * @return the new active gem allocated
 */
ActiveGem *
add_to_activegemslist(ActiveGemList *activegem_list, Gem gem, Coord tower);

/**
 * @brief Frees the space allocated for the list of active gems
 *
 * @param activegems the list of active gems
 */
void free_activegems(ActiveGemList *activegems);

/**
 * @brief Fuses gems `first` and `second` into a new gem of higher level
 *
 * @param first the first gem to fusion
 * @param second the second gem to fustion
 * @return the resulting gem of the fusion
 */
Gem fuse_gems(Gem first, Gem second);

#endif // __GEMS_H__
