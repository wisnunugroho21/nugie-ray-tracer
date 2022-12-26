#pragma once

#include <math.h>

#include "arr3.h"
#include "ray.h"
#include "helper/helper.h"

class camera
{
	private:
		point3 origin;
		point3 lower_left_corner;
		vector3 horizontal;
		vector3 vertical;
		vector3 u, v, w;
		double lens_radius;

	public:
    camera(
			point3 lookfrom, point3 lookat, vector3 vup, 
			double vfov, double aspect_ratio, double aperture, 
			double focus_dist
    );

    ray get_ray(double u, double v);
};
