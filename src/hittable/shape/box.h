#pragma once

#include <memory>
#include <vector>

#include "arr3.h"
#include "aabb.h"
#include "hittable/hittable.h"
#include "material/material.h"
#include "struct/face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

#include "xy_rect.h"
#include "xz_rect.h"
#include "yz_rect.h"

using namespace std;

class box : public hittable
{
private:
    point3 p0, p1;
    vector<shared_ptr<hittable>> rectangles;

public:
    box();
    box(point3 box_min, point3 box_max);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
};
