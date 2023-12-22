#include "Graphic.h"

#include <MLV/MLV_all.h>
#include <assert.h>
#include <math.h>

#include "Element.h"
#include "Game.h"
#include "Map.h"
#include "Monsters.h"

// Initializes the graphic window
WindowInfo init_graphic(void) {
    WindowInfo win;
    MLV_create_window("Test", "", GAME_WIDTH + RIGHT_BAR_SIZE, GAME_HEIGHT);
    win.right_bar_font =
        MLV_load_font("fonts/calling.ttf", CELL_SIZE * 7 / 10);
    win.small_font = MLV_load_font("fonts/calling.ttf", CELL_SIZE * 1 / 2);
    return win;
}

// assign the values (r, g, b) to (*R, *G, *B)
static void assign_rgb(double *R, double *G, double *B, double r, double g,
                       double b) {
    *R = r;
    *G = g;
    *B = b;
}

// Returns the RGBA representation of the Hue `hue`
MLV_Color hue_to_rgba(Hue hue) {
    assert(hue < 360);
    double H = hue / 60.0;
    double L = 0.5;
    double S = 1.0;
    double R, G, B;
    double C = (1 - fabs(2 * L - 1)) * S;
    double X = C * (1 - fabs(fmod(H, 2) - 1));
    double m = L - C / 2;
    switch (hue / 60) {
        case 0:
            assign_rgb(&R, &G, &B, C, X, 0);
            break;
        case 1:
            assign_rgb(&R, &G, &B, X, C, 0);
            break;
        case 2:
            assign_rgb(&R, &G, &B, 0, C, X);
            break;
        case 3:
            assign_rgb(&R, &G, &B, 0, X, C);
            break;
        case 4:
            assign_rgb(&R, &G, &B, X, 0, C);
            break;
        case 5:
            assign_rgb(&R, &G, &B, C, 0, X);
            break;
    }
    return MLV_rgba((R + m) * 255, (G + m) * 255, (B + m) * 255, 255);
}

// draws a square `square` using the color `bkgd_color`
static void draw_square(Square square, MLV_Color bkgd_color) {
    MLV_draw_filled_rectangle(square.x, square.y, square.size, square.size,
                              bkgd_color);
    MLV_draw_rectangle(square.x, square.y, square.size, square.size,
                       MLV_COLOR_BLACK);
}

// draws a tower in a square `s`
static void draw_tower_in_square(Square s) {
    draw_square(s, BUTTON_BKGD_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 1 / 10, s.y + s.size * 1 / 10,
                              s.size * 8 / 10, s.size * 2 / 10, TOWER_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 2 / 10, s.y + s.size * 3 / 10,
                              s.size * 6 / 10, s.size * 5 / 10, TOWER_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 1 / 10, s.y + s.size * 8 / 10,
                              s.size * 8 / 10, s.size * 1 / 10, TOWER_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 3 / 10, s.y + s.size * 1 / 10,
                              s.size * 1 / 10, s.size * 1 / 10,
                              BUTTON_BKGD_COLOR);
    MLV_draw_filled_rectangle(s.x + s.size * 6 / 10, s.y + s.size * 1 / 10,
                              s.size * 1 / 10, s.size * 1 / 10,
                              BUTTON_BKGD_COLOR);
}

// draws a gem with the color `color` centered in the square `s`
static void draw_gem_in_square(Square s, MLV_Color color) {
    int vx[] = {s.x + s.size * 5 / 10,  s.x + s.size * 17 / 20,
                s.x + s.size * 17 / 20, s.x + s.size * 5 / 10,
                s.x + s.size * 3 / 20,  s.x + s.size * 3 / 20};
    int vy[] = {s.y + s.size * 1 / 10, s.y + s.size * 3 / 10,
                s.y + s.size * 7 / 10, s.y + s.size * 9 / 10,
                s.y + s.size * 7 / 10, s.y + s.size * 3 / 10};
    MLV_draw_filled_polygon(vx, vy, 6, color);
}

// draw a tower in the cell of coordinates `coord`
static void draw_tower_in_cell(Coord coord) {
    Square cell =
        (Square){coord.col * CELL_SIZE, coord.line * CELL_SIZE, CELL_SIZE};
    draw_tower_in_square(cell);
}

// draws the ActiveGem `gem` in its tower
static void draw_gem_in_tower(ActiveGem gem) {
    Square tower =
        (Square){gem.tower.col * CELL_SIZE + CELL_SIZE / 4,
                 gem.tower.line * CELL_SIZE + CELL_SIZE / 4, CELL_SIZE / 2};
    draw_gem_in_square(tower, hue_to_rgba(gem.gem.hue));
}

// draws the add gem button in the Square `s`, with a current level of
// `cur_level`
static void draw_add_gem_button(Square s, int cur_level, MLV_Font *font) {
    char gem_level[7];
    draw_square(s, BUTTON_BKGD_COLOR);
    draw_gem_in_square(s, MLV_COLOR_CYAN);
    sprintf(gem_level, "< %d >", cur_level);
    MLV_draw_text_box_with_font(s.x, s.y + s.size + s.size / 10, s.size,
                                s.size / 3, gem_level, font, 1, TRANSPARANT,
                                MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// draws the fuse_gem_button is the right bar
static void draw_fuse_gem_button(Square s) {
    int size = RIGHT_BAR_SIZE * 2 / 10;
    draw_square(s, BUTTON_BKGD_COLOR);
    s.size = RIGHT_BAR_SIZE * 3 / 20;
    // gem.x -= size * 1 / 10;
    s.y += size * 1 / 10;
    draw_gem_in_square(s, MLV_rgba(0, 255, 255, 150));
    s.x += size * 5 / 20;
    draw_gem_in_square(s, MLV_rgba(160, 32, 240, 150));
}

// draw the new tower button in the Square `s`
static void draw_new_tower_button(Square s, MLV_Font *font) {
    char cost[5];
    draw_tower_in_square(s);
    sprintf(cost, "%d", mana_required_tower(0));
    MLV_draw_text_box_with_font(s.x, s.y - s.size * 2 / 5, s.size, s.size / 3,
                                cost, font, 0, TRANSPARANT, MLV_COLOR_BLACK,
                                TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

// draws the Square `s` as selected by drawing a transparent black square over
// it
static void draw_selected_square(Square s) {
    MLV_Color color = MLV_rgba(0, 0, 0, 100);
    draw_square(s, color);
}

// draws the buttons of the right bar
static void draw_top_buttons(WindowInfo *win) {
    win->new_tower = (Square){RIGHT_BAR_X + RIGHT_BAR_SIZE * 1 / 10,
                              GAME_HEIGHT * 1 / 10, RIGHT_BAR_SIZE * 2 / 10};
    win->new_gem = (Square){RIGHT_BAR_X + (RIGHT_BAR_SIZE * 4 / 10),
                            GAME_HEIGHT * 1 / 10, RIGHT_BAR_SIZE * 2 / 10};
    win->fuse_gem = (Square){RIGHT_BAR_X + (RIGHT_BAR_SIZE * 7 / 10),
                             GAME_HEIGHT * 1 / 10, RIGHT_BAR_SIZE * 2 / 10};
    MLV_draw_filled_rectangle(RIGHT_BAR_X, 0, RIGHT_BAR_SIZE, GAME_HEIGHT,
                              RIGHT_BAR_COLOR);
    draw_new_tower_button(win->new_tower, win->right_bar_font);
    draw_add_gem_button(win->new_gem, 5, win->right_bar_font);
    MLV_draw_text_box_with_font(RIGHT_BAR_X + 1, GAME_HEIGHT * 1 / 40,
                                RIGHT_BAR_SIZE, GAME_HEIGHT * 1 / 30,
                                "Cost:", win->right_bar_font, 0, TRANSPARANT,
                                MLV_COLOR_BLACK, TRANSPARANT, MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    draw_fuse_gem_button(win->fuse_gem);
}

// draws a bar on the right of the game window
void draw_right_bar(WindowInfo *win) {
    draw_top_buttons(win);
}

// Draws a cell of coordinates `coord` according to the CellType `type`
static void draw_cell(CellType type, Coord coord) {
    MLV_Color outline = MLV_COLOR_BLACK;
    MLV_Color color;

    if (type == TOWER) {
        draw_tower_in_cell(coord);
        return;
    }

    if (type == EMPTY)
        color = GRID_COLOR;
    else if (type == PATH)
        color = PATH_COLOR;
    else if (type == NEST)
        color = NEST_COLOR;
    else if (type == HOME)
        color = HOME_COLOR;

    MLV_draw_filled_rectangle(coord.col * CELL_SIZE, coord.line * CELL_SIZE,
                              CELL_SIZE, CELL_SIZE, color);
    MLV_draw_rectangle(coord.col * CELL_SIZE, coord.line * CELL_SIZE,
                       CELL_SIZE, CELL_SIZE, outline);
}

// Draw a blank grid
void draw_grid(Map map) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            draw_cell(map.cells[i][j].type, map.cells[i][j].coord);
        }
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
    MLV_draw_filled_rectangle(x, y, width * filled, height, color);
    MLV_draw_filled_rectangle(x + width * filled, y, width * (1.0 - filled),
                              height, MLV_COLOR_WHITE);
    MLV_draw_rectangle(x, y, width, height, MLV_COLOR_BLACK);
}

// draws the game int its entirety according the th current UserAction
// `current_action`
void draw_game(Game game, UserAction current_action, WindowInfo *win) {
    draw_grid(game.map);
    draw_mana(game.mana);
    draw_right_bar(win);

    if (current_action == NEW_TOWER)
        draw_selected_square(win->new_tower);
}

// Draws the mana bar at the top of the window
void draw_mana(Mana mana) {
    char mana_values[12];
    sprintf(mana_values, "%d/%d", mana.quantity, mana.max);

    double filled = (double)mana.quantity / (double)mana.max;
    draw_bar((MAP_WIDTH * CELL_SIZE) * 1 / 5, CELL_SIZE * 1 / 4,
             (MAP_WIDTH * CELL_SIZE) * 3 / 5, CELL_SIZE * 1 / 2, filled,
             MLV_COLOR_CYAN);

    MLV_draw_text_box((MAP_WIDTH * CELL_SIZE) * 1 / 5, CELL_SIZE * 1 / 4,
                      (MAP_WIDTH * CELL_SIZE) * 3 / 5, CELL_SIZE * 1 / 2,
                      mana_values, 1, MLV_COLOR_BLACK, MLV_COLOR_BLACK,
                      MLV_rgba(0, 0, 0, 0), MLV_TEXT_CENTER, MLV_TEXT_CENTER,
                      MLV_TEXT_CENTER);
}

// draws the monster `monster` at its position as a circle, having its hue for
// color
void draw_monster(Monster monster) {
    int radius = CELL_SIZE / 3;
    int x = monster.position.x * CELL_SIZE;
    int y = monster.position.y * CELL_SIZE;
    MLV_draw_filled_circle(x, y, radius, hue_to_rgba(monster.hue));
}

// Clears the window
void clear_window(void) {
    MLV_draw_filled_rectangle(0, 0, MAP_WIDTH * CELL_SIZE,
                              MAP_HEIGHT * CELL_SIZE, MLV_COLOR_LIGHT_GREY);
}

// Waits `time` seconds
void wait_milliseconds(int time) {
    MLV_wait_milliseconds(time);
}

// Refreshes the window with the changes made
void refresh(void) {
    MLV_update_window();
}

// Quits and frees the window
void quit(void) {
    MLV_free_window();
}
