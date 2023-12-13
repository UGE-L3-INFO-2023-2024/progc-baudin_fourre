#include "Map.h"

#include <MLV/MLV_random.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Coord random_nest_coords() {
    const int margin = 3;
    return (Coord){
        .col = MLV_get_random_integer(0 + margin, MAP_WIDTH - margin),
        .line = MLV_get_random_integer(0 + margin, MAP_HEIGHT - margin)};
}

static bool out_of_edges(Coord coord, int margin) {
    return (coord.line < margin || coord.line >= MAP_HEIGHT - margin ||
            coord.col < margin || coord.col >= MAP_WIDTH - margin);
}

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

Cell *next_cell_direction(const Map *map, const Cell *cell, Direction dir) {
    assert(map);
    assert(cell);

    Coord next_coord = cell->coord;
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
    if (out_of_edges(next_coord, 0)) {
        return NULL;
    }
    return (Cell *)&map->cells[CI(next_coord)];
}

static bool check_around(const Map *map, const Cell *cell, Direction dir,
                         Direction forbidden_dir, int dist) {
    // fprintf(stderr, "CHECK AROUND d%d %d (%d, %d) %c\n", dir, dist,
    // cell->coord.col, cell->coord.line, 'A' + cell->type);

    if (cell == NULL) {
        return false;
    }
    if (cell->type != EMPTY) {
        return false;
    }
    if (dist > 0) {
        for (int i = 0; i < 4; i++) {
            if (i != forbidden_dir && i != (dir ^ 0b01) &&
                !check_around(map, next_cell_direction(map, cell, i), i,
                              forbidden_dir, dist - 1)) {
                return false;
            }
        }
    }
    return true;
}

static int distance_reached_direction(const Map *map, const Cell *cell,
                                      Direction dir) {
    int distance = 0;
    while ((cell = next_cell_direction(map, cell, dir)) &&
           !out_of_edges(cell->coord, 2) &&
           check_around(map, cell, dir, (dir ^ 0b01), 2)) {
        // fprintf(stderr, "COMPUTE DISTANCE\n");
        distance++;
    }
    // fprintf(stderr, "DISTANCE %d\n", distance);
    return distance;
}

static int weighted_random(int weights[], int size) {
    assert(weights);

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += weights[i];
    }
    // fprintf(stderr, "%d", sum);
    assert(sum > 0);

    int random_index = size - 1;
    int random_num = MLV_get_random_integer(0, sum);
    int acc = 0;
    for (int i = 0; i < random_index; i++) {
        if (random_num < (acc += weights[i])) {
            random_index = i;
            break;
        }
    }
    return random_index;
}

Map generate_map() {
    int turns;
    int length;
    int r;
    int random_length;
    Map map;

    do {
        map = (Map){0};
        init_map(&map);
        map.nest = random_nest_coords();
        // map.nest = (Coord){.col = 6, .line = 9};
        turns = 0;
        length = 0;
        // fprintf(stderr, "NEST (%d, %d)\n", map.nest.col, map.nest.line);
        map.cells[CI(map.nest)].type = NEST;

        Cell *cell = &map.cells[CI(map.nest)];

        int length_in_dir[4];
        for (int i = 0; i < 4; i++) {
            length_in_dir[i] =
                distance_reached_direction(&map, cell, i);  // Only if > 3 ??
        }
        // fprintf(stderr, "LENGTHS %d %d %d %d\n", length_in_dir[0],
        // length_in_dir[1], length_in_dir[2], length_in_dir[3]);
        Direction random_dir = weighted_random(length_in_dir, 4);

        while (length_in_dir[random_dir] > 2) {
            random_length = 0;
            for (int i = 0; i < length_in_dir[random_dir]; i++) {
                random_length += MLV_get_random_integer(0, 3) < 3 ? 1 : 0;
            }
            random_length = random_length < 3 ? 3 : random_length;

            /** trace path **/
            for (int i = 0; i < random_length; i++) {
                cell->direction = random_dir;
                cell = next_cell_direction(&map, cell, random_dir);
                assert(cell);
                cell->type = PATH;
            }
            /* for (int i = 0; i < MAP_WIDTH; i++) {
                for (int j = 0; j < MAP_HEIGHT; j++) {
                    printf("%c", 'A' + map.cells[i][j].type);
                }
                printf("\n");
            } */

            int axe = (~random_dir & 0b10);  // Get axe to turn
            length_in_dir[axe | 0b00] =
                distance_reached_direction(&map, cell, axe | 0b00);
            length_in_dir[axe | 0b01] =
                distance_reached_direction(&map, cell, axe | 0b01);
            // fprintf(stderr, "E(%d = %d, %d = %d)\n", axe | 0b00,
            // length_in_dir[axe | 0b00], axe | 0b01, length_in_dir[axe |
            // 0b01]);
            if (length_in_dir[axe | 0b00] + length_in_dir[axe | 0b01] <= 0) {
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

// Returns the direction of the cell where the `position`is situated
Direction get_position_direction(Map map, Position position) {
    int x = position.x;
    int y = position.y;
    CellType type = map.cells[x][y].type;
    if (type != PATH && type != NEST)
        return NODIR;
    return map.cells[x][y].direction;
}

/*
TODO:
- clean code
- remove 0B00
*/

// gcc src/Map.c -Iinclude/ -o TestMap -lMLV
/*
int main() {
    Map map = generate_map();

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            printf("%c", 'A' + map.cells[i][j].type);
        }
        printf("\n");
    }

    return 0;
}
*/
