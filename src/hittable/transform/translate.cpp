#include "translate.h"

translate::translate() {
}

translate::translate(shared_ptr<hittable> object, vector3 offset) {
	this->object = object;
	this->offset = offset;
}

hit_record translate::hit(ray r, double t_min, double t_max) {
	ray moved_r(r.origin() - this->offset, r.direction());
	hit_record hit = this->object->hit(moved_r, t_min, t_max);

	if (hit.is_hit) {		
		hit_face_normal hitted_ray = ray::set_hit_face_normal(moved_r, hit.normal);

		hit.p += this->offset;
		hit.front_face = hitted_ray.front_face;
		hit.normal = hitted_ray.normal;
	}

	return hit;
}

bounding_record translate::bounding_box() {
	bounding_record bound = this->object->bounding_box();

	if (bound.is_hit) {
		bound.bounding_box = aabb(
			bound.bounding_box.min() + this->offset,
			bound.bounding_box.max() + this->offset
		);
	}
	
	return bound;
}
