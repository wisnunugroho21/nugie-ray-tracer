#include "material/material.h"

color material::emitted(double u, double v, point3 p) {
    return color(0, 0, 0);
}

hit_record material::scatter(ray r_in, hit_record hit) {
    hit.is_scatter = false;
    return hit;
}

double material::scattering_pdf(ray r_in, hit_record hit) {
    return 0;
}