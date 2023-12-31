#ifndef HITTABLE_H
#define HITTABLE_H

#include "aabb.h"
#include "ray.h"
#include "vec3.h"
#include <memory>

class material;

struct hit_record {
  point3 p;
  vec3 normal;
  shared_ptr<material> mat_ptr;
  double t, u, v;
  bool front_face;

  inline void set_face_normal(const ray &r, const vec3 &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const = 0;
  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const = 0;
};

class translate : public hittable {
public:
  translate(shared_ptr<hittable> p, const vec3 &displacement);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

public:
  shared_ptr<hittable> ptr;
  vec3 offset;
};

class rotate_y : public hittable {
public:
  rotate_y(shared_ptr<hittable> p, double angle);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

public:
  shared_ptr<hittable> ptr;
  double sin_theta, cos_theta;
  bool hasbox;
  aabb bbox;
};

#endif
