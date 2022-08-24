#pragma once

#include "shape/shape.h"
#include "arr3.h"
#include "aabb.h"
#include "material/material.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

class yz_rect : public shape
{
private:
    double y0, y1, z0, z1, k;

public:
    yz_rect();
    yz_rect(double y0, double y1, double z0, double z1, double k);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;

    hit_face_normal set_hit_face_normal(ray r, double t);
    texture_coordinate get_uv(double y, double z);
};
