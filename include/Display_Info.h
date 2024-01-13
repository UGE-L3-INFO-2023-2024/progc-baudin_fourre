#ifndef __DISPLAY_INFO_H__
#define __DISPLAY_INFO_H__

#include "Error.h"
#include "Mana.h"
#include "Timer.h"
#include "Window.h"

/**
 * @brief Get the shortened string associated to the `number`
 *
 * @param number
 * @param nb_str address of the string to put the string obtained from the
 * number
 */
void get_string_from_number(uint64_t number, char *nb_str);

/**
 * @brief Displays the error in the right bar of the window
 *
 * @param error Error containing the type of the message to display
 * @param win WindowInfo containing information on the current window
 */
void display_error(Error *error, WindowInfo win);

/**
 * @brief Draws the mana bar at the top of the window
 *
 * @param mana Mana to draw
 * @param win WindowInfo containing information on the current window
 */
void draw_mana(Mana mana, WindowInfo win);

/**
 * @brief Draws information on the game in the window
 *
 * @param next_wave Timestamp indicating the time at which the next wave starts
 * @param win WindowInfo containing information on the current window
 */
void draw_game_information(Timestamp next_wave, WindowInfo win);

#endif // __DISPLAY_INFO_H__
