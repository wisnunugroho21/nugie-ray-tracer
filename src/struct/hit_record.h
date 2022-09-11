#pragma once

#include "arr3.h"

struct hit_record
{
    bool is_hit = false;
    bool is_scatter = false;

    point3 p;
    double t;

    vector3 normal;
    bool front_face;

    double u;
    double v;
    
    ray scattered;
    color attenuation;
    color emitted; 
};