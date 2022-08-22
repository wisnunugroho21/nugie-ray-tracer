#pragma once

#include "arr3.h"
#include "ray.h"

struct hit_result {
    bool is_hit = false;
    color attenuation;
    ray scattered;
};