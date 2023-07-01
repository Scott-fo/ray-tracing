#include "bvh.h"
#include "camera.h"
#include "colour.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "texture.h"
#include "utils.h"
#include "vec3.h"

#include <iostream>
#include <memory>

colour ray_colour(const ray &r, const colour &background, const hittable &world,
                  int depth) {
  hit_record rec;

  if (depth <= 0) {
    return colour(0, 0, 0);
  }

  if (!world.hit(r, 0.001, infinity, rec)) {
    return background;
  }

  ray scattered;
  colour attenuation;
  colour emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

  if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
    return emitted;
  }

  return emitted +
         attenuation * ray_colour(scattered, background, world, depth - 1);
}

int main() {
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int samples_per_pixel = 100;
  const int max_depth = 50;

  hittable_list world;
  point3 lookfrom;
  point3 lookat;
  auto vfov = 20.0;
  auto aperture = 0.0;
  colour background(0.70, 0.80, 1.00);

  switch (8) {
  case 1:
    world = random_scene();
    lookfrom = point3(13, 2, 3);
    lookat = point3(0, 0, 0);
    aperture = 0.1;
    break;

  case 2:
    world = two_spheres();
    lookfrom = point3(13, 2, 3);
    lookat = point3(0, 0, 0);
    break;

  case 3:
    world = two_perlin_spheres();
    lookfrom = point3(13, 2, 3);
    lookat = point3(0, 0, 0);
    break;

  case 4:
    world = earth();
    lookfrom = point3(13, 2, 3);
    lookat = point3(0, 0, 0);
    break;

  case 5:
    world = simple_light();
    background = colour(0, 0, 0);
    lookfrom = point3(26, 3, 6);
    lookat = point3(0, 2, 0);
    break;

  case 6:
    world = cornell_box();
    aspect_ratio = 1.0;
    image_width = 600;
    samples_per_pixel = 10;
    background = colour(0, 0, 0);
    lookfrom = point3(278, 278, -800);
    lookat = point3(278, 278, 0);
    vfov = 40.0;
    break;

  case 7:
    world = cornell_smoke();
    aspect_ratio = 1.0;
    image_width = 600;
    samples_per_pixel = 10;
    background = colour(0, 0, 0);
    lookfrom = point3(278, 278, -800);
    lookat = point3(278, 278, 0);
    vfov = 40.0;
    break;

  case 8:
    world = final_scene();
    aspect_ratio = 1.0;
    image_width = 800;
    samples_per_pixel = 10;
    background = colour(0, 0, 0);
    lookfrom = point3(478, 278, -600);
    lookat = point3(278, 278, 0);
    vfov = 40.0;
    break;

  default:
    world = two_spheres();
    lookfrom = point3(13, 2, 3);
    lookat = point3(0, 0, 0);
    break;
  }

  int image_height = static_cast<int>(image_width / aspect_ratio);

  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;

  camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus,
             0.0, 1.0);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanline remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      colour pixel_colour(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = double(i + random_double()) / (image_width - 1);
        auto v = double(j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_colour += ray_colour(r, background, world, max_depth);
      }

      write_colour(std::cout, pixel_colour, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
}
