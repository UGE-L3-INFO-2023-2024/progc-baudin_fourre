#include "Utils.h"

#include "Timer.h"

// Returns the vector associated to the cardinal Direction given
Vector get_direction_vector(Direction direction) {
    switch (direction) {
        case NORTH:
            return (Vector){0, -1};
        case SOUTH:
            return (Vector){0, 1};
        case WEST:
            return (Vector){-1, 0};
        case EAST:
            return (Vector){1, 0};
        case NODIR:
            return (Vector){0, 0};
    }
    return (Vector){0, 0};
}

// Returns the new position of an object with a position `old_pos`
// moving with a vector `move` for a distance `distance`
Position get_new_position(Position old_pos, double distance, Vector move) {
    Position new_pos;
    new_pos.x = (old_pos.x) + (move.x * distance);
    new_pos.y = (old_pos.y) + (move.y * distance);
    return new_pos;
}

// Returns 1 is the `position` is centered in a cell, or else 0
int is_position_center(Position position) {
    double margin = 0.05;
    double x = position.x - (int)position.x;
    double y = position.y - (int)position.y;
    if (0.5 - margin <= x && x <= 0.5 + margin && 0.5 - margin <= y &&
        y <= 0.5 + margin)
        return 1;
    return 0;
}
