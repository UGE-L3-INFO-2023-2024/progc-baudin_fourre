/**
 * @file Events.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief  Provides functions allowing create and manage Events using the events
 * retrived with the MLV library
 * @date 2023-11-16
 *
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "Graphic_Utils.h"
#include "Utils.h"
#include "Window.h"
#include <stdbool.h>

/**
 * @brief Enum of the different types of events that can occur in the game
 */
typedef enum {
    NOEVENT,
    CLICK,
    ESCAPE,
    SPACE,
    QUIT,
} EventType;

/**
 * @brief Structure representing an event
 */
typedef struct {
    EventType type;
    Coord mouse;
} Event;

/**
 * @brief Gets the interface event from the user, if there's one
 *
 * @return the event retrieved
 */
Event get_events(void);

/**
 * @brief Get the index of the selected gem of the inventory from an event
 *
 * @param event Event retrieved (must be of type click), with the coordinates of the click
 * @param win Information of the current window
 * @return index of the selected gem of the inventory
 */
int get_selected_inventory_gem(Event event, const WindowInfo *win);

/**
 * @brief Checks if the Coord `click` are within the Square `button`
 *
 * @param click Coordinates of the click
 * @param button Square to check
 * @return true if the click is in the square, false otherwise
 */
bool is_click_in_button(Coord click, Square button);

/**
 * @brief Checks if the Coord `click` are in the game window
 *
 * @param click Coordinates of the click
 * @param cell_size size of a cell
 * @return true if the click is in the Game window, false otherwise
 */
bool is_click_in_game(Coord click, int cell_size);

#endif // __EVENTS_H__
