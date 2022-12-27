#pragma once

#include "arr3.h"
#include "ray.h"

struct face_normal
{	
	vector3 normal;
	bool front_face = false;

	static face_normal set_face_normal(ray r, vector3 hit_normal) {
		face_normal hitted_ray;

		hitted_ray.front_face = dot(r.direction(), hit_normal) < 0;
		hitted_ray.normal = hitted_ray.front_face ? hit_normal : -hit_normal;

		return hitted_ray;
	}
};