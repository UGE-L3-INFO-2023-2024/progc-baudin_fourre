#include "Utils.h"

#include "Timer.h"

#include <math.h>

#define SQUARE(x) ((x) * (x))

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
    double x = position.x - (int) position.x;
    double y = position.y - (int) position.y;
    if (0.5 - margin <= x && x <= 0.5 + margin && 0.5 - margin <= y
        && y <= 0.5 + margin)
        return 1;
    return 0;
}

// Returns 1 if the position is past the center of the `next_cell` according to
// te `direction`, 0 otherwise
int has_past_center_position(Position position, Direction dir,
                             Coord next_cell) {
    Position next = coord_to_center_position(next_cell);
    switch (dir) {
    case NORTH:
        return position.y <= next.y;
    case SOUTH:
        return position.y >= next.y;
    case WEST:
        return position.x <= next.x;
    case EAST:
        return position.x >= next.x;
    default:
        return 0;
    }
}

// Returns the coordinates of the next cell according to
// the `current_position` and direction `dir
Coord next_cell_coord(Coord current_position, Direction dir) {
    Coord next_coord = current_position;
    switch (dir) {
    case NORTH:
        next_coord.line--;
        break;
    case SOUTH:
        next_coord.line++;
        break;
    case EAST:
        next_coord.col++;
        break;
    case WEST:
        next_coord.col--;
        break;
    case NODIR:
        break;
    }
    return next_coord;
}

Position coord_to_center_position(Coord coord) {
    return (Position){.x = coord.col + 0.5, .y = coord.line + 0.5};
}

Coord position_to_coord(Position position) {
    return (Coord){
        .col = (int) position.x,
        .line = (int) position.y,
    };
}

double distance_between_positions(Position pos1, Position pos2) {
    return sqrt(SQUARE(pos1.x - pos2.x) + SQUARE(pos1.y - pos2.y));
}
