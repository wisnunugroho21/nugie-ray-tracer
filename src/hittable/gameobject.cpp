#include "gameobject.h"

gameobject::gameobject(shared_ptr<shape> object_shape, shared_ptr<material> object_material) {
    this->object_shape = object_shape;
    this->object_material = object_material;
}

hit_result gameobject::hit(ray r, double t_min, double t_max) {
    hit_result res;

    hit_record hit = this->object_shape->hit(r, t_min, t_max);
    res.is_hit = hit.is_hit;

    if (hit.is_hit) {
        scattered_record scat = this->object_material->scatter(r, hit);
        res.emitted = this->object_material->emitted(hit.u, hit.v, hit.p);        
        res.is_scatter = scat.is_scatter;        

        if (scat.is_scatter) {   
            res.attenuation = scat.attenuation;
            res.scattered = scat.scattered;            
        }
    }

    return res;
}

bounding_record gameobject::bounding_box() {
    return this->object_shape->bounding_box();
}