#include <stdlib.h>
#include <time.h>

#include "Events.h"
#include "Game.h"
#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Time.h"

// returns the current user action from the `event` and `action` given.
UserAction get_user_action(UserAction current_action, Event event,
                           WindowInfo win) {
    if (current_action == NO_ACTION) {
        if (event.type == CLICK) {
            if (is_click_in_button(event.mouse, win.new_tower)) {
                return NEW_TOWER;
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
    Game game;
    Timestamp timetp;
    Monster *monster;
    double itvl;
    Event event = (Event){NOEVENT, (Coord){0, 0}};
    UserAction action = NO_ACTION;

    game.map = generate_map();
    game.mana = init_mana();
    timetp = time_future(2.0);  // TODO time
    monster = create_new_monster(game.map, 1, 10, timetp);
    itvl = 0.017;  // TODO time

    WindowInfo win = init_graphic();
    clear_window();
    draw_game(game, action, &win);

    while ((event = get_events()).type != QUIT) {
        action = get_user_action(action, event, win);
        if (action == ADD_TOWER)
            add_tower(&game, (Coord){event.mouse.col / CELL_SIZE,
                                     event.mouse.line / CELL_SIZE});
        draw_game(game, action, &win);
        draw_monster(*monster);
        refresh();

        move_monster(game.map, monster,
                     itvl);              // retrouver l'ellapsed proprement
        wait_milliseconds(itvl * 1000);  // TODO time
        // wait according to framerate serait mieux, non ?
    }
    quit();

    return 0;
}