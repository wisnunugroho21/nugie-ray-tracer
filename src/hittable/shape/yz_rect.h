#pragma once

#include "arr3.h"
#include "aabb.h"
#include "hittable/hittable.h"
#include "material/material.h"
#include "struct/face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

class yz_rect : public hittable
{
private:
    double y0, y1, z0, z1, k;

public:
    yz_rect();
    yz_rect(double y0, double y1, double z0, double z1, double k);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
    texture_coordinate get_uv(double y, double z);
};
