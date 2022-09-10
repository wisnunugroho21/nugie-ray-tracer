#pragma once

#include <memory>

#include "ray.h"
#include "struct/hit_record.h"
#include "struct/bounding_record.h"
#include "hittable/shape/shape.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

using std::shared_ptr;
using std::make_shared;

class rotate_y : public shape
{
private:
    shared_ptr<shape> object;

    double sin_theta;
    double cos_theta;

    bool hasBox;
    aabb bbox;


public:
    rotate_y();
    rotate_y(shared_ptr<shape> object, double angle);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;

    hit_face_normal set_hit_face_normal(ray r, vector3 hit_normal);
};