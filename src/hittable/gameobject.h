#pragma once

#include <memory>

#include "arr3.h"
#include "material/material.h"
#include "shape/shape.h"
#include "struct/hit_record.h"
#include "struct/scattered_record.h"
#include "struct/hit_result.h"

using std::shared_ptr;

class gameobject
{
private:
    shared_ptr<shape> object_shape;
    shared_ptr<material> object_material;

public:
    gameobject(shared_ptr<shape> object_shape, shared_ptr<material> object_material);
    hit_result hit(ray r, double t_min, double t_max);
};
