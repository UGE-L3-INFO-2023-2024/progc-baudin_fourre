#include "Action.h"
#include "Events.h"
#include "Game.h"
#include "Window.h"

// Returns the current user action from the `event` when there was previously no
// action
static UserAction get_action_no_action(Event event, WindowInfo win) {
    if (event.type == CLICK) {
        if (is_click_in_button(event.mouse, win.new_tower))
            return NEW_TOWER;
        if (is_click_in_button(event.mouse, win.new_gem))
            return NEW_GEM;
        if (is_click_in_button(event.mouse, win.inc_gem_level))
            return INC_GEM_LEVEL;
        if (is_click_in_button(event.mouse, win.dec_gem_level))
            return DEC_GEM_LEVEL;
        if (is_click_in_button(event.mouse, win.inventory))
            return SELECT_GEM;
        if (is_click_in_button(event.mouse, win.increase_mana_level))
            return INC_MANA_LEVEL;
        if (is_click_in_game(event.mouse))
            return REMOVE_ACTIVEGEM;
        if (is_click_in_button(event.mouse, win.fuse_gem))
            return WAIT_FUSE_GEM;
    }
    if (event.type == SPACE)
        return NEW_WAVE;
    return NO_ACTION;
}

// Returns the current user action from the `event` when the user has clicked on
// the new tower button
static UserAction get_action_new_tower(Event event) {
    if (event.type == CLICK)
        return ADD_TOWER;
    if (event.type == ESCAPE)
        return NO_ACTION;
    return NEW_TOWER;
}

// Returns the current user action from the `event` when the user has selected a
// gem to add to a tower
static UserAction get_action_wait_tower(Event event) {
    if (event.type == CLICK) {
        return ADD_ACTIVEGEM;
    }
    if (event.type == ESCAPE)
        return NO_ACTION;
    return WAIT_TOWER;
}

// Returns the current user action from the `event` when the  user has clicked
// on the fuse gem button
static UserAction get_action_wait_fuse_gem(Event event, WindowInfo win) {
    if (event.type == CLICK) {
        if (is_click_in_button(event.mouse, win.inventory))
            return SELECT_FUSE_GEM;
        else
            return NO_ACTION;
    }
    if (event.type == ESCAPE)
        return NO_ACTION;
    return WAIT_FUSE_GEM;
}

// Returns the current user action from the `event` when the user has selected a
// first gem to fuse
static UserAction get_action_wait_second_fuse_gem(Event event, WindowInfo win) {
    if (event.type == CLICK) {
        if (is_click_in_button(event.mouse, win.inventory))
            return FUSE_GEM;
        else
            return NO_ACTION;
    }
    if (event.type == ESCAPE)
        return NO_ACTION;
    return WAIT_SECOND_FUSE_GEM;
}

// returns the current user action from the `event` and `action` given.
UserAction get_user_action(UserAction previous_action, Event event,
                           WindowInfo win) {
    if (previous_action == NO_ACTION) {
        return get_action_no_action(event, win);
    }

    if (previous_action == NEW_TOWER) {
        return get_action_new_tower(event);
    }

    if (previous_action == WAIT_TOWER) {
        return get_action_wait_tower(event);
    }

    if (previous_action == WAIT_FUSE_GEM) {
        return get_action_wait_fuse_gem(event, win);
    }

    if (previous_action == WAIT_SECOND_FUSE_GEM) {
        return get_action_wait_second_fuse_gem(event, win);
    }

    return previous_action;
}

// Performs the correct action on the `game`, depending on the current `action`
void perform_user_action(UserAction *action, Event event, Game *game,
                         WindowInfo *win) {
    static int selected_gem;
    Coord tower;
    switch (*action) {
        case NO_ACTION:
            win->selected_gem = -1;
            break;
        case ADD_TOWER:
            add_tower(game, win,
                      (Coord){event.mouse.col / CELL_SIZE,
                              event.mouse.line / CELL_SIZE});
            *action = NO_ACTION;
            break;
        case NEW_GEM:
            new_gem(game, win->new_gem_level);
            *action = NO_ACTION;
            break;
        case INC_GEM_LEVEL:
            increase_new_gem_level(win);
            *action = NO_ACTION;
            break;
        case DEC_GEM_LEVEL:
            decrease_new_gem_level(win);
            *action = NO_ACTION;
            break;
        case INC_MANA_LEVEL:
            increase_mana_level(&game->mana, &game->error);
            *action = NO_ACTION;
            break;
        case SELECT_GEM:
            win->selected_gem = get_selected_inventory_gem(event, *win);
            *action = WAIT_TOWER;
            break;
        case SELECT_FUSE_GEM:
            win->selected_gem = get_selected_inventory_gem(event, *win);
            if (win->selected_gem >= game->inventory.size)
                *action = WAIT_FUSE_GEM;
            else
                *action = WAIT_SECOND_FUSE_GEM;
            break;
        case FUSE_GEM:
            selected_gem = get_selected_inventory_gem(event, *win);
            if (selected_gem >= game->inventory.size
                || selected_gem == win->selected_gem)
                *action = WAIT_SECOND_FUSE_GEM;
            else {
                game_fuse_gems(game, win->selected_gem, selected_gem);
                *action = NO_ACTION;
            }
            break;
        case ADD_ACTIVEGEM:
            add_activegem(game, *win,
                          (Coord){event.mouse.col / CELL_SIZE,
                                  event.mouse.line / CELL_SIZE});
            *action = NO_ACTION;
            break;
        case REMOVE_ACTIVEGEM:
            tower = (Coord){event.mouse.col / CELL_SIZE,
                            event.mouse.line / CELL_SIZE};
            if (game->map.cells[CI(tower)].type == TOWER)
                remove_activegem(game, tower);
            *action = NO_ACTION;
            break;
        case NEW_WAVE:
            add_wave(game);
            *action = NO_ACTION;
            break;
        default:
            break;
    }
}
