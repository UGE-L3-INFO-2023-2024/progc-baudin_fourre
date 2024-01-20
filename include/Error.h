
/**
 * @file Error.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of the various
 * user Errors that can occur in the game
 * @date 2024-01-03
 *
 */
#ifndef __ERROR_H__
#define __ERROR_H__

#include "Timer.h"

#define ERROR_TIMEOUT 3

/**
 * @brief Enumerates the different types of errors that can occur in the game
 */
typedef enum {
    NO_ERROR,
    MISSING_MANA,
    INVENTORY_MAX,
    SAME_LEVEL_GEM,
    MAX_TOWER_COUNT,
} ErrorType;

/**
 * @brief Structure representing an error
 */
typedef struct {
    ErrorType type;
    Timestamp timeout;
} Error;

/**
 * @brief Initializes an Error with type NO_ERROR
 *
 * @return the initialized Error
 */
Error init_error(void);

/**
 * @brief Modifies the `error` with the new `type`
 *
 * @param error Error to modify
 * @param type New type of the error
 */
void new_error(Error *error, ErrorType type);

/**
 * @brief Get the error message from its type
 *
 * @param error the error to get the message from
 * @return the message associated to the error type
 */
char *get_error_message(Error error);

#endif
