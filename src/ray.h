#pragma once

#include "arr3.h"
#include "struct/hit_face_normal.h"

class ray
{
private:
	vector3 org;
	vector3 dir;

public:
	ray();
	ray(point3 origin, vector3 direction);

	point3 origin();
	vector3 direction();

	vector3 at(double t);

	static hit_face_normal set_hit_face_normal(ray r, vector3 hit_normal);
};