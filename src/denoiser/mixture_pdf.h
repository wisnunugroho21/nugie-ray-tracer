#pragma once

#include "pdf.h"
#include "arr3.h"

#include <memory>

using std::shared_ptr;

class mixture_pdf : public pdf {
    private:
        shared_ptr<pdf> p[2];

    public:
        mixture_pdf(shared_ptr<pdf> p0, shared_ptr<pdf> p1);

        virtual double value(vector3 direction) override;
        virtual vector3 generate() override;
};