#include "gameobject_list.h"

gameobject_list::gameobject_list()
{

}

gameobject_list::gameobject_list(shared_ptr<gameobject> object)
{
    this->add(object);
}

void gameobject_list::clear()
{
    this->objects.clear();
}

void gameobject_list::add(shared_ptr<gameobject> object)
{
    this->objects.push_back(object);
}

hit_result gameobject_list::hit(ray r, double t_min, double t_max)
{
    hit_result hitted;
    double closest = t_max;

    for (shared_ptr<gameobject> object : this->objects) {
        hit_result hit = object->hit(r, t_min, closest);

        if (hit.is_hit) {
            hitted = hit;
        }
    }

    return hitted;
}