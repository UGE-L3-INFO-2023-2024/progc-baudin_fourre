/**
 * @file Inventory.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions used to manage the addition and removal of Gems in
 * an Inventory
 * @date 2023-11-16
 *
 */

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Error.h"
#include "Gems.h"

#include <math.h>

#define INVENTORY_SIZE 20

typedef struct {
    Gem gems[INVENTORY_SIZE];
    int size;
} Inventory;

/**
 * @brief Adds the `gem` to the inventory, if possible
 *
 * @param inventory Address of the Inventory to add the gem to
 * @param gem Gem to add
 * @param error Address of the Error structure to modify if the inventory max is
 * reached
 * @return int 1 if the gem could be added, 0 otherwise
 */
int add_to_inventory(Inventory *inventory, Gem gem, Error *error);

/**
 * @brief Removes the gem of the given index from the inventory
 *
 * @param inventory address of the Inventory to remove the gem from
 * @param index index of the gem, between 0 and size - 1
 */
void remove_from_inventory(Inventory *inventory, int index);

#endif // __INVENTORY_H__
