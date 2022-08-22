#pragma once

#include "ray.h"
#include "struct/hit_record.h"

class shape
{
public:
    shape();
    virtual hit_record hit(ray r, double t_min, double t_max) = 0;
};