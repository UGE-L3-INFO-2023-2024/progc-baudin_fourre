#include "Window.h"

// Initializes the graphic window
WindowInfo init_graphic(void) {
    WindowInfo win;
    MLV_create_window("Test", "", GAME_WIDTH + RIGHT_BAR_SIZE, GAME_HEIGHT);
    win.right_bar_font = MLV_load_font("fonts/calling.ttf", CELL_SIZE * 7 / 10);
    win.small_font = MLV_load_font("fonts/calling.ttf", CELL_SIZE * 1 / 2);
    win.new_gem_level = 0;
    win.selected_gem = -1;
    MLV_change_frame_rate(60);
    return win;
}

// Creates and returns a new Square structure with the given arguments
Square new_square(int x, int y, int size) {
    return (Square){x, y, size, size};
}

// Clears the window
void clear_window(void) {
    MLV_draw_filled_rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT,
                              MLV_COLOR_LIGHT_GREY);
}

// Waits according to the framerate
void wait_framerate() {
    MLV_delay_according_to_frame_rate();
}

// Refreshes the window with the changes made
void refresh(void) {
    MLV_update_window();
}

// Quits and frees the window
void quit(void) {
    MLV_free_window();
}
