#include <stdlib.h>
#include <time.h>

#include "Events.h"
#include "Game.h"
#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Time.h"
#include "Waves.h"

// returns the current user action from the `event` and `action` given.
UserAction get_user_action(UserAction current_action, Event event,
                           WindowInfo win) {
    if (current_action == NO_ACTION) {
        if (event.type == CLICK) {
            if (is_click_in_button(event.mouse, win.new_tower)) {
                return NEW_TOWER;
            }
            if (is_click_in_button(event.mouse, win.new_gem)) {
                return NEW_GEM;
            }
            if (is_click_in_button(event.mouse, win.inc_gem_level)) {
                return INC_GEM_LEVEL;
            }
            if (is_click_in_button(event.mouse, win.dec_gem_level)) {
                return DEC_GEM_LEVEL;
            }
        }
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
    return NO_ACTION;
}

int main(void) {
    srand(time(NULL));
    Game game = init_game();
    Timestamp cur_time;
    Event event = (Event){NOEVENT, (Coord){0, 0}};
    UserAction action = NO_ACTION;
    WindowInfo win = init_graphic();

    clear_window();
    draw_game(game, action, &win);
    if (!wave_generation(&(game.monsters), game.map))
        return 1;

    cur_time = time_now();
    while ((event = get_events()).type != QUIT) {
        action = get_user_action(action, event, win);
        if (action == ADD_TOWER)
            add_tower(&game, (Coord){event.mouse.col / CELL_SIZE,
                                     event.mouse.line / CELL_SIZE});
        if (action == NEW_GEM)
            new_gem(&game, win.new_gem_level);
        if (action == INC_GEM_LEVEL)
            increase_new_gem_level(&win);
        if (action == DEC_GEM_LEVEL)
            decrease_new_gem_level(&win);

        draw_game(game, action, &win);
        draw_monsters(game.monsters, game.map);
        refresh();

        move_monsters(&game, cur_time);
        cur_time = time_now();
        wait_framerate();  // TODO time
    }
    quit();

    return 0;
}