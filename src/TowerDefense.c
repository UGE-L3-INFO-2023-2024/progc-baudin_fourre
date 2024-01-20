/**
 * @file TowerDefense.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Main loop of the game, retrieving the events from the user, performing
 * the associated action, and updating the game, in terms of structure and
 * graphic. This module is where the Game and the graphic window are intialized
 * and freed.
 * @date 2024-01-14
 *
 */

#include <stdlib.h>
#include <time.h>

#include "Action.h"
#include "Events.h"
#include "Game.h"
#include "Graphic.h"
#include "Timer.h"
#include "Window.h"

int main(void) {
    Timestamp cur_time, begin_frame_time;
    double wait_time;
    Game game;
    Event event;
    UserAction action;
    WindowInfo win;

    srand(time(NULL));

    game = init_game();
    event = (Event){NOEVENT, (Coord){0, 0}};
    action = NO_ACTION;
    init_graphic(&win);
    cur_time = time_now();

    draw_game(&game, action, &win);

    while ((event = get_events()).type != QUIT) {
        if (game.defeat)
            continue;

        begin_frame_time = time_now();
        action = get_user_action(action, event, &win);
        perform_user_action(&action, event, &game, &win);

        update_game(&game, cur_time);
        cur_time = time_now();

        draw_game(&game, action, &win);
        refresh();

        wait_time = elapsed_since(begin_frame_time);
        wait_framerate(1.0 / 60 - wait_time);
    }
    free_game(&game);
    quit(&win);

    return 0;
}
