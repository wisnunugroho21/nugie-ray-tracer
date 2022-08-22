#pragma once

#include "ray.h"
#include "hit_record.h"
#include "scattered_record.h"

class material
{
public:
    virtual scattered_record scatter(ray r_in, hit_record hit) = 0;
};
