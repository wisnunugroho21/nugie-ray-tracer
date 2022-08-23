#include "checker.h"

checker::checker(shared_ptr<solid_color> first_color, shared_ptr<solid_color> second_color) {
    this->even = first_color;
    this->odd = second_color;
}

checker::checker(solid_color first_color, solid_color second_color) {
    this->even = make_shared<solid_color>(first_color);
    this->odd = make_shared<solid_color>(second_color);
}

color checker::value(double u, double v, point3 p) {
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

    if (sines < 0) {
        return this->odd->value(u, v, p);
    } 

    return this->even->value(u, v, p);
}