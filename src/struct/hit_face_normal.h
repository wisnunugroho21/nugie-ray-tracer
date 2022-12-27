#pragma once

#include "arr3.h"
#include "ray.h"

struct hit_face_normal
{	
	vector3 normal;
	bool front_face = false;

	static hit_face_normal set_hit_face_normal(ray r, vector3 hit_normal) {
		hit_face_normal hitted_ray;

		hitted_ray.front_face = dot(r.direction(), hit_normal) < 0;
		hitted_ray.normal = hitted_ray.front_face ? hit_normal : -hit_normal;

		return hitted_ray;
	}
};