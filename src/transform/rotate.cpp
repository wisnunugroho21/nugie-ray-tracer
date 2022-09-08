#include "rotate.h"

rotate_y::rotate_y(shared_ptr<shape> object, double angle) {
	this->object = object;

	auto radians = degrees_to_radians(angle);
	this->sin_theta = sin(radians);
	this->cos_theta = cos(radians);

	bounding_record bound = this->object->bounding_box();
	this->hasBox = bound.is_hit;
	this->bbox = bound.bounding_box;

	point3 min(infinity, infinity, infinity);
	point3 max(-infinity, -infinity, -infinity);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				auto x = i * this->bbox.max().x() + (1 - i) * this->bbox.min().x();
				auto y = j * this->bbox.max().y() + (1 - j) * this->bbox.min().y();
				auto z = k * this->bbox.max().z() + (1 - k) * this->bbox.min().z();

				auto newX = this->cos_theta * x + this->sin_theta * z;
				auto newZ = -1 * this->sin_theta * x + this->cos_theta * z;

				vector3 tester(newX, y, newZ);

				for (int c = 0; c < 3; c++) {
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}
			}
		}
	}

	this->bbox = aabb(min, max);
}

hit_record rotate_y::hit(ray r, double t_min, double t_max) {
	auto origin = r.origin();
	auto direction = r.direction();

	origin[0] = this->cos_theta * r.origin()[0] - this->sin_theta * r.origin()[2];
	origin[2] = this->sin_theta * r.origin()[0] + this->cos_theta * r.origin()[2];

	direction[0] = this->cos_theta * r.direction()[0] - this->sin_theta * r.direction()[2];
	direction[2] = this->sin_theta * r.direction()[0] + this->cos_theta * r.direction()[2];

	ray rotated_r(origin, direction);

	hit_record hit = this->object->hit(rotated_r, t_min, t_max);
	if (hit.is_hit) {
		auto p = hit.p;
		auto normal = hit.normal;

		p[0] = this->cos_theta * hit.p[0] + this->sin_theta * hit.p[2];
		p[2] = -1 * this->sin_theta * hit.p[0] + this->cos_theta * hit.p[2];

		normal[0] = this->cos_theta * hit.normal[0] + this->sin_theta * hit.normal[2];
		normal[2] = -1 * this->sin_theta * hit.normal[0] + this->cos_theta * hit.normal[2];		

		hit_face_normal hitted_ray = this->set_hit_face_normal(rotated_r, normal);

		hit.p = p;
		hit.front_face = hitted_ray.front_face;
		hit.normal = hitted_ray.normal;
	}

	return hit;
}

bounding_record rotate_y::bounding_box() {
	bounding_record bound;

	bound.is_hit = this->hasBox;
	bound.bounding_box = this->bbox;

	return bound;
}

hit_face_normal rotate_y::set_hit_face_normal(ray r, vector3 hit_normal) {
	hit_face_normal hitted_ray;

	hitted_ray.front_face = dot(r.direction(), hit_normal) < 0;
	hitted_ray.normal = hitted_ray.front_face ? hit_normal : -hit_normal;

	return hitted_ray;
}
