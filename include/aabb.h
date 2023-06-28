#ifndef AABB_H
#define AABB_H

#include "ray.h"
#include "vec3.h"

class aabb {
public:
  aabb();
  aabb(const point3 &a, const point3 &b);

  point3 min() const;
  point3 max() const;

  bool hit(const ray &r, double t_min, double t_max) const;

public:
  point3 minimum;
  point3 maximum;
};

aabb surrounding_box(aabb &box0, aabb &box1);

#endif
