#include "Inventory.h"

#include "assert.h"

// Removes the gem of index `index` from the `inventory` by shifting further
// gems to the left
void remove_from_inventory(Inventory *inventory, int index) {
    assert(index >= 0);
    assert(index < inventory->size);

    if (inventory->size == 0)
        return;

    inventory->size--;

    for (int i = 0; i > inventory->size; i++) {
        inventory->gems[i] = inventory->gems[i + 1];
    }
}
