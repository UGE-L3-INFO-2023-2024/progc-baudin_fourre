#include "Gems.h"

#include <stdio.h>
#include <stdlib.h>

#include "Element.h"
#include "Map.h"
#include "Timer.h"

// Generates a random pure gem of level `level` by first choosing its type, and
// then its hue
Gem generate_pure_gem(int level) {
    Gem gem;
    gem.damage_mult = 1;
    gem.level = level;
    gem.type = 1 << (rand() % 3);
    gem.hue = random_hue(gem.type);
    return gem;
}

// Returns the resulting em of the fusion of `first` and `second`
Gem fuse_gems(Gem first, Gem second) {
    Gem new_gem;
    new_gem.hue = (first.hue + second.hue) / 2;
    new_gem.level = first.level + 1;
    if (first.type == second.type) {
        new_gem.type = first.type;
        new_gem.damage_mult = 1;
    } else {
        new_gem.type = NONE;
        new_gem.damage_mult = rand() % 10 ? 2 : 4;
    }
    return new_gem;
}

// Allocates a new ActiveGem for the `gem`.
// Returns the address of the ActiveGem allocated, or NULL if there was an
// error.
static ActiveGem *create_new_activegem(Gem gem, Coord tower) {
    // Timestamp instant_time;
    ActiveGem *active_gem = malloc(sizeof(ActiveGem));
    if (!active_gem) {
        perror("Crash on active gem allocation");
        exit(EXIT_FAILURE);
    }
    *active_gem = (ActiveGem){
        .gem = gem,
        .tower = tower,
        .start_time = time_future(2),
        // Random shot interval between 1 and 2 seconds
        .shot_interval = ((rand() % 5) + 6) / 10.,
    };
    active_gem->next_shot = active_gem->start_time;

    return active_gem;
}

// Adds the `gem` at the head of the `activegem_list`
ActiveGem *add_to_activegemslist(ActiveGemList *activegem_list, Gem gem,
                                 Coord tower) {
    ActiveGem *activegem = create_new_activegem(gem, tower);
    if (!activegem)
        return NULL;
    LIST_INSERT_HEAD(activegem_list, activegem, entries);

    return activegem;
}

// Frees the space allocated for the list of active gems
void free_activegems(ActiveGemList *activegems) {
    ActiveGem *activegem = NULL;
    while (!LIST_EMPTY(activegems)) {
        activegem = LIST_FIRST(activegems);
        LIST_REMOVE(activegem, entries);
        free(activegem);
        activegem = NULL;
    }
}
