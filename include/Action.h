/**
 * @file Action.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing to create and manage actions retrieved
 * from the user
 * @date 2024-01-14
 *
 */

#ifndef __ACTION_H__
#define __ACTION_H__

#include "Events.h"
#include "Game.h"
#include "Window.h"

// Enumerates the various possible actions of the user
typedef enum {
    NO_ACTION,
    NEW_TOWER,
    ADD_TOWER,
    FUSE_GEM,
    NEW_GEM,
    ADD_ACTIVEGEM,
    INC_GEM_LEVEL,
    DEC_GEM_LEVEL,
    SELECT_GEM,
    WAIT_TOWER,
    NEW_WAVE,
    REMOVE_ACTIVEGEM,
    INC_MANA_LEVEL,
    SELECT_FUSE_GEM,
    WAIT_FUSE_GEM,
    WAIT_SECOND_FUSE_GEM,
} UserAction;

/**
 * @brief Get the user action object
 *
 * @param previous_action the UserAction of the game, before the present, from
 * which the current UserAction will depend
 * @param event Event retrieved from which to get the corresponding UserAction
 * @param win WindowInfo containing information on the current window
 * @return UserAction
 */
UserAction
get_user_action(UserAction previous_action, Event event, const WindowInfo *win);

/**
 * @brief Performs the correct action on the `game`, depending on the current
 * `action`
 *
 * @param action adress of the UserAction previously retrieved
 * @param event the Event previously retrieved
 * @param game Address of the current Game to modify
 * @param win Address of the WindowInfo containing information on the current
 * window
 */
void perform_user_action(UserAction *action,
                         Event event,
                         Game *game,
                         WindowInfo *win);

#endif // __ACTION_H__
