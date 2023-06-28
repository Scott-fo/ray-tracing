#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"
#include <memory>

class sphere : public hittable {
public:
  sphere();
  sphere(point3 cen, double r, shared_ptr<material> m);

  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;

  virtual bool bounding_box(double time0, double time1,
                            aabb &output_box) const override;

  virtual ~sphere();

public:
  point3 center;
  double radius;
  shared_ptr<material> mat_ptr;
};

#endif
