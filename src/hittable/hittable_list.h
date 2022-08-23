#pragma once

#include <memory>
#include <vector>

#include "aabb.h"
#include "hittable/hittable.h"
#include "struct/hit_result.h"
#include "struct/bounding_record.h"
#include "hittable/gameobject.h"

using std::shared_ptr;
using std::vector;

class hittable_list : public hittable
{
public:
    vector<shared_ptr<hittable>> objects;

    hittable_list();
    hittable_list(shared_ptr<hittable> object);

    void clear();
    void add(shared_ptr<hittable> object);
    vector<shared_ptr<hittable>> getAll();

    hit_result hit(ray r, double t_min, double t_max) override;
    bounding_record bounding_box() override;
};
