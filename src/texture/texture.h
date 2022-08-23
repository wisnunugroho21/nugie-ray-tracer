#pragma once

#include "arr3.h"

class texture
{
public:
    virtual color value(double u, double v, point3 p) = 0;
};
