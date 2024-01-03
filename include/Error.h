#ifndef __ERROR_H__
#define __ERROR_H__

#include "Timer.h"
#include "Window.h"

typedef struct {
    char *message;
    Timestamp timeout;
} Error;

/**
 * @brief Displays the error in the right bar of the window
 *
 * @param error Error containing the message to display
 * @param win information of the current window
 */
void display_error(Error error, WindowInfo win);

/**
 * @brief Creates a new error with the given message
 *
 * @param error address of the Error to modify
 * @param message message describing the error
 * @return int 1 if the error was correctly created, 0 otherwise
 */
int new_error(Error *error, char *message);

#endif