#include "noise_texture.h"

noise_texture::noise_texture() {
    this->noise = std::make_shared<perlin>();
}

noise_texture::noise_texture(double scale) {
    this->scale = scale;
    this->noise = std::make_shared<perlin>();
}

color noise_texture::value(double u, double v, point3 p) {
    return color(1.0, 1.0, 1.0) * 0.5 * (1.0 + sin(scale * p.z() + 10 * this->noise->turbl(this->scale * p)));
}