/**
 * @file Monsters.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief 
 * @date 2023-11-25
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>

#include "Monsters.h"
#include "Element.h"
#include "Hue.h"

// Returns the adress of the new Monster created with the given arguments
Monster *create_new_monster(int speed, int HP, timestamp start_time, Position position){
    Monster *monster = (Monster *)malloc(sizeof(Monster));
    if (!monster){
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }
    monster->hp = HP;
    monster->hp_init = HP;
    monster->hue = random_hue(NONE);
    monster->position = position;
    monster->residue = NONE;
    LIST_INIT(&(monster->shots));
    monster->speed = speed;
    monster->start_time = start_time;
    return monster;
}

// Frees the space allocated for the list of monsters
void free_monsters(MonsterList *monsters) {
    Monster *monster = NULL;
    while (!LIST_EMPTY(monsters)) {
        monster = LIST_FIRST(monsters);
        LIST_REMOVE(monster, entries);
        free(monster);
        monster = NULL;
    }
}
