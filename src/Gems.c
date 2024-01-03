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

// Allocates a new ActiveGem for the `gem`.
// Returns the address of the ActiveGem allocated, or NULL if there was an
// error.
static ActiveGem *create_new_activegem(Gem gem, Coord tower) {
    Timestamp instant_time;
    ActiveGem *active_gem = (ActiveGem *)malloc(sizeof(ActiveGem));
    if (!active_gem) {
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }

    active_gem->gem = gem;
    active_gem->tower = tower;
    active_gem->start_time = time_future(2);
    active_gem->next_shot = active_gem->start_time;
    // Random shot interval between 1 and 2 seconds
    active_gem->shot_interval = rand() / RAND_MAX + 1.;

    return active_gem;
}

// Adds the `gem` at the head of the `activegem_list`
int add_to_activegemslist(ActiveGemList *activegem_list, Gem gem,
                          Coord tower) {
    ActiveGem *activegem = create_new_activegem(gem, tower);
    if (!activegem)
        return 0;
    LIST_INSERT_HEAD(activegem_list, activegem, entries);
    return 1;
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
