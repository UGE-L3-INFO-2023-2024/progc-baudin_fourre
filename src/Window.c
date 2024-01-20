/**
 * @file Window.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to initialize and manage graphic windows of
 * the MLV library
 * @date 2023-12-25
 *
 */

#include "Window.h"
#include "Color.h"
#include "Map.h"
#include <MLV/MLV_all.h>
#include <MLV/MLV_window.h>

// Returns the cell size according to the user desktop size
static void get_cell_size(int *cell_size, int *w, int *h) {
    int w_cell_size, h_cell_size;
    *w = MLV_get_desktop_width();
    *h = MLV_get_desktop_height();
    w_cell_size = *w / (MAP_WIDTH + RIGHT_BAR_COLS);
    h_cell_size = *h / MAP_HEIGHT;
    *cell_size = w_cell_size <= h_cell_size ? w_cell_size : h_cell_size;
}

// Initializes the graphic window
void init_graphic(WindowInfo *win) {
    int w, h;
    get_cell_size(&win->cell_size, &w, &h);
    MLV_create_window("Tower Defense", "", w, h);
    MLV_clear_window(RIGHT_BAR_COLOR);
    win->right_bar_font =
        MLV_load_font("fonts/calling.ttf", win->cell_size * 7 / 10);
    win->small_font =
        MLV_load_font("fonts/calling.ttf", win->cell_size * 1 / 2);
    win->new_gem_level = 0;
    win->selected_gem = -1;
    win->nb_towers = 0;
}

// Clears the window
void clear_window(WindowInfo win) {
    MLV_draw_filled_rectangle(0,
                              0,
                              MAP_WIDTH * win.cell_size,
                              MAP_HEIGHT * win.cell_size,
                              MLV_COLOR_LIGHT_GREY);
}

// Waits `wait_time` seconds to respect the framerate
void wait_framerate(double wait_time) {
    MLV_wait_milliseconds((int) (wait_time * 1000));
}

// Refreshes the window with the changes made
void refresh(void) {
    MLV_update_window();
}

// Quits and frees the window
void quit(WindowInfo *win) {
    MLV_free_font(win->right_bar_font);
    MLV_free_font(win->small_font);
    MLV_free_window();
}
