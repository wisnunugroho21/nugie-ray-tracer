#pragma once

#include <memory>

#include "shape.h"
#include "arr3.h"
#include "aabb.h"
#include "material/material.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

using std::shared_ptr;

class sphere : public shape
{
private:
    point3 center;
    double radius;

public:
    sphere();
    sphere(point3 center, double radius);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;

    hit_face_normal set_hit_face_normal(ray r, double t);
    texture_coordinate get_uv(point3 p);
};
