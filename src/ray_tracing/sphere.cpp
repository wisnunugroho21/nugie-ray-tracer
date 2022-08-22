#include <math.h>

#include "sphere.h"
#include <iostream>

sphere::sphere() : shape()
{

}

sphere::sphere(point3 center, double radius) : shape()
{
    this->center = center;
    this->radius = radius;
}

hit_record sphere::hit(ray r, double t_min, double t_max)
{
    vector3 oc = r.origin() - this->center;

    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - this->radius * this->radius;

    double discriminant = b * b - 4 * a * c;

    hit_record hit;
    double root;

    if (discriminant >= 0) {
        hit.is_hit = true;

        root = (-b - sqrt(discriminant)) / (2.0 * a);
        if (root < t_min || root > t_max) {
            root = (-b + sqrt(discriminant)) / (2.0 * a);            
            if (root < t_min || root > t_max) {
                hit.is_hit = false;
            }
        }
    }

    if (hit.is_hit) {
        hit.t = root;

        hit_face_normal hitted_ray = this->set_hit_face_normal(r, hit.t);

        hit.p = hitted_ray.p;
        hit.front_face = hitted_ray.front_face;
        hit.normal = hitted_ray.normal;
    }

    return hit;
}

hit_face_normal sphere::set_hit_face_normal(ray r, double t) {
    hit_face_normal hitted_ray;
    hitted_ray.p = r.at(t);

    vector3 outward_normal = (hitted_ray.p - this->center) / this->radius;
    
    hitted_ray.front_face = dot(r.direction(), outward_normal) < 0;
    hitted_ray.normal = hitted_ray.front_face ? outward_normal : -outward_normal;   

    return hitted_ray;
}