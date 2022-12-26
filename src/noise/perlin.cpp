#include "perlin.h"

perlin::perlin() {
	for(int i = 0; i < this->point_count; i++) {
		this->ranvec.push_back(
			arr3::random(-1, 1).unit_vector()
		);
	}

	this->perm_x = this->perlin_generate_perm();
	this->perm_y = this->perlin_generate_perm();
	this->perm_z = this->perlin_generate_perm();
}

perlin::~perlin() {
	this->ranvec.clear();
	this->perm_x.clear();
	this->perm_y.clear();
	this->perm_z.clear();
}

double perlin::noise(point3 p) {
	auto u = p.x() - floor(p.x());
	auto v = p.y() - floor(p.y());
	auto w = p.z() - floor(p.z());

	auto i = static_cast<int>(floor(p.x()));
	auto j = static_cast<int>(floor(p.y()));
	auto k = static_cast<int>(floor(p.z()));

	vector3 c[2][2][2];

	for(int di = 0; di < 2; di++) {
		for(int dj = 0; dj < 2; dj++) {
			for(int dk = 0; dk < 2; dk++) {
				c[di][dj][dk] = this->ranvec.at(
					this->perm_x.at((i + di) & 255) ^
					this->perm_y.at((j + dj) & 255) ^
					this->perm_z.at((k + dk) & 255)
				);
			}
		}
	}

	return this->trilinear_interp(c, u, v, w);
}

 std::vector<int> perlin::perlin_generate_perm() {
	std::vector<int> p;

	for(int i = 0; i < this->point_count; i++) {
		p.push_back(i);
	}

	return this->permute(p, this->point_count);
 }

 std::vector<int> perlin::permute(std::vector<int> p, int n) {
	for (int i = n - 1; i > 0; i--) {
		int target = rand_int(0, i);

		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}

	return p;
 }

 double perlin::trilinear_interp(vector3 c[2][2][2], double u, double v, double w) {
	auto uu = u * u *(3 - 2 * u);
	auto vv = v * v *(3 - 2 * v);
	auto ww = w * w *(3 - 2 * w);

	auto accum = 0.0;
	
	for (int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				vector3 weight_v(u - i, v - j, w - k);
				
				accum += 
					(i * uu + (1 - i) * (1 - uu)) * 
					(j * vv + (1 - j) * (1 - vv)) *
					(k * ww + (1 - k) * (1 - ww)) * 
					dot(c[i][j][k], weight_v);
			}
		}
	}

	return accum;
 }

 double perlin::turbl(point3 p, int depth) {
	auto accum = 0.0;
	auto temp_p = p;
	auto weight = 1.0;

	for (int i = 0; i < depth; i++) {
		accum += weight * this->noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}

	return fabs(accum);
 }