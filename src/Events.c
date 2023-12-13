#include "Events.h"

#include <MLV/MLV_all.h>
#include <stdlib.h>

// Returns the keyboard event from the user, if there's one
Event get_events(void) {
    MLV_Keyboard_button key;
    MLV_Event event =
        MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    if (event == MLV_KEY && key == MLV_KEYBOARD_q)
        return QUIT;
    return NOEVENT;
}
