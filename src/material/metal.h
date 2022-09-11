#pragma once

#include <memory>

#include "material/material.h"
#include "arr3.h"
#include "struct/scattered_record.h"
#include "texture/texture.h"
#include "texture/solid_color.h"

using namespace std;

class metal : public material
{
private:
    shared_ptr<texture> albedo;
    double fuzz;

protected:
    vector3 reflect(vector3 v, vector3 n);

public:
    metal(shared_ptr<texture> albedo, double fuzz);
    metal(color c, double fuzz);
  
    hit_record scatter(ray r_in, hit_record hit) override;
};