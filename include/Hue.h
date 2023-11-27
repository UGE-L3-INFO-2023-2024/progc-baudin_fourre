#ifndef __HUE_H__
#define __HUE_H__

#include "Element.h"

typedef int Hue;

/**
 * @brief Generates a random hue in the given element, if there's one
 * 
 * @param element Element from which to generate the hue, or NONE to generate any hue
 * @return Hue random hue generated
 */
Hue random_hue(Element element);

#endif // __HUE_H__
