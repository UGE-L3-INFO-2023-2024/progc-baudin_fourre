#include "Element.h"

#include <stdio.h>
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
    int r = (rand() % interval + start) % 360;
    // printf("%d\n", r);
    return r;
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

// returns an initialized ElementEffect
ElementEffect init_element_effect(void) {
    ElementEffect effect = {
        .speed_mult = 1,
        .damage = 0,
        .damage_interval = 0,
        .timeout = time_now(),
    };
    return effect;
}

// Returns the ElementEffect associated to the EffectType `type`, according to
// the `damage` done by the shot
ElementEffect get_element_effect(EffectType type, double damage) {
    ElementEffect effect = {
        .speed_mult = 1,
        .damage = 0,
        .next_damage = time_now(),
        .damage_interval = 0,
    };
    switch (type) {
        case HYDRO_EFFECT:
            effect.speed_mult = 1 / 1.5;
            effect.timeout = time_future(10);
            break;
        case DENDRO_EFFECT:
            effect.damage = 0.025 * damage;
            effect.timeout = time_future(10);
            effect.damage_interval = 0.5;
            effect.next_damage = time_future(effect.damage_interval);
            break;
        case HYDRO_PYRO_EFFECT:
            effect.speed_mult = 1 / 1.25;
            effect.timeout = time_future(5);
            break;
        case DENDRO_HYDRO_EFFECT:
            effect.speed_mult = 0;
            effect.timeout = time_future(3);
            break;
    }
    return effect;
}
