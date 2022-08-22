#pragma once

#include <memory>

#include "shape/shape.h"
#include "arr3.h"
#include "material/material.h"
#include "struct/hit_face_normal.h"

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
    hit_face_normal set_hit_face_normal(ray r, double t);
};
