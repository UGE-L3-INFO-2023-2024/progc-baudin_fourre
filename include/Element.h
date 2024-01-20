/**
 * @file Elements.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing the creation and management of Elements
 * and their effects (ElementEffect)
 * @date 2023-11-16
 *
 */

#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "Timer.h"
#include <stdbool.h>

/**
 * @brief Hue as an integer between 0 and 360
 */
typedef int Hue;

/**
 * @brief Enumerates the different elements, can be combined with bitwise OR
 */
typedef enum {
    NONE,
    PYRO = 1,
    DENDRO = 2,
    HYDRO = 4,
} Element;

/**
 * @brief Enumerates the different persistent effects
 */
typedef enum {
    HYDRO_EFFECT = 0,
    DENDRO_EFFECT = 1,
    HYDRO_PYRO_EFFECT = 2,
    DENDRO_HYDRO_EFFECT = 3,
} EffectType;

/**
 * @brief Structure representing an ElementEffect
 */
typedef struct {
    double speed_mult;
    double damage;
    double damage_interval;
    Timestamp next_damage;
    Timestamp timeout;
} ElementEffect;

/**
 * @brief Gets the median hue between `hue1` and `hue2`
 *
 * @param hue1 the first hue
 * @param hue2 the second hue
 * @return the median hue
 */
Hue get_median_hue(Hue hue1, Hue hue2);

/**
 * @brief Initializes an ElementEffect
 *
 * @return ElementEffect the structure initialized
 */
ElementEffect init_element_effect(void);

/**
 * @brief Generates a random hue in the given element, if there's one
 *
 * @param element Element from which to generate the hue (if NONE, generate any
 * hue)
 * @return Hue random hue generated
 */
Hue random_hue(Element element);

/**
 * @brief Returns the Element associated with the value of the `hue`
 *
 * @param hue the hue to convert
 * @return the element associated with the hue
 */
Element hue_to_element(Hue hue);

/**
 * @brief Gets the ElementEffect according to its type
 *
 * @param type type of the effect to return
 * @param damage Current damage of the shot producing the ElementEffect
 * @return the ElementEffect produced
 */
ElementEffect get_element_effect(EffectType type, double damage);

#endif // __ELEMENT_H__
