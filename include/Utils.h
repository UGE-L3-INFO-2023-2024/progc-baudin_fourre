#ifndef __UTILS_H__
#define __UTILS_H__

typedef struct {
    char col;
    char line;
} Coord;

typedef struct {
    float x;
    float y;
} Position, Vector;

typedef enum {
    NORTH = 0b00,
    SOUTH = 0b01,
    WEST = 0b10,
    EAST = 0b11,
    NODIR = 5,
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

// Distance entre deux points
// Calcul vecteur de déplacement
// Calcul nouvelle position à partir de vitesse et vecteur de déplacement

#endif  // __UTILS_H__
