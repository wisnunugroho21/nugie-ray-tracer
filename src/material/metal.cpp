#include "metal.h"

metal::metal(shared_ptr<texture> albedo, double fuzz) {
	this->albedo = albedo;
	this->fuzz = fuzz;
}

metal::metal(color c, double fuzz) {
	this->albedo = make_shared<solid_color>(c);
	this->fuzz = fuzz;
}

vector3 metal::reflect(vector3 v, vector3 n) {
	return v - 2 * dot(v, n) * n;
}

hit_record metal::scatter(ray r_in, hit_record hit) {
	point3 reflected = this->reflect(r_in.direction().unit_vector(), hit.normal);

	hit.scattered = ray(hit.p, reflected + this->fuzz * vector3::random_unit_length());
	hit.attenuation = this->albedo->value(hit.u, hit.v, hit.p);
	hit.is_scatter = (dot(reflected, hit.normal) > 0);
	
	return hit;
}