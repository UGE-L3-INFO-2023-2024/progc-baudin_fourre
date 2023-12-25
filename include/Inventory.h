#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Gems.h"

#define INVENTORY_SIZE 20

typedef struct {
    Gem gems[INVENTORY_SIZE];
    int size;
} Inventory;

#endif  // __INVENTORY_H__
