#pragma once

#include "arr3.h"

class pdf {
    public:
        virtual double value(const vector3 direction) = 0;
        virtual vector3 generate() = 0;
};