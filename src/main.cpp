#include <math.h>

#include "arr3.h"
#include "ray.h"
#include "shape/sphere.h"
#include "hittable/hittable_list.h"
#include "camera/camera.h"
#include "helper/helper.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "struct/hit_result.h"
#include "hittable/bvh.h"
#include "hittable/hittable.h"
#include "texture/checker.h"
#include "texture/image_texture.h"
#include "material/diffuse_light.h"
#include "shape/xy_rect.h"
#include "shape/yz_rect.h"
#include "shape/xz_rect.h"
#include "shape/box.h"
#include "transform/translate.h"
#include "transform/rotate.h"

#include <iostream>
#include <fstream>

using std::make_shared;

hittable_list cornell_box() {
	hittable_list objects;

	auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
	auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
	auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
	auto light = make_shared<diffuse_light>(color(15, 15, 15));

	auto rect1 = make_shared<yz_rect>(0, 555, 0, 555, 555);
	objects.add(make_shared<gameobject>(rect1, green));

	auto rect2 = make_shared<yz_rect>(0, 555, 0, 555, 0);
	objects.add(make_shared<gameobject>(rect2, red));

	auto rect3 = make_shared<xz_rect>(213, 343, 227, 332, 554);
	objects.add(make_shared<gameobject>(rect3, light));

	auto rect4 = make_shared<xz_rect>(0, 555, 0, 555, 0);
	objects.add(make_shared<gameobject>(rect4, white));

	auto rect5 = make_shared<xz_rect>(0, 555, 0, 555, 555);
	objects.add(make_shared<gameobject>(rect5, white));

	auto rect6 = make_shared<xy_rect>(0, 555, 0, 555, 555);
	objects.add(make_shared<gameobject>(rect6, white));

	shared_ptr<shape> box1 = make_shared<box>(point3(130, 0, 65), point3(295, 165, 230));
	objects.add(make_shared<gameobject>(box1, white));

	shared_ptr<shape> box2 = make_shared<box>(point3(265, 0, 295), point3(430, 330, 460));
	objects.add(make_shared<gameobject>(box2, white));

	return objects;
}

hittable_list translate_rotate_cornell_box() {
	hittable_list objects;

	auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
	auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
	auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
	auto light = make_shared<diffuse_light>(color(15, 15, 15));

	auto rect1 = make_shared<yz_rect>(0, 555, 0, 555, 555);
	objects.add(make_shared<gameobject>(rect1, green));

	auto rect2 = make_shared<yz_rect>(0, 555, 0, 555, 0);
	objects.add(make_shared<gameobject>(rect2, red));

	auto rect3 = make_shared<xz_rect>(213, 343, 227, 332, 554);
	objects.add(make_shared<gameobject>(rect3, light));

	auto rect4 = make_shared<xz_rect>(0, 555, 0, 555, 0);
	objects.add(make_shared<gameobject>(rect4, white));

	auto rect5 = make_shared<xz_rect>(0, 555, 0, 555, 555);
	objects.add(make_shared<gameobject>(rect5, white));

	auto rect6 = make_shared<xy_rect>(0, 555, 0, 555, 555);
	objects.add(make_shared<gameobject>(rect6, white));

	shared_ptr<shape> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165));
	box1 = make_shared<rotate_y>(box1, 15.0);
	box1 = make_shared<translate>(box1, vector3(265, 0, 295));
	objects.add(make_shared<gameobject>(box1, white));

	shared_ptr<shape> box2 = make_shared<box>(point3(0, 0, 0), point3(165, 165, 165));
	box2 = make_shared<rotate_y>(box2, -18.0);
	box2 = make_shared<translate>(box2, vector3(130, 0, 65));
	objects.add(make_shared<gameobject>(box2, white));

	return objects;
}

hittable_list random_scenes() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<shape> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<shape> obj_shape;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
			}
		}
	}	

	shared_ptr<material> mat1 = make_shared<dielectric>(1.5);
	shared_ptr<shape> shp1 = make_shared<sphere>(point3(0, 1, 0), 1);
	world.add(make_shared<gameobject>(shp1, mat1));

	shared_ptr<material> mat2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	shared_ptr<shape> shp2 = make_shared<sphere>(point3(-4, 1, 0), 1);
	world.add(make_shared<gameobject>(shp2, mat2));

	shared_ptr<material> mat3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
	shared_ptr<shape> shp3 = make_shared<sphere>(point3(4, 1, 0), 1);
	world.add(make_shared<gameobject>(shp3, mat3));

	return world;
}

hittable_list random_scenes_rectangle() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<shape> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -12; a < 12; a++) {
		for (int b = -12; b < 12; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<shape> obj_shape;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
			}
		}
	}

	shared_ptr<material> mat1 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	shared_ptr<shape> shp1 = make_shared<box>(point3(-0.5, 0.5, -0.5), point3(0.5, 1.5, 0.5));
	world.add(make_shared<gameobject>(shp1, mat1));

	shared_ptr<material> mat2 = make_shared<dielectric>(1.5);
	shared_ptr<shape> shp2 = make_shared<box>(point3(-3.5, 0.5, -0.5), point3(-2.5, 1.5, 0.5));
	world.add(make_shared<gameobject>(shp2, mat2));

	shared_ptr<material> mat3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
	shared_ptr<shape> shp3 = make_shared<box>(point3(3.5, 0.5, -0.5), point3(4.5, 1.5, 0.5));
	world.add(make_shared<gameobject>(shp3, mat3));

	return world;
}

hittable_list mirror_random_scenes() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(color(1, 1, 1));
	shared_ptr<shape> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<shape> obj_shape;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_shape = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_shape, obj_mat));
				}
			}			
		}
	}	

	shared_ptr<material> glass_mat = make_shared<dielectric>(1.5);
	shared_ptr<shape> rect = make_shared<sphere>(point3(0, 1, 0), 1);
	world.add(make_shared<gameobject>(rect, glass_mat));

	return world;
}

hittable_list earth() {
	hittable_list world;

	shared_ptr<texture> text_ground = make_shared<image_texture>("map.jpg");
	shared_ptr<material> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<shape> shp_ground = make_shared<sphere>(point3(0,0,0), 2);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

    return world;
}

void write_color(std::ofstream& ofl, color pixel_color, int sample_per_pixel) {
	double r = pixel_color.r();
	double g = pixel_color.g();
	double b = pixel_color.b();

	double scale = 1.0 / sample_per_pixel;

	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	ofl << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0, 0.999)) << "\n";
}

color ray_color(ray r, color background, hittable& world, int depth) {
	if (depth <= 0)
		return color(0, 0, 0);

	hit_result res = world.hit(r, 0.001, infinity);
	if (!res.is_hit) {
		return background;
	}

	if (!res.is_scatter) {
		return res.emitted;
	}

	return res.emitted + res.attenuation * ray_color(res.scattered, background, world, depth - 1);
}

int main(int argc, char const* argv[]) {

	int depth = 10;
	int sample_per_pixel = 10;
	double aspect_ratio = 1.0;
	int image_width = 300;
	int image_height = static_cast<int> (image_width / aspect_ratio);

	hittable_list list;
	color background;

	point3 lookfrom;
	point3 lookto;
	point3 vup(0, 1, 0);
	auto vpov = 40.0;
	auto aperture = 0.0;
	auto dist_to_focus = 10.0;

	switch (5)
	{
		case 0:
			list = random_scenes();
			background = color(0.7, 0.8, 1.0);
			lookfrom = point3(13, 2, 3);
			lookto = point3(0, 0, 0);
			vpov = 20.0;
			aperture = 0;
			break;
		case 1:
			list = cornell_box();
			background = color(0, 0, 0);
			lookfrom = point3(278, 278, -800);
			lookto = point3(278, 278, 0);
			vpov = 40.0;
			aperture = 0.0;
			break;
		case 2:
			list = mirror_random_scenes();
			background = color(0.7, 0.8, 1.0);
			lookfrom = point3(0, 1, -5);
			lookto = point3(0, 1, 0);
			vpov = 20.0;
			aperture = 0;
			break;
		case 3:
			list = translate_rotate_cornell_box();
			background = color(0, 0, 0);
			lookfrom = point3(278, 278, -800);
			lookto = point3(278, 278, 0);
			vpov = 40.0;
			aperture = 0.0;
			break;
		case 4:
			list = random_scenes_rectangle();
			background = color(0.7, 0.8, 1.0);
			lookfrom = point3(13, 2, 3);
			lookto = point3(0, 0, 0);
			vpov = 20.0;
			aperture = 0;
			break;
		case 5:
			list = earth();
			background = color(0.7, 0.8, 1.0);
			lookfrom = point3(13, 2, 3);
			lookto = point3(0, 0, 0);
			vpov = 20.0;
			aperture = 0;
			break;

		default:
			break;
	}

	// ----- World ----- //    
	// hittable_list world = list;
	bvh_node world(list);

	// ----- Camera ----- //
	camera cam = camera(lookfrom, lookto, vup, vpov, aspect_ratio, aperture, dist_to_focus);

	// ----- Render ----- //

	std::ofstream outfile("image.ppm");
	outfile << "P3\n" << image_width << " " << image_height << "\n255\n";

	std::cerr << image_height;

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;

		for (int i = 0; i < image_width; ++i) {
			color pixel_color = color(0, 0, 0);

			for (int k = 0; k < sample_per_pixel; k++) {
				double u = double(i + random_double()) / (image_width - 1);
				double v = double(j + random_double()) / (image_height - 1);

				ray r = cam.get_ray(u, v);
				pixel_color = ray_color(r, background, world, depth) + pixel_color;
			}

			write_color(outfile, pixel_color, sample_per_pixel);
		}
	}

	outfile.close();
	std::cerr << "\nDone!!\n";

	return 0;
}