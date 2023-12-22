#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "Graphic.h"
#include "Utils.h"

typedef enum {
    NOEVENT,
    CLICK,
    ESCAPE,
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
 * @brief Checks if the Coord `click`are within the Square `button`
 *
 * @param click
 * @param button
 * @return int 1 if the click is in the square, 0 otherwise
 */
int is_click_in_button(Coord click, Square button);

#endif  // __EVENTS_H__
