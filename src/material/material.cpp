#include "material/material.h"

color material::emitted(double u, double v, point3 p) {
	return color(0, 0, 0);
}

hit_record material::scatter(ray r_in, hit_record hit) {
	hit.scattered.is_scatter = false;
	return hit;
}

hit_record material::texturing(ray r_in, hit_record hit) {
	hit.emitted.clr = this->emitted(hit.text_coord.u, hit.text_coord.v, hit.p);
	return this->scatter(r_in, hit);
}