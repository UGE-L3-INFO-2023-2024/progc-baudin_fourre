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

typedef struct {
    short damage_mult;
    int level;
    Hue hue;
    Element type;
} Gem;

typedef struct ActiveGem {
    Gem gem;
    Coord tower;
    Timestamp start_time;
    double shot_interval;
    Timestamp next_shot;
    LIST_ENTRY(ActiveGem) entries;
} ActiveGem;

typedef LIST_HEAD(ActiveGemList, ActiveGem) ActiveGemList;

/**
 * @brief Generates a random pure gem
 *
 * @param level level of the gem to be created
 * @return Gem gem created
 */
Gem generate_pure_gem(int level);

/**
 * @brief Adds the `gem` at the head of the `activegem_list`
 *
 * @param activegem_list address of the head og the list of active gems
 * @param gem Gem to add to the list
 * @param tower Address of the cell where the active gem will be placed
 * @return ActiveGem* the address of the gem created, or NULL if there was an
 * error
 */
ActiveGem *
add_to_activegemslist(ActiveGemList *activegem_list, Gem gem, Coord tower);

/**
 * @brief Frees the space allocated for the list of active gems
 *
 * @param activegems Address of the head of the list of active gems
 */
void free_activegems(ActiveGemList *activegems);

/**
 * @brief Fuses gems `first` and `second` into a new gem of higher level
 *
 * @param first
 * @param second
 * @return Gem the resulting Gem of the fusion
 */
Gem fuse_gems(Gem first, Gem second);

#endif // __GEMS_H__
