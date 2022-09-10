#include "isotropic.h"

isotropic::isotropic(shared_ptr<texture> albedo) {
    this->albedo = albedo;
}

isotropic::isotropic(color c) {
    this->albedo = make_shared<solid_color>(c);
}

scattered_record isotropic::scatter(ray r_in, hit_record hit) {
    scattered_record scat;

    scat.scattered = ray(hit.p, arr3::random_in_unit_disk());
    scat.attenuation = this->albedo->value(hit.u, hit.v, hit.p);
    scat.is_scatter = true;

    return scat;
}


