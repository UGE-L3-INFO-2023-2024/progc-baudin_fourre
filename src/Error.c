#include "Error.h"

#include "Color.h"
#include "Timer.h"
#include "Window.h"

// Modifies the `error` with the new `type`
void new_error(Error *error, ErrorType type) {
    error->type = type;
    error->timeout = time_future(ERROR_TIMEOUT);
}

// Returns an initialized Error structure
Error init_error(void) {
    return (Error){.type = NO_ERROR};
}

// Returns the error message associated to the error type
static char *get_error_message(Error error) {
    switch (error.type) {
        case MISSING_MANA:
            return "Not enough mana";
        case INVENTORY_MAX:
            return "Inventory full";
        case SAME_LEVEL_GEM:
            return "Gems must have same\n levels for fusion";
        default:
            return "";
    }
}

// Displays the error in the right bar of the window
void display_error(Error *error, WindowInfo win) {

    if (error->type == NO_ERROR)
        return;

    if (!is_past_time(error->timeout))
        MLV_draw_text_box_with_font(RIGHT_BAR_X, 0, RIGHT_BAR_SIZE, GAME_HEIGHT,
                                    get_error_message(*error),
                                    win.right_bar_font, 10, TRANSPARANT,
                                    MLV_COLOR_RED, TRANSPARANT, MLV_TEXT_CENTER,
                                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_BOTTOM);
    else
        error->type = NO_ERROR;
}
