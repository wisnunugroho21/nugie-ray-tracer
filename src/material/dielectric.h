#pragma once

#include <math.h>
#include <memory>

#include "material/material.h"
#include "arr3.h"
#include "helper/helper.h"
#include "struct/scattered_record.h"
#include "texture/texture.h"
#include "texture/solid_color.h"

using namespace std;

class dielectric : public material
{
private:
	double ir;
	shared_ptr<texture> albedo;

protected:
	vector3 reflect(vector3 v, vector3 n);
	vector3 refract(vector3 uv, vector3 n, double etai_over_etat);
	double reflectance(double cosine, double ref_idx);

public:
	dielectric(double index_of_refraction);
	dielectric(shared_ptr<texture> albedo, double index_of_refraction);
	dielectric(color c, double index_of_refraction);

	hit_record scatter(ray r_in, hit_record hit) override;
};