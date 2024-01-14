#include <stdlib.h>
#include <time.h>

#include "Action.h"
#include "Events.h"
#include "Game.h"
#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Timer.h"
#include "Waves.h"

int main(void) {
    Timestamp cur_time;
    Game game;
    Event event;
    UserAction action;
    WindowInfo win;

    srand(time(NULL));

    game = init_game();
    event = (Event){NOEVENT, (Coord){0, 0}};
    action = NO_ACTION;
    win = init_graphic();
    cur_time = time_now();

    draw_game(&game, action, &win);

    while ((event = get_events()).type != QUIT) {
        if (game.defeat)
            continue;

        action = get_user_action(action, event, win);
        perform_user_action(&action, event, &game, &win);

        update_game(&game, cur_time);
        cur_time = time_now();

        draw_game(&game, action, &win);
        refresh();

        wait_framerate();
    }
    quit();

    return 0;
}
