/**
 * @file Color.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing to create and manages colors from the MLV
 * library (MLV_Color)
 * @date 2023-12-25
 *
 */

#ifndef __COLOR_H__
#define __COLOR_H__

#include <MLV/MLV_color.h>

#include "Element.h"

#define GRID_COLOR      MLV_COLOR_GREY
#define NEST_COLOR      MLV_COLOR_RED
#define HOME_COLOR      MLV_COLOR_GREEN
#define PATH_COLOR      MLV_COLOR_WHITE
#define BKGD_COLOR      MLV_COLOR_GREY
#define TOWER_COLOR     MLV_COLOR_BLACK
#define RIGHT_BAR_COLOR MLV_COLOR_LIGHT_GREY
#define SELECTED_COLOR  MLV_rgba(0, 0, 0, 100)
#define TRANSPARANT     MLV_rgba(255, 255, 255, 0)

/**
 * @brief Calculates the RGBA color from the Hue
 *
 * @param hue Hue to convert to RGBA
 * @return the RGBA color converted as an MLV_Color
 */
MLV_Color hue_to_rgba(Hue hue);

#endif // __COLOR_H__
