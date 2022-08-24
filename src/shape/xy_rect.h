#pragma once

#include "shape/shape.h"
#include "arr3.h"
#include "aabb.h"
#include "material/material.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

class xy_rect : public shape
{
private:
    double x0, x1, y0, y1, k;

public:
    xy_rect();
    xy_rect(double x0, double x1, double y0, double y1, double k);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;

    hit_face_normal set_hit_face_normal(ray r, double t);
    texture_coordinate get_uv(double x, double y);
};
