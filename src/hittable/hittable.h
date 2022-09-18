#pragma once

#include "ray.h"
#include "struct/hit_record.h"
#include "struct/bounding_record.h"

class hittable
{
public:
    virtual hit_record hit(ray r, double t_min, double t_max) = 0;
    virtual bounding_record bounding_box() = 0;

    virtual double pdf_value(point3 o, vector3 v);
    virtual vector3 random(vector3 o);
};
