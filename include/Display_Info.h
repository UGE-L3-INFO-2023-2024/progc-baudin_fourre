/**
 * @file Display_Info.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to display information (as text) in the window
 * of the game using the MLV library
 * @date 2024-01-12
 *
 */

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
void get_string_from_number(unsigned long long number, char *nb_str);

/**
 * @brief Displays the error in the right bar of the window
 *
 * @param error Error containing the type of the message to display
 * @param win WindowInfo containing information on the current window
 */
void display_error(Error error, const WindowInfo *win);

/**
 * @brief Draws the mana bar at the top of the window
 *
 * @param mana Mana to draw
 * @param win WindowInfo containing information on the current window
 */
void draw_mana(Mana mana, const WindowInfo *win);

/**
 * @brief Draws information on the game in the window
 *
 * @param next_wave Timestamp indicating the time at which the next wave starts
 * @param win WindowInfo containing information on the current window
 */
void draw_game_information(Timestamp next_wave, const WindowInfo *win);

/**
 * @brief Displays the costs of the actions of the game at the top of the right
 * bar window
 *
 * @param win WindowInfo containing the information of the current window
 */
void display_cost(const WindowInfo *win);

/**
 * @brief Displays that the game is over in the center of the window
 *
 * @param win WindowInfo containing information on the current window
 */
void display_game_over(const WindowInfo *win);

#endif // __DISPLAY_INFO_H__
