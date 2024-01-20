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
void get_string_from_number(unsigned long long number, char *nb_str) {
    char suffix = 0;
    int frac_nb = 0;
    if (number / 1000 > 0) {
        suffix = 'k';
        frac_nb = (int) ((number % 1000) / 100);
        number /= 1000;
        if (number / 1000 > 0) {
            suffix = 'M';
            frac_nb = (int) ((number % 1000) / 100);
            number /= 1000;
            if (number / 1000 > 0) {
                suffix = 'G';
                frac_nb = (int) ((number % 1000) / 100);
                number /= 1000;
            }
        }
        snprintf(nb_str, 31, "%lld,%d%c", number, frac_nb, suffix);
    } else
        snprintf(nb_str, 31, "%lld", number);
}

// Displays the error in the right bar of the window
void display_error(Error error, const WindowInfo *win) {
    if (error.type == NO_ERROR)
        return;

    if (!is_past_time(error.timeout))
        MLV_draw_text_box_with_font(MAP_WIDTH * win->cell_size,
                                    0,
                                    RIGHT_BAR_COLS * win->cell_size,
                                    MAP_HEIGHT * win->cell_size,
                                    get_error_message(error),
                                    win->right_bar_font,
                                    10,
                                    TRANSPARANT,
                                    MLV_COLOR_RED,
                                    TRANSPARANT,
                                    MLV_TEXT_CENTER,
                                    MLV_HORIZONTAL_CENTER,
                                    MLV_VERTICAL_BOTTOM);
    else
        error.type = NO_ERROR;
}

// Draws the mana bar at the top of the window
void draw_mana(Mana mana, const WindowInfo *win) {
    char mana_values[130] = {0};
    snprintf(mana_values, 129, "%.0f/%.0f", mana.quantity, mana.max);
    double filled = mana.quantity / mana.max;
    draw_bar((MAP_WIDTH * win->cell_size) * 1 / 5,
             win->cell_size * 1 / 4,
             (MAP_WIDTH * win->cell_size) * 3 / 5,
             win->cell_size * 1 / 2,
             filled,
             MLV_COLOR_CYAN);

    MLV_draw_text_box((MAP_WIDTH * win->cell_size) * 1 / 5,
                      win->cell_size * 1 / 4,
                      (MAP_WIDTH * win->cell_size) * 3 / 5,
                      win->cell_size * 1 / 2,
                      mana_values,
                      1,
                      MLV_COLOR_BLACK,
                      MLV_COLOR_BLACK,
                      TRANSPARANT,
                      MLV_TEXT_CENTER,
                      MLV_HORIZONTAL_CENTER,
                      MLV_VERTICAL_CENTER);
}

// displays the cost of adding a new tower over the new tower button
static void display_new_tower_cost(const WindowInfo *win) {
    int w = 0, h = 0;
    char cost[32] = {0};
    get_string_from_number((unsigned long long) mana_required_tower(win->nb_towers), cost);
    MLV_get_size_of_text_with_font(cost, &w, &h, win->right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        win->new_tower.x - (w - win->new_tower.size) / 2, // TODO : verifier que * 0.5 était transformable en / 2
        win->new_tower.y - win->new_tower.size * 2 / 5,
        cost,
        win->right_bar_font,
        0,
        TRANSPARANT,
        MLV_COLOR_BLACK,
        TRANSPARANT,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
}

// displays the cost of adding a new gem over the new gem button
static void display_new_gem_cost(const WindowInfo *win) {
    int w = 0, h = 0;
    char cost[32] = {0};
    get_string_from_number((uint64_t) (100 * pow(2, win->new_gem_level)), cost);
    MLV_get_size_of_text_with_font(cost, &w, &h, win->right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        win->new_gem.x - (w - win->new_gem.size) / 2,
        win->new_gem.y - win->new_gem.size * 2 / 5,
        cost,
        win->right_bar_font,
        1,
        TRANSPARANT,
        MLV_COLOR_BLACK,
        TRANSPARANT,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
}

// displays the cost of fusing two gems over the fuse gems button
static void display_fuse_gem_cost(const WindowInfo *win) {
    int w = 0, h = 0;
    MLV_get_size_of_text_with_font("100", &w, &h, win->right_bar_font);
    MLV_draw_adapted_text_box_with_font(
        win->fuse_gem.x - (w - win->fuse_gem.size) / 2,
        win->fuse_gem.y - win->fuse_gem.size * 2 / 5,
        "100",
        win->right_bar_font,
        0,
        TRANSPARANT,
        MLV_COLOR_BLACK,
        TRANSPARANT,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
}

// Displays the costs of the actions of the game at the top of the right bar
// window
void display_cost(const WindowInfo *win) {
    MLV_draw_text_box_with_font(MAP_WIDTH * win->cell_size + 1,
                                MAP_HEIGHT * win->cell_size * 1 / 40,
                                RIGHT_BAR_COLS * win->cell_size,
                                MAP_HEIGHT * win->cell_size * 1 / 30,
                                "Cost:",
                                win->right_bar_font,
                                0,
                                TRANSPARANT,
                                MLV_COLOR_BLACK,
                                TRANSPARANT,
                                MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER,
                                MLV_VERTICAL_CENTER);

    display_new_tower_cost(win);
    display_new_gem_cost(win);
    display_fuse_gem_cost(win);
}

// draws information on the game in the window
void draw_game_information(Timestamp next_wave, const WindowInfo *win) {
    int w = 0, h = 0;
    char time_to_wave[4] = {0};
    MLV_Color color;
    MLV_Color bkgd = MLV_rgba(255, 255, 255, 230);
    int t_left = (int) time_to(next_wave);
    snprintf(time_to_wave, 3, "%d", t_left);

    MLV_get_size_of_text_with_font("Next wave : ", &w, &h, win->right_bar_font);
    MLV_draw_adapted_text_box_with_font(0,
                                        MAP_HEIGHT * win->cell_size - h,
                                        "Next wave : ",
                                        win->right_bar_font,
                                        1,
                                        TRANSPARANT,
                                        MLV_COLOR_BLACK,
                                        bkgd,
                                        MLV_TEXT_CENTER);

    color = t_left >= 25 ? MLV_rgba(100, 100, 100, 255) : MLV_COLOR_BLACK;
    MLV_draw_adapted_text_box_with_font(w,
                                        MAP_HEIGHT * win->cell_size - h,
                                        time_to_wave,
                                        win->right_bar_font,
                                        1,
                                        TRANSPARANT,
                                        color,
                                        bkgd,
                                        MLV_TEXT_CENTER);
}

// Displays that the game is over in the center of the window
void display_game_over(const WindowInfo *win) {
    int w = 0, h = 0;
    MLV_get_size_of_text_with_font("GAME OVER", &w, &h, win->right_bar_font);
    MLV_draw_adapted_text_box_with_font((MAP_WIDTH * win->cell_size - w) / 2,
                                        MAP_HEIGHT * win->cell_size * 0.5 - h,
                                        "GAME OVER",
                                        win->right_bar_font,
                                        1,
                                        TRANSPARANT,
                                        MLV_COLOR_BLACK,
                                        MLV_rgba(255, 255, 255, 230),
                                        MLV_TEXT_CENTER);
}
