#pragma once

#include "arr3.h"

struct hit_face_normal
{
	point3 p;
	vector3 normal;
	bool front_face = false;
};