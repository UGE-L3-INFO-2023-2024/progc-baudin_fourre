#include "Graphic.h"

int main(void) {

    init_graphic();
    clear_window();
    draw_grid();
    refresh();
    wait_seconds(5);
    quit();

    return 0;
}