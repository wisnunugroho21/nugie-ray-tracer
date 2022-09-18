#include "hittable_pdf.h"

hittable_pdf::hittable_pdf(shared_ptr<hittable> p, const point3 origin)
{
    this->ptr = p;
    this->origin = origin;
}

double hittable_pdf::value(vector3 direction)
{
    return this->ptr->pdf_value(this->origin, direction);
}

vector3 hittable_pdf::generate()
{
    return this->ptr->random(this->origin);
}