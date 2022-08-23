#pragma once

#include <memory>
#include <cmath>

#include "texture/texture.h"
#include "texture/solid_color.h"
#include "arr3.h"

using namespace std;

class checker : public texture
{
private:
    shared_ptr<solid_color> even;
    shared_ptr<solid_color> odd;

public:
    checker(shared_ptr<solid_color> first_color, shared_ptr<solid_color> second_color);
    checker(solid_color first_color, solid_color second_color);

    color value(double u, double v, point3 p) override;
};
