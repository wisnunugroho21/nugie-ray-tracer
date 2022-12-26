#pragma once

#include "math.h"
#include "arr3.h"
#include "helper/helper.h"

#include <vector>

class perlin {
	private:
		int point_count = 256;

		std::vector<vector3> ranvec;
		std::vector<int> perm_x;
		std::vector<int> perm_y;
		std::vector<int> perm_z;

		std::vector<int> perlin_generate_perm();
		std::vector<int> permute(std::vector<int> p, int n);
		double trilinear_interp(vector3 c[2][2][2], double u, double v, double w);

	public:
		perlin();
		~perlin();
		double noise(const point3 p);
		double turbl(point3 p, int depth = 7);
};