#pragma once

#include <memory>

#include "material/material.h"
#include "arr3.h"
#include "struct/scattered_record.h"
#include "texture/solid_color.h"
#include "texture/texture.h"

using namespace std;

class lambertian : public material
{
private:
    shared_ptr<texture> albedo;

public:
    lambertian(shared_ptr<texture> albedo);
    lambertian(color c);

    hit_record scatter(ray r_in, hit_record hit) override;
    double scattering_pdf(ray r_in, hit_record hit) override;
};