#pragma once

#include "pdf.h"
#include "onb.h"
#include "arr3.h"

class cosine_pdf : public pdf {
    private:
        onb uvw;

    public:
        cosine_pdf(vector3 w);

        double value(vector3 direction) override;
        vector3 generate() override;
};