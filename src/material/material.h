#pragma once

#include "ray.h"
#include "struct/hit_record.h"

class material
{
protected:
    virtual color emitted(double u, double v, point3 p);
    virtual hit_record scatter(ray r_in, hit_record hit);
    virtual double scattering_pdf(ray r_in, hit_record hit);

public:
    virtual hit_record texturing(ray r_in, hit_record hit);
};
