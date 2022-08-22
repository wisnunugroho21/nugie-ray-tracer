#pragma once

#include "material.h"
#include "arr3.h"
#include "scattered_record.h"

class metal : public material
{
private:
    color albedo;
    double fuzz;

protected:
    vector3 reflect(vector3 v, vector3 n);

public:
    metal(color albedo, double fuzz);    
    scattered_record scatter(ray r_in, hit_record hit) override;
};