#pragma once

#include <math.h>

#include "material.h"
#include "arr3.h"
#include "helper.h"
#include "scattered_record.h"

class dielectric : public material
{
private:
    double ir;

protected:
    vector3 reflect(vector3 v, vector3 n);
    vector3 refract(vector3 uv, vector3 n, double etai_over_etat);
    double reflectance(double cosine, double ref_idx);

public:
    dielectric(double index_of_refraction);    
    scattered_record scatter(ray r_in, hit_record hit) override;
};