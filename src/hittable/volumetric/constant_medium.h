#pragma once

#include "arr3.h"
#include "hittable/hittable.h"
#include "texture/texture.h"
#include "struct/face_normal.h"
#include "helper/helper.h"

#include <memory>

using namespace std;

class constant_medium : public hittable
{
private:
    shared_ptr<hittable> boundary;
    double neg_inv_density;

public:
    constant_medium(shared_ptr<hittable> b, double d);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
};
