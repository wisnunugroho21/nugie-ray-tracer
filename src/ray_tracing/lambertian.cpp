#include "lambertian.h"

lambertian::lambertian(color albedo) {
    this->albedo = albedo;
}

scattered_record lambertian::scatter(ray r_in, hit_record hit) {
    scattered_record scat;
    point3 scatter_direction = hit.normal + arr3::random_unit_vector();

    if (scatter_direction.near_zero()) {
        scatter_direction = hit.normal;
    }

    scat.scattered = ray(hit.p, scatter_direction);
    scat.attenuation = this->albedo;
    scat.is_scatter = true;
    
    return scat;
}