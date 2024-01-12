#include "Display_Info.h"

#include "Color.h"
#include "Error.h"
#include "Mana.h"
#include "Window.h"
#include <MLV/MLV_all.h>

// Displays the error in the right bar of the window
void display_error(Error *error, WindowInfo win) {

    if (error->type == NO_ERROR)
        return;

    if (!is_past_time(error->timeout))
        MLV_draw_text_box_with_font(RIGHT_BAR_X, 0, RIGHT_BAR_SIZE, GAME_HEIGHT,
                                    get_error_message(*error),
                                    win.right_bar_font, 10, TRANSPARANT,
                                    MLV_COLOR_RED, TRANSPARANT, MLV_TEXT_CENTER,
                                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_BOTTOM);
    else
        error->type = NO_ERROR;
}

// Draws the mana bar at the top of the window
void draw_mana(Mana mana, WindowInfo *win) {
    char mana_values[12];
    sprintf(mana_values, "%d/%d", mana.quantity, mana.max);

    double filled = (double) mana.quantity / (double) mana.max;
    draw_bar((MAP_WIDTH * CELL_SIZE) * 1 / 5, CELL_SIZE * 1 / 4,
             (MAP_WIDTH * CELL_SIZE) * 3 / 5, CELL_SIZE * 1 / 2, filled,
             MLV_COLOR_CYAN);
    win->increase_mana_level = new_square((MAP_WIDTH * CELL_SIZE) * 4 / 5,
                                          CELL_SIZE * 1 / 4, CELL_SIZE * 1 / 2);
    MLV_draw_text_box(win->increase_mana_level.x, win->increase_mana_level.y,
                      win->increase_mana_level.length,
                      win->increase_mana_level.size, "+", 0, MLV_COLOR_BLACK,
                      MLV_COLOR_BLACK, PATH_COLOR, MLV_TEXT_CENTER,
                      MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box((MAP_WIDTH * CELL_SIZE) * 1 / 5, CELL_SIZE * 1 / 4,
                      (MAP_WIDTH * CELL_SIZE) * 3 / 5, CELL_SIZE * 1 / 2,
                      mana_values, 1, MLV_COLOR_BLACK, MLV_COLOR_BLACK,
                      TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
                      MLV_VERTICAL_CENTER);
}
