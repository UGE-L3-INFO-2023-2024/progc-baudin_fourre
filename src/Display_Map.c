#include "Display_Map.h"

#include <MLV/MLV_all.h>
#include <math.h>

#include "Color.h"
#include "Gems.h"
#include "Graphic_Utils.h"
#include "Monsters.h"
#include "Shots.h"
#include "Window.h"

// draws a tower in a square `s`
void draw_tower_in_square(Square s) {
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

// draws a gem of color `color` centered in the square `s`
void draw_gem_color_in_square(Square s, MLV_Color color) {
    draw_gem(s.x + s.size / 2, s.y + s.size / 2, s.size * 0.45, color);
}

// draws a gem with the color `color` centered in the square `s`
// prints the gem level if level is different than -1
void draw_gem_in_square(Square s, Gem gem, MLV_Font *font) {
    int text_w, text_h;
    char level_str[2];
    sprintf(level_str, "%d", gem.level);
    if (gem.type != NONE) {
        draw_gem(s.x + s.size / 2, s.y + s.size / 2,
                 s.size * 0.45 + s.size * 0.05, MLV_COLOR_GOLD);
    }
    draw_gem(s.x + s.size / 2, s.y + s.size / 2, s.size * 0.45,
             hue_to_rgba(gem.hue));

    if (font) {
        MLV_get_size_of_text_with_font(level_str, &text_w, &text_h, font);
        MLV_draw_adapted_text_box_with_font(
            s.x + (s.size - text_w) * 0.5, s.y + (s.size - text_h - 1) * 0.5,
            level_str, font, 1, TRANSPARANT, MLV_COLOR_BLACK, TRANSPARANT,
            MLV_TEXT_CENTER);
    } else {
        MLV_get_size_of_text(level_str, &text_w, &text_h);
        MLV_draw_adapted_text_box(s.x + (s.size - text_w) * 0.5,
                                  s.y + (s.size - text_h - 1) * 0.5, level_str,
                                  1, TRANSPARANT, MLV_COLOR_BLACK, TRANSPARANT,
                                  MLV_TEXT_CENTER);
    }
}

// draw a tower in the cell of coordinates `coord`
static void draw_tower_in_cell(Coord coord) {
    Square cell =
        new_square(coord.col * CELL_SIZE, coord.line * CELL_SIZE, CELL_SIZE);
    draw_tower_in_square(cell);
}

// draws the ActiveGem `gem` in its tower
static void draw_activegem(ActiveGem gem) {
    Square tower = new_square(gem.tower.col * CELL_SIZE + CELL_SIZE / 5,
                              gem.tower.line * CELL_SIZE + CELL_SIZE / 5,
                              3 * CELL_SIZE / 5);
    draw_gem_in_square(tower, gem.gem, NULL);
    if (!is_past_time(gem.start_time))
        draw_gem_color_in_square(tower, SELECTED_COLOR);
}

// draws the list of activegems by drawing gems in the correct towers
void draw_activegems(ActiveGemList activegems) {
    ActiveGem *activegem;
    LIST_FOREACH(activegem, &activegems, entries) {
        draw_activegem(*activegem);
    }
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

// Draws the grid of the `map`
void draw_map(const Map *map) {
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
void draw_shots(ShotList shots) {
    Shot *shot;
    LIST_FOREACH(shot, &shots, entries) {
        draw_shot(*shot);
    }
}

// draws the monster `monster` at its position as a circle, having its hue
// for color
static void draw_monster(Monster monster) {
    int radius = CELL_SIZE / 3;
    int x = (int) (monster.position.x * CELL_SIZE);
    int y = (int) (monster.position.y * CELL_SIZE);
    MLV_draw_filled_circle(x, y, radius, hue_to_rgba(monster.hue));
    draw_bar((int) (x - radius * 1.5), (int) (y - radius * 1.5), radius * 3,
             radius / 2, (double) monster.hp / monster.hp_init,
             MLV_COLOR_GREEN);
}

// draws the list of `monsters` on their position of the `map`
void draw_monsters(MonsterList monsters, const Map *map) {
    Monster *monster;
    LIST_FOREACH(monster, &monsters, entries) {
        if ((int) monster->position.x != map->nest.col
            || (int) monster->position.y != map->nest.line)
            draw_monster(*monster);
    }
}
