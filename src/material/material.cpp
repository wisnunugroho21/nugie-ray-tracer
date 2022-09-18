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

hit_record material::texturing(ray r_in, hit_record hit) {
    hit = this->scatter(r_in, hit);

    hit.emitted = this->emitted(hit.u, hit.v, hit.p);
    hit.scattering_pdf = this->scattering_pdf(r_in, hit);

    return hit;
}