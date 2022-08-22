#pragma once

#include "material/material.h"
#include "arr3.h"
#include "struct/scattered_record.h"

class lambertian : public material
{
private:
    color albedo;

public:
    lambertian(color albedo);    
    scattered_record scatter(ray r_in, hit_record hit) override;
};