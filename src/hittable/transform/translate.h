#pragma once

#include <memory>

#include "ray.h"
#include "hittable/hittable.h"
#include "struct/hit_record.h"
#include "struct/bounding_record.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

using std::shared_ptr;
using std::make_shared;

class translate : public hittable
{
private:
	shared_ptr<hittable> object;
	vector3 offset;

public:
	translate() {};
	translate(shared_ptr<hittable> object, vector3 offset);

	hit_record hit(ray r, double t_min, double t_max) override;
	bounding_record bounding_box() override;
};