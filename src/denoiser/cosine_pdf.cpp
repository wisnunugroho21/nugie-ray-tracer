#include "cosine_pdf.h"

cosine_pdf::cosine_pdf(vector3 w)
{
    this->uvw.build_from_w(w);
}

double cosine_pdf::value(vector3 direction)
{
    auto cosine = dot(direction.unit_vector(), uvw.w());
    return (cosine <= 0) ? 0 : cosine / pi;
}

vector3 cosine_pdf::generate()
{
    return this->uvw.local(arr3::random_cosine_direction());
}