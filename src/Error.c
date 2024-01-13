#include "Error.h"

#include "Timer.h"

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
char *get_error_message(Error error) {
    switch (error.type) {
        case MISSING_MANA:
            return "Not enough mana";
        case INVENTORY_MAX:
            return "Inventory full";
        case SAME_LEVEL_GEM:
            return "Gems must have same\n levels for fusion";
        case MAX_TOWER_COUNT:
            return "Maximum number of \n towers reached";
        default:
            return "";
    }
}
