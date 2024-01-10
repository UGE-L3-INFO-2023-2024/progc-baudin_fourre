#ifndef __UTILS_H__
#define __UTILS_H__

#define EQUAL_POSITIONS(pos1, pos2)                                            \
    (((pos1).x == (pos2).x) && ((pos1).y == (pos2).y))

typedef struct {
    int col;
    int line;
} Coord;

typedef struct {
    double x;
    double y;
} Position, Vector;

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
 * @param direction
 * @return Vector
 */
Vector get_direction_vector(Direction direction);

/**
 * @brief Returns the new position of an object with a position `old_pos`
 * moving with a vector `move` for a distance `distance`
 *
 * @param old_pos
 * @param distance
 * @param move
 * @return Position
 */
Position get_new_position(Position old_pos, double distance, Vector move);

/**
 * @brief Checks if the `position`is centered in a cell, or else 0
 *
 * @param position Position to check
 * @return int 1 if the position is centered, else 0
 */
int is_position_center(Position position);

/**
 * @brief Gets the center position of the cell given
 *
 * @param coord Coordinates of the cell
 * @return Position the float center position of the cell
 */
Position coord_to_position(Coord coord);

double distance_between_positions(Position pos1, Position pos2);

/**
 * @brief Checks if the `position` is past the center of the next_cell
 *
 * @param position Float position
 * @param dir Cardinal direction in which the `position` is moving
 * @param next_cell Coordinates of the `next_cell` the position must past
 * @return int 1 if the position is past the center of the next cell, 0
 * otherwise
 */
int has_past_center_position(Position position, Direction dir, Coord next_cell);

/**
 * @brief Gets the coordinates of the next cell on the path
 *
 * @param current_position Coordinates of the current position from which to get
 * the next coordinates
 * @param dir Cardinal direction in which to get the next coordinates
 * @return Coord the Coordinates of the next cell calculated
 */
Coord next_cell_coord(Coord current_position, Direction dir);

// Distance entre deux points
// Calcul vecteur de déplacement
// Calcul nouvelle position à partir de vitesse et vecteur de déplacement

#endif // __UTILS_H__
