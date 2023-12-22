#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <MLV/MLV_all.h>

#include "Game.h"
#define CELL_SIZE 32
#define GAME_WIDTH (CELL_SIZE * MAP_WIDTH)
#define GAME_HEIGHT (CELL_SIZE * MAP_HEIGHT)
#define RIGHT_BAR_SIZE (10 * CELL_SIZE)
#define RIGHT_BAR_X (MAP_WIDTH * CELL_SIZE)

#define GRID_COLOR MLV_COLOR_GREY
#define NEST_COLOR MLV_COLOR_RED
#define HOME_COLOR MLV_COLOR_GREEN
#define PATH_COLOR MLV_COLOR_WHITE
#define BUTTON_BKGD_COLOR MLV_COLOR_GREY
#define TOWER_COLOR MLV_COLOR_BLACK
#define RIGHT_BAR_COLOR MLV_COLOR_LIGHT_GREY
#define TRANSPARANT MLV_rgba(255, 255, 255, 0)

typedef struct {
    int x;
    int y;
    int size;
} Square;

typedef struct {
    MLV_Font *right_bar_font;
    MLV_Font *small_font;
    Square new_tower;
    Square new_gem;
    Square fuse_gem;
} WindowInfo;

/**
 * @brief Initializes the graphic window
 *
 * @return WindowInfo structure containing information about the window created
 */
WindowInfo init_graphic(void);

/**
 * @brief Waits `time` seconds
 *
 * @param time
 */
void wait_milliseconds(int time);

/**
 * @brief Refreshes the graphic window with the changes made
 *
 */
void refresh(void);

/**
 * @brief Clears the window (displays a grey rectangle over the window)
 *
 */
void clear_window(void);

/**
 * @brief draws the Monster `monster` as a circle centered at its position
 *
 * @param monster Monster structure to draw
 */
void draw_monster(Monster monster);

/**
 * @brief Draw the mana bar at the top of the window
 *
 * @param mana Mana structure to display
 */
void draw_mana(Mana mana);

/**
 * @brief draws the game in int entirety according to the current action
 *
 * @param game Game structure to draw
 * @param action current UserAction of the game
 * @param win address of the WindowInfo containing information on the graphic
 * window
 */
void draw_game(Game game, UserAction action, WindowInfo *win);

/**
 * @brief Quits and frees the window
 *
 * @param image image of the game to free
 */
void quit(void);

#endif  // __GRAPHIC_H__
