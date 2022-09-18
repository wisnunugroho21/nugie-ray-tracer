#pragma once

#include "ray.h"
#include "struct/hit_record.h"
#include "hittable/hittable.h"
#include "denoiser/hittable_pdf.h"
#include "denoiser/cosine_pdf.h"
#include "denoiser/mixture_pdf.h"

#include <memory>

using std::shared_ptr;
using std::make_shared;

class material
{   
protected:
    virtual color emitted(double u, double v, point3 p);
    virtual hit_record scatter(ray r_in, hit_record hit);
    virtual double scattering_pdf(ray r_in, hit_record hit);

public:
    virtual hit_record texturing(ray r_in, hit_record hit);
};
