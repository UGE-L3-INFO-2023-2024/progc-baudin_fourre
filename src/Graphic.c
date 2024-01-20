/**
 * @file Graphic.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to display the entirety of the game
 * @date 2023-11-29
 *
 */

#include "Graphic.h"

#include "Action.h"
#include "Color.h"
#include "Display_Buttons.h"
#include "Display_Info.h"
#include "Display_Map.h"
#include "Game.h"
#include "Graphic_Utils.h"
#include "Map.h"
#include "Monsters.h"
#include "Window.h"

// draws a bar on the right of the game window
static void
draw_right_bar(Game *game, UserAction current_action, WindowInfo *win) {
    MLV_draw_filled_rectangle(MAP_WIDTH * win->cell_size,
                              0,
                              RIGHT_BAR_COLS * win->cell_size,
                              MAP_HEIGHT * win->cell_size,
                              RIGHT_BAR_COLOR);
    draw_top_buttons(win);
    draw_inventory(game->inventory, win);
    display_error(game->error, win);
    display_cost(win);
    display_score(win, game->total_damage);
    if (current_action == NEW_TOWER)
        draw_selected_square(win->new_tower);
    if (current_action == WAIT_FUSE_GEM
        || current_action == WAIT_SECOND_FUSE_GEM)
        draw_selected_square(win->fuse_gem);
}

// draws the game int its entirety according the th current UserAction
// `current_action`
void draw_game(Game *game, UserAction current_action, WindowInfo *win) {
    Monster *monster;
    draw_map(&game->map, win->cell_size);
    draw_right_bar(game, current_action, win);
    draw_mana(game->mana, win);
    draw_monsters(game->monsters, &game->map, win->cell_size);
    draw_activegems(game->active_gems, win->cell_size);
    LIST_FOREACH(monster, &game->monsters, entries) {
        draw_shots(monster->shots, win->cell_size);
    }
    draw_game_information(game->next_wave, win);
    if (game->defeat)
        display_game_over(win);
}
