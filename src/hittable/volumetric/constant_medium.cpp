#include "constant_medium.h"

constant_medium::constant_medium(shared_ptr<hittable> b, double d) {
    this->boundary = b;
    this->neg_inv_density = -1 / d;
}

bounding_record constant_medium::bounding_box() {
    return this->boundary->bounding_box();
}

hit_record constant_medium::hit(ray r, double t_min, double t_max) {
    hit_record rec_res;

    hit_record rec1 = this->boundary->hit(r, -infinity, infinity);
    if (!rec1.is_hit) return rec_res;

    hit_record rec2 = this->boundary->hit(r, rec1.t + 0.0001, infinity);
    if (!rec2.is_hit) return rec_res;

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t = t_max;

    if (rec1.t >= rec2.t) return rec_res;
    if (rec1.t < 0) rec1.t = 0;

    auto ray_length = r.direction().length();
    auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    auto hit_distance = neg_inv_density * log(random_double());

    if (hit_distance > distance_inside_boundary) return rec_res;  

    rec_res.t = rec1.t + hit_distance / ray_length;
    rec_res.p = r.at(rec_res.t);

    rec_res.face_normal.normal = arr3(1.0, 0.0, 0.0);
    rec_res.face_normal.front_face = true;
    rec_res.is_hit = true;

    return rec_res;
}