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
    timestamp timetp = (timestamp){0, 0};
    Monster *monster = create_new_monster(game.map, 1, 10, timetp);
    interval itvl = (interval){0, 17};

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

        move_monster(game.map, monster, itvl);
        wait_milliseconds(itvl.tv_usec);
    }
    quit();

    return 0;
}