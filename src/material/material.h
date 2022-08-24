#pragma once

#include "ray.h"
#include "struct/hit_record.h"
#include "struct/scattered_record.h"

class material
{
public:
    virtual color emitted(double u, double v, point3 p);
    virtual scattered_record scatter(ray r_in, hit_record hit) = 0;
};
