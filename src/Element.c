#include "Element.h"
#include "Monsters.h"

#include <stdlib.h>

// Returns the element associated with the `hue`
static Element hue_to_element(Hue hue) {
    if (hue >= 330 || hue <= 30)
        return PYRO;
    else if (hue >= 90 && hue <= 150)
        return DENDRO;
    else if (hue >= 210 && hue <= 270)
        return HYDRO;
    else
        return NONE;
}

// calls the function producing the effect of the element 
// according to the `monster_residue` and the `shot_element`
static void get_element_effect(Element monster_residue, Element shot_element) {
    switch (monster_residue | shot_element) {
        case PYRO:
            break;
        case DENDRO:
            break;
        case HYDRO:
            break;
        case PYRO | DENDRO:
            break;
        case PYRO | HYDRO:
            break;
        case HYDRO | DENDRO:
            break;
    }
}

// Adds, if necessary, an element to the field `residue` of the monster, according to the `shot_hue`
void add_monster_residue(Monster *monster, Hue shot_hue) {
    Element shot_element = hue_to_element(shot_hue);
    if (shot_element == NONE)
        return;

    if (monster->residue == NONE)
        monster->residue = shot_element;
    else {
        get_element_effect(monster->residue, shot_element);
        monster->residue = NONE;
    }
}