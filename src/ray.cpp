#include "ray.h"

ray::ray() {

}

ray::ray(point3 origin, vector3 direction)
{
    this->org = origin;
    this->dir = direction;
}

point3 ray::origin()
{
    return this->org;
}

vector3 ray::direction()
{
    return this->dir;
}

vector3 ray::at(double t)
{
    vector3 a = this->org;
    vector3 b = t * this->dir;

    return a + b;
}

hit_face_normal ray::set_hit_face_normal(ray r, vector3 hit_normal) {
    hit_face_normal hitted_ray;

    hitted_ray.front_face = dot(r.direction(), hit_normal) < 0;
    hitted_ray.normal = hitted_ray.front_face ? hit_normal : -hit_normal;

    return hitted_ray;
}