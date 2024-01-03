#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Gems.h"

#define INVENTORY_SIZE 20

typedef struct {
    Gem gems[INVENTORY_SIZE];
    int size;
} Inventory;

/**
 * @brief Removes the gem of the given index from the inventory
 *
 * @param inventory address of the Inventory to remove the gem from
 * @param index index of the gem, between 0 and size - 1
 */
void remove_from_inventory(Inventory *inventory, int index);

#endif  // __INVENTORY_H__
