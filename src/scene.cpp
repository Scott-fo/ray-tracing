#include "scene.h"
#include "bvh.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "sphere.h"
#include "texture.h"
#include "utils.h"

hittable_list random_scene() {
  hittable_list world;

  auto checker = make_shared<checker_texture>(colour(0.2, 0.3, 0.1),
                                              colour(0.9, 0.9, 0.9));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000,
                                make_shared<lambertian>(checker)));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) { // Diffuse
          auto albedo = colour::random() * colour::random();
          sphere_material = make_shared<lambertian>(albedo);
          auto center2 = center + vec3(0, random_double(0, 0.5), 0);
          world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2,
                                               sphere_material));
        } else if (choose_mat < 0.95) { // Metal
          auto albedo = colour::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else { // Glass
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(colour(0.4, 0.2, 0.1));
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(colour(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  return hittable_list(make_shared<bvh_node>(world, 0.0, 1.0));
}

hittable_list two_spheres() {
  hittable_list objects;

  auto checker = make_shared<checker_texture>(colour(0.2, 0.3, 0.1),
                                              colour(0.9, 0.9, 0.9));

  objects.add(make_shared<sphere>(point3(0, -10, 0), 10,
                                  make_shared<lambertian>(checker)));
  objects.add(make_shared<sphere>(point3(0, 10, 0), 10,
                                  make_shared<lambertian>(checker)));

  return objects;
}