#include "Game.h"

#include <stdio.h>

#include "Gems.h"
#include "Graphic.h"
#include "Mana.h"
#include "Monsters.h"
#include "Shots.h"
#include "Timer.h"
#include "Utils.h"
#include "Window.h"

// Returns 0 if a tower couldn't be added to the map at the coordinates
// `coord`, or 1 otherwise
int add_tower(Game *game, Coord coord) {
    if (!is_in_map(coord)
        || game->map.cells[coord.col][coord.line].type != EMPTY)
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
    int x, y;
    double elapsed = elapsed_since(time);
    LIST_FOREACH(monster, &(game->monsters), entries) {
        if (is_past_time(monster->start_time))
            move_monster(game->map, monster, elapsed);
        x = monster->position.x;
        y = monster->position.y;
        if (game->map.cells[x][y].type == HOME) {
            if (!mana_banish_monster(&(game->mana), *monster))
                game->defeat = 1;
            monster->position = coord_to_position(game->map.nest);
            free_shots(&(monster->shots));
        }
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
    game.next_wave = time_future(100000);
    game.error = (Error){NULL, time_now()};
    game.defeat = 0;
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

// Adds a new wave of monsters to the game
int add_wave(Game *game) {
    static int wave_count = 1;
    double t_left;
    if (!wave_generation(&(game->monsters), game->map, wave_count))
        return 0;
    if (wave_count != 1) {
        t_left = time_to(game->next_wave);
        mana_new_wave(&(game->mana), t_left);
    }
    game->next_wave = time_future(35);
    wave_count++;
    return 1;
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

void move_shots(Game *game, Timestamp time) {
    double elapsed = elapsed_since(time);
    Monster *monster;
    LIST_FOREACH(monster, &game->monsters, entries) {
        Shot *shot;
        LIST_FOREACH(shot, &monster->shots, entries) {
            move_shot(shot, monster->position, elapsed);
        }
    }
}

void damage_monsters(Game *game) {
    Monster *monster, *next_m;
    LIST_FOREACH_SAFE(monster, &game->monsters, entries, next_m) {
        Shot *shot, *next_s;
        LIST_FOREACH_SAFE(shot, &monster->shots, entries, next_s) {
            if (!EQUAL_POSITIONS(shot->position, monster->position))
                continue;
            Gem gem = shot->source;
            LIST_REMOVE(shot, entries);
            free_shot(shot);
            damage_monster(monster, gem);
            if (is_dead_monster(monster)) {
                mana_eliminate_monster(&(game->mana), *monster);
                LIST_REMOVE(monster, entries);
                free_monster(monster);
                break;
            }
        }
    }
}

static Monster *find_monster_to_shoot(Coord tower_coord,
                                      MonsterList *monster_list) {
    const float tower_field_radius = 3.0;
    Monster *monster;
    Monster *monster_fit = NULL;
    LIST_FOREACH(monster, monster_list, entries) {
        if (distance_between_positions(monster->position,
                                       coord_to_position(tower_coord))
            < tower_field_radius) {
            if (!monster_fit || monster_fit->hp < monster->hp) {
                monster_fit = monster;
            }
        }
    }
    return monster_fit;
}

void activegems_fire(Game *game) {
    ActiveGem *activegem;
    LIST_FOREACH(activegem, &game->active_gems, entries) {
        if (is_past_time(activegem->next_shot)) {
            Monster *monster =
                find_monster_to_shoot(activegem->tower, &game->monsters);
            if (monster) {
                Shot *shot = create_new_shot(activegem->tower, activegem->gem);
                LIST_INSERT_HEAD(&monster->shots, shot, entries);
                activegem->next_shot = time_future(activegem->shot_interval);
            }
        }
    }
}
