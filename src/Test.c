#include <stdlib.h>
#include <time.h>

#include "Events.h"
#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Time.h"

int main(void) {
    srand(time(NULL));
    Direction dir;
    Map map = generate_map();
    timestamp timetp = (timestamp){0, 0};
    Monster *monster = create_new_monster(map, 1, 10, timetp);
    interval itvl = (interval){0, 17};

    init_graphic();
    clear_window();
    draw_grid();

    while (get_events() != QUIT) {
        clear_path(map);
        draw_path(map);
        draw_monster(*monster);
        refresh();

        move_monster(map, monster, itvl);
        wait_milliseconds(itvl.tv_usec);
    }
    quit();

    return 0;
}