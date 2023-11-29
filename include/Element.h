#ifndef __ELEMENT_H__
#define __ELEMENT_H__

typedef int Hue;

typedef enum {
    NONE,
    PYRO = 1,
    DENDRO = 2,
    HYDRO = 4,
} Element;

/**
 * @brief Generates a random hue in the given element, if there's one
 *
 * @param element Element from which to generate the hue, or NONE to generate any hue
 * @return Hue random hue generated
 */
Hue random_hue(Element element);

Element hue_to_element(Hue hue);

void get_element_effect(Element monster_residue, Element shot_element);

#endif // __ELEMENT_H__
