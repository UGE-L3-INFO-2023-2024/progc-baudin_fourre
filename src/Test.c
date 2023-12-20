#include <stdlib.h>
#include <time.h>

#include "Events.h"
#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Time.h"

int main(void) {
    srand(time(NULL));
    Game game;
    game.map = generate_map();
    game.mana = init_mana();
    Timestamp timetp = time_future(2.0); // TODO time
    Monster *monster = create_new_monster(game.map, 1, 10, timetp);
    double itvl = 0.017; // TODO time

    WindowInfo win = init_graphic();
    clear_window();
    draw_game(game, win);
    // draw_grid();
    // draw_right_bar(win);
    // draw_mana(game.mana);

    while (get_events() != QUIT) {
        clear_path(game.map);
        draw_path(game.map);
        draw_monster(*monster);
        refresh();

        move_monster(game.map, monster, itvl); // retrouver l'ellapsed proprement
        wait_milliseconds(itvl * 1000); // TODO time
        // wait according to framerate serait mieux, non ?
    }
    quit();

    return 0;
}