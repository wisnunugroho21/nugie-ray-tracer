#include "image_texture.h"
#include "helper/image_helper.h"

image_texture::image_texture(const char* filename) {
	auto component_per_pixel= this->bytes_per_pixel;

	data = stbi_load(filename, &(this->width), &(this->height), &component_per_pixel, component_per_pixel);

	if (!data) {
			std::cerr << "ERROR: Could not load texture file " << filename << " \n";
			this->width = this->height = 0;
	}

	this->bytes_per_scanline = this->bytes_per_pixel * width;
}

image_texture::~image_texture() {
	delete this->data;
}

color image_texture::value(double u, double v, point3 p) {
	if (this->data == nullptr) {
			return color(0, 1, 1);
	}

	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0);

	auto i = static_cast<int>(u * this->width);
	auto j = static_cast<int>(v * this->height);

	if (i >= this->width) i = this->width - 1;
	if (j >= this->height) j = this->height - 1;

	const auto color_scale = 1.0 / 255.0;
	auto pixel = this->data + j * this->bytes_per_scanline + i * this->bytes_per_pixel;

	return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}



