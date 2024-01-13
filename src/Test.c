#include <stdlib.h>
#include <time.h>

#include "Events.h"
#include "Game.h"
#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Timer.h"
#include "Waves.h"

// returns the current user action from the `event` and `action` given.
UserAction get_user_action(UserAction current_action, Event event,
                           WindowInfo win) {
    if (current_action == NO_ACTION) {
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

    if (current_action == NEW_TOWER) {
        if (event.type == CLICK)
            return ADD_TOWER;
        if (event.type == ESCAPE)
            return NO_ACTION;
        else
            return NEW_TOWER;
    }

    if (current_action == WAIT_TOWER) {
        if (event.type == CLICK) {
            return ADD_ACTIVEGEM;
        }
        if (event.type == ESCAPE)
            return NO_ACTION;
    }

    if (current_action == WAIT_FUSE_GEM) {
        if (event.type == CLICK) {
            if (is_click_in_button(event.mouse, win.inventory))
                return SELECT_FUSE_GEM;
            // if (is_click_in_button(event.mouse, win.fuse_gem))
            else
                return NO_ACTION;
        }
        if (event.type == ESCAPE)
            return NO_ACTION;
    }

    if (current_action == WAIT_SECOND_FUSE_GEM) {
        if (event.type == CLICK) {
            if (is_click_in_button(event.mouse, win.inventory))
                return FUSE_GEM;
            // if (is_click_in_button(event.mouse, win.fuse_gem))
            else
                return NO_ACTION;
        }
        if (event.type == ESCAPE)
            return NO_ACTION;
    }

    return current_action;
}

int main(void) {
    srand(time(NULL));
    Game game = init_game();
    Timestamp cur_time;
    Event event = (Event){NOEVENT, (Coord){0, 0}};
    UserAction action = NO_ACTION;
    WindowInfo win = init_graphic();
    Coord tower;
    int selected_gem;

    clear_window();
    draw_game(game, action, &win);

    cur_time = time_now();
    while ((event = get_events()).type != QUIT && !game.defeat) {
        action = get_user_action(action, event, win);

        switch (action) {
            case NO_ACTION:
                win.selected_gem = -1;
                break;
            case ADD_TOWER:
                add_tower(&game, (Coord){event.mouse.col / CELL_SIZE,
                                         event.mouse.line / CELL_SIZE});
                action = NO_ACTION;
                break;
            case NEW_GEM:
                new_gem(&game, win.new_gem_level);
                action = NO_ACTION;
                break;
            case INC_GEM_LEVEL:
                increase_new_gem_level(&win);
                action = NO_ACTION;
                break;
            case DEC_GEM_LEVEL:
                decrease_new_gem_level(&win);
                action = NO_ACTION;
                break;
            case INC_MANA_LEVEL:
                increase_mana_level(&game.mana, &game.error);
                action = NO_ACTION;
                break;
            case SELECT_GEM:
                win.selected_gem = get_selected_inventory_gem(event, win);
                action = WAIT_TOWER;
                break;
            case SELECT_FUSE_GEM:
                win.selected_gem = get_selected_inventory_gem(event, win);
                if (win.selected_gem >= game.inventory.size)
                    action = WAIT_FUSE_GEM;
                else
                    action = WAIT_SECOND_FUSE_GEM;
                break;
            case FUSE_GEM:
                selected_gem = get_selected_inventory_gem(event, win);
                if (selected_gem >= game.inventory.size
                    || selected_gem == win.selected_gem)
                    action = WAIT_SECOND_FUSE_GEM;
                else {
                    game_fuse_gems(&game, win.selected_gem, selected_gem);
                    action = NO_ACTION;
                }
                break;
            case ADD_ACTIVEGEM:
                add_activegem(&game, win,
                              (Coord){event.mouse.col / CELL_SIZE,
                                      event.mouse.line / CELL_SIZE});
                action = NO_ACTION;
                break;
            case REMOVE_ACTIVEGEM:
                tower = (Coord){event.mouse.col / CELL_SIZE,
                                event.mouse.line / CELL_SIZE};
                if (game.map.cells[CI(tower)].type == TOWER)
                    remove_activegem(&game, tower);
                action = NO_ACTION;
                break;
            case NEW_WAVE:
                add_wave(&game);
                action = NO_ACTION;
                break;
            default:
                break;
        }

        draw_game(game, action, &win);
        refresh();

        if (is_past_time(game.next_wave))
            add_wave(&game);
        move_monsters(&game, cur_time);
        move_shots(&game, cur_time);
        activegems_fire(&game);
        damage_monsters(&game);
        cur_time = time_now();
        wait_framerate();
    }
    quit();

    return 0;
}
