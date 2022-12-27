#include "lambertian.h"

lambertian::lambertian(shared_ptr<texture> albedo) {
	this->albedo = albedo;
}

lambertian::lambertian(color c) {
	this->albedo = make_shared<solid_color>(c);
}

hit_record lambertian::scatter(ray r_in, hit_record hit) {
	point3 scatter_direction = hit.face_normal.normal + arr3::random_unit_vector();

	if (scatter_direction.near_zero()) {
		scatter_direction = hit.face_normal.normal;
	}

	hit.scattered.r = ray(hit.p, scatter_direction);
	hit.scattered.attenuation = this->albedo->value(hit.text_coord.u, hit.text_coord.v, hit.p);
	hit.scattered.is_scatter = true;
	
	return hit;
}