#include "Window.h"
#include "Color.h"
#include "Inventory.h"
#include <MLV/MLV_all.h>

// Initializes the graphic window
void init_graphic(WindowInfo *win) {
    MLV_create_window("Test", "", GAME_WIDTH + RIGHT_BAR_SIZE, GAME_HEIGHT);
    win->right_bar_font = MLV_load_font("fonts/calling.ttf", CELL_SIZE * 0.7);
    win->small_font = MLV_load_font("fonts/calling.ttf", CELL_SIZE * 1 / 2);
    win->new_gem_level = 0;
    win->selected_gem = -1;
    win->nb_towers = 0;
    MLV_change_frame_rate(60);
}

// Clears the window
void clear_window(void) {
    MLV_draw_filled_rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT,
                              MLV_COLOR_LIGHT_GREY);
}

// Waits according to the framerate
void wait_framerate(void) {
    MLV_delay_according_to_frame_rate();
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
