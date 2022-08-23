#include "lambertian.h"

lambertian::lambertian(shared_ptr<texture> albedo) {
    this->albedo = albedo;
}

lambertian::lambertian(color c) {
    this->albedo = make_shared<solid_color>(c);
}

scattered_record lambertian::scatter(ray r_in, hit_record hit) {
    scattered_record scat;
    point3 scatter_direction = hit.normal + arr3::random_unit_vector();

    if (scatter_direction.near_zero()) {
        scatter_direction = hit.normal;
    }

    scat.scattered = ray(hit.p, scatter_direction);
    scat.attenuation = this->albedo->value(hit.u, hit.v, hit.p);
    scat.is_scatter = true;
    
    return scat;
}