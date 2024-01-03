#include "Game.h"

#include <stdio.h>

#include "Gems.h"
#include "Graphic.h"
#include "Monsters.h"
#include "Time.h"
#include "Utils.h"
#include "Window.h"

// Returns 0 if a tower couldn't be added to the map at the coordinates
// `coord`, or 1 otherwise
int add_tower(Game *game, Coord coord) {
    if (!is_in_map(coord) ||
        game->map.cells[coord.col][coord.line].type != EMPTY)
        return 0;
    if (!mana_buy_tower(&game->mana, &(game->error)))
        return 0;
    game->map.cells[coord.col][coord.line].type = TOWER;
    return 1;
}

// Creates a new pure gem, adding it to the inventory
// Returns 1 if the gem could be created, 0 otherwise
int new_gem(Game *game, int level) {
    if (game->inventory.size == INVENTORY_SIZE) {
        fprintf(stderr, "Inventory size exceeded\n");
        return 0;
    }
    if (!mana_buy_gem(&game->mana, level, &(game->error)))
        return 0;
    Gem new_gem = generate_pure_gem(level);
    game->inventory.gems[game->inventory.size] = new_gem;
    game->inventory.size++;
    return 1;
}

// Move the monsters of the `game` according to their movement since `time`
void move_monsters(Game *game, Timestamp time) {
    Monster *monster;
    double elapsed = elapsed_since(time);
    LIST_FOREACH(monster, &(game->monsters), entries) {
        if (is_past_time(monster->start_time))
            move_monster(game->map, monster, elapsed);
    }
}

// Returns a Game structure with its initial values
Game init_game(void) {
    Game game;
    game.map = generate_map();
    game.inventory.size = 0;
    game.active_gems.lh_first = NULL;
    game.mana = init_mana();
    game.monsters.lh_first = NULL;
    game.next_wave = time_now();
    game.error = (Error){NULL, time_now()};
    return game;
}

// Increases the new gem level of `win` by one
void increase_new_gem_level(WindowInfo *win) {
    if (win->new_gem_level < GEM_LEVEL_MAX)
        win->new_gem_level++;
}

// Decreases the new gem level of `win` by one
void decrease_new_gem_level(WindowInfo *win) {
    if (win->new_gem_level > 0)
        win->new_gem_level--;
}

// Adds the selected gem of the inventory to the `tower` if the coordinates
// correspond to one
void add_activegem(Game *game, WindowInfo win, Coord tower) {
    if (tower.col >= MAP_WIDTH || tower.line >= MAP_HEIGHT)
        return;
    if (game->map.cells[tower.col][tower.line].type == TOWER) {
        add_to_activegemslist(&(game->active_gems),
                              game->inventory.gems[win.selected_gem], tower);
        remove_from_inventory(&(game->inventory), win.selected_gem);
    }
}
