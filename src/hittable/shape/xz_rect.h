#pragma once

#include "arr3.h"
#include "aabb.h"
#include "hittable/hittable.h"
#include "material/material.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

class xz_rect : public hittable
{
private:
	double x0, x1, z0, z1, k;

public:
	xz_rect() {};
	xz_rect(double x0, double x1, double z0, double z1, double k);

	hit_record hit(ray r, double t_min, double t_max) override;
	bounding_record bounding_box() override;
	texture_coordinate get_uv(double x, double z);
};
