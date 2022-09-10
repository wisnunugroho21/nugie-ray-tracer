#pragma once

#include "arr3.h"
#include "texture/texture.h"
#include "shape/shape.h"
#include "struct/hit_face_normal.h"
#include "helper/helper.h"

#include <memory>

using namespace std;

class constant_medium : public shape
{
private:
    shared_ptr<shape> boundary;
    double neg_inv_density;

public:
    constant_medium(shared_ptr<shape> b, double d);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
};
