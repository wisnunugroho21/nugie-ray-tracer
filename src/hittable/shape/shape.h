#pragma once

#include "ray.h"
#include "hittable/hittable.h"
#include "struct/hit_record.h"
#include "struct/bounding_record.h"

class shape : public hittable
{
public:
    virtual hit_record hit(ray r, double t_min, double t_max) = 0;
    virtual bounding_record bounding_box() = 0;
};