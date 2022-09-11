#include "dielectric.h"

dielectric::dielectric(double index_of_refraction) {
    this->ir = index_of_refraction;
    this->albedo = make_shared<solid_color>(color(1.0, 1.0, 1.0));
}

dielectric::dielectric(shared_ptr<texture> albedo, double index_of_refraction) {
    this->ir = index_of_refraction;
    this->albedo = albedo;
}

dielectric::dielectric(color c, double index_of_refraction) {
    this->ir = index_of_refraction;
    this->albedo = make_shared<solid_color>(c);
}

vector3 dielectric::reflect(vector3 v, vector3 n) {
    return v - 2 * dot(v, n) * n;
}

vector3 dielectric::refract(vector3 uv, vector3 n, double etai_over_etat) {
    double cos_theta = fmin(dot(-uv, n), 1.0);
    vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;

    return r_out_perp + r_out_parallel;
}

hit_record dielectric::scatter(ray r_in, hit_record hit) {    
    double refraction_ratio = hit.front_face ? (1.0 / ir) : ir;
    vector3 unit_direction = r_in.direction().unit_vector();

    double cost_theta = fmin(dot(-unit_direction, hit.normal), 1.0);
    double sin_theta = sqrt(1.0 - cost_theta * cost_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vector3 direction;

    if (cannot_refract || this->reflectance(cost_theta, refraction_ratio) > random_double()) {
        direction = this->reflect(unit_direction, hit.normal);
    } else {
        direction = this->refract(unit_direction, hit.normal, refraction_ratio);
    }

    hit.scattered = ray(hit.p, direction);
    hit.is_scatter = true;
    hit.attenuation = this->albedo->value(hit.u, hit.v, hit.p);

    return hit;
}

double dielectric::reflectance(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}