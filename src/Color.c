/**
 * @file Color.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing to create and manages colors from the MLV
 * library (MLV_Color)
 * @date 2023-12-25
 *
 */

#include "Color.h"

#include <MLV/MLV_all.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>

#include "Element.h"

// assign the values (r, g, b) to (*R, *G, *B)
static void
assign_rgb(double *R, double *G, double *B, double r, double g, double b) {
    *R = r;
    *G = g;
    *B = b;
}

// Returns the RGBA representation of the Hue `hue`
MLV_Color hue_to_rgba(Hue hue) {
    assert(hue >= 0 && hue < 360);
    double H = hue / 60.0;
    double L = .6;
    double S = 1.;
    double R = 0., G = 0., B = 0.;
    double C = (1 - fabs(2 * L - 1)) * S;
    double X = C * (1 - fabs(fmod(H, 2) - 1));
    double m = L - C / 2;
    switch (hue / 60) {
        case 0:
            assign_rgb(&R, &G, &B, C, X, 0);
            break;
        case 1:
            assign_rgb(&R, &G, &B, X, C, 0);
            break;
        case 2:
            assign_rgb(&R, &G, &B, 0, C, X);
            break;
        case 3:
            assign_rgb(&R, &G, &B, 0, X, C);
            break;
        case 4:
            assign_rgb(&R, &G, &B, X, 0, C);
            break;
        case 5:
            assign_rgb(&R, &G, &B, C, 0, X);
            break;
        default:
            break;
    }
    return MLV_rgba((uint8_t) ((R + m) * 255),
                    (uint8_t) ((G + m) * 255),
                    (uint8_t) ((B + m) * 255),
                    255);
}
