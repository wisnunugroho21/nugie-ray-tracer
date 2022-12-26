#pragma once

#include <memory>

#include "material/material.h"
#include "arr3.h"
#include "struct/scattered_record.h"
#include "texture/solid_color.h"
#include "texture/texture.h"

using namespace std;

class diffuse_light : public material
{
private:
	shared_ptr<texture> emit;

public:
	diffuse_light(shared_ptr<texture> emit);
	diffuse_light(color c);

	color emitted(double u, double v, point3 p) override;
};