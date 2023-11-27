/**
 * @file Hue.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief 
 * @date 2023-11-25
 * 
 */

#include "Hue.h"
#include "Element.h"

#include <stdlib.h>

Hue random_hue(Element element){
    int start, interval;
    switch(element) {
        case PYRO :
            start = 330;
            interval = 60;
            break;
        case DENDRO :
            start = 90;
            interval = 60;
            break;
        case HYDRO:
            start = 210;
            interval = 60;
            break;
        case NONE :
            start = 0;
            interval = 360;
            break;
    }
    return (rand() % interval + start) % 360;
}