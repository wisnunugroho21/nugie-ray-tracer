#include "mixture_pdf.h"

mixture_pdf::mixture_pdf(shared_ptr<pdf> p0, shared_ptr<pdf> p1)
{
    this->p[0] = p0;
    this->p[1] = p1;
}

double mixture_pdf::value(vector3 direction)
{
    return 0.5 * this->p[0]->value(direction) + 0.5 * this->p[1]->value(direction);
}

vector3 mixture_pdf::generate()
{
    if (random_double() < 0.5)
        return this->p[0]->generate();
    else
        return this->p[1]->generate();
}