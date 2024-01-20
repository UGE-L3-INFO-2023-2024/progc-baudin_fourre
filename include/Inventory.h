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

#define INVENTORY_SIZE 20

/**
 * @brief Structure representing the inventory
 */
typedef struct {
    Gem gems[INVENTORY_SIZE];
    int size;
} Inventory;

/**
 * @brief Adds the `gem` to the inventory, if possible
 *
 * @param inventory the inventory to add the gem to
 * @param gem the gem to add
 * @param error the Error structure to modify if the inventory max is reached
 * @return int 1 if the gem could be added, 0 otherwise
 */
int add_to_inventory(Inventory *inventory, Gem gem, Error *error);

/**
 * @brief Removes the gem of the given index from the inventory
 *
 * @param inventory the Inventory to remove the gem from
 * @param index index of the gem, between 0 and size - 1
 */
void remove_from_inventory(Inventory *inventory, int index);

#endif // __INVENTORY_H__
