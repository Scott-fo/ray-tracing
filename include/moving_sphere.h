#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "hittable.h"
#include "material.h"
#include "utils.h"
#include "vec3.h"
#include <memory>

class moving_sphere : public hittable {
public:
  moving_sphere();
  moving_sphere(point3 cen0, point3 cen1, double _time0, double _time1,
                double r, shared_ptr<material> m);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double _time0, double _time1,
                            aabb &output_box) const override;

  virtual ~moving_sphere();

  point3 center(double time) const;

public:
  point3 center0, center1;
  double time0, time1;
  double radius;
  shared_ptr<material> mat_ptr;
};

#endif
