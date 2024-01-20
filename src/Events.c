/**
 * @file Events.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief  Provides functions allowing create and manage Events using the events
 * retrived with the MLV library
 * @date 2023-12-13
 *
 */

#include "Events.h"

#include <MLV/MLV_all.h>
#include <assert.h>
#include <stdlib.h>

#include "Map.h"
#include "Utils.h"

// Returns the keyboard event from the user, if there's one
Event get_events(void) {
    Event event;
    MLV_Keyboard_button key;
    MLV_Mouse_button button;
    MLV_Event mlv_event;
    MLV_Button_state state;
    event.type = NOEVENT;
    do {
        mlv_event = MLV_get_event(&key,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &event.mouse.col,
                                  &event.mouse.line,
                                  &button,
                                  &state);
        if (mlv_event == MLV_MOUSE_BUTTON && button == MLV_BUTTON_LEFT
            && state == MLV_PRESSED)
            event.type = CLICK;
        if (mlv_event == MLV_KEY && state == MLV_PRESSED) {
            if (key == MLV_KEYBOARD_q)
                event.type = QUIT;
            if (key == MLV_KEYBOARD_ESCAPE)
                event.type = ESCAPE;
            if (key == MLV_KEYBOARD_SPACE)
                event.type = SPACE;
        }
    } while (mlv_event != MLV_NONE && event.type == NOEVENT);
    return event;
}

// Returns the index in the inventory of the gem selected
int get_selected_inventory_gem(Event event, const WindowInfo *win) {
    assert(event.type == CLICK);
    return ((event.mouse.line - win->inventory.y)
            / (win->inventory.size / INVENTORY_COLS))
               * INVENTORY_COLS
           + (event.mouse.col - win->inventory.x)
                 / (win->inventory.size / INVENTORY_COLS);
}

// Returns true if the Coord `click` are within the Square `button`, or false
// otherwise
bool is_click_in_button(Coord click, Square button) {
    if (click.col < button.x || click.col > button.x + button.size)
        return false;
    if (click.line < button.y || click.line > button.y + button.length)
        return false;
    return true;
}

// Returns true if the Coord `click` are in the game window, or false otherwise
bool is_click_in_game(Coord click, int cell_size) {
    if (click.col > MAP_WIDTH * cell_size)
        return false;
    if (click.line > MAP_HEIGHT * cell_size)
        return false;
    return true;
}
