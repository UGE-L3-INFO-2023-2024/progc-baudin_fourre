#include "Graphic.h"

#include <MLV/MLV_all.h>

#include "Game.h"
#include "Map.h"

// Initializes the graphic window
void init_graphic(void) {
    MLV_create_window("Test", "", MAP_WIDTH * CELL_SIZE + 2, MAP_HEIGHT * CELL_SIZE + 2);
}

// Draw a blank grid
void draw_grid(void) {
    for (int i = 0; i <= MAP_WIDTH; i++) {
        MLV_draw_filled_rectangle(i * CELL_SIZE, 0, 2, MAP_HEIGHT * CELL_SIZE, MLV_COLOR_BLACK);
    }
    for (int j = 0; j <= MAP_HEIGHT; j++) {
        MLV_draw_filled_rectangle(0, j * CELL_SIZE, MAP_WIDTH * CELL_SIZE, 2, MLV_COLOR_BLACK);
    }
}

// Clears the window
void clear_window(void) {
    MLV_draw_filled_rectangle(0, 0, MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE, MLV_COLOR_GREY);
}

// Waits `time` seconds
void wait_seconds(int time) {
    MLV_wait_seconds(time);
}

// Refreshes the window with the changes made
void refresh(void) {
    MLV_update_window();
}

// Quits and frees the window
void quit(void) {
    MLV_free_window();
}
