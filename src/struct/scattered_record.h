#pragma once

#include "arr3.h"
#include "ray.h"

struct scattered_record {
    bool is_scatter = false;
    color attenuation;
    ray scattered;
};