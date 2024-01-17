/**
 * @file Game.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions defining the game play, allowing the creation and
 * update of the Game structure
 * @date 2023-12-13
 *
 */

#include "Game.h"

#include <stdint.h>
#include <stdio.h>

#include "Error.h"
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
    return (Game){
        .map = generate_map(),
        .inventory.size = 0,
        .active_gems.lh_first = NULL,
        .mana = init_mana(),
        .wave_count = 1,
        .monsters.lh_first = NULL,
        .next_wave = time_now(),
        .error = init_error(),
        .defeat = 0,
        .total_damage = 0,
    };
}

// Returns 0 if a tower couldn't be added to the map at the coordinates
// `coord`, or 1 otherwise
int add_tower(Game *game, WindowInfo *win, Coord coord) {
    if (win->nb_towers > NB_TOWERS_MAX)
        new_error(&game->error, MAX_TOWER_COUNT);
    if (!is_in_map(coord) || game->map.cells[CI(coord)].type != EMPTY)
        return 0;
    if (!mana_buy_tower(&game->mana, win->nb_towers, &game->error))
        return 0;
    game->map.cells[CI(coord)].type = TOWER;
    game->map.cells[CI(coord)].gem = NULL;
    win->nb_towers += 1;
    return 1;
}

// Creates a new pure gem, adding it to the inventory
// Returns 1 if the gem could be created, 0 otherwise
int new_gem(Game *game, int level) {
    if (!mana_buy_gem(&game->mana, level, &game->error))
        return 0;
    Gem new_gem = generate_pure_gem(level);
    if (!add_to_inventory(&game->inventory, new_gem, &game->error))
        add_mana(&game->mana, (int) (100 * pow(2, level)));
    return 1;
}

// Move the monsters of the `game` according to their movement since `time`
void move_monsters(Game *game, Timestamp time) {
    Monster *monster;
    double elapsed = elapsed_since(time);
    LIST_FOREACH(monster, &game->monsters, entries) {
        if (is_past_time(monster->start_time)) {
            move_monster(&game->map, monster, elapsed);
            apply_extra_damage(monster, &game->total_damage); // TODO : pas convaincu
        }
        if (game->map.cells[CI_RAW_POS(monster->position)].type == HOME) {
            if (!mana_banish_monster(&game->mana, monster, &game->error))
                game->defeat = 1;
            monster->position = coord_to_center_position(game->map.nest);
            monster->direction = game->map.cells[CI(game->map.nest)].direction;
            free_shots(&monster->shots);
        }
    }
}

// Applies the pyro effect to the `monster`
static void apply_pyro_effect(Game *game, Monster *monster, Gem gem) {
    Monster *monster_tmp = NULL;
    get_next_monster_in_radius(&game->monsters, monster->position, 2, true);
    while ((monster_tmp = get_next_monster_in_radius(
                &game->monsters, monster->position, 2, false))) {
        if (monster_tmp != monster)
            apply_damage(monster_tmp, 0.15 * get_damage(monster_tmp, gem), &game->total_damage);
    }
}

// Applies the hydro effect to the `monster`
static void apply_hydro_effect(Monster *monster) {
    monster->effects.type[HYDRO_EFFECT] = get_element_effect(HYDRO_EFFECT, 0);
}

// Applies the dendro effect to the `monster`
static void apply_dendro_effect(Monster *monster, Gem gem) {
    monster->effects.type[DENDRO_EFFECT] =
        get_element_effect(DENDRO_EFFECT, get_damage(monster, gem));
}

// Applies the combination of pyro and hydro effect to the `monster`
static void apply_pyro_hydro_effect(Game *game, Monster *monster, Gem gem) {
    Monster *monster_tmp = NULL;
    get_next_monster_in_radius(&game->monsters, monster->position, 3.5, true);
    while ((monster_tmp = get_next_monster_in_radius(
                &game->monsters, monster->position, 3.5, false))) {
        if (monster_tmp != monster) {
            apply_damage(monster_tmp, 0.05 * get_damage(monster_tmp, gem), &game->total_damage);
            monster->effects.type[HYDRO_PYRO_EFFECT] =
                get_element_effect(HYDRO_PYRO_EFFECT, 0);
        }
    }
}

// Applies the combination of pyro and dendro effect to the `monster`
static void apply_pyro_dendro_effect(Monster *monster, Gem gem, double *add_damage) {
    apply_damage(monster, 2 * get_damage(monster, gem), add_damage);
}

// Applies the combination of hydro and dendro effect to the `monster`
static void apply_hydro_dendro_effect(Monster *monster) {
    monster->effects.type[DENDRO_HYDRO_EFFECT] =
        get_element_effect(DENDRO_HYDRO_EFFECT, 0);
}

// Adds the effect of the element of the gem, if there's one, to the `monster`
// receiving the shot
static void add_monster_element_effect(Game *game, Monster *monster, Gem gem) {
    if (gem.type == NONE)
        return;

    unsigned int elements = gem.type | monster->residue;

    if (monster->residue == NONE)
        monster->residue = gem.type;
    else
        monster->residue = NONE;

    switch (elements) {
        case PYRO:
            apply_pyro_effect(game, monster, gem);
            break;
        case DENDRO:
            apply_dendro_effect(monster, gem);
            break;
        case HYDRO:
            apply_hydro_effect(monster);
            break;
        case PYRO | DENDRO:
            apply_pyro_dendro_effect(monster, gem, &game->total_damage);
            break;
        case PYRO | HYDRO:
            apply_pyro_hydro_effect(game, monster, gem);
            break;
        case HYDRO | DENDRO:
            apply_hydro_dendro_effect(monster);
            break;
        default:
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
void add_wave(Game *game) {
    double t_left = time_to(game->next_wave);
    if (game->wave_count > 1 && t_left > 25.) {
        // TODO: on introduit un temps minimum de 10 secondes (35 - 25)
        // entre chaque vague
        return;
    }
    wave_generation(&game->monsters, &game->map, game->wave_count);
    if (game->wave_count > 1) {
        mana_new_wave(&game->mana, t_left);
    }
    game->next_wave = time_future(35);
    game->wave_count++;
}

// Adds the selected gem of the inventory to the `tower` if the coordinates
// correspond to one
void add_activegem(Game *game, WindowInfo win, Coord tower) {
    ActiveGem *new_gem;
    if (tower.col >= MAP_WIDTH || tower.line >= MAP_HEIGHT)
        return;
    if (game->map.cells[CI(tower)].type == TOWER) {
        new_gem = add_to_activegemslist(
            &game->active_gems, game->inventory.gems[win.selected_gem], tower);
        remove_from_inventory(&game->inventory, win.selected_gem);
        remove_activegem(game, tower);
        game->map.cells[CI(tower)].gem = new_gem;
    }
}

// Removes the ActiveGem in the `tower` and puts it back in the inventory
void remove_activegem(Game *game, Coord tower) {
    ActiveGem *last_gem = game->map.cells[CI(tower)].gem;
    if (last_gem) {
        LIST_REMOVE(last_gem, entries);
        game->inventory.gems[game->inventory.size] = last_gem->gem;
        game->map.cells[CI(tower)].gem = NULL;
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
            apply_damage(monster, get_damage(monster, gem), &game->total_damage);
            add_monster_element_effect(game, monster, gem);
            if (is_dead_monster(monster)) {
                mana_eliminate_monster(&game->mana, monster);
                LIST_REMOVE(monster, entries);
                free_monster(monster);
                break;
            }
        }
    }
}

static Monster *find_monster_to_shoot(Coord tower_coord,
                                      MonsterList *monster_list) {
    const double tower_field_radius = 3.0;
    Monster *monster;
    Monster *monster_fit = NULL;
    get_next_monster_in_radius(monster_list,
                               coord_to_center_position(tower_coord),
                               tower_field_radius, true);
    while ((monster = get_next_monster_in_radius(
                monster_list, coord_to_center_position(tower_coord),
                tower_field_radius, false))) {
        if (!monster_fit || monster_fit->hp < monster->hp) {
            monster_fit = monster;
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
    Gem first_gem, second_gem;
    int tmp;

    if (!mana_fuse_gem(&game->mana, &game->error))
        return;

    first_gem = game->inventory.gems[gem1];
    second_gem = game->inventory.gems[gem2];
    if (first_gem.level != second_gem.level) {
        new_error(&game->error, SAME_LEVEL_GEM);
        return;
    }
    if (gem1 < gem2) {
        tmp = gem1;
        gem1 = gem2;
        gem2 = tmp;
    }
    remove_from_inventory(&game->inventory, gem1);
    remove_from_inventory(&game->inventory, gem2);
    add_to_inventory(&game->inventory, fuse_gems(first_gem, second_gem),
                     &game->error);
}

// Updates the `game` sinc the last update at `prev_time`
void update_game(Game *game, Timestamp prev_time) {

    if (game->wave_count > 1 && is_past_time(game->next_wave))
        add_wave(game);
    move_monsters(game, prev_time);
    move_shots(game, prev_time);
    activegems_fire(game);
    damage_monsters(game);
}

// Frees the allocated values of the Game
void free_game(Game *game) {
    free_monsters(&game->monsters);
    free_activegems(&game->active_gems);
}
