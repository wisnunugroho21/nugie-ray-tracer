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

    /* cosine_pdf p1(hit.normal);

    hit.scattered = ray(hit.p, p1.generate());
    hit.pdf = p1.value(hit.scattered.direction()); */

    auto on_light = point3(random_double(213, 343), 554, random_double(227, 332));
    auto to_light = on_light - hit.p;
    auto distance_squared = to_light.length_squared();
    to_light = to_light.unit_vector();

    if (dot(to_light, hit.normal) < 0)
        hit.is_scatter = false;

    double light_area = (343 - 213) * (332 - 227);
    auto light_cosine = fabs(to_light.e2());

    if (light_cosine < 0.000001)
        hit.is_scatter = false;

    hit.pdf = distance_squared / (light_cosine * light_area);
    hit.scattered = ray(hit.p, to_light);

    hit.emitted = this->emitted(hit.u, hit.v, hit.p);
    hit.scattering_pdf = this->scattering_pdf(r_in, hit);

    return hit;
}