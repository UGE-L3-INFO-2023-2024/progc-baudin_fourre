/**
 * @file Map.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the generation and reading of the game map
 * @date 2023-12-11
 *
 */

#include "Map.h"

#include <MLV/MLV_random.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// Returns a random coordinate within the map away by margin from the edges for the nest
static Coord random_nest_coords(void) {
    return (Coord){
        .col = MLV_get_random_integer(MARGIN, MAP_WIDTH - MARGIN - 1),
        .line = MLV_get_random_integer(MARGIN, MAP_HEIGHT - MARGIN - 1)};
}

// Checks if the coordinate `coord` is within the map, away by `margin` from the edges
static bool out_of_edges(Coord coord, int margin) {
    return (coord.line < margin || coord.line >= MAP_HEIGHT - margin
            || coord.col < margin || coord.col >= MAP_WIDTH - margin);
}

// Initializes the map with the coordinates of each cell
static void init_map(Map *map) {
    assert(map);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            map->cells[i][j].coord = (Coord){
                .col = i,
                .line = j,
            };
        }
    }
}

// Returns the next cell in dir from the cell in the map
static Cell *
next_cell_from_direction(const Map *map, const Cell *cell, Direction dir) {
    assert(map);
    assert(cell);

    Coord next_coord = next_cell_coord(cell->coord, dir);
    if (out_of_edges(next_coord, 0)) {
        return NULL;
    }
    return (Cell *) &map->cells[CI(next_coord)];
}

// Returns true if the cell `cell` is surrounded by empty cells in a triangle of `dist` cells in the oposite direction of `forbidden_dir`
static bool check_around(const Map *map,
                         const Cell *cell,
                         Direction dir,
                         Direction forbidden_dir,
                         int dist) {
    if (cell == NULL) {
        return false;
    }
    if (cell->type != EMPTY) {
        return false;
    }
    if (dist > 0) {
        for (int i = 0; i < 4; i++) {
            if (i != forbidden_dir && i != (dir ^ 1)
                && !check_around(map,
                                 next_cell_from_direction(map, cell, i),
                                 i,
                                 forbidden_dir,
                                 dist - 1)) {
                return false;
            }
        }
    }
    return true;
}

// Returns the maximum distance of a potential path in dir from the cell in the map
static int
distance_reached_direction(const Map *map, const Cell *cell, Direction dir) {
    int distance = 0;
    while ((cell = next_cell_from_direction(map, cell, dir))
           && !out_of_edges(cell->coord, MARGIN - 1)
           && check_around(map, cell, dir, (dir ^ 1), MARGIN - 1)) {
        distance++;
    }
    return distance;
}

// Returns a random number between 0 and size - 1, weighted by the weights
static int weighted_random(int weights[], int size) {
    assert(weights);

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += weights[i];
    }
    assert(sum > 0);

    int random_index = size - 1;
    int random_num = MLV_get_random_integer(0, sum - 1);
    int acc = 0;
    for (int i = 0; i < random_index; i++) {
        acc += weights[i];
        if (random_num < acc) {
            random_index = i;
            break;
        }
    }
    return random_index;
}

Map generate_map(void) {
    int turns;
    int length;
    int random_length;
    Map map;

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            map.cells[i][j].type = EMPTY;
        }
    }

    do {
        turns = 0;
        length = 0;
        map = (Map){0};
        init_map(&map);
        map.nest = random_nest_coords();

        Cell *cell = &map.cells[CI(map.nest)];
        cell->type = NEST;

        int length_in_dir[4];
        for (int i = 0; i < 4; i++) {
            length_in_dir[i] = distance_reached_direction(&map, cell, i);
        }

        Direction random_dir = weighted_random(length_in_dir, 4);

        while (length_in_dir[random_dir] > MARGIN - 1) {
            random_length = 0;
            for (int i = 0; i < length_in_dir[random_dir]; i++) {
                random_length += MLV_get_random_integer(0, 3) < 3 ? 1 : 0;
            }
            random_length = random_length < MARGIN ? MARGIN : random_length;

            /** trace path **/
            for (int i = 0; i < random_length; i++) {
                cell->direction = random_dir;
                cell = next_cell_from_direction(&map, cell, random_dir);
                assert(cell);
                cell->type = PATH;
            }

            int axe = (~random_dir & 2); // Get axe to turn
            length_in_dir[axe | 0] =
                distance_reached_direction(&map, cell, axe | 0);
            length_in_dir[axe | 1] =
                distance_reached_direction(&map, cell, axe | 1);
            if (length_in_dir[axe | 0] + length_in_dir[axe | 1] <= 0) {
                break;
            }

            random_dir = axe | weighted_random(length_in_dir + axe, 2);

            turns += 1;
            length += random_length;
        }

        cell->type = HOME;
    } while (turns < 8 || length < 75);

    return map;
}

// Returns true if the coordinates `coord` are within the map, or false
// otherwise
bool is_in_map(Coord coord) {
    return coord.col >= 0 && coord.line >= 0 && coord.col < MAP_WIDTH
           && coord.line < MAP_HEIGHT;
}

// Returns the direction of the cell where the `position` is situated
Direction get_position_direction(const Map *map, Position position) {
    Cell cell = map->cells[CI_RAW_POS(position)];
    if (cell.type != PATH && cell.type != NEST)
        return NODIR;
    return cell.direction;
}
