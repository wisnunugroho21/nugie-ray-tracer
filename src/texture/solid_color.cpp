#include "solid_color.h"

solid_color::solid_color(color c) {
    this->color_value = c;
}

color solid_color::value(double u, double v, point3 p){
    return this->color_value;
}