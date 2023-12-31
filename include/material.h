#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "ray.h"
#include "texture.h"
#include "utils.h"
#include "vec3.h"
#include <memory>

struct hit_record;

class material {
public:
  virtual colour emitted(double u, double v, const point3 &p) const {
    return colour(0, 0, 0);
  }

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       colour &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
public:
  lambertian(const colour &a) : albedo(make_shared<solid_colour>(a)) {}
  lambertian(shared_ptr<texture> a) : albedo(a) {}

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       colour &attenuation, ray &scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
  }

public:
  shared_ptr<texture> albedo;
};

class metal : public material {
public:
  metal(const colour &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       colour &attenuation, ray &scattered) const override {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered =
        ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

public:
  colour albedo;
  double fuzz;
};

class dielectric : public material {
public:
  dielectric(double index_of_refraction) : ir(index_of_refraction) {}

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       colour &attenuation, ray &scattered) const override {
    attenuation = colour(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    vec3 unit_direction = unit_vector(r_in.direction());

    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool total_internal_reflection = refraction_ratio * sin_theta > 1.0;

    vec3 direction;
    if (total_internal_reflection ||
        reflectance(cos_theta, refraction_ratio) > random_double()) {
      direction = reflect(unit_direction, rec.normal);
    } else {
      direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = ray(rec.p, direction, r_in.time());

    return true;
  }

public:
  double ir;

private:
  static double reflectance(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;

    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }
};

class diffuse_light : public material {
public:
  diffuse_light(shared_ptr<texture> a) : emit(a) {}
  diffuse_light(colour c) : emit(make_shared<solid_colour>(c)) {}

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       colour &attenuation, ray &scattered) const override {
    return false;
  }

  virtual colour emitted(double u, double v, const point3 &p) const override {
    return emit->value(u, v, p);
  }

public:
  shared_ptr<texture> emit;
};

class isotropic : public material {
public:
  isotropic(colour c) : albedo(make_shared<solid_colour>(c)) {}
  isotropic(shared_ptr<texture> a) : albedo(a) {}

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       colour &attenuation, ray &scattered) const {
    scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
  }

public:
  shared_ptr<texture> albedo;
};

#endif
