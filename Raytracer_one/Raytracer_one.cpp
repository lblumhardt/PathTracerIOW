#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>
#include <time.h>

hittable_list random_scene() {
	/* Initial demo
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
		
	*/

	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(35.0/255.0, 59.0/255.0, 43.0/255.0));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;
				auto albedo = color::random() * color::random();
				sphere_material = make_shared<lambertian>(albedo);

				if (choose_mat < 0.8) {
					// diffuse
					//auto albedo = color::random() * color::random();
					//sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					//sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					//sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	auto material2 = make_shared<lambertian>(color(0, 0.45, 1.0));
	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);
	auto material4 = make_shared <metal>(color(1.0, 125.0 / 255.0, 216.0 / 255.0), 0.9);

	auto metalmaterial_nofuzz = make_shared<metal>(color(117.0 / 255.0, 0.0, 207.0 / 255.0), 0.0);
	auto metalmaterial_medfuzz = make_shared<metal>(color(117.0 / 255.0, 0.0, 207.0 / 255.0), 0.2);
	auto metalmaterial_maxfuzz = make_shared<metal>(color(117.0 / 255.0, 0.0, 207.0 / 255.0), 1.0);


	world.add(make_shared<sphere>(point3(0, 1, 2), 1.0, metalmaterial_medfuzz));
	world.add(make_shared<sphere>(point3(-2, 1, 2), 1.0, metalmaterial_nofuzz));
	world.add(make_shared<sphere>(point3(2, 1, 2), 1.0, metalmaterial_maxfuzz));

	return world;
}

color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;
	color sky = color(0.1, 0.1, 0.9);
	//color sky = color(0.5, 0.7, 1.0);

	// ray bounce limit (no more light is gathered)
	if (depth <= 0)
		return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec)) {
		//point3 target = rec.p + random_in_hemisphere(rec.normal);
		//point3 target = rec.p + rec.normal + random_in_unit_sphere();
		//point3 target = rec.p + rec.normal + random_unit_vector();
		//return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);

		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		return color(0, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*color(1.0, 1.0, 1.0) + t*sky;
}

int main() {
	/* initialize random seed: */
	srand(time(NULL));

	// Image
	/*
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 50;
	*/
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 50;

	// World
	//hittable_list world;
	//auto R = cos(pi / 4);
	auto world = random_scene();

	
	// Camera
	/*
	point3 lookfrom(13,2,3);
	point3 lookat(0,0,0);
	vec3 vup(0,1,0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	*/

	point3 lookfrom(0,2.3,12);
	point3 lookat(0, 0.2, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.1;
	auto aperture = 0.1;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	//camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 20, aspect_ratio);
	//camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90, aspect_ratio);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {

		//progress tracker
		std::cerr << "\rScanlines remaining: " << j << std::flush;

		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
