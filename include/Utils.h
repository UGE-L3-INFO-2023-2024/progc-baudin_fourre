/**
 * @file Utils.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the management of Positions, Coords,
 * Directions, and Vectors, used for movements
 * @date 2023-11-16
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

// PI as a constant double
#include <stdbool.h>
#define PI 3.14159265358979323846

/**
 * @brief Macro that checks if two positions are equal (warning: check equality on double)
 */
#define EQUAL_POSITIONS(pos1, pos2)                                            \
    (((pos1).x == (pos2).x) && ((pos1).y == (pos2).y))

/**
 * @brief Structure representing a coordinate (integers)
 */
typedef struct {
    int col;
    int line;
} Coord;

/**
 * @brief Structure representing a position and a vector (double)
 */
typedef struct {
    double x;
    double y;
} Position, Vector;

/**
 * @brief Structure representing a direction
 */
typedef enum {
    NORTH = 0,
    SOUTH = 1,
    WEST = 2,
    EAST = 3,
    NODIR = -1,
} Direction;

/**
 * @brief Returns the vector associated to the cardinal Direction
 *
 * @param direction the direction
 * @return the vector associated to the direction
 */
Vector get_direction_vector(Direction direction);

/**
 * @brief Returns the new position of an object with a position `old_pos`
 * moving with a vector `move` for a distance `distance`
 *
 * @param old_pos the old position of the object
 * @param distance the distance the object moved
 * @param move the vector of the movement
 * @return the new position of the object
 */
Position get_new_position(Position old_pos, double distance, Vector move);

/**
 * @brief Checks if the `position` is centered in a cell, or else 0
 *
 * @param position Position to check
 * @return true if the position is centered, false otherwise
 */
bool is_position_center(Position position);

/**
 * @brief Gets the center position of the cell given
 *
 * @param coord Coordinates of the cell
 * @return Position the float center position of the cell
 */
Position coord_to_center_position(Coord coord);

/**
 * @brief Gets the distance between two positions
 * 
 * @param pos1 First position
 * @param pos2 Second position
 * @return the distance between the two positions
 */
double distance_between_positions(Position pos1, Position pos2);

/**
 * @brief Checks if the `position` is past the center of the next_cell
 *
 * @param position Float position
 * @param dir Cardinal direction in which the `position` is moving
 * @param next_cell Coordinates of the `next_cell` the position must past
 * @return true if the position is past the center of the next cell, false otherwise
 */
bool has_past_center_position(Position position, Direction dir, Coord next_cell);

/**
 * @brief Gets the coordinates of the next cell on the path
 *
 * @param current_position Coordinates of the current position from which to get
 * the next coordinates
 * @param dir Cardinal direction in which to get the next coordinates
 * @return the Coordinates of the next cell calculated
 */
Coord next_cell_coord(Coord current_position, Direction dir);

/**
 * @brief Gets the coordinates from a position
 *
 * @param position a position
 * @return the coordinates of the position
 */
Coord position_to_coord(Position position);

#endif // __UTILS_H__
