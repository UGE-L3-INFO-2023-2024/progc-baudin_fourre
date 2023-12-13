#include "Graphic.h"

#include <MLV/MLV_all.h>
#include <assert.h>

#include "Element.h"
#include "Game.h"
#include "Map.h"
#include "Monsters.h"

// Returns the absolute value of the double `x`
static double d_abs(double x) {
    if (x < 0)
        return -x;
    else
        return x;
}

// Initializes the graphic window
void init_graphic(void) {
    MLV_create_window("Test", "", MAP_WIDTH * CELL_SIZE + 2,
                      MAP_HEIGHT * CELL_SIZE + 2);
}

// Draws a cell of coordinates (x, y), in the color `color`
static void draw_cell(int x, int y, MLV_Color color) {
    MLV_Color outline = MLV_COLOR_BLACK;

    MLV_draw_filled_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE,
                              CELL_SIZE, color);
    MLV_draw_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                       outline);
}

// draws the path of the map
void draw_path(Map map) {
    MLV_Color color;
    int test = 1;
    for (Cell cell = map.cells[CI(map.nest)]; test;
         cell = *next_cell_direction(&map, &cell, cell.direction)) {
        switch (cell.type) {
            case NEST:
                color = MLV_COLOR_RED;
                break;
            case HOME:
                color = MLV_COLOR_GREEN;
                test = 0;
                break;
            default:
                color = MLV_COLOR_WHITE;
        }
        draw_cell(cell.coord.col, cell.coord.line, color);
    }
}

// clears the path of the map
void clear_path(Map map) {
    int test = 1;
    for (Cell cell = map.cells[CI(map.nest)]; test;
         cell = *next_cell_direction(&map, &cell, cell.direction)) {
        draw_cell(cell.coord.col, cell.coord.line, MLV_COLOR_GREY);
        if (cell.type == HOME)
            test = 0;
    }
}

// Draw a blank grid
void draw_grid(void) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            draw_cell(i, j, MLV_COLOR_GREY);
        }
    }
}

void draw_mana(Mana mana) {}

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
    double H2 = H - 2 * ((int)H / 2);
    int R, G, B;
    double L = 0.5;
    double S = 1.0;
    double R1, G1, B1;
    double C = (1 - d_abs(2 * L - 1)) * S;
    double X = C * (1 - d_abs(H2 - 1));
    double m = L - C / 2;
    switch (hue / 60) {
        case 0:
            assign_rgb(&R1, &G1, &B1, C, X, 0);
            break;
        case 1:
            assign_rgb(&R1, &G1, &B1, X, C, 0);
            break;
        case 2:
            assign_rgb(&R1, &G1, &B1, 0, C, X);
            break;
        case 3:
            assign_rgb(&R1, &G1, &B1, 0, X, C);
            break;
        case 4:
            assign_rgb(&R1, &G1, &B1, X, 0, C);
            break;
        case 5:
            assign_rgb(&R1, &G1, &B1, C, 0, X);
            break;
    }
    R = (R1 + m) * 255;
    G = (G1 + m) * 255;
    B = (B1 + m) * 255;
    return MLV_rgba(R, G, B, 255);
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
