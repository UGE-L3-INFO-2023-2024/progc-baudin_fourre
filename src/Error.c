#include "Error.h"

#include "Color.h"
#include "Time.h"
#include "Window.h"

// Modifies the `error` with the new `message`
int new_error(Error *error, char *message) {
    error->message =
        realloc(error->message, (strlen(message) + 1) * sizeof(char));
    if (!error->message)
        return 0;
    strcpy(error->message, message);
    error->timeout = time_future(3);
    return 1;
}

// Displays the error in the right bar of the window
void display_error(Error error, WindowInfo win) {
    if (!is_past_time(error.timeout))
        MLV_draw_text_box_with_font(
            RIGHT_BAR_X, 0, RIGHT_BAR_SIZE, GAME_HEIGHT, error.message,
            win.right_bar_font, 1, TRANSPARANT, MLV_COLOR_RED, TRANSPARANT,
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_BOTTOM);
}
