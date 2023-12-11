#include "Element.h"

#include <stdlib.h>

#include "Monsters.h"

// Generates a random hue in the range of the `element`
Hue random_hue(Element element) {
    int start, interval;
    switch (element) {
    case PYRO:
        start = 330;
        interval = 60;
        break;
    case DENDRO:
        start = 90;
        interval = 60;
        break;
    case HYDRO:
        start = 210;
        interval = 60;
        break;
    case NONE:
        start = 0;
        interval = 360;
        break;
    }
    return (rand() % interval + start) % 360;
}

// Returns the element associated with the `hue`
Element hue_to_element(Hue hue) {
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
void get_element_effect(Element monster_residue, Element shot_element) {
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
