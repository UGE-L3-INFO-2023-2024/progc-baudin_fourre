#include <stdlib.h>
#include <time.h>

#include "Graphic.h"
#include "Map.h"
#include "Monsters.h"
#include "Time.h"

int main(void) {
    srand(time(NULL));
    Map map = generate_map();
    // Position nest = (Position){map.nest.col, map.nest.line};
    // timestamp timetp = (timestamp){0, 0};
    // Monster *monster = create_new_monster(1, 10, timetp, nest);

    init_graphic();
    clear_window();
    draw_grid();
    draw_path(map);
    // draw_monster(*monster);
    refresh();
    wait_seconds(10);
    quit();

    return 0;
}