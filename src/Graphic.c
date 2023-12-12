#include "Graphic.h"

#include <MLV/MLV_all.h>

#include "Element.h"
#include "Game.h"
#include "Map.h"
#include "Monsters.h"

// Initializes the graphic window
void init_graphic(void) {
    MLV_create_window("Test", "", MAP_WIDTH * CELL_SIZE + 2,
                      MAP_HEIGHT * CELL_SIZE + 2);
}

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

// Draw a blank grid
void draw_grid(void) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            draw_cell(i, j, MLV_COLOR_GREY);
        }
    }
}

MLV_Color hue_to_rgba(Hue hue) {
    int H = hue / 60;
    double L = 0.5;
    double S = 1.0;
    double R, G, B;
    double C = (1 - abs(2 * L - 1)) * S;
    double X = C * (1 - abs(H % 2 - 1));
    double m = L - C / 2;
    switch (H) {
        case 0:
            R = C;
            G = X;
            B = 0;
            break;
        case 1:
            R = X;
            G = C;
            B = 0;
            break;
        case 2:
            R = 0;
            G = C;
            B = X;
            break;
        case 3:
            R = 0;
            G = X;
            B = C;
            break;
        case 4:
            R = X;
            G = 0;
            B = C;
            break;
        case 5:
            R = C;
            G = 0;
            B = X;
            break;
    }
    R = (R + m) * 255;
    G = (G + m) * 255;
    B = (B + m) * 255;
    return MLV_rgba(R, G, B, 255);
}

void draw_monster(Monster monster) {
    int radius = CELL_SIZE / 3;
    int x = monster.position.x * CELL_SIZE + CELL_SIZE / 2;
    int y = monster.position.y * CELL_SIZE + CELL_SIZE / 2;
    MLV_draw_filled_circle(x, y, radius, hue_to_rgba(monster.hue));
}

// Clears the window
void clear_window(void) {
    MLV_draw_filled_rectangle(0, 0, MAP_WIDTH * CELL_SIZE,
                              MAP_HEIGHT * CELL_SIZE, MLV_COLOR_LIGHT_GREY);
}

// Waits `time` seconds
void wait_seconds(int time) {
    MLV_wait_seconds(time);
}

// Refreshes the window with the changes made
void refresh(void) {
    MLV_update_window();
}

// Quits and frees the window
void quit(void) {
    MLV_free_window();
}
