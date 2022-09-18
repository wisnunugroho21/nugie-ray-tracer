#pragma once

#include "arr3.h"
#include "math.h"

class onb
{
private:
    vector3 axis[3];

public:
    onb();

    vector3 operator[](int i);

    vector3 u();
    vector3 v();
    vector3 w();

    vector3 local(double a, double b, double c);
    vector3 local(vector3 a);

    void build_from_w(vector3 n);
};
