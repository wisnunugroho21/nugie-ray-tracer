#include "isotropic.h"

isotropic::isotropic(shared_ptr<texture> albedo) {
	this->albedo = albedo;
}

isotropic::isotropic(color c) {
	this->albedo = make_shared<solid_color>(c);
}

hit_record isotropic::scatter(ray r_in, hit_record hit) {
	hit.scattered.r = ray(hit.p, arr3::random_in_unit_sphere());
	hit.scattered.attenuation = this->albedo->value(hit.text_coord.u, hit.text_coord.v, hit.p);
	hit.scattered.is_scatter = true;

	return hit;
}


