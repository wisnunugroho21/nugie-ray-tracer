#pragma once

#include "arr3.h"
#include "ray.h"

struct hit_result {
    bool is_hit = false;
    bool is_scatter = false;
    
    ray scattered;

    color attenuation;
    color emitted;    
};