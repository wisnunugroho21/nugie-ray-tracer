#pragma once

#include <memory>
#include <vector>

#include "shape/shape.h"
#include "arr3.h"
#include "aabb.h"
#include "material/material.h"
#include "struct/hit_face_normal.h"
#include "struct/bounding_record.h"
#include "struct/texture_coordinate.h"

#include "shape/xy_rect.h"
#include "shape/xz_rect.h"
#include "shape/yz_rect.h"

using namespace std;

class box : public shape
{
private:
    point3 p0, p1;
    vector<shared_ptr<shape>> rectangles;

public:
    box();
    box(point3 box_min, point3 box_max);

    hit_record hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
};
