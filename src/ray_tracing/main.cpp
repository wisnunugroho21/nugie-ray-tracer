#include <math.h>

#include "arr3.h"
#include "ray.h"
#include "sphere.h"
#include "gameobject_list.h"
#include "camera.h"
#include "helper.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "hit_result.h"

#include <iostream>

using std::make_shared;

gameobject_list random_scenes() {
    gameobject_list world;

    shared_ptr<lambertian> mat_ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    shared_ptr<sphere> shp_ground = make_shared<sphere>(point3(0, -1000, 0), 1000);
    world.add(make_shared<gameobject>(shp_ground, mat_ground));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double chosen_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> obj_mat;
                shared_ptr<sphere> obj_shape;

                if (chosen_mat < 0.8) {
                    color albedo = color::random() * color::random();

                    obj_mat = make_shared<lambertian>(albedo);
                    obj_shape = make_shared<sphere>(center, 0.2);

                    world.add(make_shared<gameobject>(obj_shape, obj_mat));
                } else if (chosen_mat < 0.95) {
                    color albedo = color::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);

                    obj_mat = make_shared<metal>(albedo, fuzz);
                    obj_shape = make_shared<sphere>(center, 0.2);
                    
                    world.add(make_shared<gameobject>(obj_shape, obj_mat));
                } else {
                    obj_mat = make_shared<dielectric>(1.5);
                    obj_shape = make_shared<sphere>(center, 0.2);
                    
                    world.add(make_shared<gameobject>(obj_shape, obj_mat));
                }
            }
        }
    }

    shared_ptr<material> mat1 = make_shared<dielectric>(1.5);
    shared_ptr<sphere> shp1 = make_shared<sphere>(point3(0, 1, 0), 1.0);
    world.add(make_shared<gameobject>(shp1, mat1));

    shared_ptr<material> mat2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    shared_ptr<sphere> shp2 = make_shared<sphere>(point3(-4, 1, 0), 1.0);
    world.add(make_shared<gameobject>(shp2, mat2));

    shared_ptr<material> mat3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
    shared_ptr<sphere> shp3 = make_shared<sphere>(point3(4, 1, 0), 1.0);
    world.add(make_shared<gameobject>(shp3, mat3));

    return world;
}

void write_color(std::ostream &out, color pixel_color, int sample_per_pixel) {
    double r = pixel_color.r();
    double g = pixel_color.g();
    double b = pixel_color.b();

    double scale = 1.0 / sample_per_pixel;

    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << "\n";
}

color ray_color(ray &r, gameobject_list world, int depth) {
    if (depth <= 0)
        return color(0, 0, 0);

    hit_result res = world.hit(r, 0.001, infinity);
    if (res.is_hit) {
        return res.attenuation * ray_color(res.scattered , world, depth - 1);
    }

    vector3 unit_vector = r.direction().unit_vector();
    double target = 0.5 * (unit_vector.y() + 1.0);

    return (1.0 - target) * color(1.0, 1.0, 1.0) + target * color(0.5, 0.7, 1.0);
}

int main(int argc, char const *argv[]) {  

    // ----- Image ----- //

    int depth = 40;
    int sample_per_pixel = 100;
    double aspect_ratio = 3.0 / 2.0;
    int image_width = 1200;
    int image_height = static_cast<int> (image_width / aspect_ratio);

    // ----- World ----- //
    gameobject_list world = random_scenes();

    // ----- Camera ----- //

    point3 lookfrom(13, 2, 3);
    point3 lookto(0, 0, 0);
    vector3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    camera cam = camera(lookfrom, lookto, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // ----- Render ----- //

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;

        for (int i = 0; i < image_width; ++i) {
            color pixel_color = color(0, 0, 0);

            for (int k = 0; k < sample_per_pixel; k++) {
                double u = double(i + random_double()) / (image_width - 1);
                double v = double(j + random_double()) / (image_height - 1);

                ray r = cam.get_ray(u, v);
                pixel_color = ray_color(r, world, depth) + pixel_color;
            }
            
            write_color(std::cout, pixel_color, sample_per_pixel);
        }
    }

    std::cerr << "\nDone!!\n";

    return 0;
}