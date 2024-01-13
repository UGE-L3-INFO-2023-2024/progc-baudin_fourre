#include "Graphic.h"

#include <MLV/MLV_all.h>
#include <assert.h>
#include <math.h>

#include "Element.h"
#include "Game.h"
#include "Map.h"
#include "Monsters.h"
#include "Window.h"

#define PI 3.14159265358979323846

// draws a square `square` using the color `bkgd_color`
static void draw_square(Square square, MLV_Color bkgd_color) {
    MLV_draw_filled_rectangle(square.x, square.y, square.size, square.size,
                              bkgd_color);
    MLV_draw_rectangle(square.x, square.y, square.size, square.size,
                       MLV_COLOR_BLACK);
}

// draws a tower in a square `s`
static void draw_tower_in_square(Square s) {
    draw_square(s, BKGD_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 0.1, s.y + s.size * 0.1,
                              s.size * 0.8, s.size * 0.2, TOWER_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 0.2, s.y + s.size * 0.2,
                              s.size * 0.6, s.size * 0.5, TOWER_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 0.1, s.y + s.size * 0.7,
                              s.size * 0.8, s.size * 0.2, TOWER_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 0.3, s.y + s.size * 0.1,
                              s.size * 0.1, s.size * 0.1, BKGD_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 0.6, s.y + s.size * 0.1,
                              s.size * 0.1, s.size * 0.1, BKGD_COLOR);
}

// Draws a gem of color `color` with its center coordinates and size
static void draw_gem(int center_x, int center_y, double size, MLV_Color color) {
    int vx[6], vy[6];
    for (int i = 0; i < 6; i++) {
        vx[i] = (int) (center_x + size * cos(2 * PI / 6 * i - PI * 0.5));
        vy[i] = (int) (center_y + size * sin(2 * PI / 6 * i - PI * 0.5));
    }
    MLV_draw_filled_polygon(vx, vy, 6, color);
}

// draws a gem with the color `color` centered in the square `s`
// prints the gem level if level is different than -1
static void draw_gem_in_square(Square s, MLV_Color color, int level,
                               MLV_Font *font) {
    int text_w, text_h;
    char level_str[2];
    sprintf(level_str, "%d", level);
    draw_gem(s.x + s.size / 2, s.y + s.size / 2, s.size * 0.45, color);
    if (level != -1) {
        if (font) {
            MLV_get_size_of_text_with_font(level_str, &text_w, &text_h, font);
            MLV_draw_adapted_text_box_with_font(
                s.x + s.size / 2 - text_w / 2, s.y + s.size / 2 - text_h / 2,
                level_str, font, 1, TRANSPARANT, MLV_COLOR_BLACK, TRANSPARANT,
                MLV_TEXT_CENTER);
        } else {
            MLV_get_size_of_text(level_str, &text_w, &text_h);
            MLV_draw_adapted_text_box(s.x + (s.size - text_w) * 0.5,
                                      s.y + (s.size - text_h) * 0.5, level_str,
                                      1, TRANSPARANT, MLV_COLOR_BLACK,
                                      TRANSPARANT, MLV_TEXT_CENTER);
        }
    }
}

// draw a tower in the cell of coordinates `coord`
static void draw_tower_in_cell(Coord coord) {
    Square cell =
        new_square(coord.col * CELL_SIZE, coord.line * CELL_SIZE, CELL_SIZE);
    draw_tower_in_square(cell);
}

// draws the ActiveGem `gem` in its tower
static void draw_gem_in_tower(ActiveGem gem) {
    Square tower = new_square(gem.tower.col * CELL_SIZE + CELL_SIZE / 5,
                              gem.tower.line * CELL_SIZE + CELL_SIZE / 5,
                              3 * CELL_SIZE / 5);
    draw_gem_in_square(tower, hue_to_rgba(gem.gem.hue), gem.gem.level, NULL);
    if (!is_past_time(gem.start_time))
        draw_gem_in_square(tower, SELECTED_COLOR, -1, NULL);
}

// draws the add gem button in the Square `s`, with a current level of
// `cur_level`
static void draw_add_gem_button(Square s, WindowInfo *win) {
    char gem_level[64];
    char cost[64];
    sprintf(gem_level, "%d", win->new_gem_level);
    sprintf(cost, "%d", (int) (100 * pow(2, win->new_gem_level)));

    draw_square(s, BKGD_COLOR);
    draw_gem_in_square(s, MLV_COLOR_CYAN, -1, NULL);
    win->dec_gem_level =
        new_square(s.x, s.y + s.size + s.size / 6, s.size * 2 / 10);
    win->inc_gem_level = new_square(s.x + s.size * 8 / 10,
                                    s.y + s.size + s.size / 6, s.size * 2 / 10),
    MLV_draw_text_box_with_font(
        win->dec_gem_level.x, win->dec_gem_level.y, win->dec_gem_level.size,
        win->dec_gem_level.size, "<", win->right_bar_font, 1, TRANSPARANT,
        MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
    MLV_draw_text_box_with_font(
        s.x + s.size * 2 / 10, s.y + s.size + s.size / 10, s.size * 6 / 10,
        s.size / 3, gem_level, win->right_bar_font, 1, TRANSPARANT,
        MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
    MLV_draw_text_box_with_font(
        win->inc_gem_level.x, win->inc_gem_level.y, win->inc_gem_level.size,
        win->inc_gem_level.size, ">", win->right_bar_font, 1, TRANSPARANT,
        MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
    MLV_draw_text_box_with_font(s.x, s.y - s.size * 2 / 5, s.size, s.size / 3,
                                cost, win->right_bar_font, 1, TRANSPARANT,
                                MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// draws the fuse_gem_button is the right bar
static void draw_fuse_gem_button(Square s, MLV_Font *font) {
    int size = RIGHT_BAR_SIZE * 2 / 10;
    draw_square(s, BKGD_COLOR);
    MLV_draw_text_box_with_font(s.x, s.y - s.size * 2 / 5, s.size, s.size / 3,
                                "100", font, 0, TRANSPARANT, MLV_COLOR_BLACK,
                                TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    s.size = RIGHT_BAR_SIZE * 3 / 20;
    // gem.x -= size * 1 / 10;
    s.y += size * 1 / 10;
    draw_gem_in_square(s, MLV_rgba(0, 255, 255, 150), -1, NULL);
    s.x += size * 5 / 20;
    draw_gem_in_square(s, MLV_rgba(160, 32, 240, 150), -1, NULL);
}

// draw the new tower button in the Square `s`
static void draw_new_tower_button(Square s, MLV_Font *font) {
    char cost[64];
    draw_tower_in_square(s);
    sprintf(cost, "%ld", mana_required_tower(0));
    MLV_draw_text_box_with_font(s.x, s.y - s.size * 2 / 5, s.size, s.size / 3,
                                cost, font, 0, TRANSPARANT, MLV_COLOR_BLACK,
                                TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// draws the Square `s` as selected by drawing a transparent black square
// over it
static void draw_selected_square(Square s) {
    draw_square(s, SELECTED_COLOR);
}

static Square get_inventory_gem(Inventory inventory, int index,
                                WindowInfo win) {
    int size = RIGHT_BAR_SIZE * 2 / 10;
    int x = RIGHT_BAR_X + RIGHT_BAR_SIZE / 10 + size * (index % INVENTORY_COLS);
    int y = GAME_HEIGHT * 7 / 20 + size * (index / INVENTORY_COLS);
    return new_square(x, y, size);
}

// draws the buttons of the right bar
static void draw_top_buttons(WindowInfo *win) {
    win->new_tower = new_square(RIGHT_BAR_X + RIGHT_BAR_SIZE * 1 / 10,
                                GAME_HEIGHT * 1 / 10, RIGHT_BAR_SIZE * 2 / 10);
    win->new_gem = new_square(RIGHT_BAR_X + (RIGHT_BAR_SIZE * 4 / 10),
                              GAME_HEIGHT * 1 / 10, RIGHT_BAR_SIZE * 2 / 10);
    win->fuse_gem = new_square(RIGHT_BAR_X + (RIGHT_BAR_SIZE * 7 / 10),
                               GAME_HEIGHT * 1 / 10, RIGHT_BAR_SIZE * 2 / 10);
    MLV_draw_filled_rectangle(RIGHT_BAR_X, 0, RIGHT_BAR_SIZE, GAME_HEIGHT,
                              RIGHT_BAR_COLOR);
    draw_new_tower_button(win->new_tower, win->right_bar_font);
    draw_add_gem_button(win->new_gem, win);
    MLV_draw_text_box_with_font(RIGHT_BAR_X + 1, GAME_HEIGHT * 1 / 40,
                                RIGHT_BAR_SIZE, GAME_HEIGHT * 1 / 30,
                                "Cost:", win->right_bar_font, 0, TRANSPARANT,
                                MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    draw_fuse_gem_button(win->fuse_gem, win->right_bar_font);
}

// draws a bar on the right of the game window
static void draw_right_bar(WindowInfo *win) {
    draw_top_buttons(win);
}

// draw the `inventory` in the right bar, drawing the selected gem if there's
// one
static void draw_inventory(Inventory inventory, WindowInfo *win) {
    Square s_gem;
    MLV_draw_text_box_with_font(
        RIGHT_BAR_X + 1, GAME_HEIGHT * 3 / 10, RIGHT_BAR_SIZE,
        GAME_HEIGHT * 1 / 30, "Inventory:", win->right_bar_font, 0, TRANSPARANT,
        MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER);
    Square s =
        (Square){RIGHT_BAR_X + RIGHT_BAR_SIZE * 1 / 10, GAME_HEIGHT * 7 / 20,
                 RIGHT_BAR_SIZE * 8 / 10,
                 (s.size / INVENTORY_COLS) * (INVENTORY_SIZE / INVENTORY_COLS)};
    win->inventory = s;
    for (int i = 0; i < inventory.size; i++) {
        s_gem = get_inventory_gem(inventory, i, *win);
        if (inventory.gems[i].type != NONE) {
            draw_gem(s_gem.x + s_gem.size / 2, s_gem.y + s_gem.size / 2,
                     s_gem.size * 0.45 + CELL_SIZE * 0.1, MLV_COLOR_GOLD);
        }
        draw_gem_in_square(s_gem, hue_to_rgba(inventory.gems[i].hue),
                           inventory.gems[i].level, win->right_bar_font);
    }
    if (win->selected_gem >= 0 && win->selected_gem < inventory.size)
        draw_gem_in_square(
            get_inventory_gem(inventory, win->selected_gem, *win),
            SELECTED_COLOR, inventory.gems[win->selected_gem].level,
            win->right_bar_font);
}

// Draws a cell of coordinates `coord` according to the CellType `type`
static void draw_cell(CellType type, Coord coord) {
    MLV_Color outline = MLV_COLOR_BLACK;
    MLV_Color color = GRID_COLOR;

    if (type == TOWER) {
        draw_tower_in_cell(coord);
        return;
    }

    if (type == PATH)
        color = PATH_COLOR;
    else if (type == NEST)
        color = NEST_COLOR;
    else if (type == HOME)
        color = HOME_COLOR;

    MLV_draw_filled_rectangle(coord.col * CELL_SIZE, coord.line * CELL_SIZE,
                              CELL_SIZE, CELL_SIZE, color);
    MLV_draw_rectangle(coord.col * CELL_SIZE, coord.line * CELL_SIZE, CELL_SIZE,
                       CELL_SIZE, outline);
}

// Draw a blank grid
void draw_grid(const Map *map) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            draw_cell(map->cells[i][j].type, map->cells[i][j].coord);
        }
    }
}

// draws the Shot `shot` as a dot with the color of the shot
static void draw_shot(Shot shot) {
    int radius = 3;
    MLV_draw_filled_circle((int) (shot.position.x * CELL_SIZE),
                           (int) (shot.position.y * CELL_SIZE), radius,
                           hue_to_rgba(shot.source.hue));
}

// draws the list of `shots`
static void draw_shots(ShotList shots) {
    Shot *shot;
    LIST_FOREACH(shot, &shots, entries) {
        draw_shot(*shot);
    }
}

// draws a bar at the corner (x, y), of size (width x height),
// with its first (`filled`*100)% filled with color `color`
static void draw_bar(int x, int y, int width, int height, double filled,
                     MLV_Color color) {
    assert(x >= 0 && x < MAP_WIDTH * CELL_SIZE);
    assert(y >= 0 && y < MAP_HEIGHT * CELL_SIZE);
    assert(width >= 0 && width < MAP_WIDTH * CELL_SIZE);
    assert(height >= 0 && height < MAP_HEIGHT * CELL_SIZE);
    assert(filled >= 0 && filled <= 100);
    MLV_draw_filled_rectangle(x, y, (int) (width * filled), height, color);
    MLV_draw_filled_rectangle((int) (x + width * filled), y,
                              (int) (width * (1.0 - filled)), height,
                              MLV_COLOR_WHITE);
    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_BLACK);
}

// draws the list of activegems by drawing gems in the correct towers
static void draw_activegems(ActiveGemList activegems) {
    ActiveGem *activegem;
    LIST_FOREACH(activegem, &activegems, entries) {
        draw_gem_in_tower(*activegem);
    }
}

// Draws the mana bar at the top of the window
static void draw_mana(Mana mana, WindowInfo *win) {
    char mana_values[64];
    sprintf(mana_values, "%ld/%ld", mana.quantity, mana.max);
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

// draws the monster `monster` at its position as a circle, having its hue
// for color
static void draw_monster(const Monster *monster) {
    int radius = CELL_SIZE / 3;
    int x = (int) (monster->position.x * CELL_SIZE);
    int y = (int) (monster->position.y * CELL_SIZE);
    MLV_draw_filled_circle(x, y, radius, hue_to_rgba(monster->hue));
    draw_bar((int) (x - radius * 1.5), (int) (y - radius * 1.5), radius * 3,
             radius / 2, (double) monster->hp / monster->hp_init,
             MLV_COLOR_GREEN);
}

// draws the list of `monsters` on their position of the `map`
static void draw_monsters(MonsterList monsters, const Map *map) {
    Monster *monster;
    LIST_FOREACH(monster, &monsters, entries) {
        if ((int) monster->position.x != map->nest.col
            || (int) monster->position.y != map->nest.line)
            draw_monster(monster);
    }
}

// draws the game int its entirety according the th current UserAction
// `current_action`
void draw_game(Game game, UserAction current_action, WindowInfo *win) {
    Monster *monster;
    draw_grid(&game.map);
    draw_mana(game.mana, win);
    draw_right_bar(win);
    draw_inventory(game.inventory, win);
    draw_monsters(game.monsters, &game.map);
    display_error(&(game.error), *win);
    draw_activegems(game.active_gems);
    LIST_FOREACH(monster, &game.monsters, entries) {
        draw_shots(monster->shots);
    }
    if (current_action == NEW_TOWER)
        draw_selected_square(win->new_tower);
    if (current_action == WAIT_FUSE_GEM
        || current_action == WAIT_SECOND_FUSE_GEM)
        draw_selected_square(win->fuse_gem);
}
