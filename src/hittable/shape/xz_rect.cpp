#include "xz_rect.h"

xz_rect::xz_rect(double x0, double x1, double z0, double z1, double k) {
	this->x0 = x0;
	this->x1 = x1;
	this->z0 = z0;
	this->z1 = z1;
	this->k = k;
}

hit_record xz_rect::hit(ray r, double t_min, double t_max) {
	hit_record hit;
	hit.is_hit = true;

	auto t = (k - r.origin().y()) / r.direction().y();
	if (t < t_min || t > t_max) {
			hit.is_hit = false;
	}

	auto x = r.origin().x() + t * r.direction().x();
	auto z = r.origin().z() + t * r.direction().z();

	if (x < this->x0 || x > this->x1 || z < this->z0 || z > this->z1) {
			hit.is_hit = false;
	}

	if (hit.is_hit) {
		hit.t = t;
		hit.p = r.at(hit.t);

		vector3 outward_normal = vector3(0, 1, 0);

		hit_face_normal hitted_ray = ray::set_hit_face_normal(r, outward_normal);
		texture_coordinate txc = this->get_uv(x, z);

		hit.front_face = hitted_ray.front_face;
		hit.normal = hitted_ray.normal;

		hit.u = txc.u;
		hit.v = txc.v;
	}

	return hit;
}

bounding_record xz_rect::bounding_box() {
	bounding_record bound;

	bound.is_hit = true;
	bound.bounding_box = aabb(
		point3(this->x0, k - 0.001, this->z0), 
		point3(this->x1, k + 0.001, this->z1)
	);

	return bound;
}

texture_coordinate xz_rect::get_uv(double x, double z) {
	texture_coordinate txc;

	txc.u = (x - this->x0) / (this->x1 - this->x0);
	txc.v = (z - this->z0) / (this->z1 - this->z0);

	return txc;
}