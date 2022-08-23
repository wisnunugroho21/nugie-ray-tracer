#pragma once

#include "texture/texture.h"
#include "arr3.h"

class solid_color : public texture
{
private:
    color color_value;

public:
    solid_color(color c);
    solid_color(double r, double g, double b) : solid_color(color(r, g, b)) {}

    color value(double u, double v, point3 p) override;
};
