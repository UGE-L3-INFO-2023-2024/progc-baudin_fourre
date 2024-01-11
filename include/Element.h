#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "Timer.h"
#include <stdbool.h>

typedef int Hue;

typedef enum {
    NONE,
    PYRO = 1,
    DENDRO = 2,
    HYDRO = 4,
} Element;

typedef enum {
    HYDRO_EFFECT = 0,
    DENDRO_EFFECT = 1,
    HYDRO_PYRO_EFFECT = 2,
    DENDRO_HYDRO_EFFECT = 3,
} EffectType;

typedef struct {
    double speed_mult;
    double damage;
    Timestamp next_damage;
    Timestamp timeout;
} ElementEffect;

/**
 * @brief Initializes an ElementEffect
 *
 * @return ElementEffect the structure initialized
 */
ElementEffect init_element_effect(void);

/**
 * @brief Generates a random hue in the given element, if there's one
 *
 * @param element Element from which to generate the hue, or NONE to
 * generate any hue
 * @return Hue random hue generated
 */
Hue random_hue(Element element);

/**
 * @brief Returns the Element associated with the value of the `hue`
 *
 * @param hue
 * @return Element
 */
Element hue_to_element(Hue hue);

/**
 * @brief
 *
 * @param monster_residue
 * @param shot_element
 */
void get_element_effect(Element monster_residue, Element shot_element);

#endif // __ELEMENT_H__
