#include "Inventory.h"
#include "Error.h"

// Adds the `gem` to the `inventory`, if possible
int add_to_inventory(Inventory *inventory, Gem gem, Error *error) {
    if (inventory->size >= INVENTORY_SIZE) {
        new_error(error, INVENTORY_MAX);
        return 0;
    }
    inventory->gems[inventory->size] = gem;
    inventory->size++;
    return 1;
}

// Removes the gem of index `index` from the `inventory` by shifting further
// gems to the left
void remove_from_inventory(Inventory *inventory, int index) {
    if (inventory->size == 0)
        return;

    inventory->size--;

    for (int i = index; i < inventory->size; i++) {
        inventory->gems[i] = inventory->gems[i + 1];
    }
}
