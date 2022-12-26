#include "camera.h"

camera::camera(
	point3 lookfrom, point3 lookat, vector3 vup, 
	double vfov, double aspect_ratio, double aperture, 
	double focus_dist
)
{
	double theta = degrees_to_radians(vfov);
	double height = tan(theta / 2);
	double viewport_height = 2.0 * height;
	double viewport_width = aspect_ratio * viewport_height;

	this->w = (lookfrom - lookat).unit_vector();
	this->u = cross(vup, this->w).unit_vector();
	this->v = cross(this->w, this->u); 

	this->origin = lookfrom;
	this->horizontal = focus_dist * viewport_width * this->u;
	this->vertical = focus_dist * viewport_height * this->v;
	this->lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * this->w;

	this->lens_radius = aperture / 2;
}

ray camera::get_ray(double s, double t) {
	vector3 rd = this->lens_radius * arr3::random_in_unit_disk();
	vector3 offset = this->u * rd.x() + this->v * rd.y();

	return ray(
		this->origin + offset, 
		this->lower_left_corner + s * this->horizontal + t * this->vertical - this->origin - offset
	);
}