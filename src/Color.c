#include "Color.h"

#include <assert.h>
#include <math.h>

#include "Element.h"

// assign the values (r, g, b) to (*R, *G, *B)
static void assign_rgb(double *R, double *G, double *B, double r, double g,
                       double b) {
    *R = r;
    *G = g;
    *B = b;
}

// Returns the RGBA representation of the Hue `hue`
MLV_Color hue_to_rgba(Hue hue) {
    assert(hue < 360);
    double H = hue / 60.0;
    double L = 0.6;
    double S = 1.0;
    double R, G, B;
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
    }
    return MLV_rgba((R + m) * 255, (G + m) * 255, (B + m) * 255, 255);
}
