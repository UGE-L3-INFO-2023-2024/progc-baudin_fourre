/**
 * @file Display_Button.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to create and dipslay the buttons needed in
 * the game using the MLV library
 * @date 2024-01-12
 *
 */

#include "Display_Buttons.h"

#include "Color.h"
#include "Display_Map.h"
#include "Graphic_Utils.h"
#include "Inventory.h"
#include "Window.h"
#include <MLV/MLV_text.h>

// draws the add gem button in the Square `s`, with a current level of
// `cur_level`
static void draw_add_gem_button(WindowInfo *win) {
    char gem_level[5] = {0};
    Square s = win->new_gem;
    snprintf(gem_level, 4, "%d", win->new_gem_level);
    draw_square(s, BKGD_COLOR);
    draw_gem_color_in_square(s, MLV_COLOR_CYAN);
    win->dec_gem_level =
        new_square(s.x, s.y + s.size + s.size / 6, s.size * 2 / 10);
    win->inc_gem_level = new_square(
        s.x + s.size * 8 / 10, s.y + s.size + s.size / 6, s.size * 2 / 10),
    MLV_draw_text_box_with_font(win->dec_gem_level.x,
                                win->dec_gem_level.y,
                                win->dec_gem_level.size,
                                win->dec_gem_level.size,
                                "<",
                                win->right_bar_font,
                                1,
                                TRANSPARANT,
                                MLV_COLOR_BLACK,
                                TRANSPARANT,
                                MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER,
                                MLV_VERTICAL_CENTER);
    MLV_draw_text_box_with_font(s.x + s.size * 2 / 10,
                                s.y + s.size + s.size / 10,
                                s.size * 6 / 10,
                                s.size / 3,
                                gem_level,
                                win->right_bar_font,
                                1,
                                TRANSPARANT,
                                MLV_COLOR_BLACK,
                                TRANSPARANT,
                                MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER,
                                MLV_VERTICAL_CENTER);
    MLV_draw_text_box_with_font(win->inc_gem_level.x,
                                win->inc_gem_level.y,
                                win->inc_gem_level.size,
                                win->inc_gem_level.size,
                                ">",
                                win->right_bar_font,
                                1,
                                TRANSPARANT,
                                MLV_COLOR_BLACK,
                                TRANSPARANT,
                                MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER,
                                MLV_VERTICAL_CENTER);
}

// draws the fuse_gem_button is the right bar
static void draw_fuse_gem_button(WindowInfo win) {
    Square s = win.fuse_gem;
    int size = RIGHT_BAR_COLS * win.cell_size * 2 / 10;
    draw_square(s, BKGD_COLOR);

    s.size = RIGHT_BAR_COLS * win.cell_size * 3 / 20;
    s.y += size * 1 / 10;
    draw_gem_color_in_square(s, MLV_rgba(0, 255, 255, 150));
    s.x += size * 5 / 20;
    draw_gem_color_in_square(s, MLV_rgba(160, 32, 240, 150));
}

// draw the new tower button in the Square `s`
static void draw_new_tower_button(Square s) {
    draw_tower_in_square(s);
}

// draws the buttons of the right bar
void draw_top_buttons(WindowInfo *win) {
    win->new_tower = new_square(MAP_WIDTH * win->cell_size
                                    + RIGHT_BAR_COLS * win->cell_size * 1 / 10,
                                MAP_HEIGHT * win->cell_size * 1 / 10,
                                RIGHT_BAR_COLS * win->cell_size * 2 / 10);
    draw_new_tower_button(win->new_tower);
    win->new_gem = new_square(MAP_WIDTH * win->cell_size
                                  + RIGHT_BAR_COLS * win->cell_size * 4 / 10,
                              MAP_HEIGHT * win->cell_size * 1 / 10,
                              RIGHT_BAR_COLS * win->cell_size * 2 / 10);
    draw_add_gem_button(win);
    win->fuse_gem = new_square(MAP_WIDTH * win->cell_size
                                   + RIGHT_BAR_COLS * win->cell_size * 7 / 10,
                               MAP_HEIGHT * win->cell_size * 1 / 10,
                               RIGHT_BAR_COLS * win->cell_size * 2 / 10);
    draw_fuse_gem_button(*win);

    win->increase_mana_level = new_square((MAP_WIDTH * win->cell_size) * 4 / 5,
                                          win->cell_size * 1 / 4,
                                          win->cell_size * 1 / 2);
    MLV_draw_text_box(win->increase_mana_level.x,
                      win->increase_mana_level.y,
                      win->increase_mana_level.length,
                      win->increase_mana_level.size,
                      "+",
                      0,
                      MLV_COLOR_BLACK,
                      MLV_COLOR_BLACK,
                      PATH_COLOR,
                      MLV_TEXT_CENTER,
                      MLV_HORIZONTAL_CENTER,
                      MLV_VERTICAL_CENTER);
}

// Returns the square surrounding the gem of of index `index` in the `inventory`
static Square
get_inventory_gem(int index, WindowInfo win) {
    int size = RIGHT_BAR_COLS * win.cell_size * 2 / 10;
    int x = MAP_WIDTH * win.cell_size + RIGHT_BAR_COLS * win.cell_size / 10
            + size * (index % INVENTORY_COLS);
    int y =
        MAP_HEIGHT * win.cell_size * 7 / 20 + size * (index / INVENTORY_COLS);
    return new_square(x, y, size);
}

// draw the `inventory` in the right bar, drawing the selected gem if there's
// one
void draw_inventory(Inventory inventory, WindowInfo *win) {
    Square s_gem;
    MLV_draw_text_box_with_font(MAP_WIDTH * win->cell_size + 1,
                                MAP_HEIGHT * win->cell_size * 3 / 10,
                                RIGHT_BAR_COLS * win->cell_size,
                                MAP_HEIGHT * win->cell_size * 1 / 30,
                                "Inventory:",
                                win->right_bar_font,
                                0,
                                TRANSPARANT,
                                MLV_COLOR_BLACK,
                                TRANSPARANT,
                                MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER,
                                MLV_VERTICAL_CENTER);
    Square s = (Square){
        MAP_WIDTH * win->cell_size + RIGHT_BAR_COLS * win->cell_size * 1 / 10,
        MAP_HEIGHT * win->cell_size * 7 / 20,
        RIGHT_BAR_COLS * win->cell_size * 8 / 10,
        (s.size / INVENTORY_COLS) * (INVENTORY_SIZE / INVENTORY_COLS)};
    win->inventory = s;
    for (int i = 0; i < inventory.size; i++) {
        s_gem = get_inventory_gem(i, *win);
        draw_gem_in_square(s_gem, inventory.gems[i], win->right_bar_font);
    }
    if (win->selected_gem >= 0 && win->selected_gem < inventory.size)
        draw_gem_color_in_square(
            get_inventory_gem(win->selected_gem, *win),
            SELECTED_COLOR);
}
