#pragma once

#include <memory>

#include "arr3.h"
#include "hittable/hittable.h"
#include "material/material.h"
#include "struct/hit_record.h"
#include "struct/scattered_record.h"
#include "struct/hit_record.h"
#include "struct/bounding_record.h"

using std::shared_ptr;

class gameobject : public hittable
{
private:
    shared_ptr<hittable> object_shape;
    shared_ptr<material> object_material;

public:
    gameobject(shared_ptr<hittable> object_shape, shared_ptr<material> object_material);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
};
