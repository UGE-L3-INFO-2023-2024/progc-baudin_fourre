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

// Returns 0 if a tower couldn't be added to the map at the coordinates
// `coord`, or 1 otherwise
int add_tower(Game *game, Coord coord) {
    if (!is_in_map(coord)
        || game->map.cells[coord.col][coord.line].type != EMPTY)
        return 0;
    if (!mana_buy_tower(&game->mana, &(game->error)))
        return 0;
    game->map.cells[coord.col][coord.line].type = TOWER;
    game->map.cells[coord.col][coord.line].gem = NULL;
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
        if (is_past_time(monster->start_time)) {
            move_monster(&game->map, monster, elapsed);
            apply_extra_damage(monster);
        }
        x = monster->position.x;
        y = monster->position.y;
        if (game->map.cells[x][y].type == HOME) {
            if (!mana_banish_monster(&(game->mana), *monster))
                game->defeat = 1;
            monster->position = coord_to_position(game->map.nest);
            monster->direction =
                game->map.cells[game->map.nest.col][game->map.nest.line]
                    .direction;
            free_shots(&(monster->shots));
        }
    }
}

// Adds the effect of the element of the gem, if there's one, to the `monster`
// receiving the shot
static void add_monster_element_effect(Game *game, Monster *monster, Gem gem) {
    Monster *monster_tmp;
    double distance, damage;
    switch (gem.type) {
    case PYRO:
        LIST_FOREACH(monster_tmp, &game->monsters, entries) {
            distance = distance_between_positions(monster_tmp->position,
                                                  monster->position);
            if (monster_tmp != monster && distance < 2) {
                damage = get_damage(*monster_tmp, gem);
                damage *= 0.15;
                monster_tmp->hp =
                    (monster->hp - damage) > 0 ? monster->hp - damage : 0;
            }
        }
        break;
    case DENDRO:
        monster->effect.type = EXTRA_DAMAGE;
        monster->effect.damage.damage = 0.025 * get_damage(*monster, gem);
        monster->effect.damage.next_damage = time_future(0.5);
        monster->effect.timeout = time_future(10);
        break;
    case HYDRO:
        monster->effect.type = LOWER_SPEED;
        monster->effect.speed = monster->speed / 1.5;
        monster->effect.timeout = time_future(10);
        break;
    case NONE:
        break;
    }
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
    if (!wave_generation(&(game->monsters), &game->map, wave_count))
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
    ActiveGem *new_gem;
    if (tower.col >= MAP_WIDTH || tower.line >= MAP_HEIGHT)
        return;
    if (game->map.cells[tower.col][tower.line].type == TOWER) {
        new_gem = add_to_activegemslist(&(game->active_gems),
                                        game->inventory.gems[win.selected_gem],
                                        tower);
        remove_from_inventory(&(game->inventory), win.selected_gem);
        remove_activegem(game, tower);
        game->map.cells[tower.col][tower.line].gem = new_gem;
    }
}

// Removes the ActiveGem in the `tower` and puts it back in the inventory
void remove_activegem(Game *game, Coord tower) {
    ActiveGem *last_gem = game->map.cells[tower.col][tower.line].gem;
    if (last_gem) {
        LIST_REMOVE(last_gem, entries);
        game->inventory.gems[game->inventory.size] = last_gem->gem;
        game->map.cells[tower.col][tower.line].gem = NULL;
        free(last_gem);
        game->inventory.size++;
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
            add_monster_residue(monster, gem.hue);
            add_monster_element_effect(game, monster, gem);
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

// Fuses two gems in a new gem
void game_fuse_gems(Game *game, int gem1, int gem2) {
    Gem firstGem, secondGem;
    int tmp;

    if (!mana_fuse_gem(&(game->mana), &(game->error)))
        return;

    firstGem = game->inventory.gems[gem1];
    secondGem = game->inventory.gems[gem2];
    if (firstGem.level != secondGem.level) // TODO : ADD ERROR
        return;
    if (gem1 < gem2) {
        tmp = gem1;
        gem1 = gem2;
        gem2 = tmp;
    }
    remove_from_inventory(&(game->inventory), gem1);
    remove_from_inventory(&(game->inventory), gem2);
    game->inventory.gems[game->inventory.size] =
        fuse_gems(firstGem, secondGem); // TODO : ADD TO INVENTORY
    game->inventory.size++;
}
