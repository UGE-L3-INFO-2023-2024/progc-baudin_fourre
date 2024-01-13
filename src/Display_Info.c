#include "Display_Info.h"

#include "Color.h"
#include "Error.h"
#include "Mana.h"
#include "Timer.h"
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
void draw_mana(Mana mana, WindowInfo win) {
    char mana_values[130];
    sprintf(mana_values, "%ld/%ld", mana.quantity, mana.max);
    double filled = (double) mana.quantity / (double) mana.max;
    draw_bar((MAP_WIDTH * CELL_SIZE) * 1 / 5, CELL_SIZE * 1 / 4,
             (MAP_WIDTH * CELL_SIZE) * 3 / 5, CELL_SIZE * 1 / 2, filled,
             MLV_COLOR_CYAN);

    MLV_draw_text_box((MAP_WIDTH * CELL_SIZE) * 1 / 5, CELL_SIZE * 1 / 4,
                      (MAP_WIDTH * CELL_SIZE) * 3 / 5, CELL_SIZE * 1 / 2,
                      mana_values, 1, MLV_COLOR_BLACK, MLV_COLOR_BLACK,
                      TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
                      MLV_VERTICAL_CENTER);
}

// draws information on the game in the window
void draw_game_information(Timestamp next_wave, WindowInfo win) {
    int w, h;
    char time_to_wave[3];
    MLV_Color color;
    MLV_Color bkgd = MLV_rgba(255, 255, 255, 230);
    int t_left = (int) time_to(next_wave);
    sprintf(time_to_wave, "%d", t_left);

    MLV_get_size_of_text_with_font("Next wave : ", &w, &h, win.right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        0, MAP_HEIGHT * CELL_SIZE - h, "Next wave : ", win.right_bar_font, 1,
        TRANSPARANT, MLV_COLOR_BLACK, bkgd, MLV_TEXT_CENTER);

    color = t_left >= 25 ? MLV_rgba(100, 100, 100, 255) : MLV_COLOR_BLACK;
    MLV_draw_adapted_text_box_with_font(
        w, MAP_HEIGHT * CELL_SIZE - h, time_to_wave, win.right_bar_font, 1,
        TRANSPARANT, color, bkgd, MLV_TEXT_CENTER);
}
