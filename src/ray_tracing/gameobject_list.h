#pragma once

#include <memory>
#include <vector>

#include "hit_result.h"
#include "gameobject.h"

using std::shared_ptr;
using std::vector;

class gameobject_list
{
private:
    vector<shared_ptr<gameobject>> objects;

public:
    gameobject_list();
    gameobject_list(shared_ptr<gameobject> object);

    void clear();
    void add(shared_ptr<gameobject> object);
    vector<shared_ptr<gameobject>> getAll();

    hit_result hit(ray r, double t_min, double t_max);
};
