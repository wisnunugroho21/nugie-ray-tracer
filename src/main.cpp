#include <math.h>

#include "arr3.h"
#include "ray.h"

#include "camera/camera.h"
#include "helper/helper.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "material/diffuse_light.h"
#include "material/isotropic.h"
#include "struct/hit_record.h"
#include "texture/checker.h"
#include "texture/image_texture.h"
#include "texture/noise_texture.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list.h"
#include "hittable/bvh.h"
#include "hittable/shape/xy_rect.h"
#include "hittable/shape/yz_rect.h"
#include "hittable/shape/xz_rect.h"
#include "hittable/shape/sphere.h"
#include "hittable/shape/box.h"
#include "hittable/transform/translate.h"
#include "hittable/transform/rotate.h"
#include "hittable/volumetric/constant_medium.h"

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

	shared_ptr<hittable> box1 = make_shared<box>(point3(130, 0, 65), point3(295, 165, 230));
	objects.add(make_shared<gameobject>(box1, white));

	shared_ptr<hittable> box2 = make_shared<box>(point3(265, 0, 295), point3(430, 330, 460));
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

	shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165));
	box1 = make_shared<rotate_y>(box1, 15.0);
	box1 = make_shared<translate>(box1, vector3(265, 0, 295));
	objects.add(make_shared<gameobject>(box1, white));

	shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165, 165, 165));
	box2 = make_shared<rotate_y>(box2, -18.0);
	box2 = make_shared<translate>(box2, vector3(130, 0, 65));
	objects.add(make_shared<gameobject>(box2, white));

	return objects;
}

hittable_list random_scenes() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<hittable> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<hittable> obj_hittable;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
			}
		}
	}	

	shared_ptr<material> mat1 = make_shared<dielectric>(1.5);
	shared_ptr<hittable> shp1 = make_shared<sphere>(point3(0, 1, 0), 1);
	world.add(make_shared<gameobject>(shp1, mat1));

	shared_ptr<material> mat2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	shared_ptr<hittable> shp2 = make_shared<sphere>(point3(-4, 1, 0), 1);
	world.add(make_shared<gameobject>(shp2, mat2));

	shared_ptr<material> mat3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
	shared_ptr<hittable> shp3 = make_shared<sphere>(point3(4, 1, 0), 1);
	world.add(make_shared<gameobject>(shp3, mat3));	

	return world;
}

hittable_list random_scenes_light() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<hittable> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -12; a < 12; a++) {
		for (int b = -12; b < 12; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<hittable> obj_hittable;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
			}
		}
	}

	shared_ptr<material> mat1 = make_shared<dielectric>(1.5);
	shared_ptr<hittable> shp1 = make_shared<sphere>(point3(0, 1, 0), 1);
	world.add(make_shared<gameobject>(shp1, mat1));

	shared_ptr<material> mat2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	shared_ptr<hittable> shp2 = make_shared<sphere>(point3(-4, 1, 0), 1);
	world.add(make_shared<gameobject>(shp2, mat2));

	shared_ptr<material> mat3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
	shared_ptr<hittable> shp3 = make_shared<sphere>(point3(4, 1, 0), 1);
	world.add(make_shared<gameobject>(shp3, mat3));

	shared_ptr<material> light = make_shared<diffuse_light>(color(5.0, 5.0, 5.0));
	shared_ptr<hittable> shp4 = make_shared<xz_rect>(-3, 3, -3, 3, 3);
	world.add(make_shared<gameobject>(shp4, light));

	return world;
}

hittable_list random_scenes_rectangle() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<hittable> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -14; a < 14; a++) {
		for (int b = -14; b < 14; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<hittable> obj_hittable;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
			}
		}
	}

	shared_ptr<material> mat1 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	shared_ptr<hittable> shp1 = make_shared<box>(point3(-0.5, 0.5, -0.5), point3(0.5, 1.5, 0.5));
	world.add(make_shared<gameobject>(shp1, mat1));

	shared_ptr<material> mat2 = make_shared<dielectric>(1.5);
	shared_ptr<hittable> shp2 = make_shared<box>(point3(-3.5, 0.5, -0.5), point3(-2.5, 1.5, 0.5));
	world.add(make_shared<gameobject>(shp2, mat2));

	shared_ptr<material> mat3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
	shared_ptr<hittable> shp3 = make_shared<box>(point3(3.5, 0.5, -0.5), point3(4.5, 1.5, 0.5));
	world.add(make_shared<gameobject>(shp3, mat3));

	return world;
}

hittable_list mirror_random_scenes() {
	hittable_list world;

	shared_ptr<checker> text_ground = make_shared<checker>(color(1, 1, 1), color(0, 0, 0));
	shared_ptr<lambertian> mat_ground = make_shared<lambertian>(color(1, 1, 1));
	shared_ptr<hittable> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			double chosen_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> obj_mat;
				shared_ptr<hittable> obj_hittable;

				if (chosen_mat < 0.8) {
					color albedo = color::random() * color::random();

					obj_mat = make_shared<lambertian>(albedo);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else if (chosen_mat < 0.95) {
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0, 0.5);

					obj_mat = make_shared<metal>(albedo, fuzz);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
				else {
					obj_mat = make_shared<dielectric>(1.5);
					obj_hittable = make_shared<sphere>(center, 0.2);

					world.add(make_shared<gameobject>(obj_hittable, obj_mat));
				}
			}			
		}
	}	

	shared_ptr<material> glass_mat = make_shared<dielectric>(1.5);
	shared_ptr<hittable> rect = make_shared<sphere>(point3(0, 1, 0), 1);
	world.add(make_shared<gameobject>(rect, glass_mat));

	return world;
}

hittable_list earth() {
	hittable_list world;

	shared_ptr<texture> text_ground = make_shared<image_texture>("map.jpg");
	shared_ptr<material> mat_ground = make_shared<lambertian>(text_ground);
	shared_ptr<hittable> shp_ground = make_shared<sphere>(point3(0,0,0), 2);
	world.add(make_shared<gameobject>(shp_ground, mat_ground));

    return world;
}

hittable_list two_perlin_spheres() {
    hittable_list objects;

    auto pertext = make_shared<noise_texture>(10);
	auto mat = make_shared<lambertian>(pertext);

	auto sphere1 = make_shared<sphere>(point3(0, -1000, 0), 1000);
	objects.add(make_shared<gameobject>(sphere1, mat));

	auto sphere2 = make_shared<sphere>(point3(0, 2, 0), 2);
	objects.add(make_shared<gameobject>(sphere2, mat));

    return objects;
}

hittable_list final_scene() {
    hittable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

			auto box1 = make_shared<box>(point3(x0,y0,z0), point3(x1,y1,z1));
			boxes1.add(make_shared<gameobject>(box1, ground));
        }
    }

    hittable_list objects;

    objects.add(make_shared<bvh_node>(boxes1));

    auto light = make_shared<diffuse_light>(color(7.0, 7.0, 7.0));
	auto rect1 = make_shared<xz_rect>(123, 423, 147, 412, 554);
	objects.add(make_shared<gameobject>(rect1, light));	

    auto mat1 = make_shared<lambertian>(color(0.7, 0.3, 0.1));
	auto sphere1 = make_shared<sphere>(point3(400, 400, 200), 50);
	objects.add(make_shared<gameobject>(sphere1, mat1));

	auto mat2 = make_shared<dielectric>(1.5);
	auto sphere2 = make_shared<sphere>(point3(260, 150, 45), 50);
	objects.add(make_shared<gameobject>(sphere2, mat2));

	auto mat3 = make_shared<metal>(color(0.8, 0.8, 0.9), 1.0);
	auto sphere3 = make_shared<sphere>(point3(0, 150, 145), 50);
	objects.add(make_shared<gameobject>(sphere3, mat3));

	auto mat4 = make_shared<dielectric>(1.5);
	auto sphere4 = make_shared<sphere>(point3(360, 150, 145), 70);
	auto go1 = make_shared<gameobject>(sphere4, mat4);
	objects.add(go1);

	auto boundry1 = make_shared<constant_medium>(go1, 0.2);
	auto boundry1_mat = make_shared<isotropic>(color(0.2, 0.4, 0.9));
	objects.add(make_shared<gameobject>(boundry1, boundry1_mat));

	auto mat5 = make_shared<dielectric>(1.5);
	auto sphere5 = make_shared<sphere>(point3(0, 0, 0), 5000);
	auto go2 = make_shared<gameobject>(sphere5, mat5);
	auto boundry2 = make_shared<constant_medium>(go2, 0.0001);
	auto boundry2_mat = make_shared<isotropic>(color(1, 1, 1));
	objects.add(make_shared<gameobject>(boundry2, boundry2_mat));

	auto emat = make_shared<lambertian>(make_shared<image_texture>("map.jpg"));
	auto sphere6 = make_shared<sphere>(point3(400,200,400), 100);
	objects.add(make_shared<gameobject>(sphere6, emat));

	auto pertext = make_shared<noise_texture>(5);
	auto mat7 = make_shared<lambertian>(pertext);
	auto sphere7 = make_shared<sphere>(point3(220, 280, 300), 80);
	objects.add(make_shared<gameobject>(sphere7, mat7));

    hittable_list boxes2;
    auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
		auto sphere_small = make_shared<sphere>(point3::random(0, 165), 10);
		boxes2.add(make_shared<gameobject>(sphere_small, white));
    }

	auto node1 = make_shared<bvh_node>(boxes2);
	auto translate1 = make_shared<translate>(node1, vector3(-100, 270, 395));
	auto rotate1 = make_shared<rotate_y>(translate1, 15);
	objects.add(rotate1);

    return objects;
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

	hit_record res = world.hit(r, 0.001, infinity);
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
	int sample_per_pixel = 20;
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = static_cast<int> (image_width / aspect_ratio);

	hittable_list list;
	color background(0.7, 0.8, 1.0);

	point3 lookfrom;
	point3 lookto;
	point3 vup(0, 1, 0);
	auto vpov = 40.0;
	auto aperture = 0.0;
	auto dist_to_focus = 10.0;

	switch (7)
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
			list = random_scenes_light();
			background = color(0, 0, 0);
			lookfrom = point3(13, 5, 3);
			lookto = point3(0, 1, 0);
			vpov = 20.0;
			aperture = 0;
			break;
		case 6:
			list = earth();
			background = color(0.7, 0.8, 1.0);
			lookfrom = point3(13, 2, 3);
			lookto = point3(0, 0, 0);
			vpov = 20.0;
			aperture = 0;
			break;
		case 7:
			list = final_scene();
			background = color(0, 0, 0);
			lookfrom = point3(478, 278, -600);
			lookto = point3(278, 278, 0);
			vpov = 40.0;
			aperture = 0.0;
			break;
		case 8:
            list = two_perlin_spheres();
			background = color(0.7, 0.8, 1.0);
            lookfrom = point3(13, 2, 3);
            lookto = point3(0,0,0);
            vpov = 20.0;
			aperture = 0.0;
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

	std::ofstream outfile("image12.ppm");
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