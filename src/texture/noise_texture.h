#pragma once

#include "texture/texture.h"
#include "noise/perlin.h"

#include <memory>

class noise_texture : public texture
{
private:
	std::shared_ptr<perlin> noise;
	double scale;
    
public:
	noise_texture();
	noise_texture(double scale);

	color value(double u, double v, point3 p) override;
};
