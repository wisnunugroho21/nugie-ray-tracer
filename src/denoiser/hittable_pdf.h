#pragma once

#include "pdf.h"
#include "hittable/hittable.h"

#include "memory"

using std::shared_ptr;

class hittable_pdf : public pdf {
    private:
        point3 origin;
        shared_ptr<hittable> ptr;

    public:
        hittable_pdf(shared_ptr<hittable> p, const point3 origin);

        double value(vector3 direction) override;
        vector3 generate() override;
};