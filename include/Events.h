#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "Graphic_Utils.h"
#include "Utils.h"
#include "Window.h"

typedef enum {
    NOEVENT,
    CLICK,
    ESCAPE,
    SPACE,
    QUIT,
} EventType;

typedef struct {
    EventType type;
    Coord mouse;
} Event;

/**
 * @brief Gets the keyboard event from the user, if there's one
 *
 * @return Event the event retrieved
 */
Event get_events(void);

/**
 * @brief Get the index of the selected gem of the inventory from an event
 *
 * @param event Event retrieved (click of the mouse)
 * @param win Information of the current window
 * @return int index of the selected gem of the inventory
 */
int get_selected_inventory_gem(Event event, WindowInfo win);

/**
 * @brief Checks if the Coord `click`are within the Square `button`
 *
 * @param click
 * @param button
 * @return int 1 if the click is in the square, 0 otherwise
 */
int is_click_in_button(Coord click, Square button);

/**
 * @brief Checks if the Coord `click` are in the game window
 *
 * @param click Coordinates of the click
 * @param cell_size size of a cell
 * @return int 1 if the click is in the Game window, 0 otherwise
 */
int is_click_in_game(Coord click, int cell_size);

#endif // __EVENTS_H__
