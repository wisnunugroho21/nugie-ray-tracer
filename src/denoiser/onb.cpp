#include "onb.h"

 onb::onb()
 {

 }

vector3 onb::operator[](int i)
{
    return this->axis[i];
}

vector3 onb::u()
{
    return this->axis[0];
}

vector3 onb::v()
{
    return this->axis[1];
}

vector3 onb::w()
{
    return this->axis[2];
}

vector3 onb::local(double a, double b, double c)
{
    return a * this->u() + b * this->v() + c * this->w();
}

vector3 onb::local(vector3 a)
{
    return a.x() * this->u() + a.y() * this->v() + a.z() * this->w();
}

void onb::build_from_w(vector3 n) 
{
    this->axis[2] = n.unit_vector();

    vector3 a = (fabs(this->w().x()) > 0.9) ? vector3(0, 1, 0) : vector3(1, 0, 0);
    this->axis[1] = cross(this->w(), a).unit_vector();
    this->axis[0] = cross(this->w(), this->v());
}
