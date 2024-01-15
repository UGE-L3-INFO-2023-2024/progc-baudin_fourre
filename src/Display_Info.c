/**
 * @file Display_Info.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to display information (as text) in the window
 * of the game using the MLV library
 * @date 2024-01-12
 *
 */

#include "Display_Info.h"

#include "Color.h"
#include "Error.h"
#include "Mana.h"
#include "Timer.h"
#include "Window.h"
#include <MLV/MLV_all.h>
#include <math.h>

// Returns the shortened string associated to the `number`
void get_string_from_number(uint64_t number, char *nb_str) {
    char suffix = 0;
    uint64_t tmp;
    int float_nb = 0;
    if (number / 1000) {
        suffix = 'k';
        float_nb = (number % 1000) / 100;
        tmp = number / 1000;
        if (tmp / 1000) {
            suffix = 'M';
            float_nb = (tmp % 1000) / 100;
            tmp /= 1000;
            if (tmp / 1000) {
                suffix = 'G';
                float_nb = (tmp % 1000) / 100;
                tmp /= 1000;
            }
        }
        sprintf(nb_str, "%ld,%d%c", tmp, float_nb, suffix);
    } else
        sprintf(nb_str, "%ld", number);
}

// Displays the error in the right bar of the window
void display_error(Error *error, WindowInfo win) {

    if (error->type == NO_ERROR)
        return;

    if (!is_past_time(error->timeout))
        MLV_draw_text_box_with_font(
            MAP_WIDTH * win.cell_size, 0, RIGHT_BAR_COLS * win.cell_size,
            MAP_HEIGHT * win.cell_size, get_error_message(*error),
            win.right_bar_font, 10, TRANSPARANT, MLV_COLOR_RED, TRANSPARANT,
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_BOTTOM);
    else
        error->type = NO_ERROR;
}

// Draws the mana bar at the top of the window
void draw_mana(Mana mana, WindowInfo win) {
    char mana_values[130];
    sprintf(mana_values, "%ld/%ld", mana.quantity, mana.max);
    double filled = (double) mana.quantity / (double) mana.max;
    draw_bar((MAP_WIDTH * win.cell_size) * 1 / 5, win.cell_size * 1 / 4,
             (MAP_WIDTH * win.cell_size) * 3 / 5, win.cell_size * 1 / 2, filled,
             MLV_COLOR_CYAN);

    MLV_draw_text_box(
        (MAP_WIDTH * win.cell_size) * 1 / 5, win.cell_size * 1 / 4,
        (MAP_WIDTH * win.cell_size) * 3 / 5, win.cell_size * 1 / 2, mana_values,
        1, MLV_COLOR_BLACK, MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// displays the cost of adding a new tower over the new tower button
static void display_new_tower_cost(WindowInfo win) {
    int w, h;
    char cost[33];
    get_string_from_number(mana_required_tower(win.nb_towers), cost);
    MLV_get_size_of_text_with_font(cost, &w, &h, win.right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        win.new_tower.x - (w - win.new_tower.size) * 0.5,
        win.new_tower.y - win.new_tower.size * 2 / 5, cost, win.right_bar_font,
        0, TRANSPARANT, MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// displays the cost of adding a new gem over the new gem button
static void display_new_gem_cost(WindowInfo win) {
    int w, h;
    char cost[33];
    get_string_from_number((uint64_t) (100 * pow(2, win.new_gem_level)), cost);
    MLV_get_size_of_text_with_font(cost, &w, &h, win.right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        win.new_gem.x - (w - win.new_gem.size) * 0.5,
        win.new_gem.y - win.new_gem.size * 2 / 5, cost, win.right_bar_font, 1,
        TRANSPARANT, MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// displays the cost of fusing two gems over the fuse gems button
static void display_fuse_gem_cost(WindowInfo win) {
    int w, h;
    MLV_get_size_of_text_with_font("100", &w, &h, win.right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        win.fuse_gem.x - (w - win.fuse_gem.size) * 0.5,
        win.fuse_gem.y - win.fuse_gem.size * 2 / 5, "100", win.right_bar_font,
        0, TRANSPARANT, MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// Displays the costs of the actions of the game at the top of the right bar
// window
void display_cost(WindowInfo win) {
    MLV_draw_text_box_with_font(
        MAP_WIDTH * win.cell_size + 1, MAP_HEIGHT * win.cell_size * 1 / 40,
        RIGHT_BAR_COLS * win.cell_size, MAP_HEIGHT * win.cell_size * 1 / 30,
        "Cost:", win.right_bar_font, 0, TRANSPARANT, MLV_COLOR_BLACK,
        TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);

    display_new_tower_cost(win);
    display_new_gem_cost(win);
    display_fuse_gem_cost(win);
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
        0, MAP_HEIGHT * win.cell_size - h, "Next wave : ", win.right_bar_font,
        1, TRANSPARANT, MLV_COLOR_BLACK, bkgd, MLV_TEXT_CENTER);

    color = t_left >= 25 ? MLV_rgba(100, 100, 100, 255) : MLV_COLOR_BLACK;
    MLV_draw_adapted_text_box_with_font(
        w, MAP_HEIGHT * win.cell_size - h, time_to_wave, win.right_bar_font, 1,
        TRANSPARANT, color, bkgd, MLV_TEXT_CENTER);
}

// Displays that the game is over in the center of the window
void display_game_over(WindowInfo win) {
    int w, h;
    MLV_get_size_of_text_with_font("GAME OVER", &w, &h, win.right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        (MAP_WIDTH * win.cell_size - w) * 0.5,
        MAP_HEIGHT * win.cell_size * 0.5 - h, "GAME OVER", win.right_bar_font,
        1, TRANSPARANT, MLV_COLOR_BLACK, MLV_rgba(255, 255, 255, 230),
        MLV_TEXT_CENTER);
}
