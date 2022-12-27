#pragma once

#include "arr3.h"
#include "hit_face_normal.h"
#include "scattered_record.h"
#include "texture_coordinate.h"
#include "emitted_record.h"

struct hit_record
{
	bool is_hit = false;
	double t;
	point3 p;

	hit_face_normal face_normal;
	texture_coordinate text_coord;
	emitted_record emitted;
	scattered_record scattered;
};