#include "bvh.h"

#include <iostream>

bvh_node::bvh_node() {

}

bvh_node::bvh_node(vector<shared_ptr<hittable>> objects) {
    int axis = rand_int(0, 2);
    auto comparator = (axis == 0) ? bvh_node::box_compare_x
                    : (axis == 1) ? bvh_node::box_compare_y
                                : bvh_node::box_compare_z;

    if (objects.size() == 1) {
        this->left = this->right = objects[0];
    } else if (objects.size() == 2) {
        if (comparator(objects[0], objects[1])) {
            this->left = objects[0];
            this->right = objects[1];
        } else {
            this->left = objects[1];
            this->right = objects[0];
        }        
    } else {
        std::sort(objects.begin(), objects.end(), comparator);
        auto mid = static_cast<int>(objects.size() / 2);

        vector<shared_ptr<hittable>> leftObj;
        for (unsigned i = 0; i < mid; i++)
            leftObj.push_back(objects.at(i));

        vector<shared_ptr<hittable>> rightObj;
        for (unsigned j = mid; j < objects.size(); j++)
            rightObj.push_back(objects.at(j));
        
        this->left = make_shared<bvh_node>(leftObj);
        this->right = make_shared<bvh_node>(rightObj);
    }

    bounding_record bound_left = this->left->bounding_box();
    bounding_record bound_right = this->right->bounding_box();

    this->box = aabb::surrounding_box(bound_left.bounding_box, bound_right.bounding_box);    
}

bounding_record bvh_node::bounding_box() {
    bounding_record bound;

    bound.is_hit = true;
    bound.bounding_box = this->box;

    return bound;
}

hit_result bvh_node::hit(ray r, double t_min, double t_max) {
    hit_result res;

    if (!this->box.hit(r, t_min, t_max)) {
        return res;
    }
    
    res = this->right->hit(r, t_min, t_max);
    if (res.is_hit) {
        return res;
    }

    res = this->left->hit(r, t_min, t_max);
    return res;
}

bool bvh_node::box_compare(shared_ptr<hittable> a, shared_ptr<hittable> b, int axis) {
    bounding_record bound_a = a->bounding_box();
    bounding_record bound_b = b->bounding_box();

    return bound_a.bounding_box.min()[axis] < bound_b.bounding_box.min()[axis];
}

bool bvh_node::box_compare_x(shared_ptr<hittable> a, shared_ptr<hittable> b) {
    return bvh_node::box_compare(a, b, 0);
}

bool bvh_node::box_compare_y(shared_ptr<hittable> a, shared_ptr<hittable> b) {
    return bvh_node::box_compare(a, b, 1);
}

bool bvh_node::box_compare_z(shared_ptr<hittable> a, shared_ptr<hittable> b) {
    return bvh_node::box_compare(a, b, 2);
}