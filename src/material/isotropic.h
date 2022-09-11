#pragma once

#include <memory>

#include "arr3.h"
#include "ray.h"
#include "material.h"
#include "texture/texture.h"
#include "texture/solid_color.h"
#include "helper/helper.h"

using namespace std;

class isotropic : public material
{
private:
    shared_ptr<texture> albedo;

public:
    isotropic(shared_ptr<texture> albedo);
    isotropic(color c);

    hit_record scatter(ray r_in, hit_record hit) override;
};
