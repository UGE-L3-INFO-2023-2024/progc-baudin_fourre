#ifndef __ERROR_H__
#define __ERROR_H__

#include "Timer.h"
#include "Window.h"

#define ERROR_TIMEOUT 3

typedef enum {
    NO_ERROR,
    MISSING_MANA,
    INVENTORY_MAX,
    SAME_LEVEL_GEM,
    MAX_TOWER_COUNT,
} ErrorType;

typedef struct {
    ErrorType type;
    Timestamp timeout;
} Error;

/**
 * @brief Initializes an Error structure with type : NO_ERROR
 *
 * @return Error
 */
Error init_error(void);

/**
 * @brief Modifies the `error` with the new `type`
 *
 * @param error
 * @param type
 */
void new_error(Error *error, ErrorType type);

/**
 * @brief Get the error message from its type
 *
 * @param error Error to get the message from
 * @return char* the message associated to the error type
 */
char *get_error_message(Error error);

#endif
