#pragma once

#include "helper/helper.h"
#include "texture/texture.h"
#include "arr3.h"

#include <iostream>

class image_texture : public texture
{
private:
	const static int bytes_per_pixel = 3;
	unsigned char *data;
	int width, height;
	int bytes_per_scanline;

public:
	image_texture(const char* filename);
	~image_texture();

	color value(double u, double v, point3 p) override;
};

