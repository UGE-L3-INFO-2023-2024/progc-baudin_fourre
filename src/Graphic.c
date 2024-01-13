#include "Graphic.h"

#include <MLV/MLV_all.h>
#include <assert.h>
#include <math.h>

#include "Display_Buttons.h"
#include "Display_Info.h"
#include "Display_Map.h"
#include "Element.h"
#include "Game.h"
#include "Graphic_Utils.h"
#include "Map.h"
#include "Monsters.h"
#include "Window.h"

// draws a bar on the right of the game window
static void draw_right_bar(Game *game, UserAction current_action,
                           WindowInfo *win) {
    MLV_draw_filled_rectangle(RIGHT_BAR_X, 0, RIGHT_BAR_SIZE, GAME_HEIGHT,
                              RIGHT_BAR_COLOR);
    draw_top_buttons(win);
    draw_inventory(game->inventory, win);
    display_error(&game->error, *win);
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
    draw_map(&game->map);
    draw_right_bar(game, current_action, win);
    draw_game_information(game->next_wave, *win);
    draw_mana(game->mana, *win);
    draw_monsters(game->monsters, &game->map);
    draw_activegems(game->active_gems);
    LIST_FOREACH(monster, &game->monsters, entries) {
        draw_shots(monster->shots);
    }
}
