#include "lambertian.h"

lambertian::lambertian(shared_ptr<texture> albedo) {
    this->albedo = albedo;
}

lambertian::lambertian(color c) {
    this->albedo = make_shared<solid_color>(c);
}

hit_record lambertian::scatter(ray r_in, hit_record hit) {
    point3 scatter_direction = hit.normal + arr3::random_unit_vector();

    if (scatter_direction.near_zero()) {
        scatter_direction = hit.normal;
    }

    onb uvw;
    uvw.build_from_w(hit.normal);
    auto direction = uvw.local(arr3::random_cosine_direction());

    hit.scattered = ray(hit.p, scatter_direction.unit_vector());
    hit.attenuation = this->albedo->value(hit.u, hit.v, hit.p);
    hit.pdf = dot(uvw.w(), hit.scattered.direction()) / pi;

    hit.is_scatter = true;
    return hit;
}

double lambertian::scattering_pdf(ray r_in, hit_record hit) {
    auto cosine = dot(hit.normal, hit.scattered.direction().unit_vector());
    return cosine < 0 ? 0 : cosine / pi;
}