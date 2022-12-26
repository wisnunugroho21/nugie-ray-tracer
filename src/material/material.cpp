#include "material/material.h"

color material::emitted(double u, double v, point3 p) {
	return color(0, 0, 0);
}

hit_record material::scatter(ray r_in, hit_record hit) {
	hit.is_scatter = false;
	return hit;
}

hit_record material::texturing(ray r_in, hit_record hit) {
	hit.emitted = this->emitted(hit.u, hit.v, hit.p);
	return this->scatter(r_in, hit);
}