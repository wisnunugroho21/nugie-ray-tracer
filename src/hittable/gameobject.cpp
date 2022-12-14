#include "gameobject.h"

gameobject::gameobject(shared_ptr<hittable> object_shape, shared_ptr<material> object_material) {
	this->object_shape = object_shape;
	this->object_material = object_material;
}

hit_record gameobject::hit(ray r, double t_min, double t_max) {
	hit_record hit = this->object_shape->hit(r, t_min, t_max);

	if (hit.is_hit) {
			hit = this->object_material->texturing(r, hit);
	}

	return hit;
}

bounding_record gameobject::bounding_box() {
	return this->object_shape->bounding_box();
}