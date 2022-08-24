#include "diffuse_light.h"

diffuse_light::diffuse_light(shared_ptr<texture> emit) {
    this->emit = emit;
}

diffuse_light::diffuse_light(color c) {
    this->emit = make_shared<solid_color>(c);
}

scattered_record diffuse_light::scatter(ray r_in, hit_record hit) {
    scattered_record scat;
    scat.is_scatter = false;

    return scat;
}

color diffuse_light::emitted(double u, double v, point3 p) {
    return this->emit->value(u, v, p);
}